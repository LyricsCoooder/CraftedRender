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

		Vertex();
		Vertex(float _x, float _y, float _z);
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
	public:
		std::vector<std::vector<float>> data;
		size_t rows, cols;

		Matrix(size_t rows, size_t cols);

		size_t getRows() const;

		size_t getCols() const;

		float& operator()(size_t row, size_t col);
		const  float& operator()(size_t row, size_t col) const;

		Matrix operator+(const Matrix& other) const;

		Matrix operator-(const Matrix& other) const;

		Matrix operator*(const Matrix& other) const;

		Matrix transpose() const;

		Matrix inverse() const;

		// identity
		static Matrix identity(size_t n);

		void Log() const;
	};

	// Transform in Model
	class Transform
	{
	public:
		float Translation[3];
		float Rotation[3]; // Euler angles: (Pitch, Yaw, Roll)
		float Scale[3];

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
	
	// Camera
	class Camera;

	// Model in Render
	class Model
	{
	public:
		Vertex Axis[3] = {
			Vertex(1, 0, 0),
			Vertex(0, 1, 0),
			Vertex(0, 0, 1)
		};

		std::vector<Vertex> Vertices;
		std::vector<Normal> Normals;
		std::vector<TexCoord> TexCoords;
		std::vector<VertexIndex> VertexIndexs;
		std::vector<NormalIndex> NormalIndexs;
		std::vector<TexCoordIndex> TexCoordIndexs;
		Matrix ModelMatrix = Matrix(4, 4);
		Transform Transform;
		Shader* ModelShader = nullptr;
		bool AxisIsShow = false;


		static Model readObj(std::string filename);

		void LogModel();
	};

	// VertexShaderOutput
	struct VertexShaderOutput
	{
		float VertexPosCVV[4];
	};

	// Base Shader
	class Shader
	{
	public:
		virtual ShaderType GetShaderType() = 0;
		virtual VertexShaderOutput VertexShader(Camera& Camera, Model& Model, int FaceIndex, int VertexIndex) = 0;
		virtual VertexShaderOutput VertexShader(Camera& Camera, Model& Model, Vertex Vertex) = 0;
		virtual void FragmentShader() = 0;
	};

	// WireFrame Mod Shader
	class WireFrameShader :public Common::Shader
	{
	public:
		ShaderType GetShaderType() override;

		VertexShaderOutput VertexShader(Camera& Camera, Model& Model, int FaceIndex, int VertexIndex) override;
		VertexShaderOutput VertexShader(Camera& Camera, Model& Model, Vertex Vertex);

		void FragmentShader() override;
	};

	// Camera

	class Camera
	{
	public:
		Matrix CameraMatrix = Matrix(4, 4);
		Matrix ViewMatrix = Matrix(4, 4);
		Matrix PerspectiveMatrix = Matrix(4, 4);
		Transform Transform;
		float Fov;
		float Ratio;
		float N;
		float F;

		Camera();
		Matrix SetPerspectiveMatrix();
		void UpdateCamera();
	};
}