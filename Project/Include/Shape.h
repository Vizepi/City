#pragma once

#include <vector>
#include <fstream>

class Shape
{
public:
	virtual void Subdivide(std::vector<Shape>& mesh) = 0;
	virtual void BuildNeighborhood(std::vector<Shape>& mesh) = 0;
	virtual void BuildBuilding(std::ofstream& obj, uint32_t globalHeight) = 0;
};
