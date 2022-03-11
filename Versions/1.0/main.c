/*#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

		// actual code
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f,-0.5f);
		glVertex2f(0.0f,0.5f);
		glVertex2f(0.5f,-0.5f);
		glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
*/
//#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void render(void)
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_TRIANGLES);
    {
        glColor3f(1.0,0.0,0.0);
        glVertex2f(0,.5);
        glColor3f(0.0,1.0,0.0);
        glVertex2f(-.5,-.5);
        glColor3f(1.0,0.0,1.0);
        glVertex2f(.5,-.5);
    }
    glEnd();
}

int main(int argc,const char * arg[])
{
    GLFWwindow *win;
    if(!glfwInit())
    {
        return -1;
    }
    win=glfwCreateWindow(640,400,"OpenGL Base Project",NULL,NULL);
    if(!win)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    if(!glewInit())
    {
        return -1;
    }
    
    glfwMakeContextCurrent(win);
    
    while(!glfwWindowShouldClose(win))
    {
        render();
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
    
    return 0;
}