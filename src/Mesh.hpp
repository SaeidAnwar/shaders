#pragma once

#include "OpenGL.hpp"

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Structs.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

class Mesh {
  private:
    VertexArray va;
    VertexBuffer vb;
    IndexBuffer ib;
    string shaderName;
    unordered_map<string, unsigned int> uniformMap;
    inline static Shader *shader = nullptr;

  public:
    Mesh() {};
    Mesh(vector<float> &vertices, vector<unsigned int> &indices);
    Mesh(vector<float> &vertices, vector<unsigned int> &indices,
         const string &shaderName);
    Mesh(vector<Vertex> &vertices, vector<unsigned int> &indices);
    Mesh(vector<Vertex> &vertices, vector<unsigned int> &indices,
         const string &shaderName);

    static void setShader(Shader *shader);

    void useShader(const string &shaderName);
    void setFloat(const string &uniformName, unsigned int type, float *data);
    void setFloat(const string &uniformName, unsigned int type,
                  unsigned int count, float *data);
    void setFloat(const string &uniformName, unsigned int type,
                  vector<float> data);
    void setFloat(const string &uniformName, unsigned int type,
                  unsigned int count, vector<float> data);
    void setInt(const string &uniformName, unsigned int type, int *data);
    void setInt(const string &uniformName, unsigned int type,
                unsigned int count, int *data);
    void setInt(const string &uniformName, unsigned int type, vector<int> data);
    void setInt(const string &uniformName, unsigned int type,
                unsigned int count, vector<int> data);
    void init(vector<float> &vertices, vector<unsigned int> &indices);
    void init(vector<float> &vertices, vector<unsigned int> &indices,
              const string &shaderName);
    void init(vector<Vertex> &vertices, vector<unsigned int> &indices);
    void init(vector<Vertex> &vertices, vector<unsigned int> &indices,
              const string &shaderName);
    void draw();
    void draw(const string &shader);
};
