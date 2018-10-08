#include "engine.h"



Engine::Engine() {
	playersFigure = 0;

	redraw = true;
	nudgeFigure = false;
}


void Engine::initializeGL() {
	glfwInitialize();
	glewInitialize();
	eventsInitialize();
}

void Engine::start() {

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (nudgeFigure)
		{
			playersFigure->moveTo((int)'E');
			nudgeFigure = false;
		}
		if (dropFigure) {
			playersFigure->moveTo((int)'S');
			dropFigure = false;
		}
		if (redraw)
		{
			redraw = false;
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			draw(backstage);
			draw(playersFigure);

			glfwSwapBuffers(window);
		}
	}




}

void Engine::draw(Entity* obj) {
	if (obj != nullptr)
		obj->outline();

}

void Engine::updatePlayerFigure(Entity* objPtr) {
	playersFigure = objPtr;
}
void Engine::updateBackstage(Entity* objPtr) {
	backstage = objPtr;
}



void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {


	if (action == GLFW_PRESS)
		playersFigure->moveTo(key);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Engine::glfwInitialize() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	windowInitialize(&screenHeight, &screenWidth);
	if (window == GLEW_OK)std::cout << "widnow ok" << std::endl;
	glfwSetWindowUserPointer(window, this);
}

void Engine::glewInitialize() {
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		throw "Failed to initialize GLEW";
	}
}

void Engine::eventsInitialize() {
	auto lam = [](GLFWwindow* window, int key, int scancode, int action, int mode) {
		static_cast<Engine*>(glfwGetWindowUserPointer(window))->key_callback(window, key, scancode, action, mode);
	};
	glfwSetKeyCallback(window, lam);
}

void Engine::windowInitialize(int* h, int* w) {
	window = glfwCreateWindow(*w, *h, "Tetris", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		throw "Failed to create window";
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, *w, *h);
}


void Engine::update(std::string msg, void* obj) {
	if (msg == "redraw") { redraw = true; return; }
	if (msg == "updPlayerFigure") { updatePlayerFigure((Entity*)obj); return; }
	if (msg == "updBackstage") { updateBackstage((Entity*)obj); return; }
	if (msg == "immobilized") { nudgeFigure = true; };
	if (msg == "drop") { dropFigure = true; };
	if (msg == "start") { start(); };
	if (msg == "init")
	{
		screenHeight = ((Point2D*)obj)->getY();
		screenWidth = ((Point2D*)obj)->getX();
		initializeGL();
		return;
	}
}

