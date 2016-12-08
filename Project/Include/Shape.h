#pragma once

#include <vector>
#include <fstream>

class Shape
{
public:
	inline Shape(void) : m_seed(0) {}
	inline Shape(uint64_t seed) : m_seed(seed) {}
	inline virtual ~Shape(void) {}
	virtual void Subdivide(std::ofstream & obj) = 0;
	virtual void BuildNeighborhood(std::ofstream & obj) = 0;
	void BuildBuilding(std::ofstream& obj, uint32_t minGlobalHeight, uint32_t maxGlobalHeight);
	void BuildTerrain(std::ofstream & obj, uint32_t minGlobalHeight, uint32_t maxGlobalHeight);

protected:
	uint64_t m_seed;
};
