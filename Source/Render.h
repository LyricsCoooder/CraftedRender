#pragma once


#include "CommonStructure.h"
#include "vector"
#include "set"
#include "imgui.h"
#include "GLFW/glfw3.h"

namespace Render
{
	class Renderer
	{
	private:
		// Render from FrameBuffer
		std::vector<Common::PixelColor> FrameBuffer;
		std::set<uint64_t> RenderedLines;
	public:
		int SenceHight;
		int SenceWidth;

		// Render Used Shader
		Common::WireFrameShader WireFrameShader;
		
		// Render Used Camera
		Common::Camera RenderCamera;

	public:
		// GetFrameBuffer
		std::vector<Common::PixelColor> GetFrameBuffer();

		// Clean FrameBuffer
		void  ClearFrameBuffer();

		// AddToFrameBuffer
		void AddToFrameBuffer(Common::PixelColor APixel);

		// Add line To FrameBuffer
		void RenderLine(Common::PixelPos Start, Common::PixelPos End, Common::Color Color);

		// Add Triangle To FrameBuffer
		void RenderTriangle(Common::PixelPos Pos0, Common::PixelPos Pos1, Common::PixelPos Pos2, Common::Color Color);

		// Add Model To FrameBuffer, Use Model Shader
		void RenderModel(Common::Model& Model);

		// RenderModelFace
		void RenderModelFace(Common::Model& Model, int& FaceIndex, Common::Color& Color);

		// Add Model Triangle
		void RenderModelTriangle(Common::Model& Model, int& FaceIndex, Common::PixelPos Pos0, Common::PixelPos Pos1, Common::PixelPos Pos2, Common::Color Color);

		// Divide by W
		Common::Vertex DivideW(Common::VertexShaderOutput& VertexShaderOutput);

		// NDCVertexToSecen
		Common::Vertex NDCVertexToSecen(Common::Vertex& NDCVertex, float& Deep);

		// BacksideRejected
		float Backside(Common::Vertex NDCVertexs[3]);

		// Redner Way is Render Texture in Gui
		GLuint CreateGradientTexture(unsigned char* data, int width, int height);

		// FinalRender
		void FinalRender();
	};
}