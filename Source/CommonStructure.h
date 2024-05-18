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

	struct VertexIndex
	{
		int Indexs[3] = { 0 };
	public:
		VertexIndex(std::vector<int> Indexs);
	};

	struct NormalIndex
	{
		int Indexs[3] = { 0 };
	public:
		NormalIndex(std::vector<int> Indexs);
	};

	struct TexCoordIndex
	{
		int Indexs[3] = { 0 };
	public:
		TexCoordIndex(std::vector<int> Indexs);
	};

	class Model
	{
	public:
		std::vector<Vertex> Vertices;
		std::vector<Normal> Normals;
		std::vector<TexCoord> TexCoords;
		std::vector<VertexIndex> VertexIndexs;
		std::vector<NormalIndex> NormalIndexs;
		std::vector<TexCoordIndex> TexCoordIndexs;

		static Model readObj(std::string filename);

		void LogModel();
	};
}