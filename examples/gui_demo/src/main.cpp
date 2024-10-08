
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <base/app.hpp>
#include <base/app_context.hpp>
#include <chrono>
#include <base/state.hpp>
#include <base/effect.hpp>
#include <base/style/style_manager.hpp>
#include <base/transitions/transitions_manager.hpp>
#include <base/transitions/transitions_manager.hpp>
#include <base/transitions/transition_margin.hpp>
#include <base/input_context.hpp>
#include <base/events/mouse_move_event.hpp>
#include <base/events/types.hpp>
#include <base/node.hpp>
#include <base/yg_enums.hpp>
#include <base/font.hpp>
#include <base/font_face.hpp>
#include <iostream>
#include <string>

#include "gui.h"

int main()
{

	int fakeWidth = 1280;
	int fakeHeight = 720;

	int logicalWidth = fakeWidth * 2.f;
	int logicalHeight = fakeHeight * 2.f;


	static c_gui* gui = new c_gui(logicalWidth, logicalHeight);



	GLFWwindow* window;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (! glfwInit())
		return -1;

	window = glfwCreateWindow(fakeWidth , fakeHeight , "demo", NULL, NULL);
	if (! window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int key, int scancode, int action)
							  { gui->mouse_callback(key, scancode); });

	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mode) {
		gui->keyboard_callback(key, scancode, action);
	});

	glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset)
						  { gui->scroll_callback(xoffset, yoffset); });

	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y)
							 { gui->cursor_callback(x, y); });

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		// Update the global dimensions


 // Update the viewport


 // Update the orthographic projection matrix
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 // Maintain the aspect ratio
 glOrtho(0, width * 0.5f, height * 0.5f, 0, -1, 1);  // Left, Right, Bottom, Top, Near, Far
 glMatrixMode(GL_MODELVIEW);

	});

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	std::cout << glfwGetVersionString() << std::endl;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return -1;
	}


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, logicalWidth * 0.5f , logicalHeight  * 0.5f , 0, -1, 1);  // Left, Right, Bottom, Top, Near, Far
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Make some OpenGL properties better for 2D and enable alpha channel.
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

	if(glGetError() != GL_NO_ERROR) {
		std::cout << "Error initing GL" << std::endl;
		return 1;
	}


	// Enable the texture for OpenGL.
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	bool done = false;

	glColor4ub(255, 255, 255, 255);

	std::chrono::high_resolution_clock::time_point lastFrameTime = std::chrono::high_resolution_clock::now();
	double deltaTime = 0.0;
	int frameCount = 0;
	double fps = 0.0;

	gui->setup();
	std::vector<uint8_t> buffer;
	buffer.resize(gui->width * gui->height * 4);
	uint64_t frames = 0;

	gui->app->ctx->enableHighDPI(2.f);

	while (! glfwWindowShouldClose(window))
	{

		if (gui->swap_buffer(buffer)) {
			frames++;
			auto now = std::chrono::high_resolution_clock::now();
			std::chrono::duration elapsed = now - lastFrameTime;

			if (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() > 1000) {
				std::cout << "Frames: " << frames << std::endl;
				lastFrameTime = now;
				frames = 0;
			}



			glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			float scale = 1.f;


			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, logicalWidth, logicalHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, &buffer.data()[0]);



			glBegin(GL_QUADS);
			// Bottom-left
			glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);

			// Bottom-right
			glTexCoord2f(1.0f, 0.0f); glVertex2f(scale * fakeWidth, 0.0f);

			// Top-right
			glTexCoord2f(1.0f, 1.0f); glVertex2f(scale * fakeWidth, scale * fakeHeight);

			// Top-left
			glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, scale * fakeHeight);
			glEnd();

			glfwSwapBuffers(window);
		}
		glfwWaitEventsTimeout(0.16f);
	}


	glfwTerminate();
	return 0;
}