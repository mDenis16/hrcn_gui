
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


const char *VertexShaderSource = R"(
#version 120
attribute vec3 aPos;
attribute vec2 aTexCoord;

varying vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
)";

const char *FragmentShaderSource = R"(
#version 120
varying vec2 TexCoord;

uniform sampler2D texture1;

void main() {
    gl_FragColor = texture2D(texture1, TexCoord);
}
)";
void PrintOpenGLErrors(char const * const Function, char const * const File, int const Line)
{
	bool Succeeded = true;

	GLenum Error = glGetError();
	if (Error != GL_NO_ERROR)
	{

			std::cerr << ("OpenGL Error in %s at line %d calling function %s: '%d 0x%X'", File, Line, Function, Error, Error) << std::endl;
	}
}


#define CheckedGLCall(x) do { PrintOpenGLErrors(">>BEFORE<< "#x, __FILE__, __LINE__); (x); PrintOpenGLErrors(#x, __FILE__, __LINE__); } while (0)
#define CheckedGLResult(x) (x); PrintOpenGLErrors(#x, __FILE__, __LINE__);
#define CheckExistingErrors(x) PrintOpenGLErrors(">>BEFORE<< "#x, __FILE__, __LINE__);



void PrintShaderInfoLog(GLint const Shader)
{
	int InfoLogLength = 0;
	int CharsWritten = 0;

	glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, & InfoLogLength);

	if (InfoLogLength > 0)
	{
		GLchar * InfoLog = new GLchar[InfoLogLength];
		glGetShaderInfoLog(Shader, InfoLogLength, & CharsWritten, InfoLog);
		std::cout << "Shader Info Log:" << std::endl << InfoLog << std::endl;
		delete [] InfoLog;
	}
}


int main()
{

	int width = 1280;
	int height = 720;

	auto screenw = width;
	auto screenh = height;







	static c_gui* gui = new c_gui();


	GLFWwindow* window;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (! glfwInit())
		return -1;

	window = glfwCreateWindow(1270, 720, "demo", NULL, NULL);
	if (! window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int key, int scancode, int action)
							  { gui->mouse_callback(key, scancode); });

	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mode)
					   { gui->keyboard_callback(key, scancode, action); });

	glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset)
						  { gui->scroll_callback(xoffset, yoffset); });

	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y)
							 { gui->cursor_callback(x, y); });


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
	glOrtho(0, 1280, 720, 0, -1, 1);  // Left, Right, Bottom, Top, Near, Far
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

	// Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
	size_t u2 = 1; while(u2 < width) u2 *= 2;
	size_t v2 = 1; while(v2 < height) v2 *= 2;
	// Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
	double u3 = (double)width / u2;
	double v3 = (double)height / v2;



	// Enable the texture for OpenGL.
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	bool done = false;

	glColor4ub(255, 255, 255, 255);

	std::chrono::high_resolution_clock::time_point lastFrameTime = std::chrono::high_resolution_clock::now();
	double deltaTime = 0.0;
	int frameCount = 0;
	double fps = 0.0;

	gui->setup();
	std::vector<uint8_t> buffer;
	buffer.resize(width * height * 4);
	uint64_t frames = 0;
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

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, &buffer.data()[0]);

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(width, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, height);
			glEnd();

			glfwSwapBuffers(window);
		}
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}