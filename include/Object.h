#ifndef OBJECT_H
#define OBJECT_H

#include "Model.h"

class Object {
	public:
		Object(Model* model);
		Model* model;
};

#endif