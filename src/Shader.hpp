#pragma once

#include "OpenGL.hpp"
#include <fstream>
#include <sstream>
#include <unordered_map>

class Shader {
  private:
    string currShader;
    unsigned int program;
    unordered_map<string, int> shaderType;
    unordered_map<string, unsigned int> shader;
    unordered_map<string, unsigned int> uniformLocation;

    unsigned int compile(unsigned int type, const string &shader);
    unsigned int create(vector<unsigned int> &id);

  public:
    Shader();
    ~Shader();
    string getCurrShader();
    unsigned int use(const string &name);
    unsigned int getProgram();
    void setFloat(const string &name, const string &uniform, unsigned int type,
                  float *data);
    void setFloat(const string &name, const string &uniform, unsigned int type,
                  unsigned int count, float *data);
    void setFloat(const string &name, const string &uniform, unsigned int type,
                  vector<float> data);
    void setFloat(const string &name, const string &uniform, unsigned int type,
                  unsigned int count, vector<float> data);
    void setInt(const string &name, const string &uniform, unsigned int type,
                int *data);
    void setInt(const string &name, const string &uniform, unsigned int type,
                unsigned int count, int *data);
    void setInt(const string &name, const string &uniform, unsigned int type,
                vector<int> data);
    void setInt(const string &name, const string &uniform, unsigned int type,
                unsigned int count, vector<int> data);
    void load(unordered_map<string, unsigned int> &shaderFiles,
              const string &name);
    void load(const string &filePath, const string &name);
};
