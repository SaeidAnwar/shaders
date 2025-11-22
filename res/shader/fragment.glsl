#version 330 core

uniform vec2 u_res;

layout(location = 0) out vec4 color;
void main() {
    vec2 uv = gl_FragCoord.xy / u_res;
    uv *= 2;
    uv -= 1;
    color = vec4(1.0, 0.0, 0.0, 1.0);
}
