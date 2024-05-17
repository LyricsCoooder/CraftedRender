#include "CommonStructure.h"
#include <fstream>
#include <sstream>

Common::Color::Color()
{
	this->R = 0.0f;
	this->G = 0.0f;
	this->B = 0.0f;
	this->A = 1.0f;
}

Common::Color::Color(float R, float G, float B)
{
	this->R = R;
	this->G = G;
	this->B = B;
	this->A = 1.0f;
}


Common::Color::Color(float R, float G, float B, float A)
{
	this->R = R;
	this->G = G;
	this->B = B;
	this->A = A;
}

Common::Color::Color(float Color[4])
{
	this->R = Color[0];
	this->G = Color[1];
	this->B = Color[2];
	this->A = Color[3];
}

Common::PixelPos::PixelPos()
{
	this->X = 0.0f;
	this->Y = 0.0f;
}

Common::PixelPos::PixelPos(int X, int Y)
{
	this->X = X;
	this->Y = Y;
}

Common::PixelPos::PixelPos(float Pos[2])
{
	this->X = (int) Pos[0];
	this->Y = (int) Pos[1];
}

Common::PixelColor::PixelColor()
{
	this->Pos = PixelPos();
	this->Color = Common::Color();
}

Common::PixelColor::PixelColor(PixelPos Pos, Common::Color Color)
{
	this->Pos = Pos;
	this->Color = Color;
}

Common::PixelColor::PixelColor(int X, int Y, Common::Color Color)
{
	this->Pos = PixelPos(X, Y);
	this->Color = Color;
}

 Common::Model Common::Model::readObj(std::string filename)
{
	Model AnsModel;

	std::ifstream file(filename);

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::string prefix;
		ss >> prefix;

		if (prefix == "v") {
			Vertex vertex;
			ss >> vertex.x >> vertex.y >> vertex.z;
			AnsModel.Vertices.push_back(vertex);
		}
		else if (prefix == "vn") {
			Normal normal;
			ss >> normal.x >> normal.y >> normal.z;
			AnsModel.Normals.push_back(normal);
		}
		else if (prefix == "vt") {
			TexCoord texCoord;
			ss >> texCoord.u >> texCoord.v;
			AnsModel.TexCoords.push_back(texCoord);
		}
	}

	file.close();

	return AnsModel;
}
