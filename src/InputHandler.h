#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <utility>

#include "RenderEngine.h"

class InputHandler {

public:
	static int mouseOldX;
	static int mouseOldY;
	static bool hold;
	static std::vector<std::pair<int,int>> rightClickedPositions;
	static std::vector<std::pair<int,int>> leftClickedPositions;
	static std::vector<std::pair<int,int>> middleClickedPositions;

	static void setUp(RenderEngine* renderEngine);

	static void key(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse(GLFWwindow* window, int button, int action, int mods);
	static void motion(GLFWwindow* window, double x, double y);
	static void scroll(GLFWwindow* window, double x, double y);
	static void reshape(GLFWwindow* window, int width, int height);

private:
	static RenderEngine* renderEngine;
};
