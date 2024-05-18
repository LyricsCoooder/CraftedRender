#include "Render.h"

std::vector<Common::PixelColor> Render::Renderer::GetFrameBuffer()
{
	return FrameBuffer;
}

void Render::Renderer::ClearFrameBuffer()
{
	FrameBuffer.clear();
}

void Render::Renderer::AddToFrameBuffer(Common::PixelColor APixel)
{
	this->FrameBuffer.push_back(APixel);
}

void Render::Renderer::RenderLine(Common::PixelPos Start, Common::PixelPos End, Common::Color Color)
{
	int x0 = Start.X, x1 = End.X;
	int y0 = Start.Y, y1 = End.Y;
    bool KGreaterThanOne = abs(x0 - x1) < abs(y0 - y1);
	
	if (KGreaterThanOne)
	{
		std::swap<int>(x0, y0);
		std::swap<int>(x1, y1);
	}

	if (x0 > x1)
	{
		std::swap<int>(x0, x1);
		std::swap<int>(y0, y1);
	}

	int YStep;
	if (y0 < y1)
	{
		YStep = 1;
	}
	else
	{
		YStep = -1;
	}

	int Dy = abs(y1 - y0);
	int Dx = x1 - x0;
	int e = -1 * Dx;

	for (int index = x0; index <= x1; ++index)
	{
		if (KGreaterThanOne)
		{
			Common::PixelColor APixel(y0, index, Color);
			AddToFrameBuffer(APixel);
		}
		else
		{
			Common::PixelColor APixel(index, y0, Color);
			AddToFrameBuffer(APixel);
		}
		e += Dy * 2;
		if (e > 0)
		{
			y0 += YStep;
			e += -2 * Dx;
		}
	}
}

void Render::Renderer::RenderTriangle(Common::PixelPos Pos0, Common::PixelPos Pos1, Common::PixelPos Pos2, Common::Color Color)
{
	RenderLine(Pos0, Pos1, Color);
	RenderLine(Pos1, Pos2, Color);
	RenderLine(Pos0, Pos2, Color);
}

void Render::Renderer::RenderModel(Common::Model& Model)
{

}

GLuint Render::Renderer::CreateGradientTexture(unsigned char* data, int width, int height)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // 设置纹理参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureID;
}

void Render::Renderer::FinalRender()
{
	ImVec2 WindowSize = ImGui::GetWindowSize();
    const int height = (int) WindowSize.y - 42;
    const int width = (int) WindowSize.x - 16;
    ImVec2 ImageSize = ImVec2((float)width, (float)height);
	 
    int DataSize = height * width * 4;
    unsigned char* data = new unsigned char[DataSize] (); // RGBA格式

    // Render Pixel
    for (Common::PixelColor& APixel : FrameBuffer)
    {
        int x = APixel.Pos.X;
        int y = APixel.Pos.Y;
     
        if (x > width || y > height)
        {
            continue;
        }

        if ((y * width + x) * 4 + 3 < DataSize)
        {
            float r = APixel.Color.R;
            float g = APixel.Color.G;
            float b = APixel.Color.B;
            float a = APixel.Color.A;

            data[(y * width + x) * 4 + 0] = (unsigned char)(r * 255);
            data[(y * width + x) * 4 + 1] = (unsigned char)(g * 255);
            data[(y * width + x) * 4 + 2] = (unsigned char)(b * 255);
            data[(y * width + x) * 4 + 3] = (unsigned char)(a * 255);
        }
    }

	ImGui::Image((void*)(intptr_t)CreateGradientTexture(data, width, height), ImageSize);

    delete[] data;
}
