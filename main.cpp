#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "indexbuffer.h"
#include "vertexbuffer.h"
#include "vertexarray.h"
#include "renderer.h"
#include "shader.h"

void errorCallback(int error, const char * description)
{
	puts("Glfw error:");
	puts(description);
}

int main()
{
	glfwSetErrorCallback(errorCallback);
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;


	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		puts("Could not create window");
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if(glewInit() != GLEW_OK)
	{
		puts("glew error");
		return -1;
	}

	glfwSwapInterval(1);
	std::cout << glGetString(GL_VERSION) << '\n';

	float positions [] = {
		-0.25f, -0.25f, // 0
		 0.5f,   0.5f,  // 1
		 0.5f,  -0.25f, // 2
		-0.25f,  0.5f   // 3
	};

	float positions2 [] = {
		-0.8f, -0.8f,	// 0
		-0.4f, -0.4f,	// 1
		-0.4f, -0.8f,	// 2
		-0.8f, -0.4f	// 3
	};

	u_int32_t indicies [] = {
		0, 1, 3,
		0, 1, 2
	};

	u_int32_t indicies2 [] = {
		0, 1, 3,
		0, 1, 2
	};

	{
		u_int32_t vertexArrayID;
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		VertexBuffer vb(positions, 8 * sizeof(float));
		VertexBuffer vb2(positions2, 8 * sizeof(float));

		VertexArray va, va2;

		VertexBufferLayout layout, layout2;
		layout.push(2, GL_FLOAT);
		layout2.push(2, GL_FLOAT);

		va.addBuffer(vb, layout);
		va2.addBuffer(vb2, layout2);

		IndexBuffer ib(indicies, 6);
		IndexBuffer ib2(indicies2, 6);

		Shader shader("shaders/basic.shader");
		shader.bind();

		shader.setUniform4f("u_color", 1, 0.3f, 0.8f, 1.f);

		auto error = glGetError();

		while(error != 0)
		{
			std::cerr << error << ' ' << std::hex << error << '\n';
			error = glGetError();
		}

		float r = 0.2;
		float inc = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			
			shader.setUniform4f("u_color", r, 0.3f, 0.8f, 1.f);

			va.bind();
			ib.bind();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			va2.bind();
			ib.bind();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			if(r > 1.f || r < 0.f)
				inc = -inc;

			r += inc;

			/* Poll for and process events */
			glfwPollEvents();
		}

	}
	
	glfwTerminate();
	return 0;
}
