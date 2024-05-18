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

		// Clean FrameBuffer
		void  ClearFrameBuffer();

		// AddToFrameBuffer
		void AddToFrameBuffer(Common::PixelColor APixel);

		void RenderLine(Common::PixelPos Start, Common::PixelPos End, Common::Color Color);

		void RenderTriangle(Common::PixelPos Pos0, Common::PixelPos Pos1, Common::PixelPos Pos2, Common::Color Color);

		void RenderModel(Common::Model& Model);

		GLuint CreateGradientTexture(unsigned char* data, int width, int height);

		// FinalRender
		void FinalRender();
	};
}