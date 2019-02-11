#include <pch.h>

#include "testSprites.h"

#include "imGui\imgui.h"
#include "imGui\imgui_impl_glfw_gl3.h"

namespace test {

	TestSprites::TestSprites()
	{
		m_Shader = new graphics::Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
		m_Shader->enable();

		m_Layer = new graphics::TileLayer(m_Shader);

		glActiveTexture(GL_TEXTURE0);
		m_Texture = new graphics::Texture("src/test.bmp");
		m_Texture->bind();

		m_Shader->setUniform1i("tex", 2);
		m_Shader->setUniformMat4("pr_matrix", maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
		m_Shader->setUniform2f("light_pos", maths::vec2(m_TranslationX, m_TranslationY));

		for (float y = -9.0f; y < 9.0f; y += 0.5f)
		{
			for (float x = -16.0f; x < 16.0f; x += 0.5f)
			{
				m_Layer->add(new graphics::Sprite(x, y, 0.4f, 0.4f, maths::vec4(1, 1, 1, 1)));
			}
		}
	}

	TestSprites::~TestSprites()
	{
		delete m_Layer;
		delete m_Texture;
	}

	void TestSprites::OnUpdate(float deltaTime)
	{
	}

	void TestSprites::OnRender()
	{
		m_Layer->render();
	}

	void TestSprites::OnImGuiRender()
	{
		ImGui::SliderFloat("Translation X", &m_TranslationX, 0.0f, 960.0f);
		ImGui::SliderFloat("Translation Y", &m_TranslationY, 0.0f, 540.0f);
		m_Shader->setUniform2f("light_pos", maths::vec2((float)(m_TranslationX * 32.0f / 960.0f - 16.0f), (float)(9.0f - m_TranslationY * 18.0f / 540.0f)));
	}

}