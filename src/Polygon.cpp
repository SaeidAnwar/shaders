#include "Polygon.hpp"

Mesh &Polygon::getMesh() { return mesh; }

void Polygon::draw() { mesh.draw(); }

Rectangle::Rectangle() {}

Rectangle::Rectangle(vec2f dimension) { init(dimension); }

Rectangle::Rectangle(vec2f dimension, vec2f position) {
    init(dimension, position);
}

void Rectangle::init(vec2f dimension) {
    vec2f bl = (dimension / 2.0f) * -1.0f;
    vec2f tr = (dimension / 2.0f);
    vec2f tl = vec2f(-dimension.x / 2, dimension.y / 2);
    vec2f br = vec2f(dimension.x / 2, -dimension.y / 2);

    vector<Vertex> vertices = {
        Vertex(bl, vec2f(0.0, 0.0)),
        Vertex(tl, vec2f(0.0, 1.0)),
        Vertex(tr, vec2f(1.0, 1.0)),
        Vertex(br, vec2f(1.0, 0.0)),
    };

    vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};

    mesh.init(vertices, indices);
}

void Rectangle::init(vec2f dimension, vec2f position) {
    vec2f bl = position - (dimension / 2);
    vec2f tr = position + (dimension / 2);
    vec2f tl =
        vec2f(position.x - dimension.x / 2, position.y + dimension.y / 2);
    vec2f br =
        vec2f(position.x + dimension.x / 2, position.y - dimension.y / 2);

    vector<Vertex> vertices = {
        Vertex(bl, vec2f(0.0, 0.0)),
        Vertex(tl, vec2f(0.0, 1.0)),
        Vertex(tr, vec2f(1.0, 1.0)),
        Vertex(br, vec2f(1.0, 0.0)),
    };

    vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};

    mesh.init(vertices, indices);
}
