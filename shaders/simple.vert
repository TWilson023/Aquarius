#version 330 core

layout(location = 2) in vec3 vNormal;
in vec3 vPosition;
in vec2 vertexUV;

out vec2 UV;
out vec3 vColor;

uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(vPosition, 1);
	
	vColor = vec3(0.2, 0.8, 0.2) * clamp(dot(vNormal, vec3(0, 1, 0)) + 0.25, 0, 1);

	UV = vertexUV;
}