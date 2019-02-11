#pragma once

#include "layer.h"
#include "../batchrenderer2d.h"
#include "maths\mat4.h"

namespace graphics {

	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader* shader);
		~TileLayer();
	};

}