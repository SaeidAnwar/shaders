#include "Mesh.hpp"

Mesh::Mesh(vector<float> &vertices, vector<unsigned int> &indices) {
    Mesh::init(vertices, indices);
}

Mesh::Mesh(vector<float> &vertices, vector<unsigned int> &indices,
           const string &shaderName) {
    this->shaderName = shaderName;
    Mesh::init(vertices, indices);
}

Mesh::Mesh(vector<Vertex> &vertices, vector<unsigned int> &indices) {
    Mesh::init(vertices, indices);
}

Mesh::Mesh(vector<Vertex> &vertices, vector<unsigned int> &indices,
           const string &shaderName) {
    this->shaderName = shaderName;
    Mesh::init(vertices, indices);
}

void Mesh::setShader(Shader *shader) { Mesh::shader = shader; }

void Mesh::useShader(const string &shaderName) {
    this->shaderName = shaderName;
}

void Mesh::setFloat(const string &uniform, unsigned int type, float *data) {
    shader->setFloat(shaderName, uniform, type, data);
}

void Mesh::setFloat(const string &uniform, unsigned int type, unsigned int cnt,
                    float *data) {
    shader->setFloat(shaderName, uniform, type, cnt, data);
}

void Mesh::setFloat(const string &uniform, unsigned int type,
                    vector<float> data) {
    shader->setFloat(shaderName, uniform, type, data);
}

void Mesh::setFloat(const string &uniform, unsigned int type, unsigned int cnt,
                    vector<float> data) {
    shader->setFloat(shaderName, uniform, type, cnt, data);
}

void Mesh::setInt(const string &uniform, unsigned int type, int *data) {
    shader->setInt(shaderName, uniform, type, data);
}

void Mesh::setInt(const string &uniform, unsigned int type, unsigned int cnt,
                  int *data) {
    shader->setInt(shaderName, uniform, type, cnt, data);
}

void Mesh::setInt(const string &uniform, unsigned int type, vector<int> data) {
    shader->setInt(shaderName, uniform, type, data);
}

void Mesh::setInt(const string &uniform, unsigned int type, unsigned int cnt,
                  vector<int> data) {
    shader->setInt(shaderName, uniform, type, cnt, data);
}

void Mesh::init(vector<float> &vertices, vector<unsigned int> &indices) {
    vb.init(vertices.data(), vertices.size() * 4);
    ib.init(indices.data(), indices.size());
    va.bind();
    vb.bind();
    ib.bind();
    GLCall(
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
    GLCall(glEnableVertexAttribArray(0));
    va.unBind();
}

void Mesh::init(vector<float> &vertices, vector<unsigned int> &indices,
                const string &shaderName) {
    this->shaderName = shaderName;
    Mesh::init(vertices, indices);
}

void Mesh::init(vector<Vertex> &vertices, vector<unsigned int> &indices) {
    vb.init(vertices.data(), vertices.size() * sizeof(Vertex));
    ib.init(indices.data(), indices.size());
    va.bind();
    vb.bind();
    ib.bind();
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                 (void *)offsetof(Vertex, pos)));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                 (void *)offsetof(Vertex, uv)));
    GLCall(glEnableVertexAttribArray(1));
    va.unBind();
}

void Mesh::init(vector<Vertex> &vertices, vector<unsigned int> &indices,
                const string &shaderName) {
    this->shaderName = shaderName;
    Mesh::init(vertices, indices);
}

void Mesh::draw() {
    if (shader != nullptr && !shaderName.empty()) {
        shader->use(shaderName);
    }
    va.bind();
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    va.unBind();
}

void Mesh::draw(const string &shaderName) {
    if (shader != nullptr) {
        shader->use(shaderName);
    }
    va.bind();
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    va.unBind();
}
