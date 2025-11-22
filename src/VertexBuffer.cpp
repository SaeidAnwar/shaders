#include "VertexBuffer.hpp"
#include "OpenGL.hpp"

VertexBuffer::VertexBuffer() {}

VertexBuffer::VertexBuffer(const void *buffer, unsigned int size) {
    GLCall(glGenBuffers(1, &m_rendererId));
    bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW));
    unBind();
}

VertexBuffer::~VertexBuffer() { GLCall(glDeleteBuffers(1, &m_rendererId)); }

void VertexBuffer::init(const void *buffer, unsigned int size) {
    GLCall(glGenBuffers(1, &m_rendererId));
    bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW));
    unBind();
}

void VertexBuffer::bind() {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
}

void VertexBuffer::unBind() { GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
