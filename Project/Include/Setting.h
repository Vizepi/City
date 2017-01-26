#pragma once

#include <cstdint>
#include <cmath>
#include <Vector.h>

#define ROAD_SIZE_COEF 36.0
#define SIDEWALK_SIZE 2.0
#define SIDEWALK_TOTAL_SIZE SIDEWALK_SIZE * 2.0

// DIVISION
#define QUAD_EDGE_DIVISION_INTERVAL 0.2
#define QUAD_EDGE_DIVISION_INTERVAL_HALF QUAD_EDGE_DIVISION_INTERVAL / 2.0
#define QUAD_EDGE_DIVISION_CENTER 0.5


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
	static BuildingSize		FloorSize;
	static BuildingSize		FloorSpaceSize;
	static ShapeDivision	Quads;
	static ShapeDivision	Triangles;

	static BuildingSetting	GetInstance(const Vector2 & position);
	static inline double	Ease(double x) { double y = 1.0 - x * x; return fmax(0.0, fmin(1.0, 1.0 - y * y * y)); }
	static inline double	Ease(double x, double min, double max) { return Ease((fmax(min, fmin(max, x)) - min) / (max - min)); }

};
