#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform float horizontalOffset;

out vec3 vertexColor;
out vec3 ourColor;
out vec3 vertexPosition;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vertexColor = vec3(1.0f);
    ourColor = vec3(1.0f);
    vertexPosition = aPos;
    TexCoord = aTexCoord;

    vec4 position = vec4(aPos.x + horizontalOffset, aPos.y, aPos.z, 1.0);

    gl_Position = projection * view * model * position;
}
