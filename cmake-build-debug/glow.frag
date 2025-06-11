#version 330 core

out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D texture;
uniform vec3 glowColor;
uniform float glowIntensity;
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;
void main() {
    vec4 baseColor = texture(texture, TexCoords);
    
    // Calculate glow effect based on brightness
    float brightness = dot(baseColor.rgb, vec3(0.299, 0.587, 0.114)); // Grayscale luminance
    vec3 glow = glowColor * glowIntensity * brightness;
    
    FragColor = vec4(baseColor.rgb + glow, baseColor.a);
}
