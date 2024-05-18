#pragma once

#include "vector"
#include "CommonStructure.h"

namespace UIValue
{
	struct Point
	{
		float Pos[2] = { 0.0f };
		float Color[4] = { 1.0f, 1.0f, 1.0f, 1.0f};
	};

	struct Line
	{
		float StartPos[2] = { 0.0f };
		float EndPos[2] = { 0.0f };
		float Color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	struct Triangle
	{
		float Pos0[2] = { 0.0f };
		float Pos1[2] = { 0.0f };
		float Pos2[2] = { 0.0f };
		float Color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	class UIValue
	{
	public:
		// PointTree
		std::vector<Point> PointTree;
		int PointTreeSize = 0;

		// PointTree
		std::vector<Line> LineTree;
		int LineTreeSize = 0;

		// PointTree
		std::vector<Triangle> TriangleTree;
		int TriangleTreeSize = 0;

		// ModelTree
		std::vector<Common::Model> ModelTree;
		int ModelTreeSize = 0;
	public:
		UIValue();
	};
}
