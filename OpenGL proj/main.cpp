#include <pch.h>

#include "src/graphic\window.h"

#include "src/tests\TestClearColor.h"
#include "src/tests\testSprites.h"

#include "src/imGui\imgui.h"
#include "src/imGui\imgui_impl_glfw_gl3.h"

int main()
{
	using namespace graphics;
	using namespace maths;

	Log::Init();

	Window window("Sparky!", 960, 540);
	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window.getWindow(), true);
	ImGui::StyleColorsDark();

	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<test::TestClearColor>("Clear color");
	testMenu->RegisterTest<test::TestSprites>("Sprites");

	while (!window.closed())
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		window.clear();

		ImGui_ImplGlfwGL3_NewFrame();
		if (currentTest)
		{
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();
			ImGui::Begin("Test");
			if (currentTest != testMenu && ImGui::Button("<-"))
			{
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImGuiRender();
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}
	delete currentTest;
	if (currentTest != testMenu)
		delete testMenu;

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	return 0;

}
