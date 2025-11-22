#include "Shader.hpp"

Shader::Shader() {
    shaderType["vertex"] = GL_VERTEX_SHADER;
    shaderType["fragment"] = GL_FRAGMENT_SHADER;
}

Shader::~Shader() {
    for (auto program : shader) {
        GLCall(glDeleteProgram(program.second));
    }
}

void Shader::load(const string &filepath, const string &name) {
    vector<unsigned int> ids;
    fstream file(filepath);
    string buffer = "";
    string line = "";
    stringstream ss;
    string type = "";
    while (getline(file, line)) {
        if (line.find("#shader") != string::npos) {
            if (!buffer.empty() && !type.empty()) {
                ids.push_back(compile(shaderType[type], buffer));
                type.clear();
            }
            buffer.clear();
            ss.clear();
            ss.str(line);
            ss >> type;
            ss >> type;
        } else {
            buffer.append(line);
            buffer.append("\n");
        }
    }
    ids.push_back(compile(shaderType[type], buffer));
    file.close();
    unsigned int program = create(ids);
    shader[name] = program;
}

void Shader::load(unordered_map<string, unsigned int> &shaderFiles,
                  const string &name) {
    vector<unsigned int> ids;
    for (auto &shaderFile : shaderFiles) {
        fstream file(shaderFile.first);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << shaderFile.first << endl;
            continue;
        }
        stringstream buffer;
        buffer << file.rdbuf();
        ids.push_back(compile(shaderFile.second, buffer.str()));
        file.close();
    }
    unsigned int program = create(ids);
    shader[name] = program;
}

unsigned int Shader::compile(unsigned int type, const string &source) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (!result) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        cout << "Failed to compile shader" << ": " << source << endl;
        cout << message << endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::create(vector<unsigned int> &ids) {
    unsigned int program = glCreateProgram();
    for (auto &id : ids) {
        GLCall(glAttachShader(program, id));
    }
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));
    for (auto &id : ids) {
        GLCall(glDeleteShader(id));
    }

    return program;
}

unsigned int Shader::use(const string &name) {
    if (shader.find(name) == shader.end()) {
        cerr << "shader is not loaded!, please load the shader first" << endl;
        return -1;
    }
    program = shader[name];
    GLCall(glUseProgram(shader[name]));
    this->currShader = name;
    return program;
}

void Shader::setFloat(const string &name, const string &uniform,
                      unsigned int type, float *data) {
    if (use(name) == -1) {
        return;
    }

    string key = name + uniform;
    if (!uniformLocation.contains(key)) {
        GLCall(int loc = glGetUniformLocation(getProgram(), uniform.c_str()));
        uniformLocation[key] = loc;
    }

    switch (type) {
    case 1:
        GLCall(glUniform1fv(uniformLocation[key], 1, (GLfloat *)data));
        break;

    case 2:
        GLCall(glUniform2fv(uniformLocation[key], 1, (GLfloat *)data));
        break;

    case 3:
        GLCall(glUniform3fv(uniformLocation[key], 1, (GLfloat *)data));
        break;

    case 4:
        GLCall(glUniform4fv(uniformLocation[key], 1, (GLfloat *)data));
        break;
    }
}

void Shader::setFloat(const string &name, const string &uniform,
                      unsigned int type, unsigned int cnt, float *data) {
    if (use(name) == -1) {
        return;
    }

    string key = name + uniform;
    if (!uniformLocation.contains(key)) {
        GLCall(int loc = glGetUniformLocation(getProgram(), uniform.c_str()));
        uniformLocation[key] = loc;
    }

    switch (type) {
    case 1:
        GLCall(glUniform1fv(uniformLocation[key], cnt, (GLfloat *)data));
        break;

    case 2:
        GLCall(glUniform2fv(uniformLocation[key], cnt, (GLfloat *)data));
        break;

    case 3:
        GLCall(glUniform3fv(uniformLocation[key], cnt, (GLfloat *)data));
        break;

    case 4:
        GLCall(glUniform4fv(uniformLocation[key], cnt, (GLfloat *)data));
        break;
    }
}

void Shader::setFloat(const string &name, const string &uniform,
                      unsigned int type, vector<float> data) {
    if (use(name) == -1) {
        return;
    }

    string key = name + uniform;
    if (!uniformLocation.contains(key)) {
        GLCall(int loc = glGetUniformLocation(getProgram(), uniform.c_str()));
        uniformLocation[key] = loc;
    }

    switch (type) {
    case 1:
        GLCall(glUniform1fv(uniformLocation[key], 1, (GLfloat *)data.data()));
        break;

    case 2:
        GLCall(glUniform2fv(uniformLocation[key], 1, (GLfloat *)data.data()));
        break;

    case 3:
        GLCall(glUniform3fv(uniformLocation[key], 1, (GLfloat *)data.data()));
        break;

    case 4:
        GLCall(glUniform4fv(uniformLocation[key], 1, (GLfloat *)data.data()));
        break;
    }
}

