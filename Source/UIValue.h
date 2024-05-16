#pragma once

#include "vector"
//#include "CommonStructure.h"
namespace UIValue
{
	struct Point
	{
		float Pos[2] = { 0.0f };
		float Color[4] = { 0.0f, 0.0f, 0.0f, 1.0f};
	};

	class UIValue
	{
	public:
		// PointTree
		std::vector<Point> PointTree;
		int PointTreeSize = 0;

	public:
		UIValue();
	};
}
