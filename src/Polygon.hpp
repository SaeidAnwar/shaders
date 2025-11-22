#pragma once

#include "Mesh.hpp"

class Polygon {
  protected:
    vec2f position;
    Mesh mesh;

  public:
    virtual ~Polygon() {};
    virtual void init(vec2f dimension) = 0;
    virtual void init(vec2f dimension, vec2f position) = 0;
    virtual Mesh &getMesh();
    virtual void draw();
};

class Rectangle : public Polygon {
  protected:
    vec2f dimension;

  public:
    Rectangle();
    Rectangle(vec2f dimension);
    Rectangle(vec2f dimension, vec2f position);

    void init(vec2f dimension, vec2f position);
    void init(vec2f dimension);
};
