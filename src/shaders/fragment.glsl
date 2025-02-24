#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D texture1;
uniform bool useTexture;

void main() {
    if (useTexture)
        fragColor = texture(texture1, texCoord);
    else
        fragColor = vec4(1.0, 1.0, 1.0, 1.0f);
}
