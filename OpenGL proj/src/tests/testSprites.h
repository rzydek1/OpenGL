#pragma once

#include "Test.h"
#include "graphic\sprite.h"
#include "graphic\texture.h"
#include "graphic\layers\tilelayer.h"
#include "graphic\layers\group.h"

namespace test {

	class TestSprites :public Test
	{
	public:
		TestSprites();
		~TestSprites();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_TranslationX = 0, m_TranslationY = 0;
		graphics::TileLayer* m_Layer;
		graphics::Shader* m_Shader;
		graphics::Texture* m_Texture;
	};

}