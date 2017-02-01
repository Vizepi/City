#pragma once

#include <Random.h>

#include <vector>
#include <Setting.h>

class Object;

class Shape
{
public:
    enum TerrainType
    {
        NONE,
        BUILDING
    };

    enum FloorType
    {
        GROUND,
        NO_BUILDING,
        FLOOR,
        ROOF,
        END
    };

	inline Shape(void) : m_seed(0) {}
	inline Shape(uint64_t seed) : m_seed(seed) {}
	inline virtual ~Shape(void) {}
	virtual void Subdivide(Object & obj) = 0;
	virtual void BuildNeighborhood(Object & obj, BuildingSetting& setting) = 0;

	virtual double Area(void) const = 0;
	inline static bool GetPeakChance(double area, const BuildingSetting& s)
	{
		return 0.01 * Random::NextDouble() * (area * area * 3.0 - s.Size.Min * s.Size.Min) / ((s.Size.Max * s.Size.Max) - (s.Size.Min * s.Size.Min)) < s.PeakProbability;
	}
	inline static int Shuffler(int i)
	{
		return Random::NextInt64(0, i - 1);
	}

    FloorType BuildGroundLevel(uint32_t height, const BuildingSetting & setting);
    FloorType BuildFloorLevel (uint32_t height, const BuildingSetting & setting);


	virtual void BuildBuilding          (Object &obj, BuildingSetting & setting);
	virtual void BuildEmptySpace        (Object &obj, BuildingSetting & setting);

    virtual void DrawBuildingGround     (Object & obj, BuildingSetting & setting) = 0;
    virtual void DrawBuildingFloor      (Object & obj, BuildingSetting & setting, int height) = 0;
    virtual void DrawBuildingRoof       (Object & obj, BuildingSetting & setting, int height) = 0;
    virtual void DrawEmptySpace         (Object & obj, BuildingSetting & setting, int height) = 0;

protected:
	uint64_t m_seed;
};
