#include "src/OpenGL.hpp"
#include <SDL2/SDL.h>
#include <iostream>

#include "src/Mesh.hpp"
#include "src/Shader.hpp"

const bool FULLSCREEN = false;
const int width = 512, height = 512;

bool init(SDL_Window **window, SDL_GLContext *glContext) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    if (FULLSCREEN) {
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        int screenWidth = DM.w;
        int screenHeight = DM.h;
        *window =
            SDL_CreateWindow("Borderless Fullscreen Window",
                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             screenWidth, screenHeight, SDL_WINDOW_BORDERLESS);
    } else {
        *window = SDL_CreateWindow("SDL2 + OpenGL", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, width, height,
                                   SDL_WINDOW_OPENGL);
    }

    if (!*window) {
        std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    *glContext = SDL_GL_CreateContext(*window);
    if (!*glContext) {
        std::cerr << "OpenGL Context Creation Failed: " << SDL_GetError()
                  << std::endl;
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
    cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
         << endl;

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));
    return true;
}

int main() {
    SDL_Window *window;
    SDL_GLContext glContext;
    if (!init(&window, &glContext))
        return -1;

    Shader shader;

    unordered_map<string, unsigned int> shaderFiles1;
    shaderFiles1["res/shader/vertex.glsl"] = GL_VERTEX_SHADER;
    shaderFiles1["res/shader/fragment.glsl"] = GL_FRAGMENT_SHADER;
    shader.load(shaderFiles1, "0");

    shader.load("res/shader/ver-frag.glsl", "1");
    shader.setFloat("1", "u_res", 2, {width, height});

    Mesh::setShader(&shader);

    vector<float> gridVertices = {-1, -1, -1, 1, 1, 1, 1, -1};
    vector<unsigned int> gridIndices = {0, 1, 2, 2, 3, 0};
    Mesh grid(gridVertices, gridIndices, "0");
    grid.setFloat("u_res", 2, {width, height});
    grid.useShader("1");

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        int mposx;
        int mposy;
        SDL_GetMouseState(&mposx, &mposy);

        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));

        grid.draw();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
