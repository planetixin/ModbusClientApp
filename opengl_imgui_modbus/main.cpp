#include "includes.h"
#include "Gui.h"


int main()
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(1000, 700, "Modbus Connnection", NULL, NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	Gui gui = Gui(window);
	

	while (!glfwWindowShouldClose(window))
	{
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		gui.Update(1.0f);


		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}