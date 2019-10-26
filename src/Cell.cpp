#include "Cell.h"

Cell::Cell(){
	Cell(0, 0);
}

Cell::Cell(double pos_x, double pos_y): Geometry(GL_LINE_STRIP) {
	size = 0.5;
	Cell::pos_x = pos_x;
	Cell::pos_y = pos_y;
	color = glm::vec3(1, 0, 0);
	verts.push_back(glm::vec3(pos_x, pos_y, 0.f));
	verts.push_back(glm::vec3(pos_x + size, pos_y, 0.f));
	verts.push_back(glm::vec3(pos_x + size, pos_y + size, 0.f));
	verts.push_back(glm::vec3(pos_x, pos_y + size, 0.f));
	verts.push_back(glm::vec3(pos_x, pos_y, 0.f));
}
