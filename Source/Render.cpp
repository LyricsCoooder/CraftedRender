#include "Render.h"
#include "iostream"
#include <algorithm> 

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
	if (APixel.Pos.X < 0 || APixel.Pos.Y < 0)
	{
		return;
	}
	if (APixel.Pos.X > SenceWidth || APixel.Pos.Y > SenceHight)
	{
		return;
	}
	this->FrameBuffer.push_back(APixel);
}

void Render::Renderer::RenderLine(Common::PixelPos Start, Common::PixelPos End, Common::Color Color)
{
	int x0 = Start.X;
	int	x1 = End.X;
	int y0 = Start.Y;
	int y1 = End.Y;
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
	if (!Model.ModelShader)
	{
		return;
	}

	int Size = (int) Model.VertexIndexs.size();
	for (int i = 0; i < Size; ++i)
	{
		Common::Vertex NDCVertexs[3];
		Common::Vertex SencePosList[3];
		for (int j = 0; j < 3; ++j)
		{
			Common::Vertex AimVertex = Model.Vertices[Model.VertexIndexs[i].Indexs[j]];
			Common::VertexShaderOutput VertexShaderOutput = Model.ModelShader->VertexShader(RenderCamera, Model, AimVertex);
			Common::Vertex NDCVertex;
			
			NDCVertex.x = VertexShaderOutput.VertexPosCVV[0] / VertexShaderOutput.VertexPosCVV[3];
			NDCVertex.y = VertexShaderOutput.VertexPosCVV[1] / VertexShaderOutput.VertexPosCVV[3];
			NDCVertex.z = VertexShaderOutput.VertexPosCVV[2] / VertexShaderOutput.VertexPosCVV[3];
			
			NDCVertexs[j] = NDCVertex;
			SencePosList[j].x = SenceWidth * (NDCVertex.y + 1) * 0.5;
			SencePosList[j].y = SenceHight * (1 - NDCVertex.z) * 0.5;
			SencePosList[j].z = VertexShaderOutput.VertexPosCVV[3];
		}
			
		bool IsIsBackside = Backside(NDCVertexs) >= 0;

		if (IsIsBackside)
		{
			Common::PixelPos Pos0(SencePosList[0].x, SencePosList[0].y);
			Common::PixelPos Pos1(SencePosList[1].x, SencePosList[1].y);
			Common::PixelPos Pos2(SencePosList[2].x, SencePosList[2].y);
			RenderTriangle(Pos0, Pos1, Pos2, Common::Color(1, 1, 1, 1));
		}

		if (Model.AxisIsShow)
		{
			Common::VertexShaderOutput Begin = Model.ModelShader->VertexShader(RenderCamera, Model, Common::Vertex(0, 0, 0));
			Common::Vertex NDCVertexBegin;
			NDCVertexBegin.x = Begin.VertexPosCVV[0] / Begin.VertexPosCVV[3];
			NDCVertexBegin.y = Begin.VertexPosCVV[1] / Begin.VertexPosCVV[3];
			NDCVertexBegin.z = Begin.VertexPosCVV[2] / Begin.VertexPosCVV[3];

			Common::Vertex BeginSencePos;
			BeginSencePos.x = SenceWidth * (NDCVertexBegin.y + 1) * 0.5;
			BeginSencePos.y = SenceHight * (1 - NDCVertexBegin.z) * 0.5;
			BeginSencePos.z = Begin.VertexPosCVV[3];

			Common::PixelPos B(BeginSencePos.x, BeginSencePos.y);

			for (int j = 0; j < 3; ++j)
			{
				Common::VertexShaderOutput End = Model.ModelShader->VertexShader(RenderCamera, Model, Model.Axis[j]);
				Common::Vertex NDCVertexEnd;
				NDCVertexEnd.x = End.VertexPosCVV[0] / End.VertexPosCVV[3];
				NDCVertexEnd.y = End.VertexPosCVV[1] / End.VertexPosCVV[3];
				NDCVertexEnd.z = End.VertexPosCVV[2] / End.VertexPosCVV[3];

				Common::Vertex EndSencePos;
				EndSencePos.x = SenceWidth * (NDCVertexEnd.y + 1) * 0.5;
				EndSencePos.y = SenceHight * (1 - NDCVertexEnd.z) * 0.5;
				EndSencePos.z = End.VertexPosCVV[3];

				Common::PixelPos E(EndSencePos.x, EndSencePos.y);

				RenderLine(B, E, Common::Color(Model.Axis[j].x, Model.Axis[j].y, Model.Axis[j].z));
			}

			
		}
	}
}

float Render::Renderer::Backside(Common::Vertex NDCVertexs[3])
{
	return NDCVertexs[0].y * NDCVertexs[2].z -
		   NDCVertexs[0].z * NDCVertexs[2].y +
		   NDCVertexs[0].z * NDCVertexs[1].y -
		   NDCVertexs[0].y * NDCVertexs[1].z +
		   NDCVertexs[2].y * NDCVertexs[1].z -
		   NDCVertexs[1].y * NDCVertexs[2].z;
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
	const int width = WindowSize.x - 15;
    const int height = WindowSize.y - 42;
    

	SenceHight = height;
	SenceWidth = width;
    ImVec2 ImageSize = ImVec2((float)width, (float)height);
	 
    int DataSize = height * width * 4;
    unsigned char* data = new unsigned char[DataSize] (); // RGBA格式
	for (int i = 3; i < DataSize; i = i + 4)
	{
		data[i] = 255;
	}
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
