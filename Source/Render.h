#pragma once


#include "CommonStructure.h"
#include "vector"
#include "imgui.h"
#include "GLFW/glfw3.h"

namespace Render
{
	class Renderer
	{
	private:
		std::vector<Common::PixelColor> FrameBuffer;

	public:
		// GetFrameBuffer
		std::vector<Common::PixelColor> GetFrameBuffer();

		// AddToFrameBuffer
		void AddToFrameBuffer(Common::PixelColor APixel);

		GLuint CreateGradientTexture(unsigned char* data, int width, int height);

		// FinalRender
		void FinalRender();
	};
}