#ifndef ENGINE_H
#define ENGINE_H


#include "observer.h"
#include "glew/glew.h"
#include "GLFW/glfw3.h"
#include "entity.h"
#include <string>
#include <vector>

class Engine : public Observer{
	Entity* backstage;
	Entity* playersFigure;
	GLFWwindow* window;
	bool redraw;
	bool nudgeFigure;
	bool dropFigure;
	int screenHeight, screenWidth;


public:
	Engine();
	void start();


private:
	void updatePlayerFigure(Entity* objPtr);
	void updateBackstage(Entity* objPtr);
	void draw(Entity* obj);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void glfwInitialize();
	void glewInitialize();
	void eventsInitialize();
	void windowInitialize(int* h, int* w);
	void update(std::string msg, void* obj);
	void Engine::initializeGL();

};

#endif