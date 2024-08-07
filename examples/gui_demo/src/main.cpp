
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
struct Matrix4 {
	float m[16];

	Matrix4() {
		// Initialize to identity matrix
		m[0]  = 1.0f; m[1]  = 0.0f; m[2]  = 0.0f; m[3]  = 0.0f;
		m[4]  = 0.0f; m[5]  = 1.0f; m[6]  = 0.0f; m[7]  = 0.0f;
		m[8]  = 0.0f; m[9]  = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
		m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
	}

	static Matrix4 scale(float sx, float sy, float sz) {
		Matrix4 result;
		result.m[0]  = sx;  result.m[1]  = 0.0f; result.m[2]  = 0.0f; result.m[3]  = 0.0f;
		result.m[4]  = 0.0f; result.m[5]  = sy;  result.m[6]  = 0.0f; result.m[7]  = 0.0f;
		result.m[8]  = 0.0f; result.m[9]  = 0.0f; result.m[10] = sz;  result.m[11] = 0.0f;
		result.m[12] = 0.0f; result.m[13] = 0.0f; result.m[14] = 0.0f; result.m[15] = 1.0f;
		return result;
	}

	// Convert matrix to float array (column-major order)
	const float* toArray() const {
		return m;
	}
};

int main()
{

	int fakeWidth = 1280;
	int fakeHeight = 720;

	int logicalWidth = fakeWidth * 2.f;
	int logicalHeight = fakeHeight * 2.f;






	static c_gui* gui = new c_gui(logicalWidth, logicalHeight);

	gui->app->ctx->enableHighDPI(2.f);

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

	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mode)
					   { gui->keyboard_callback(key, scancode, action); });

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
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}