#pragma once

#include <vector>
#include <Setting.h>

class Object;

class Shape
{
public:
	inline Shape(void) : m_seed(0) {}
	inline Shape(uint64_t seed) : m_seed(seed) {}
	inline virtual ~Shape(void) {}
	virtual void Subdivide(Object & obj) = 0;
	virtual void BuildNeighborhood(Object & obj) = 0;

	virtual double Area(void) const = 0;

	virtual void BuildBuilding(Object &obj, const BuildingSetting & setting);
	virtual void BuildEmptySpace(Object &obj, const BuildingSetting & setting);
	virtual void BuildTerrain(Object &obj, const BuildingSetting & setting);

protected:
	uint64_t m_seed;
};
