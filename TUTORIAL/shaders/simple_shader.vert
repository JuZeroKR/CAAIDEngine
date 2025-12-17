#version 450

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

layout(push_constant) uniform Push {
    mat4 transform;
    vec2 offset;
    vec3 color;
}push;

void main() {
    gl_Position = push.transform * vec4(position, 0.0, 1.0) + vec4(push.offset, 0.0, 0.0);
}
