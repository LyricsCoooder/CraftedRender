#pragma once

#include "vector"
#include "string"
#include "cmath"

namespace Common
{
	/*
	*	UI Part
	*/  
	// Point in Setting
	struct Point
	{
		float Pos[2] = { 0.0f };
		float Color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	// Line in Setting
	struct Line
	{
		float StartPos[2] = { 0.0f };
		float EndPos[2] = { 0.0f };
		float Color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	// Triangle in Setting
	struct Triangle
	{
		float Pos0[2] = { 0.0f };
		float Pos1[2] = { 0.0f };
		float Pos2[2] = { 0.0f };
		float Color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	/*
	*	Render Part
	*/
	
	// Color in Render
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

	// PixelPos in Render
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

	// PixelColor in Render, Used by FrameBuffer
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

	// Vertex in Model
	class Vertex
	{
	public:
		float x, y, z;
	};

	// Normal in Model
	class Normal
	{
	public:
		float x, y, z;
	};

	// TexCoord in Model
	class TexCoord
	{
	public:
		float u, v;
	};

	// VertexIndex in Model
	class VertexIndex
	{
	public:
		int Indexs[3] = { 0 };
	
		VertexIndex(std::vector<int> Indexs);
	};

	// NormalIndex in Model
	class NormalIndex
	{
	public:
		int Indexs[3] = { 0 };
	
		NormalIndex(std::vector<int> Indexs);
	};

	// TexCoordIndex in Model
	class TexCoordIndex
	{
	public:
		int Indexs[3] = { 0 };

		TexCoordIndex(std::vector<int> Indexs);
	};

	// Matrix in Model
	class Matrix
	{
	private:
		std::vector<std::vector<float>> data;
		size_t rows, cols;

	public:
		Matrix(size_t rows, size_t cols);

		size_t getRows() const;

		size_t getCols() const;

		// 重载()操作符用于元素访问
		float& operator()(size_t row, size_t col);
		const float& operator()(size_t row, size_t col) const;

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

	// Transform in Model
	class Transform 
	{
	public:
		float translation[3];
		float rotation[3]; // Euler angles: (Pitch, Yaw, Roll)
		float scale[3];

	public:
		Transform();

		Transform(float tx, float ty, float tz, float pitch, float yaw, float roll, float sx, float sy, float sz);

		Matrix toMatrix() const;

		static Transform fromMatrix(const Matrix& mat);

		void Log() const;
	};

	// ShaderType in Shader
	enum ShaderType
	{
		NONE = 0,
		WIREFRAME_SHADER
	};

	// Shader in Render
	class Shader;

	// Model in Render
	class Model
	{
	public:
		std::vector<Vertex> Vertices;
		std::vector<Normal> Normals;
		std::vector<TexCoord> TexCoords;
		std::vector<VertexIndex> VertexIndexs;
		std::vector<NormalIndex> NormalIndexs;
		std::vector<TexCoordIndex> TexCoordIndexs;
		Matrix ModelMatrix = Matrix(4, 4);
		Transform Transform;
		Shader* ModelShader;

		static Model readObj(std::string filename);

		void LogModel();
	};

	class Shader
	{
	public:
		virtual ShaderType GetShaderType();
		virtual void VertexShader(Model& Model);
		virtual void FragmentShader();
	};

	class WireFrameShader :public Common::Shader
	{
	public:
		ShaderType GetShaderType() override;

		void VertexShader(Model& Model) override;

		void FragmentShader() override;
	};
}