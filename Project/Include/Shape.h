#pragma once

#include <vector>
#include <fstream>
#include <Setting.h>

class Shape
{
public:
	inline Shape(void) : m_seed(0) {}
	inline Shape(uint64_t seed) : m_seed(seed) {}
	inline virtual ~Shape(void) {}

	virtual void Subdivide(std::ofstream & obj) = 0;
	virtual void BuildNeighborhood(std::ofstream & obj) = 0;

	virtual double Area(void) const = 0;

	void BuildBuilding(std::ofstream & obj, const BuildingSetting & setting);
	void BuildTerrain(std::ofstream & obj, const BuildingSetting & setting);

protected:
	uint64_t m_seed;
};
