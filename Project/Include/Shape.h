#pragma once

#include <vector>

class Shape
{
public:
	virtual void Subdivide(std::vector<Shape>& mesh) = 0;
	virtual void BuildNeighborhood(std::vector<Shape>& mesh) = 0;
	virtual void BuildBuilding(std::vector<Shape>& mesh) = 0;
};
