#include <Setting.h>

/*static*/ InfluencePoint Setting::InfluencePoints[256];
/*static*/ uint64_t Setting::InfluencePointsCount = 0;
/*static*/ ShapeDivision Setting::Quads;
/*static*/ ShapeDivision Setting::Triangles;

/*static*/ BuildingSetting Setting::GetInstance(const Vector2 & position)
{
	BuildingSetting instance;
	instance.Height.Min = 0;
	instance.Height.Max = 0;
	instance.Size.Min = 0;
	instance.Size.Max = 0;
	for (uint64_t nPoint = 0; nPoint < InfluencePointsCount; ++nPoint)
	{
		double radius = InfluencePoints[nPoint].radius;
		double x = radius ? (position - InfluencePoints[nPoint].position).Length() / radius : 1.0;
		if (x > 1.0)
		{
			continue;
		}
		double y = (1.0 - x*x);
		y *= y*y;
		instance.Height.Min += InfluencePoints[nPoint].setting.Height.Min * y;
		instance.Height.Max += InfluencePoints[nPoint].setting.Height.Max * y;
		instance.Size.Min += InfluencePoints[nPoint].setting.Size.Min * y;
		instance.Size.Max += InfluencePoints[nPoint].setting.Size.Max * y;
	}
	return instance;
}