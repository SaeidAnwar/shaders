#include "IndexBuffer.hpp"
#include "OpenGL.hpp"

IndexBuffer::IndexBuffer() {}

IndexBuffer::IndexBuffer(const unsigned int *buffer, unsigned int count) {
    GLCall(glGenBuffers(1, &m_rendererId));
    bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int),
                        buffer, GL_STATIC_DRAW));
    unBind();
}

IndexBuffer::~IndexBuffer() { GLCall(glDeleteBuffers(1, &m_rendererId)); }

void IndexBuffer::init(const unsigned int *buffer, unsigned int count) {
    GLCall(glGenBuffers(1, &m_rendererId));
    bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int),
                        buffer, GL_STATIC_DRAW));
    unBind();
}

void IndexBuffer::bind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
}

void IndexBuffer::unBind() { GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); }
