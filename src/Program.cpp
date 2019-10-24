#include "Program.h"


Program::Program() {
	window = nullptr;
	renderEngine = nullptr;
}

// Error callback for glfw errors
void Program::error(int error, const char* description) {
	std::cerr << description << std::endl;
}

// Called to start the program
void Program::start() {
	setupWindow();
	GLenum err = glewInit();
	if (glewInit() != GLEW_OK) {
		std::cerr << glewGetErrorString(err) << std::endl;
	}

	/*
	bool err = gl3wInit() != 0;

	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
	}
	*/
	renderEngine = new RenderEngine(window);
	InputHandler::setUp(renderEngine);
	mainLoop();
}

// Creates GLFW window for the program and sets callbacks for input
void Program::setupWindow() {
	glfwSetErrorCallback(Program::error);
	if (glfwInit() == 0) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 16);
	window = glfwCreateWindow(749, 749, "589 Boilerplate", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // V-sync on

	glfwSetKeyCallback(window, InputHandler::key);
	glfwSetMouseButtonCallback(window, InputHandler::mouse);
	glfwSetCursorPosCallback(window, InputHandler::motion);
	glfwSetScrollCallback(window, InputHandler::scroll);
	glfwSetWindowSizeCallback(window, InputHandler::reshape);

	// Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

	const char* glsl_version = "#version 430 core";

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

// Creates an object from specified vertices - no texture. Default object is a 2D triangle.
void Program::createTestGeometryObject() {
	Geometry* testObject = new Geometry();

	testObject->verts.push_back(glm::vec3(-5.f, -3.f, 0.f));
	testObject->verts.push_back(glm::vec3(5.f, -3.f, 0.f));
	testObject->verts.push_back(glm::vec3(0.f, 5.f, 0.f));
	testObject->color = glm::vec3(1, 0, 0);
	renderEngine->assignBuffers(*testObject);
	renderEngine->updateBuffers(*testObject);
	geometryObjects.push_back(testObject);
}

void Program::createTestGeometryObject1() {
	Geometry* testObject = new Geometry(GL_POINTS);
	glPointSize(5);
	glColor3f(1, 0, 0);
	testObject->verts.push_back(glm::vec3(-5.f, -3.f, 0.f));
	//testObject->verts.push_back(glm::vec3(5.f, -3.f, 0.f));
	renderEngine->assignBuffers(*testObject);
	renderEngine->updateBuffers(*testObject);
	geometryObjects.push_back(testObject);
}

Geometry* Program::createPoint(float x, float y, glm::vec3 color = glm::vec3(1, 0, 0)) {
	Geometry* point = new Geometry(GL_POINTS);
	point->color = color;
	point->verts.push_back(glm::vec3(x, y, 0.f));
	renderEngine->assignBuffers(*point);
	renderEngine->updateBuffers(*point);
	geometryObjects.push_back(point);
	return point;
}

Geometry* Program::createLine(double x1, double y1, double x2, double y2, glm::vec3 color = glm::vec3(0, 1, 1)) {

	Geometry* line = new Geometry(GL_LINE_STRIP);
	line->color = color;
	line->verts.push_back(glm::vec3(x1, y1, 0.f));
	line->verts.push_back(glm::vec3(x2, y2, 0.f));
	renderEngine->assignBuffers(*line);
	renderEngine->updateBuffers(*line);
	geometryObjects.push_back(line);
	return line;
}

void Program::drawUI() {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{

		ImGui::Begin("Wildfire Simulation!");                          // Create a window called "Hello, world!" and append into it.

		//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Test Window", &show_test_window);      // Edit bools storing our window open/close state

		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		//ImGui::SameLine();
		//ImGui::InputInt("order", &order);
		//ImGui::SliderFloat("step size", &u_inc, 0.001f, 1.0f);
		//ImGui::SliderFloat("animation", &u_animate, 0.0f, 1.0f);
	
		if (ImGui::Button("Clean")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
			Program::geometryObjects.clear();
		}
		ImGui::SameLine();
		//ImGui::Checkbox("Click me!", &show_test_window);
		ImGui::End();
	}
	// 3. Show another simple window.
	if (show_test_window)
	{
		ImGui::Begin("Another Window", &show_test_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("This is an example popup window.");
		if (ImGui::Button("Close Me"))
			show_test_window = false;
		ImGui::End();
	}
}

// Main loop
void Program::mainLoop() {
	//createTestGeometryObject();
	//createPoint(0, 0);
	//createPoint(-10, 10);
	
	
	// Our state
	show_test_window = false;
	clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		while (InputHandler::rightClickedPositions.size() > 0) {
			/**
			if (geometryObjects.size() == 8) {
				geometryObjects.clear();
			}/**/

			std::pair<int, int> point = InputHandler::rightClickedPositions.back();
			InputHandler::rightClickedPositions.pop_back();
			double factor = 20.0 / 750.0;
			//std::cout << point.first << " : " << point.second << std::endl;
			float x = point.first*factor - 10.0;
			float y = 10.0 - point.second*factor;

		}
		while (InputHandler::middleClickedPositions.size() > 0) {
			std::pair<int, int> point = InputHandler::middleClickedPositions.back();
			InputHandler::middleClickedPositions.pop_back();
			double factor = 20.0 / 750.0;
			//Do remore the control point
			double epsilon = 0.1;
			int delete_index = -1;
			float x = point.first * factor - 10.0;
			float y = 10.0 - point.second * factor;
			
		}
		while (InputHandler::leftClickedPositions.size() > 0) {
			std::pair<int, int> point = InputHandler::leftClickedPositions.back();
			InputHandler::leftClickedPositions.pop_back();
			double factor = 20.0 / 750.0;
			double epsilon = 0.1;
			float x = point.first * factor - 10.0;
			float y = 10.0 - point.second * factor;
			createPoint(x, y);
		}
		

		drawUI();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(5);

		renderEngine->render(geometryObjects, glm::mat4(1.f));
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// Clean up, program needs to exit
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	delete renderEngine;
	glfwTerminate();
}
