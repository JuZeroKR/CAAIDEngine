#include "ULveWindow.h"

namespace lve {
	ULveWindow::ULveWindow(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name }
	{
		InitWindow();
	}

	ULveWindow::~ULveWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void ULveWindow::InitWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);


	}

}
