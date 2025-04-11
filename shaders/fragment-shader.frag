#version 330
out vec4 FragColor;

in vec3 vertexColor;
in vec3 ourColor;
in vec3 vertexPosition;

void main() {
    FragColor = vec4(vertexColor, 1.0);
    FragColor = vec4(ourColor, 1.0);
    FragColor = vec4(vertexPosition, 1.0);
    // FragColor = vec4(vec3(1.0), 1.0);
}
