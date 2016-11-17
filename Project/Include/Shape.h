#pragma once

#include <vector>

class Shape
{
public:
	virtual void Subdivide(std::vector<Shape>& mesh) = 0;
};
