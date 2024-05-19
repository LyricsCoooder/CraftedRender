#pragma once

#include "CommonStructure.h"

namespace UIValue
{
	class UIValue
	{
	public:
		// PointTree
		std::vector<Common::Point> PointTree;
		int PointTreeSize = 0;

		// PointTree
		std::vector<Common::Line> LineTree;
		int LineTreeSize = 0;

		// PointTree
		std::vector<Common::Triangle> TriangleTree;
		int TriangleTreeSize = 0;

		// ModelTree
		std::vector<Common::Model> ModelTree;
		int ModelTreeSize = 0;
	};
}
