#include <pch.h>

#include "window.h"

namespace graphics {

		void window_resize(GLFWwindow *window, int width, int height);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		Window::Window(const char *title, int width, int height)
			: m_Title(title), m_Width(width), m_Height(height)
		{
			if (!init())
				glfwTerminate();

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				LOG_ERROR("Failed to initialize GLFW!");
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			if (!m_Window)
			{
				LOG_ERROR("Failed to create GLFW window!");
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			glfwSwapInterval(0);

			if (glewInit() != GLEW_OK)
			{
				LOG_ERROR("Could not initialize GLEW!");
				return false;
			}

			LOG_INFO("OpenGL {0}", glGetString(GL_VERSION));
			return true;
		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
			{
				LOG_ERROR("Out of MAX_KEYS range!");
				return false;
			}

			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_BUTTONS)
			{
				LOG_ERROR("Out of MAX_BUTTONS range!");
				return false;
			}

			return m_MouseButtons[button];
		}

		void Window::getMousePosition(double& x, double& y) const
		{
			x = mx;
			y = my;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		void Window::update()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				LOG_ERROR("OpenGl error: {0}", error);

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}
		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void window_resize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}

}