#include "VertexArray.hpp"
#include "OpenGL.hpp"

VertexArray::VertexArray() { GLCall(glGenVertexArrays(1, &m_rendererId)); }

VertexArray::~VertexArray() { GLCall(glDeleteVertexArrays(1, &m_rendererId)); }

void VertexArray::bind() { GLCall(glBindVertexArray(m_rendererId)); }

void VertexArray::unBind() { GLCall(glBindVertexArray(0)); }
