#version 450

layout(location = 0) in vec2 fragOffset;
layout(location = 0) out vec4 outColor;

struct PointLight {
    vec4 position;
    vec4 color;
};

layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projection;
    mat4 view;
    vec4 ambientLightColor; // w is intensity
    PointLight pointLights[10];
    int numLights;
} ubo;

layout(push_constant) uniform Push {
    vec4 position;
    vec4 color;
    float radius;
} push;


layout(set = 1, binding = 0) uniform sampler2D texSampler;

void main() {
    float dis = sqrt(dot(fragOffset, fragOffset));
    if(dis >= 1.0) {
        discard;
    }
    
    vec2 uv = fragOffset * 0.5 + 0.5;
    // Y축이 뒤집혀 있을 수 있으므로 확인 필요 (Vulkan은 Y가 아래로 증가)
    // 텍스처 좌표계도 (0,0)이 좌상단.
    
    vec4 texColor = texture(texSampler, uv);
    outColor = vec4(texColor.rgb, 1.0);
}