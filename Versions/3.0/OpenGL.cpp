#include "Main.h"

int main() {	
	Program program;
	if (!glfwInit()) return -1;
	
	program.window = glfwCreateWindow(SCREEN_W, SCREEN_H, "GAME", NULL, NULL);
	
	if (!program.window) { glfwTerminate(); return -1; }

	glfwMakeContextCurrent(program.window);

	if (glewInit() != GLEW_OK) cout << "Error" << endl;
	else cout << glGetString(GL_VERSION) << endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glCullFace(GL_FRONT);
	
	program.Start();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	while (!glfwWindowShouldClose(program.window))
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		program.Update();

		glfwSwapBuffers(program.window);

		glfwPollEvents();
	}
	glfwTerminate();

	program.End();

	return 0;
}