#pragma once

class VertexBuffer {
  private:
    unsigned int m_rendererId;

  public:
    VertexBuffer();
    VertexBuffer(const void *buffer, unsigned int size);
    ~VertexBuffer();

    void init(const void *buffer, unsigned int size);
    void bind();
    void unBind();
};
