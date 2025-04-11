#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform float horizontalOffset;

out vec3 vertexColor;
out vec3 ourColor;
out vec3 vertexPosition;
out vec2 TexCoord;

void main() {
    vertexColor = vec3(1.0);
    ourColor = aColor;
    vertexPosition = aPos;
    TexCoord = aTexCoord;

    gl_Position = vec4(aPos.x + horizontalOffset, aPos.y, aPos.z, 1.0);
}
