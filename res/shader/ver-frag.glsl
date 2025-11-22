#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
void main() { gl_Position = vec4(position, 0.0, 1.0); }

#shader fragment
#version 330 core

uniform vec2 u_res;
uniform vec2 u_pos;

float circle(vec2 uv, vec2 center, float rad) {
    vec2 temp = uv - center;
    return smoothstep(length(temp) - 0.01, length(temp), rad) -
           smoothstep(length(temp), length(temp) + 0.01, rad);
}

float circleFill(vec2 uv, vec2 center, float rad) {
    vec2 temp = uv - center;
    return smoothstep(length(temp) - 0.01, length(temp), rad);
}

float rectangle(vec2 uv, vec2 center, vec2 size) {
    vec2 halfSize = size * 0.5;
    vec2 d = abs(uv - center) - halfSize;
    float outside = length(max(d, 0.0));
    float inside = -min(max(d.x, d.y), 0.0);

    return smoothstep(0.01, 0.0, outside + inside);
}

float plot(float point, float axis) {
    return smoothstep(point - 0.01, point, axis) -
           smoothstep(point, point + 0.01, axis);
}

layout(location = 0) out vec4 color;
void main() {
    vec2 uv = gl_FragCoord.xy / u_res;
    uv *= 2;
    uv -= 1;

    vec4 col = vec4(1.0, 1.0, 1.0, 1.0) * circleFill(uv, u_pos, 0.5);
    color = col;
}
