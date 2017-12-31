#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Geometry.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include "planets/VoxelObject.h"

class Planet : public Geometry {
	public:
		Planet(int radius);
		void render(glm::mat4 mvp);
		
		int radius;
		
	private:
		void create();
		
		VoxelObject* voxelObject;
};

#endif