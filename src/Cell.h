#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include "RenderEngine.h"
#include "Geometry.h"

class Cell {
private:
	RenderEngine* renderEngine;
	Geometry outline;
	Geometry inner;
	double fire_level; // 0 means no fire - 1 means compeletly burned

public:
	/**/
	Cell();
	Cell(double pos_x, double pos_y, double size);

	double pos_x;
	double pos_y;
	double size;

	void setupRenderEngine(RenderEngine* renderEngine, std::vector<Geometry*>* geometryObjects);
	void Cell::setFireLevel(double fireLevel);
	/**/
};

