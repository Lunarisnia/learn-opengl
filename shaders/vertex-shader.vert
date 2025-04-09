#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform float horizontalOffset;

out vec3 vertexColor;
out vec3 ourColor;

void main() {
    vertexColor = vec3(1.0);
    ourColor = aColor;

    gl_Position = vec4(aPos.x + horizontalOffset, aPos.y, aPos.z, 1.0);
}
