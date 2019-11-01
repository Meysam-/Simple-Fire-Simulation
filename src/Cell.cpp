#include "Cell.h"

Cell::Cell(){
	Cell(0, 0, 1);
}

Cell::Cell(double pos_x, double pos_y, double size) {
	Cell::size = size;
	Cell::pos_x = pos_x;
	Cell::pos_y = pos_y;

	outline = Geometry(GL_LINE_STRIP);
	outline.color = glm::vec3(0, 0, 0);
	outline.verts.push_back(glm::vec3(pos_x, pos_y, 0.f));
	outline.verts.push_back(glm::vec3(pos_x + size, pos_y, 0.f));
	outline.verts.push_back(glm::vec3(pos_x + size, pos_y + size, 0.f));
	outline.verts.push_back(glm::vec3(pos_x, pos_y + size, 0.f));
	outline.verts.push_back(glm::vec3(pos_x, pos_y, 0.f));

	inner = Geometry(GL_POLYGON);
	inner.color = glm::vec3(0, 1, 0);
	inner.verts.push_back(glm::vec3(pos_x, pos_y, 0.f));
	inner.verts.push_back(glm::vec3(pos_x + size, pos_y, 0.f));
	inner.verts.push_back(glm::vec3(pos_x + size, pos_y + size, 0.f));
	inner.verts.push_back(glm::vec3(pos_x, pos_y + size, 0.f));
	
}

void Cell::setupRenderEngine(RenderEngine* renderEngine, std::vector<Geometry*>* geometryObjects) {
	Cell::renderEngine = renderEngine;
	renderEngine->assignBuffers(outline);
	renderEngine->updateBuffers(outline);
	geometryObjects->push_back(&outline);

	renderEngine->assignBuffers(inner);
	renderEngine->updateBuffers(inner);
	geometryObjects->push_back(&inner);
}

void Cell::setFireLevel(double fireLevel) {
	Cell::fire_level = fireLevel;
	inner.color = inner.color = glm::vec3(fire_level, 1 - fire_level, 0);
	renderEngine->updateBuffers(inner);
}