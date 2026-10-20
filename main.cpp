#include <SDL2/SDL.h>
#include <SDL_video.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

#include "src/Mesh.hpp"
#include "src/OpenGL.hpp"
#include "src/Shader.hpp"

const bool FULLSCREEN = false;
const int width = 512, height = 512;
const string SHADER_FILE = "res/shader/ver-frag.glsl";

// Check edited GLSL before calling Shader::load, whose current error path exits.
bool validateShaderFile(const string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Could not open shader file: " << filepath << std::endl;
    return false;
  }

  vector<GLuint> stages;
  auto deleteStages = [&]() {
    for (GLuint stage : stages) glDeleteShader(stage);
    stages.clear();
  };
  auto compileStage = [&](GLenum type, const string& source) {
    GLuint stage = glCreateShader(type);
    const char* text = source.c_str();
    glShaderSource(stage, 1, &text, nullptr);
    glCompileShader(stage);
    GLint compiled = GL_FALSE;
    glGetShaderiv(stage, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
      GLint length = 0;
      glGetShaderiv(stage, GL_INFO_LOG_LENGTH, &length);
      vector<char> log(std::max(length, 1));
      glGetShaderInfoLog(stage, length, nullptr, log.data());
      std::cerr << "Shader compile error:\n" << log.data() << std::endl;
      glDeleteShader(stage);
      return false;
    }
    stages.push_back(stage);
    return true;
  };

  GLenum currentType = 0;
  string source;
  string line;
  while (std::getline(file, line)) {
    if (line.find("#shader") != string::npos) {
      if (currentType && !compileStage(currentType, source)) {
        deleteStages();
        return false;
      }
      source.clear();
      std::stringstream header(line);
      string marker, stageName;
      header >> marker >> stageName;
      if (stageName == "vertex")
        currentType = GL_VERTEX_SHADER;
      else if (stageName == "fragment")
        currentType = GL_FRAGMENT_SHADER;
      else {
        std::cerr << "Unknown shader stage: " << stageName << std::endl;
        deleteStages();
        return false;
      }
    } else if (currentType) {
      source += line + '\n';
    }
  }

  if (!currentType || !compileStage(currentType, source) || stages.size() != 2) {
    std::cerr << "Expected one vertex and one fragment shader stage."
              << std::endl;
    deleteStages();
    return false;
  }

  GLuint program = glCreateProgram();
  for (GLuint stage : stages) glAttachShader(program, stage);
  glLinkProgram(program);
  GLint linked = GL_FALSE;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);
  if (!linked) {
    GLint length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    vector<char> log(std::max(length, 1));
    glGetProgramInfoLog(program, length, nullptr, log.data());
    std::cerr << "Shader link error:\n" << log.data() << std::endl;
  }
  glDeleteProgram(program);
  deleteStages();
  return linked == GL_TRUE;
}

bool init(SDL_Window** window, SDL_GLContext* glContext) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  if (FULLSCREEN) {
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int screenWidth = DM.w;
    int screenHeight = DM.h;
    *window =
        SDL_CreateWindow("Borderless Fullscreen Window", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_BORDERLESS);
  } else {
    *window = SDL_CreateWindow("SDL2 + OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  }

  if (!*window) {
    std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return false;
  }

  *glContext = SDL_GL_CreateContext(*window);
  if (!*glContext) {
    std::cerr << "OpenGL Context Creation Failed: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(*window);
    SDL_Quit();
    return false;
  }

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    SDL_GL_DeleteContext(*glContext);
    SDL_DestroyWindow(*window);
    SDL_Quit();
    return false;
  }

  cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
  cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));
  return true;
}

int main() {
  SDL_Window* window;
  SDL_GLContext glContext;
  if (!init(&window, &glContext)) return -1;

  Shader shader;
  bool shaderReady = validateShaderFile(SHADER_FILE);
  if (shaderReady) shader.load(SHADER_FILE, "1");
  Mesh::setShader(&shader);

  vector<float> gridVertices = {-1, -1, -1, 1, 1, 1, 1, -1};
  vector<unsigned int> gridIndices = {0, 1, 2, 2, 3, 0};
  Mesh grid(gridVertices, gridIndices, "1");

  std::error_code fileError;
  auto shaderWriteTime = fs::last_write_time(SHADER_FILE, fileError);
  if (fileError) {
    std::cerr << "Could not watch shader file: " << SHADER_FILE << std::endl;
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }
  auto lastShaderCheck = std::chrono::steady_clock::now();

  bool running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) running = false;
    }

    // Poll at a modest rate so editors can finish writing the saved file.
    auto now = std::chrono::steady_clock::now();
    if (now - lastShaderCheck >= std::chrono::milliseconds(200)) {
      lastShaderCheck = now;
      auto changedAt = fs::last_write_time(SHADER_FILE, fileError);
      if (!fileError && changedAt != shaderWriteTime) {
        shaderWriteTime = changedAt;
        shaderReady = validateShaderFile(SHADER_FILE);
        if (shaderReady) {
          shader.load(SHADER_FILE, "1");
          std::cout << "Reloaded shader: " << SHADER_FILE << std::endl;
        } else {
          std::cerr << "Showing red screen until the shader compiles."
                    << std::endl;
        }
      }
    }

    // SDL's drawable size can change when Hyprland tiles or resizes the window.
    int drawableWidth = 0;
    int drawableHeight = 0;
    SDL_GL_GetDrawableSize(window, &drawableWidth, &drawableHeight);
    GLCall(glViewport(0, 0, drawableWidth, drawableHeight));
    if (shaderReady) {
      grid.setFloat("u_res", 2,
                    {static_cast<float>(drawableWidth), static_cast<float>(drawableHeight)});
    }

    GLCall(glClearColor(shaderReady ? 0.0f : 1.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    if (shaderReady) grid.draw();

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
