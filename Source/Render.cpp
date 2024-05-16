#include "Render.h"

std::vector<Common::PixelColor> Render::Renderer::GetFrameBuffer()
{
	return FrameBuffer;
}

void Render::Renderer::AddToFrameBuffer(Common::PixelColor APixel)
{
	this->FrameBuffer.push_back(APixel);
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
    const int height = (int) WindowSize.y - 35;
    const int width = (int) WindowSize.x;
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
