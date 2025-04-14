#version 330
out vec4 FragColor;

in vec3 vertexColor;
in vec3 ourColor;
in vec3 vertexPosition;
in vec2 TexCoord;

uniform sampler2D imageTexture;
uniform sampler2D imageTexture2;

uniform float transparency;

void main() {
    // IGNORE THIS, THIS IS JUST SO THAT IT WONT CAUSE ANY ERROR BECAUSE OF UNREAD VALUE
    FragColor = vec4(vertexColor, 1.0);
    FragColor = vec4(ourColor, 1.0);
    FragColor = vec4(vertexPosition, 1.0);

    vec3 smileyFace = texture(imageTexture2, vec2(-TexCoord.x, TexCoord.y)).xyz;
    vec3 colour = texture(imageTexture, TexCoord).xyz;
    colour = mix(colour, smileyFace, transparency);

    FragColor = vec4(colour, 1.0);
}
