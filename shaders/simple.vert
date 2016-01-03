#version 330 core

in vec3 vPosition;
in vec2 vertexUV;

out vec2 UV;

uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(vPosition, 1);

	UV = vertexUV;
}