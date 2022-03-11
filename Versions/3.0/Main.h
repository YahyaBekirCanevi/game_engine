#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "objloader.h"
#include "camera.h"
#include "Matrix.h"
#include "Shader.h"

using namespace std;

class Color {
public:
	float r;
	float g;
	float b;
	Color() : r(0), g(0), b(0) {}
	Color(float a, float b, float c) : r(a), g(b), b(c) {}
};

class Program {
public:
	unsigned int program;
	float lastTime;
	bool locked;

	vector<vec3> coordinates;
	vector<vec3> uvs;
	vector<vec3> normals;
	Matrix Projection, View, Model;
	Camera cam;
	Transform camt, t;

	GLFWwindow* window;

	Program() : lastTime(0), locked(true), 
		Projection(Matrix::Zeros({4,4})),
		View(Matrix::Zeros({4,4})),
		Model(Matrix::Zeros({4,4})) {}
	~Program() {}

	void Start() {
		string str = "cube.obj";
		cout << "File Name : " << str << endl;
		FileReader file(str);
		file.loadObj(coordinates, uvs, normals);

		float g_color_buffer_data[] = {
			0.583f,  0.771f,  0.014f,
			0.609f,  0.115f,  0.436f,
			0.327f,  0.483f,  0.844f,
			0.822f,  0.569f,  0.201f,
			0.435f,  0.602f,  0.223f,
			0.310f,  0.747f,  0.185f,
			0.597f,  0.770f,  0.761f,
			0.559f,  0.436f,  0.730f,
			0.359f,  0.583f,  0.152f,
			0.483f,  0.596f,  0.789f,
			0.559f,  0.861f,  0.639f,
			0.195f,  0.548f,  0.859f,
			0.014f,  0.184f,  0.576f,
			0.771f,  0.328f,  0.970f,
			0.406f,  0.615f,  0.116f,
			0.676f,  0.977f,  0.133f,
			0.971f,  0.572f,  0.833f,
			0.140f,  0.616f,  0.489f,
			0.997f,  0.513f,  0.064f,
			0.945f,  0.719f,  0.592f,
			0.543f,  0.021f,  0.978f,
			0.279f,  0.317f,  0.505f,
			0.167f,  0.620f,  0.077f,
			0.347f,  0.857f,  0.137f,
			0.055f,  0.953f,  0.042f,
			0.714f,  0.505f,  0.345f,
			0.783f,  0.290f,  0.734f,
			0.722f,  0.645f,  0.174f,
			0.302f,  0.455f,  0.848f,
			0.225f,  0.587f,  0.040f,
			0.517f,  0.713f,  0.338f,
			0.053f,  0.959f,  0.120f,
			0.393f,  0.621f,  0.362f,
			0.673f,  0.211f,  0.457f,
			0.820f,  0.883f,  0.371f,
			0.982f,  0.099f,  0.879f,
			0.583f,  0.771f,  0.014f,
			0.609f,  0.115f,  0.436f,
			0.327f,  0.483f,  0.844f,
			0.822f,  0.569f,  0.201f,
			0.435f,  0.602f,  0.223f,
			0.310f,  0.747f,  0.185f,
			0.597f,  0.770f,  0.761f,
			0.559f,  0.436f,  0.730f,
			0.359f,  0.583f,  0.152f,
			0.483f,  0.596f,  0.789f,
			0.559f,  0.861f,  0.639f,
			0.195f,  0.548f,  0.859f,
			0.014f,  0.184f,  0.576f,
			0.771f,  0.328f,  0.970f,
			0.406f,  0.615f,  0.116f,
			0.676f,  0.977f,  0.133f,
			0.971f,  0.572f,  0.833f,
			0.140f,  0.616f,  0.489f,
			0.997f,  0.513f,  0.064f,
			0.945f,  0.719f,  0.592f,
			0.543f,  0.021f,  0.978f,
			0.279f,  0.317f,  0.505f,
			0.167f,  0.620f,  0.077f,
			0.347f,  0.857f,  0.137f,
			0.055f,  0.953f,  0.042f,
			0.714f,  0.505f,  0.345f,
			0.783f,  0.290f,  0.734f,
			0.722f,  0.645f,  0.174f,
			0.302f,  0.455f,  0.848f,
			0.225f,  0.587f,  0.040f,
			0.517f,  0.713f,  0.338f,
			0.053f,  0.959f,  0.120f,
			0.393f,  0.621f,  0.362f,
			0.673f,  0.211f,  0.457f,
			0.820f,  0.883f,  0.371f,
			0.982f,  0.099f,  0.879f,
			0.583f,  0.771f,  0.014f,
			0.609f,  0.115f,  0.436f,
			0.327f,  0.483f,  0.844f,
			0.822f,  0.569f,  0.201f,
			0.435f,  0.602f,  0.223f,
			0.310f,  0.747f,  0.185f,
			0.597f,  0.770f,  0.761f,
			0.559f,  0.436f,  0.730f,
			0.359f,  0.583f,  0.152f,
			0.483f,  0.596f,  0.789f,
			0.559f,  0.861f,  0.639f,
			0.195f,  0.548f,  0.859f,
			0.014f,  0.184f,  0.576f,
			0.771f,  0.328f,  0.970f,
			0.406f,  0.615f,  0.116f,
			0.676f,  0.977f,  0.133f,
			0.971f,  0.572f,  0.833f,
			0.140f,  0.616f,  0.489f,
			0.997f,  0.513f,  0.064f,
			0.945f,  0.719f,  0.592f,
			0.543f,  0.021f,  0.978f,
			0.279f,  0.317f,  0.505f,
			0.167f,  0.620f,  0.077f,
			0.347f,  0.857f,  0.137f,
			0.055f,  0.953f,  0.042f,
			0.714f,  0.505f,  0.345f,
			0.783f,  0.290f,  0.734f,
			0.722f,  0.645f,  0.174f,
			0.302f,  0.455f,  0.848f,
			0.225f,  0.587f,  0.040f,
			0.517f,  0.713f,  0.338f,
			0.053f,  0.959f,  0.120f,
			0.393f,  0.621f,  0.362f,
			0.673f,  0.211f,  0.457f,
			0.820f,  0.883f,  0.371f,
			0.982f,  0.099f,  0.879f
		};
		
		GLuint vertexbuffer;
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(vec3), &coordinates[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		GLuint colorbuffer;
		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vec3)));

		GLuint normalbuffer;
		glGenBuffers(1, &normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vec3)));

		ShaderSource ss = ParseShader("Basic.shader");
		program = CreateShader(ss.vertexSource, ss.fragmentSource);
		glUseProgram(program);

		camt.position = vec3(0,0,0);
		camt.rotation = EulerAngle(0,0,0);
		t.position = vec3(0,0,0);
		t.Scale(vec3(.5f,.5f,.5f));

		Projection = cam.Perspective(SCREEN_W / SCREEN_H);

		/*unsigned int lightID = glGetUniformLocation(program, "LightDirection");
		glUniform3f(lightID, 2,2,2);*/
		
		lastTime = (float)glfwGetTime();
	}

	void Update() {
		float deltaTime = (float)(glfwGetTime() - lastTime);
		lastTime = (float)glfwGetTime();
		//cout << "FPS : " << (1 / (deltaTime * 60)) << endl;
		double xpos = 0, ypos = 0;

		glfwGetCursorPos(window, &xpos, &ypos);
		bool l = false;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) l = true;
		if (l) this->locked = !this->locked;

		if (this->locked) {
			glfwSetCursorPos(window, SCREEN_W * 0.5f, SCREEN_H * 0.5f);
			EulerAngle euler(SCREEN_H/2 - ypos, 0, SCREEN_W / 2 - xpos);
			t.Rotate(euler * cam.mouse_speed * deltaTime);
		}

		float h = 0, w = 0;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) h = 1;
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) h = -1;
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) w = 1;
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) w = -1;
		vec3 move = (camt.forward() * h) + (camt.right() * w);
		t.Translate(move * -1 * cam.speed * deltaTime);
		cout << "/////////////////////////" << endl;
		cout << t.position << t.rotation << endl;

		View = camt.LookAt(camt.position - camt.forward(), camt.up());
		Model = t.PositionMatrix() * t.RotationMatrix() * t.ScaleMatrix();

		Matrix modelView = View * Model;
		unsigned int mvID = glGetUniformLocation(program, "MV");
		glUniformMatrix4fv(mvID, 1, GL_FALSE, &modelView.data[0]);
		Matrix modelViewProjection = Projection * modelView;
		unsigned int mvpID = glGetUniformLocation(program, "MVP");
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &modelViewProjection.data[0]);

		glDrawArrays(GL_TRIANGLES, 0, normals.size() * 6);
	}
	void End() {

		glDisableVertexAttribArray(0);
		glDeleteProgram(program);
		coordinates.clear();
		uvs.clear();
		normals.clear();
		this->~Program();
	}
};