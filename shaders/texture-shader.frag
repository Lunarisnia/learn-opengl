#version 330
out vec4 FragColor;

in vec3 vertexColor;
in vec3 ourColor;
in vec3 vertexPosition;
in vec2 TexCoord;

uniform sampler2D imageTexture;

void main() {
    // IGNORE THIS, THIS IS JUST SO THAT IT WONT CAUSE ANY ERROR BECAUSE OF UNREAD VALUE
    FragColor = vec4(vertexColor, 1.0);
    FragColor = vec4(ourColor, 1.0);
    FragColor = vec4(vertexPosition, 1.0);

    FragColor = texture(imageTexture, TexCoord);
}
