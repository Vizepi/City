#pragma once

#include <cstdint>
#include <cmath>
#include <Vector.h>

#define ROAD_SIZE_COEF 50.0
#define SIDEWALK_SIZE 5.0
#define SIDEWALK_TOTAL_SIZE SIDEWALK_SIZE * 2.0

// DIVISION
#define QUAD_EDGE_DIVISION_INTERVAL 0.2
#define QUAD_EDGE_DIVISION_INTERVAL_HALF (QUAD_EDGE_DIVISION_INTERVAL / 2.0)
#define QUAD_EDGE_DIVISION_CENTER 0.5

#define TRIANGLE_EDGE_DIVISION_INTERVAL 0.2
#define TRIANGLE_EDGE_DIVISION_INTERVAL_HALF (TRIANGLE_EDGE_DIVISION_INTERVAL / 2.0)
#define TRIANGLE_EDGE_DIVISION_CENTER 0.5

#define PARK_DENSITY 0.05

struct BuildingSize
{
	double Min;
	double Max;
};

struct BuildingSetting
{
	BuildingSize Size;
	BuildingSize Height;
	BuildingSize Neighborhood;
	double PeakSize;
	double PeakProbability;
	double FloorSize;
	double FloorSpaceSize;
};

struct InfluencePoint
{
	BuildingSetting setting;
	BuildingSetting border;
	Vector2			position;
	double			radius;
};

struct Setting
{
	
	static InfluencePoint	InfluencePoints[256];
	static uint64_t			InfluencePointsCount;
	static BuildingSize		FloorSize;
	static BuildingSize		FloorSpaceSize;
	static double			MaxNeighborhoodSize;

	static BuildingSetting	GetInstance(const Vector2 & position);
	static inline double	Ease(double x) { double y = 1.0 - x * x; return fmax(0.0, fmin(1.0, 1.0 - y * y * y)); }
	static inline double	Ease(double x, double min, double max) { return (min == max) ? min : Ease((fmax(min, fmin(max, x)) - min) / (max - min)); }
	static inline double	EaseCentered(double x, double min, double max) { return Ease(2.0 * (fmax(min, fmin(max, x)) - min) / (max - min) - 1.0); }

};
