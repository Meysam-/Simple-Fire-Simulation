#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include "Geometry.h"

class Cell: public Geometry {

public:
	/**/
	Cell();
	Cell(double pos_x, double pos_y);

	double pos_x;
	double pos_y;
	double size;
	double fire_level; // 0 means no fire - 1 means compeletly burned 
	/**/
};

