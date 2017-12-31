#ifndef CHUNK
#define CHUNK

#include <deque>
#include <math.h>
#include <glm/glm.hpp>

#include "planets/voxels.h"
#include "planets/MarchingCubes.h"
#include "planets/Perlin.h"

#define LOD_MAX 64

class Chunk
{
	public:
		Chunk();
		void generateSphere();
		
		int lod;
		int size;
		int vertexCount;
		
		Voxel* voxels;
		glm::vec3* vertices;
		glm::vec3* normals;
		
	private:
		glm::vec3 interpolateVertex(float isorange, glm::vec3 p1, glm::vec3 p2, float p1Val, float p2Val);
		glm::vec3 interpolateNormal(int x, int y, int z, int isorange, int corner1, int corner2);
};

#endif