void Shader::setFloat(const string &name, const string &uniform,
                      unsigned int type, unsigned int cnt, vector<float> data) {
    if (use(name) == -1) {
        return;
    }

    string key = name + uniform;
    if (!uniformLocation.contains(key)) {
        GLCall(int loc = glGetUniformLocation(getProgram(), uniform.c_str()));
        uniformLocation[key] = loc;
    }

    switch (type) {
    case 1:
        GLCall(glUniform1fv(uniformLocation[key], cnt, (GLfloat *)data.data()));
        break;

    case 2:
        GLCall(glUniform2fv(uniformLocation[key], cnt, (GLfloat *)data.data()));
        break;

    case 3:
        GLCall(glUniform3fv(uniformLocation[key], cnt, (GLfloat *)data.data()));
        break;

    case 4:
        GLCall(glUniform4fv(uniformLocation[key], cnt, (GLfloat *)data.data()));
        break;
    }
}

void Shader::setInt(const string &name, const string &uniform,
                    unsigned int type, int *data) {
    if (use(name) == -1) {
        return;
    }

    string key = name + uniform;
    if (!uniformLocation.contains(key)) {
        GLCall(int loc = glGetUniformLocation(getProgram(), uniform.c_str()));
        uniformLocation[key] = loc;
    }

    switch (type) {
    case 1:
        GLCall(glUniform1iv(uniformLocation[key], 1, (GLint *)data));
        break;

    case 2:
        GLCall(glUniform2iv(uniformLocation[key], 1, (GLint *)data));
        break;

    case 3:
        GLCall(glUniform3iv(uniformLocation[key], 1, (GLint *)data));
        break;

    case 4:
        GLCall(glUniform4iv(uniformLocation[key], 1, (GLint *)data));
        break;
    }
}

void Shader::setInt(const string &name, const string &uniform,
                    unsigned int type, unsigned int cnt, int *data) {
    if (use(name) == -1) {
        return;
    }

    string key = name + uniform;
    if (!uniformLocation.contains(key)) {
        GLCall(int loc = glGetUniformLocation(getProgram(), uniform.c_str()));
        uniformLocation[key] = loc;
    }

    switch (type) {
    case 1:
        GLCall(glUniform1iv(uniformLocation[key], cnt, (GLint *)data));
        break;

    case 2:
        GLCall(glUniform2iv(uniformLocation[key], cnt, (GLint *)data));
        break;

    case 3:
        GLCall(glUniform3iv(uniformLocation[key], cnt, (GLint *)data));
        break;

    case 4:
        GLCall(glUniform4iv(uniformLocation[key], cnt, (GLint *)data));
        break;
    }
}

void Shader::setInt(const string &name, const string &uniform,
                    unsigned int type, vector<int> data) {
    if (use(name) == -1) {
        return;
    }

    string key = name + uniform;
    if (!uniformLocation.contains(key)) {
        GLCall(int loc = glGetUniformLocation(getProgram(), uniform.c_str()));
        uniformLocation[key] = loc;
    }

    switch (type) {
    case 1:
        GLCall(glUniform1iv(uniformLocation[key], 1, (GLint *)data.data()));
        break;

    case 2:
        GLCall(glUniform2iv(uniformLocation[key], 1, (GLint *)data.data()));
        break;

    case 3:
        GLCall(glUniform3iv(uniformLocation[key], 1, (GLint *)data.data()));
        break;

    case 4:
        GLCall(glUniform4iv(uniformLocation[key], 1, (GLint *)data.data()));
        break;
    }
}

void Shader::setInt(const string &name, const string &uniform,
                    unsigned int type, unsigned int cnt, vector<int> data) {
    if (use(name) == -1) {
        return;
    }

    string key = name + uniform;
    if (!uniformLocation.contains(key)) {
        GLCall(int loc = glGetUniformLocation(getProgram(), uniform.c_str()));
        uniformLocation[key] = loc;
    }

    switch (type) {
    case 1:
        GLCall(glUniform1iv(uniformLocation[key], cnt, (GLint *)data.data()));
        break;

    case 2:
        GLCall(glUniform2iv(uniformLocation[key], cnt, (GLint *)data.data()));
        break;

    case 3:
        GLCall(glUniform3iv(uniformLocation[key], cnt, (GLint *)data.data()));
        break;

    case 4:
        GLCall(glUniform4iv(uniformLocation[key], cnt, (GLint *)data.data()));
        break;
    }
}

unsigned int Shader::getProgram() { return program; }

string Shader::getCurrShader() { return currShader; }
