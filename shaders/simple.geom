#version 330 core

layout(triangles) in;
layout(triangles, max_vertices = 3) out;

void main() {
	for(int i = 0; i < 3; i++) { // You used triangles, so it's always 3
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}