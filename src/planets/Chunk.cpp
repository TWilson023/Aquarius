#include "planets/Chunk.h"

#include <iostream>

Chunk::Chunk() : size(CHUNK_SIZE)
{
	unsigned int totalSize = size * size * size;
	
	voxels = new Voxel[totalSize];
	vertices = new glm::vec3[totalSize * 15];
	normals = new glm::vec3[totalSize * 15];
	
	generateSphere();
}

void Chunk::generateSphere()
{
	std::cout << "Creating voxels..." << std::endl;
	int idx = 0;
	for (int x = 0; x < size; ++x)
		for (int y = 0; y < size; ++y)
			for (int z = 0; z < size; ++z)
			{
				Voxel v;
				voxels[idx++] = v;
			}
	
	int totalSize = size * size * size;
	
	std::cout << "Generating isovalues..." << std::endl;
	
	Perlin noise = Perlin(0);
	
	for (int x = 0; x < size + 1; ++x) {
		for (int y = 0; y < size + 1; ++y) {
			for (int z = 0; z < size + 1; ++z) {
				idx = x * size*size + y * size + z;
				
				float realX = x - size / 2,
					realY = y - size / 2,
					realZ = z - size / 2;
					
				float radius = 32;
				float scale = 0.1;
				radius += noise.noise(realX * scale, realY * scale, realZ * scale) * 4.0;
				float* isovalue = new float;
				*isovalue = pow(realX, 2)
							+ pow(realY, 2)
							+ pow(realZ, 2)
							- pow(radius, 2);
				
				int adjacents[] = {
					idx,
					idx - size*size, // Left
					idx - size*size - 1, // Behind left
					idx - 1, // Behind
					idx - size, // Below
					idx - size*size - size, // Below left
					idx - size*size - size - 1, // Below behind left
					idx - size - 1 // Below behind
				};
				
				for (int i = 0; i < 8; ++i)
					if (adjacents[i] >= 0 && adjacents[i] < totalSize)
						voxels[adjacents[i]].isovalue[i] = isovalue;
			}
		}
	}
	
	std::cout << "Generating vertices..." << std::endl;	
	
	vertexCount = 0;
	glm::vec3 position[8];
	for (int x = 0; x < size; ++x)
		for (int y = 0; y < size; ++y)
			for (int z = 0; z < size; ++z)
			{
				position[0] = glm::vec3(x, y, z);
				position[1] = glm::vec3(x + 1, y, z);
				position[2] = glm::vec3(x + 1, y, z + 1);
				position[3] = glm::vec3(x, y, z + 1);
				position[4] = glm::vec3(x, y + 1, z);
				position[5] = glm::vec3(x + 1, y + 1, z);
				position[6] = glm::vec3(x + 1, y + 1, z + 1);
				position[7] = glm::vec3(x, y + 1, z + 1);
				
				int i = x * size*size + y * size + z;
				VoxelMesh* mesh = MarchingCubes::generateMesh(&voxels[i], position, 0);
				if (mesh == NULL) continue;
				
				for (int v = 0; v < mesh->VERTEX_COUNT; ++v)
				{
					normals[vertexCount] = mesh->normals[v];
					vertices[vertexCount++] = mesh->vertices[v];
				}
			}
}