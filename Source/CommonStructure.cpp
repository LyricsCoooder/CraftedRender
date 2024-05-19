#include "CommonStructure.h"
#include <fstream>
#include <sstream>
#include <iostream>

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
	while (std::getline(file, line)) 
	{
		std::istringstream ss(line);
		std::string prefix;
		ss >> prefix;

		if (prefix == "v") 
		{
			Vertex vertex;
			ss >> vertex.x >> vertex.y >> vertex.z;
			AnsModel.Vertices.push_back(vertex);
		}
		else if (prefix == "vn") 
		{
			Normal normal;
			ss >> normal.x >> normal.y >> normal.z;
			AnsModel.Normals.push_back(normal);
		}
		else if (prefix == "vt") 
		{
			TexCoord texCoord;
			ss >> texCoord.u >> texCoord.v;
			AnsModel.TexCoords.push_back(texCoord);
		}
		else if (prefix == "f")
		{
			std::string indexStr;
			std::vector<int> TempVertexIndex;
			std::vector<int> TempNormalIndex;
			std::vector<int> TempTexCoordIndex;
			int size = 0;
			while (ss >> indexStr)
			{
				std::istringstream indexStream(indexStr);
				std::string index;
				std::getline(indexStream, index, '/');
				int vertexIndex = std::stoi(index);

				std::getline(indexStream, index, '/');
				int texCoordIndex = std::stoi(index);

				std::getline(indexStream, index);
				int normalIndex = std::stoi(index);

				TempVertexIndex.push_back(vertexIndex);
				TempNormalIndex.push_back(normalIndex);
				TempTexCoordIndex.push_back(texCoordIndex);

				std::cout << "VTN:" << vertexIndex << ", " << texCoordIndex << ", " << normalIndex << std::endl;
				size++;
			}
			

			if (size > 3)
			{
				for (int i = 1; i < size - 1; ++i)
				{
					AnsModel.VertexIndexs.push_back(VertexIndex({ TempVertexIndex[0], TempVertexIndex[i], TempVertexIndex[i + 1] }));
					AnsModel.TexCoordIndexs.push_back(TexCoordIndex({ TempTexCoordIndex[0], TempTexCoordIndex[i], TempTexCoordIndex[i + 1] }));
					AnsModel.NormalIndexs.push_back(NormalIndex({ TempNormalIndex[0], TempNormalIndex[i], TempNormalIndex[i + 1] }));
				}
			}
			else
			{
				AnsModel.VertexIndexs.push_back(VertexIndex(TempVertexIndex));
				AnsModel.TexCoordIndexs.push_back(TexCoordIndex(TempTexCoordIndex));
				AnsModel.NormalIndexs.push_back(NormalIndex(TempNormalIndex));
			}
			std::cout << "-----------------------------------" << std::endl;
		}

	}

	file.close();

	return AnsModel;
}

 void Common::Model::LogModel()
 {
	 std::cout << "Vertices:" << std::endl;
	 for (Vertex Vertice : Vertices)
	 {
		 std::cout << Vertice.x << " " << Vertice.y << " " << Vertice.z << std::endl;
	 }

	 std::cout << "Normals:" << std::endl;
	 for (Normal Normal : Normals)
	 {
		 std::cout << Normal.x << " " << Normal.y << " " << Normal.z << std::endl;
	 }

	 std::cout << "TexCoords:" << std::endl;
	 for (TexCoord TexCoord : TexCoords)
	 {
		 std::cout << TexCoord.u << " " << TexCoord.v << std::endl;
	 }
	 
	 std::cout << "VertexIndexs:" << std::endl;
	 for (VertexIndex temp : VertexIndexs)
	 {
		 std::cout << temp.Indexs[0] << " " << temp.Indexs[1] << " " << temp.Indexs[2] << std::endl;
	 }

	 std::cout << "NormalIndexs:" << std::endl;
	 for (NormalIndex temp : NormalIndexs)
	 {
		 std::cout << temp.Indexs[0] << " " << temp.Indexs[1] << " " << temp.Indexs[2] << std::endl;
	 }

	 std::cout << "TexCoordIndexs:" << std::endl;
	 for (TexCoordIndex temp : TexCoordIndexs)
	 {
		 std::cout << temp.Indexs[0] << " " << temp.Indexs[1] << " " << temp.Indexs[2] << std::endl;
	 }

	 std::cout << "ModelMatrix:" << std::endl;
	 ModelMatrix.Log();

	 std::cout << "ShaderType: ";
	 if (ModelShader)
	 {
		 std::cout << ModelShader->GetShaderType() << std::endl;
	 }
	 else
	 {
		 std::cout << 0 << std::endl;
	 }
 }

 Common::VertexIndex::VertexIndex(std::vector<int> Indexs)
 {
	 this->Indexs[0] = Indexs[0];
	 this->Indexs[1] = Indexs[1];
	 this->Indexs[2] = Indexs[2];
 }

 Common::NormalIndex::NormalIndex(std::vector<int> Indexs)
 {
	 this->Indexs[0] = Indexs[0];
	 this->Indexs[1] = Indexs[1];
	 this->Indexs[2] = Indexs[2];
 }

 Common::TexCoordIndex::TexCoordIndex(std::vector<int> Indexs)
 {
	 this->Indexs[0] = Indexs[0];
	 this->Indexs[1] = Indexs[1];
	 this->Indexs[2] = Indexs[2];
 }

 Common::Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
 {
	 data.resize(rows, std::vector<float>(cols, 0.0));
 }

 size_t Common::Matrix::getRows() const
 {
	 return rows;
 }

 size_t Common::Matrix::getCols() const
 {
	 return cols;
 }

 float& Common::Matrix::operator()(size_t row, size_t col)
 {
	 if (row >= rows || col >= cols) 
	 {
		 throw std::out_of_range("Index out of bounds");
	 }
	 return data[row][col];
 }

 const float& Common::Matrix::operator()(size_t row, size_t col) const
 {
	 if (row >= rows || col >= cols)
	 {
		 throw std::out_of_range("Index out of bounds");
	 }
	 return data[row][col];
 }

 Common::Matrix Common::Matrix::operator+(const Matrix& other) const
 {
	 if (rows != other.rows || cols != other.cols)
	 {
		 throw std::invalid_argument("Matrix dimensions must match for addition");
	 }

	 Matrix result(rows, cols);
	 for (size_t i = 0; i < rows; ++i) 
	 {
		 for (size_t j = 0; j < cols; ++j) 
		 {
			 result(i, j) = data[i][j] + other(i, j);
		 }
	 }
	 return result;
 }

 Common::Matrix Common::Matrix::operator-(const Matrix& other) const
 {
	 if (rows != other.rows || cols != other.cols) 
	 {
		 throw std::invalid_argument("Matrix dimensions must match for subtraction");
	 }

	 Matrix result(rows, cols);
	 for (size_t i = 0; i < rows; ++i) 
	 {
		 for (size_t j = 0; j < cols; ++j)
		 {
			 result(i, j) = data[i][j] - other(i, j);
		 }
	 }
	 return result;
 }

 Common::Matrix Common::Matrix::operator*(const Matrix& other) const
 {
	 if (cols != other.rows) 
	 {
		 throw std::invalid_argument("Matrix dimensions must match for multiplication");
	 }

	 Matrix result(rows, other.cols);
	 for (size_t i = 0; i < rows; ++i) 
	 {
		 for (size_t j = 0; j < other.cols; ++j)
		 {
			 for (size_t k = 0; k < cols; ++k) 
			 {
				 result(i, j) += data[i][k] * other(k, j);
			 }
		 }
	 }
	 return result;
 }

 Common::Matrix Common::Matrix::transpose() const
 {
	Matrix result(cols, rows);
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			result(j, i) = data[i][j];
		}
	}
	return result;
 }

 void Common::Matrix::Log() const
 {
	 for (size_t i = 0; i < rows; ++i) 
	 {
		 for (size_t j = 0; j < cols; ++j) 
		 {
			 if (data[i][j] == -0)
			 {
				 std::cout << 0 << " ";
				 continue;
			 }
			 std::cout << data[i][j] << " ";
		 }
		 std::cout << std::endl;
	 }
 }

 Common::ShaderType Common::Shader::GetShaderType()
 {
	 return Common::ShaderType::NONE;
 }

 void Common::Shader::VertexShader(Model& Model)
 {

 }

 void Common::Shader::FragmentShader()
 {

 }

 Common::ShaderType Common::WireFrameShader::GetShaderType()
 {
	 return Common::ShaderType::WIREFRAME_SHADER;
 }

 void Common::WireFrameShader::VertexShader(Model& Model)
 {

 }

 void Common::WireFrameShader::FragmentShader()
 {

 }

 Common::Transform::Transform()
 {
	 translation[0] = translation[1] = translation[2] = 0.0;
	 rotation[0] = rotation[1] = rotation[2] = 0.0;
	 scale[0] = scale[1] = scale[2] = 1.0;
 }

 Common::Transform::Transform(float tx, float ty, float tz, float pitch, float yaw, float roll, float sx, float sy, float sz)
 {
	 translation[0] = tx;
	 translation[1] = ty;
	 translation[2] = tz;
	 rotation[0] = pitch;
	 rotation[1] = yaw;
	 rotation[2] = roll;
	 scale[0] = sx;
	 scale[1] = sy;
	 scale[2] = sz;
 }

