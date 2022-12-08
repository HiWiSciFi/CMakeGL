#include "Core.hpp"
#include <Junia/Core/Window.hpp>

#include <iostream>

namespace Junia
{
	std::vector<Window*> Window::windows{ nullptr };

	int Window::GetWindowCount()
	{
		return windows.size() - 1;
	}

	Window** Window::GetWindows()
	{
		return windows.data();
	}

	Window* Window::GetWindow(int id)
	{
		return windows.at(id);
	}

	Window* Window::CreateWindow()
	{
		return new Window();
	}

	void Window::DestroyWindow(int id)
	{
		DestroyWindow(GetWindow(id));
	}

	void Window::DestroyWindow(Window* window)
	{
		delete window;
	}

	Window::Window()
	{
		index = -1;
		window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
		if (!window)
		{
			const char* msg;
			glfwGetError(&msg);
			std::cerr << "Window could not be created!" << std::endl << msg << std::endl;
			return;
		}
		glfwSetKeyCallback(window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
					glfwSetWindowShouldClose(window, GLFW_TRUE);
				});
		index = windows.size();
		windows.push_back(this);
		if (windows[0] == nullptr) windows[0] = this;
	}

	Window::~Window()
	{
		int lastIndex = GetWindowCount();
		if (lastIndex != index)
		{
			windows[index] = windows[lastIndex];
			windows[index]->index = index;
		}
		windows.pop_back();
		glfwDestroyWindow(window);
	}

	int Window::GetID()
	{
		return index;
	}

	void Window::Update()
	{
		if (glfwWindowShouldClose(window))
		{
			shouldClose = true;
			return;
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
