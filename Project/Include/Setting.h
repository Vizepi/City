#pragma once

#include <cstdint>

struct BuildingSize
{
	double Min;
	double Max;
};

struct BuildingSetting
{
	BuildingSize Size;
	BuildingSize Height;
};

struct ShapeDivision
{
	double Probabilities[256];
	uint64_t Count;
};

struct Setting
{
	
	static BuildingSetting	Outskirt;
	static BuildingSetting	Citycenter;
	static ShapeDivision	QuadSetting;
	static ShapeDivision	TriangleSetting;

	inline double			Interpolate(double x)
	{
		return 0.0;
	}

};
