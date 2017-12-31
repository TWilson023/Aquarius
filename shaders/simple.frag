#version 330 core

in vec2 UV;
uniform float glfwTime;

in vec3 vColor;
out vec3 color;

uniform sampler2D textureSampler;

void main() {
	color = texture(textureSampler, UV).rgb;
	
	color = vColor;
}
