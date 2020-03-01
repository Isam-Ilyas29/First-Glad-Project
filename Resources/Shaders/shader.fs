#version 330 core
out vec4 FragColour;

in vec3 ourColour;
in vec2 TexCoord;

// Texture samplers
uniform sampler2D texture1;
uniform sampler2D transparent1;

void main() {
	// Linearly interpolate between both textures (65% container, 35% awesomeface)
	FragColour = mix(texture(texture1, TexCoord), texture(transparent1, TexCoord), 0.35);
}