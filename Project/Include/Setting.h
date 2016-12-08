#pragma once

#include <cstdint>
#include <Vector.h>

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

struct InfluencePoint
{
	BuildingSetting setting;
	Vector2			position;
	double			radius;
};

struct Setting
{
	
	static InfluencePoint	InfluencePoints[256];
	static uint64_t			InfluencePointsCount;
	static ShapeDivision	Quads;
	static ShapeDivision	Triangles;

	static BuildingSetting	GetInstance(const Vector2 & position);

};
