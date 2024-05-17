#pragma once

#include "vector"
#include "string"

namespace Common
{
	class Color
	{
	public:
		float R;
		float G;
		float B;
		float A;
	public:
		Color();
		Color(float R, float G, float B);
		Color(float R, float G, float B, float A);
		Color(float Color[4]);
	};

	class PixelPos
	{
	public:
		int X;
		int Y;
	public:
		PixelPos();
		PixelPos(int X, int Y);
		PixelPos(float Pos[2]);
	};

	class PixelColor
	{
	public:
		PixelPos Pos;
		Color Color;
	public:
		PixelColor();
		PixelColor(PixelPos Pos, Common::Color Color);
		PixelColor(int X, int Y, Common::Color Color);
	};

	struct Vertex 
	{
		float x, y, z;
	};

	struct Normal 
	{
		float x, y, z;
	};

	struct TexCoord 
	{
		float u, v;
	};

	class Model
	{
	public:
		std::vector<Vertex> Vertices;
		std::vector<Normal> Normals;
		std::vector<TexCoord> TexCoords;

		static Model readObj(std::string filename);
	};
}