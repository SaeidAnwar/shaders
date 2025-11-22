#pragma once

struct vec2f {
    float x, y;

    vec2f operator+(const vec2f &other) {
        return vec2f(x + other.x, y + other.y);
    }
    vec2f operator-(const vec2f &other) {
        return vec2f(x - other.x, y - other.y);
    }
    vec2f operator*(const vec2f &other) {
        return vec2f(x * other.x, y * other.y);
    }
    vec2f operator/(const vec2f &other) {
        return vec2f(x / other.x, y / other.y);
    }
    vec2f operator*(float t) { return vec2f(x * t, y * t); }
    vec2f operator/(float t) { return vec2f(x / t, y / t); }
};

struct vec3f {
    float x, y, z;

    vec3f operator+(const vec3f &other) {
        return vec3f(x + other.x, y + other.y, z + other.z);
    }
    vec3f operator-(const vec3f &other) {
        return vec3f(x - other.x, y - other.y, z - other.z);
    }
    vec3f operator*(const vec3f &other) {
        return vec3f(x * other.x, y * other.y, z * other.z);
    }
    vec3f operator/(const vec3f &other) {
        return vec3f(x / other.x, y / other.y, z / other.z);
    }
    vec3f operator*(float t) { return vec3f(x * t, y * t, z * t); }
    vec3f operator/(float t) { return vec3f(x / t, y / t, z / t); }
};

struct vec4f {
    float x, y, z, w;

    vec4f operator+(const vec4f &other) {
        return vec4f(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    vec4f operator-(const vec4f &other) {
        return vec4f(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    vec4f operator*(const vec4f &other) {
        return vec4f(x * other.x, y * other.y, z * other.z, w * other.w);
    }
    vec4f operator/(const vec4f &other) {
        return vec4f(x / other.x, y / other.y, z / other.z, w / other.w);
    }
    vec4f operator*(float t) { return vec4f(x * t, y * t, z * t, w * t); }
    vec4f operator/(float t) { return vec4f(x / t, y / t, z / t, w / t); }
};

struct vec2i {
    int x, y;

    vec2i operator+(const vec2i &other) {
        return vec2i(x + other.x, y + other.y);
    }
    vec2i operator-(const vec2i &other) {
        return vec2i(x - other.x, y - other.y);
    }
    vec2i operator*(const vec2i &other) {
        return vec2i(x * other.x, y * other.y);
    }
    vec2i operator/(const vec2i &other) {
        return vec2i(x / other.x, y / other.y);
    }
    vec2i operator*(int t) { return vec2i(x * t, y * t); }
    vec2i operator/(int t) { return vec2i(x / t, y / t); }
};

struct vec3i {
    int x, y, z;

    vec3i operator+(const vec3i &other) {
        return vec3i(x + other.x, y + other.y, z + other.z);
    }
    vec3i operator-(const vec3i &other) {
        return vec3i(x - other.x, y - other.y, z - other.z);
    }
    vec3i operator*(const vec3i &other) {
        return vec3i(x * other.x, y * other.y, z * other.z);
    }
    vec3i operator/(const vec3i &other) {
        return vec3i(x / other.x, y / other.y, z / other.z);
    }
    vec3i operator*(int t) { return vec3i(x * t, y * t, z * t); }
    vec3i operator/(int t) { return vec3i(x / t, y / t, z / t); }
};

struct vec4i {
    int x, y, z, w;

    vec4i operator+(const vec4i &other) {
        return vec4i(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    vec4i operator-(const vec4i &other) {
        return vec4i(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    vec4i operator*(const vec4i &other) {
        return vec4i(x * other.x, y * other.y, z * other.z, w * other.w);
    }
    vec4i operator/(const vec4i &other) {
        return vec4i(x / other.x, y / other.y, z / other.z, w / other.w);
    }
    vec4i operator*(int t) { return vec4i(x * t, y * t, z * t, w * t); }
    vec4i operator/(int t) { return vec4i(x / t, y / t, z / t, w / t); }
};

struct Vertex {
    vec2f pos;
    vec2f uv;
};
