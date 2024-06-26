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
	this->X = 0;
	this->Y = 0;
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
			// x -> y y -> z z -> x
			ss >> vertex.y >> vertex.z >> vertex.x;
			AnsModel.Vertices.push_back(vertex);
		}
		else if (prefix == "vn") 
		{
			Normal normal;
			// x -> y y -> z z -> x
			ss >> normal.y >> normal.z >> normal.x;
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
				int vertexIndex = std::stoi(index) - 1;

				std::getline(indexStream, index, '/');
				int texCoordIndex = std::stoi(index) - 1;

				std::getline(indexStream, index);
				int normalIndex = std::stoi(index) - 1;

				TempVertexIndex.push_back(vertexIndex);
				TempNormalIndex.push_back(normalIndex);
				TempTexCoordIndex.push_back(texCoordIndex);

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

 Common::Matrix Common::Matrix::inverse() const
 {
	 if (rows != cols) {
		 throw std::invalid_argument("Matrix must be square to compute its inverse.");
	 }

	 size_t n = rows;
	 Matrix augmented(n, 2 * n);

	 // 构造增广矩阵 [A | I]
	 for (size_t i = 0; i < n; ++i) {
		 for (size_t j = 0; j < n; ++j) {
			 augmented(i, j) = data[i][j];
			 augmented(i, n + j) = (i == j) ? 1.0f : 0.0f;
		 }
	 }

	 // 进行高斯-约旦消去
	 for (int i = 0; i < n; ++i) 
	 {
		 double maxEl = abs(augmented.data[i][i]);
		 int maxRow = i;
		 for (int k = i + 1; k < n; ++k) 
		 {
			 if (abs(augmented.data[k][i]) > maxEl) 
			 {
				 maxEl = abs(augmented.data[k][i]);
				 maxRow = k;
			 }
		 }
		 for (int k = 0; k < 2 * n; ++k) 
		 {
			 std::swap(augmented.data[maxRow][k], augmented.data[i][k]);
		 }
		 double diagEl = augmented.data[i][i];

		 for (int k = 0; k < 2 * n; ++k) 
		 {
			 augmented.data[i][k] /= (float) diagEl;
		 }
		 for (int k = 0; k < n; ++k) 
		 {
			 if (k != i) {
				 double factor = augmented.data[k][i];
				 for (int j = 0; j < 2 * n; ++j) {
					 augmented.data[k][j] -= (float) factor * augmented.data[i][j];
				 }
			 }
		 }

	 }

	 // 提取逆矩阵
	 Matrix inverse(n, n);
	 for (size_t i = 0; i < n; ++i) {
		 for (size_t j = 0; j < n; ++j) {
			 inverse(i, j) = augmented(i, n + j);
		 }
	 }

	 return inverse;
 }

 Common::Matrix Common::Matrix::identity(size_t n)
 {
	 Matrix I(n, n);
	 for (size_t i = 0; i < n; ++i) {
		 I(i, i) = 1.0f;
	 }
	 return I;
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

 void Common::Shader::FragmentShader()
 {

 }

 Common::ShaderType Common::WireFrameShader::GetShaderType()
 {
	 return Common::ShaderType::WIREFRAME_SHADER;
 }

 Common::VertexShaderOutput Common::WireFrameShader::VertexShader(Camera& Camera, Model& Model, int FaceIndex, int VertexIndex)
 {
	 Common::VertexShaderOutput Result;
	 Vertex AimVertex = Model.Vertices[Model.VertexIndexs[FaceIndex].Indexs[VertexIndex]];

	 Matrix Pos(1, 4);
	 Pos(0, 0) = AimVertex.x;
	 Pos(0, 1) = AimVertex.y;
	 Pos(0, 2) = AimVertex.z;
	 Pos(0, 3) = 1.0f;
	 Common::Matrix MVP = Model.ModelMatrix * Camera.ViewMatrix * Camera.PerspectiveMatrix;
	 Matrix ResultMatrix = Pos * MVP;
	 Result.VertexPosCVV[0] = ResultMatrix(0, 0);
	 Result.VertexPosCVV[1] = ResultMatrix(0, 1);
	 Result.VertexPosCVV[2] = ResultMatrix(0, 2);
	 Result.VertexPosCVV[3] = ResultMatrix(0, 3);
	 return Result;
 }
 Common::VertexShaderOutput Common::WireFrameShader::VertexShader(Camera& Camera, Model& Model, Vertex Vertex)
 {
	 Common::VertexShaderOutput Result;
	 Matrix Pos(1, 4);
	 Pos(0, 0) = Vertex.x;
	 Pos(0, 1) = Vertex.y;
	 Pos(0, 2) = Vertex.z;
	 Pos(0, 3) = 1.0f;
	 Common::Matrix MVP = Model.ModelMatrix * Camera.ViewMatrix * Camera.PerspectiveMatrix;
	 Matrix ResultMatrix = Pos * MVP;
	 Result.VertexPosCVV[0] = ResultMatrix(0, 0);
	 Result.VertexPosCVV[1] = ResultMatrix(0, 1);
	 Result.VertexPosCVV[2] = ResultMatrix(0, 2);
	 Result.VertexPosCVV[3] = ResultMatrix(0, 3);
	 return Result;
 }

 void Common::WireFrameShader::FragmentShader()
 {

 }

 Common::Transform::Transform()
 {
	 Translation[0] = Translation[1] = Translation[2] = 0.0;
	 Rotation[0] = Rotation[1] = Rotation[2] = 0.0;
	 Scale[0] = Scale[1] = Scale[2] = 1.0;
 }

 Common::Transform::Transform(float tx, float ty, float tz, float pitch, float yaw, float roll, float sx, float sy, float sz)
 {
	 Translation[0] = tx;
	 Translation[1] = ty;
	 Translation[2] = tz;
	 Rotation[0] = pitch;
	 Rotation[1] = yaw;
	 Rotation[2] = roll;
	 Scale[0] = sx;
	 Scale[1] = sy;
	 Scale[2] = sz;
 }

Common::Matrix Common::Transform::toMatrix() const
 {
	const double PI = 3.14159265358979323846;

	const double DEG_TO_RAD = PI / 180.0;
	const double RADS_DIVIDED_BY_2 = DEG_TO_RAD / 2.0;

	double PitchNoWinding = fmod(Rotation[1], 360.0);
	double YawNoWinding = fmod(Rotation[2], 360.0);
	double RollNoWinding = fmod(Rotation[0], 360.0);

	double SP = sin(PitchNoWinding * RADS_DIVIDED_BY_2);
	double CP = cos(PitchNoWinding * RADS_DIVIDED_BY_2);
	double SY = sin(YawNoWinding * RADS_DIVIDED_BY_2);
	double CY = cos(YawNoWinding * RADS_DIVIDED_BY_2);
	double SR = sin(RollNoWinding * RADS_DIVIDED_BY_2);
	double CR = cos(RollNoWinding * RADS_DIVIDED_BY_2);

	float W = float (CR * CP * CY + SR * SP * SY);
	float X = float (CR * SP * SY - SR * CP * CY);
	float Y = float (-CR * SP * CY - SR * CP * SY);
	float Z = float (CR * CP * SY - SR * SP * CY);

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

	result(0, 0) = (1.0f - (yy2 + zz2)) * Scale[0];
	result(0, 1) = (xy2 + wz2) * Scale[0];
	result(0, 2) = (xz2 - wy2) * Scale[0];
	result(0, 3) = 0.0f;

	result(1, 0) = (xy2 - wz2) * Scale[1];
	result(1, 1) = (1.0f - (xx2 + zz2)) * Scale[1];
	result(1, 2) = (yz2 + wx2) * Scale[1];
	result(1, 3) = 0.0f;

	result(2, 0) = (xz2 + wy2) * Scale[2];
	result(2, 1) = (yz2 - wx2) * Scale[2];
	result(2, 2) = (1.0f - (xx2 + yy2)) * Scale[2];
	result(2, 3) = 0.0f;


	result(3, 0) = Translation[0];
	result(3, 1) = Translation[1];
	result(3, 2) = Translation[2];
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
	transform.Translation[0] = mat(0, 3);
	transform.Translation[1] = mat(1, 3);
	transform.Translation[2] = mat(2, 3);

	// 提取缩放
	transform.Scale[0] = std::sqrt(mat(0, 0) * mat(0, 0) + mat(0, 1) * mat(0, 1) + mat(0, 2) * mat(0, 2));
	transform.Scale[1] = std::sqrt(mat(1, 0) * mat(1, 0) + mat(1, 1) * mat(1, 1) + mat(1, 2) * mat(1, 2));
	transform.Scale[2] = std::sqrt(mat(2, 0) * mat(2, 0) + mat(2, 1) * mat(2, 1) + mat(2, 2) * mat(2, 2));

	// 提取旋转矩阵（缩放除以）
	Matrix rotationMatrix(3, 3);
	rotationMatrix(0, 0) = mat(0, 0) / transform.Scale[0];
	rotationMatrix(0, 1) = mat(0, 1) / transform.Scale[0];
	rotationMatrix(0, 2) = mat(0, 2) / transform.Scale[0];
	rotationMatrix(1, 0) = mat(1, 0) / transform.Scale[1];
	rotationMatrix(1, 1) = mat(1, 1) / transform.Scale[1];
	rotationMatrix(1, 2) = mat(1, 2) / transform.Scale[1];
	rotationMatrix(2, 0) = mat(2, 0) / transform.Scale[2];
	rotationMatrix(2, 1) = mat(2, 1) / transform.Scale[2];
	rotationMatrix(2, 2) = mat(2, 2) / transform.Scale[2];

	// 提取欧拉角
	transform.Rotation[1] = std::asin(-rotationMatrix(0, 2));
	if (std::cos(transform.Rotation[1]) != 0) {
		transform.Rotation[0] = std::atan2(rotationMatrix(1, 2), rotationMatrix(2, 2));
		transform.Rotation[2] = std::atan2(rotationMatrix(0, 1), rotationMatrix(0, 0));
	}
	else {
		transform.Rotation[0] = std::atan2(-rotationMatrix(2, 0), rotationMatrix(1, 1));
		transform.Rotation[2] = 0;
	}

	return transform;
}

void Common::Transform::Log() const
{
	std::cout << "Translation: (" << Translation[0] << ", " << Translation[1] << ", " << Translation[2] << ")\n";
	std::cout << "Rotation: (" << Rotation[0] << ", " << Rotation[1] << ", " << Rotation[2] << ")\n";
	std::cout << "Scale: (" << Scale[0] << ", " << Scale[1] << ", " << Scale[2] << ")\n";
}

Common::Camera::Camera()
{
	Transform = Common::Transform(-10, 0, 0, 0, 0, 0, 1, 1, 1);
	CameraMatrix = Transform.toMatrix();
	ViewMatrix = CameraMatrix.inverse();

	Fov = 120;
	Ratio = 1;
	N = 10;
	F = 1250;

	PerspectiveMatrix = SetPerspectiveMatrix();
}

Common::Matrix Common::Camera::SetPerspectiveMatrix()
{
	float T, B, R, L;
	T = (float) tan(Fov * 0.5) * N;
	B = T * -1;
	R = Ratio * T;
	L = R * -1;

	Common::Matrix Result(4, 4);
	Result(0, 3) = 1.0f;
	Result(0, 0) = F / (F - N);

	Result(1, 1) = 2 * N / (R - L);

	Result(2, 2) = 2 * N / (T - B);

	Result(3, 0) = -1 * F * N / (F - N);

	return Result;
}

void Common::Camera::UpdateCamera()
{
	CameraMatrix = Transform.toMatrix();
	ViewMatrix = CameraMatrix.inverse();
	PerspectiveMatrix = SetPerspectiveMatrix();
}

Common::Vertex::Vertex()
{
	x = 0;
	y = 0;
	z = 0;
}

Common::Vertex::Vertex(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}
