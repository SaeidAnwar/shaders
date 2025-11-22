#pragma once

class IndexBuffer {
  private:
    unsigned int m_rendererId;

  public:
    IndexBuffer();
    IndexBuffer(const unsigned int *buffer, unsigned int indexCnt);
    ~IndexBuffer();

    void init(const unsigned int *buffer, unsigned int indexCnt);
    void bind();
    void unBind();
};
