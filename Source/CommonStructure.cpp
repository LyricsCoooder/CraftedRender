#include "CommonStructure.h"

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
