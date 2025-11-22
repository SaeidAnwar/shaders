#pragma once

class VertexArray {
  private:
    unsigned int m_rendererId;

  public:
    VertexArray();
    ~VertexArray();

    void bind();
    void unBind();
};