Common::Matrix Common::Transform::toMatrix() const
 {
	const double PI = 3.14159265358979323846;

	const double DEG_TO_RAD = PI / 180.0;
	const double RADS_DIVIDED_BY_2 = DEG_TO_RAD / 2.0;

	double PitchNoWinding = fmod(rotation[1], 360.0);
	double YawNoWinding = fmod(rotation[2], 360.0);
	double RollNoWinding = fmod(rotation[0], 360.0);

	double SP = sin(PitchNoWinding * RADS_DIVIDED_BY_2);
	double CP = cos(PitchNoWinding * RADS_DIVIDED_BY_2);
	double SY = sin(YawNoWinding * RADS_DIVIDED_BY_2);
	double CY = cos(YawNoWinding * RADS_DIVIDED_BY_2);
	double SR = sin(RollNoWinding * RADS_DIVIDED_BY_2);
	double CR = cos(RollNoWinding * RADS_DIVIDED_BY_2);

	float W = CR * CP * CY + SR * SP * SY;
	float X = CR * SP * SY - SR * CP * CY;
	float Y = -CR * SP * CY - SR * CP * SY;
	float Z = CR * CP * SY - SR * SP * CY;

	float yy2 = Y * Y * 2;
	float zz2 = Z * Z * 2;
	float xy2 = X * Y * 2;
	float wz2 = W * Z * 2;
	float xz2 = X * Z * 2;
	float wy2 = W * Y * 2;
	float yz2 = Y * Z * 2;
	float wx2 = W * X * 2;
	float xx2 = X * X * 2;

	Matrix result(4, 4);

	result(0, 0) = (1.0f - (yy2 + zz2)) * scale[0];
	result(0, 1) = (xy2 + wz2) * scale[0];
	result(0, 2) = (xz2 - wy2) * scale[0];
	result(0, 3) = 0.0f;

	result(1, 0) = (xy2 - wz2) * scale[1];
	result(1, 1) = (1.0f - (xx2 + zz2)) * scale[1];
	result(1, 2) = (yz2 + wx2) * scale[1];
	result(1, 3) = 0.0f;

	result(2, 0) = (xz2 + wy2) * scale[2];
	result(2, 1) = (yz2 - wx2) * scale[2];
	result(2, 2) = (1.0f - (xx2 + yy2)) * scale[2];
	result(2, 3) = 0.0f;


	result(3, 0) = translation[0];
	result(3, 1) = translation[1];
	result(3, 2) = translation[2];
	result(3, 3) = 1.0f;

	return result;
 }

