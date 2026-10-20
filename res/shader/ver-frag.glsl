#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
void main() { gl_Position = vec4(position, 0.0, 1.0); }

#shader fragment
#version 330 core

uniform vec2 u_res;
uniform vec2 u_pos;

float circle_fill(float r, vec2 pos, float b, vec2 uv) {
  float d = length(uv - pos);
  return smoothstep(r, r - b, d);
}

float circle_fill(float r, vec2 pos, vec2 uv) { return circle_fill(r, pos, 0.01, uv); }

float circle(float r, vec2 pos, float b, vec2 uv) {
  float d = length(uv - pos);
  return smoothstep(r + b, r, d) - smoothstep(r, r - b, d);
}

float circle(float r, vec2 pos, vec2 uv) { return circle(r, pos, 0.01, uv); }

float bandx(float w, vec2 pos, float b, vec2 uv) {
  uv -= pos;
  float s = pos.y - w / 2;
  float e = pos.y + w / 2;
  return smoothstep(s - b, s, uv.y) * smoothstep(e, e - b, uv.y);
}

float bandy(float w, vec2 pos, float b, vec2 uv) {
  uv -= pos;
  float s = pos.x - w / 2;
  float e = pos.x + w / 2;
  return smoothstep(s - b, s, uv.x) * smoothstep(e, e - b, uv.x);
}

float rect(float w, float h, vec2 pos, float b, vec2 uv) {
  return bandx(w, pos, b, uv) * bandy(h, pos, b, uv);
}

layout(location = 0) out vec4 color;
void main() {
  vec2 uv = gl_FragCoord.xy / u_res;
  uv -= 0.5;
  uv *= 2;
  uv.x *= u_res.x / u_res.y;

  vec2 pos = vec2(0.0);

  float x = uv.x;
  float y = uv.y - x * x;

  float col = circle(0.5, pos, uv);
  col += rect(0.01, 10.0, pos, 0.01, vec2(x, y));
  color = vec4(1.0, 1.0, 1.0, 1.0) * col;
}
