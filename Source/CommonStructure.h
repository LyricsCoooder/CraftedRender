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

	class Vertex
	{
	public:
		float x, y, z;
	};

	class Normal
	{
	public:
		float x, y, z;
	};

	class TexCoord
	{
	public:
		float u, v;
	};

	class VertexIndex
	{
	public:
		int Indexs[3] = { 0 };
	
		VertexIndex(std::vector<int> Indexs);
	};

	class NormalIndex
	{
	public:
		int Indexs[3] = { 0 };
	
		NormalIndex(std::vector<int> Indexs);
	};

	class TexCoordIndex
	{
	public:
		int Indexs[3] = { 0 };

		TexCoordIndex(std::vector<int> Indexs);
	};

	class Matrix {
	private:
		std::vector<std::vector<double>> data;
		size_t rows, cols;

	public:
		Matrix(size_t rows, size_t cols);

		size_t getRows() const;

		size_t getCols() const;

		// 重载()操作符用于元素访问
		double& operator()(size_t row, size_t col);
		const double& operator()(size_t row, size_t col) const;

		// 矩阵加法
		Matrix operator+(const Matrix& other) const;

		// 矩阵减法
		Matrix operator-(const Matrix& other) const;

		// 矩阵乘法
		Matrix operator*(const Matrix& other) const;

		// 矩阵转置
		Matrix transpose() const;

		// 输出矩阵
		void Log() const;
	};

	enum ShaderType
	{
		NONE = 0,
		WIREFRAME_SHADER
	};

	class Shader
	{
	public:
		virtual ShaderType GetShaderType() = 0;
		virtual void VertexShader() = 0;
		virtual void FragmentShader() = 0;
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
		Matrix ModelMatrix = Matrix(3, 4);

		static Model readObj(std::string filename);

		void LogModel();
	};
}