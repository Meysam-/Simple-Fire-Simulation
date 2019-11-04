#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <vector>
#include <utility>
#include <math.h>

#include "Geometry.h"
#include "Cell.h"
#include "InputHandler.h"
#include "RenderEngine.h"

class Program {

public:
	Program();
	void start();

private:
	GLFWwindow* window;
	RenderEngine* renderEngine;

	std::vector<Geometry*> geometryObjects;

	bool show_test_window;
	ImVec4 clear_color;

	Cell** grid;
	float cellSize;
	float fireLevel;
	int w; // width
	int h; // hight

	bool sim_run;

	static void error(int error, const char* description);
	void setupWindow();
	void mainLoop();
	void drawUI();
	
	void createTestGeometryObject();
	void createTestGeometryObject1();
	Geometry* createPoint(float x, float y, glm::vec3 color);
	Geometry* createLine(double x1, double y1, double x2, double y2, glm::vec3 color);
	Cell** createGrid(int w, int h);
	void applyRules();
};