Common::Transform Common::Transform::fromMatrix(const Matrix& mat)
{
	if (mat.getRows() != 4 || mat.getCols() != 4) {
		throw std::invalid_argument("Matrix must be 4x4.");
	}

	Transform transform;

	// 提取平移
	transform.translation[0] = mat(0, 3);
	transform.translation[1] = mat(1, 3);
	transform.translation[2] = mat(2, 3);

	// 提取缩放
	transform.scale[0] = std::sqrt(mat(0, 0) * mat(0, 0) + mat(0, 1) * mat(0, 1) + mat(0, 2) * mat(0, 2));
	transform.scale[1] = std::sqrt(mat(1, 0) * mat(1, 0) + mat(1, 1) * mat(1, 1) + mat(1, 2) * mat(1, 2));
	transform.scale[2] = std::sqrt(mat(2, 0) * mat(2, 0) + mat(2, 1) * mat(2, 1) + mat(2, 2) * mat(2, 2));

	// 提取旋转矩阵（缩放除以）
	Matrix rotationMatrix(3, 3);
	rotationMatrix(0, 0) = mat(0, 0) / transform.scale[0];
	rotationMatrix(0, 1) = mat(0, 1) / transform.scale[0];
	rotationMatrix(0, 2) = mat(0, 2) / transform.scale[0];
	rotationMatrix(1, 0) = mat(1, 0) / transform.scale[1];
	rotationMatrix(1, 1) = mat(1, 1) / transform.scale[1];
	rotationMatrix(1, 2) = mat(1, 2) / transform.scale[1];
	rotationMatrix(2, 0) = mat(2, 0) / transform.scale[2];
	rotationMatrix(2, 1) = mat(2, 1) / transform.scale[2];
	rotationMatrix(2, 2) = mat(2, 2) / transform.scale[2];

	// 提取欧拉角
	transform.rotation[1] = std::asin(-rotationMatrix(0, 2));
	if (std::cos(transform.rotation[1]) != 0) {
		transform.rotation[0] = std::atan2(rotationMatrix(1, 2), rotationMatrix(2, 2));
		transform.rotation[2] = std::atan2(rotationMatrix(0, 1), rotationMatrix(0, 0));
	}
	else {
		transform.rotation[0] = std::atan2(-rotationMatrix(2, 0), rotationMatrix(1, 1));
		transform.rotation[2] = 0;
	}

	return transform;
}

void Common::Transform::Log() const
{
	std::cout << "Translation: (" << translation[0] << ", " << translation[1] << ", " << translation[2] << ")\n";
	std::cout << "Rotation: (" << rotation[0] << ", " << rotation[1] << ", " << rotation[2] << ")\n";
	std::cout << "Scale: (" << scale[0] << ", " << scale[1] << ", " << scale[2] << ")\n";
}
