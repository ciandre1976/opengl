#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

static unsigned int CompileShader(unsigned int type, const std::string& source) {

	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	return id;
}

static int CreateShader(const std::string& vertex_shader, const std::string& fragment_shader) {

	unsigned int program = glCreateProgram();

	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

std::string vertexShader =
"#version 330 core\n"
"\n"
"layout(location = 0) in vec4 position;\n"
"\n"
"void main()\n"
"{\n"
"gl_Position = position;\n"
"}\n";

std::string fragmentshader =
"#version 330 core\n"
"\n"
"layout(location = 0) out vec4 color;\n "
"\n"
"void main()\n"
"{\n"
"color = vec4(1, 0.0, 1.0, 1);\n"
"}\n";

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "Ciao openGL", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (glewInit() == GLEW_OK) {
		std::cout << "Its fine!";
	};

	float positions[] = {
		 -0.5f,-0.5f,
		  0.5f,-0.5f,
		  0.5f,0.5f,
		 -0.5f,0.5f
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);



	unsigned int shader = CreateShader(vertexShader, fragmentshader);
	glUseProgram(shader);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		//glDrawArrays(GL_TRIANGLES, 0, 6);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */

	}

	glfwTerminate();
	return 0;
}