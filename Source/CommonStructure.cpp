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
	 data.resize(rows, std::vector<double>(cols, 0.0));
 }

 size_t Common::Matrix::getRows() const
 {
	 return rows;
 }

 size_t Common::Matrix::getCols() const
 {
	 return cols;
 }

 double& Common::Matrix::operator()(size_t row, size_t col)
 {
	 if (row >= rows || col >= cols) 
	 {
		 throw std::out_of_range("Index out of bounds");
	 }
	 return data[row][col];
 }

 const double& Common::Matrix::operator()(size_t row, size_t col) const
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
			 std::cout << data[i][j] << " ";
		 }
		 std::cout << std::endl;
	 }
 }
