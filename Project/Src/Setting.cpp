#include <Setting.h>
#include <cmath>
#include <limits>

/*static*/ InfluencePoint Setting::InfluencePoints[256];
/*static*/ uint64_t Setting::InfluencePointsCount = 0;
/*static*/ BuildingSize Setting::FloorSize;
/*static*/ BuildingSize Setting::FloorSpaceSize;
/*static*/ double Setting::MaxNeighborhoodSize = 400.0;


/*static*/ BuildingSetting Setting::GetInstance(const Vector2 & position)
{
	BuildingSetting instance;
	instance.Height.Min = 0.0;
	instance.Height.Max = 0.0;
	instance.Size.Min = std::numeric_limits<double>::max();
	instance.Size.Max = 0.0;
	instance.Neighborhood.Min = 0.0;
	instance.Neighborhood.Max = 0.0;
	instance.PeakSize = 0.0;
	instance.PeakProbability = 0.0;
	for (uint64_t nPoint = 0; nPoint < InfluencePointsCount; ++nPoint)
	{
		double radius = InfluencePoints[nPoint].radius;
		double x = radius ? (position - InfluencePoints[nPoint].position).Length() / radius : 1.0;
		if (x > 1.0)
		{
			continue;
		}
		double y = Ease(1.0 - x);
		double z = 1.0 - y;
		instance.Height.Min += InfluencePoints[nPoint].setting.Height.Min * y + InfluencePoints[nPoint].border.Height.Min * z;
		instance.Height.Max += InfluencePoints[nPoint].setting.Height.Max * y + InfluencePoints[nPoint].border.Height.Max * z;
		instance.Size.Min = fmin(instance.Size.Min, InfluencePoints[nPoint].setting.Size.Min * y + InfluencePoints[nPoint].border.Size.Min * z);
		instance.Size.Max = fmax(instance.Size.Max, InfluencePoints[nPoint].setting.Size.Max * y + InfluencePoints[nPoint].border.Size.Max * z);
		instance.Neighborhood.Min += InfluencePoints[nPoint].setting.Neighborhood.Min * y + InfluencePoints[nPoint].border.Neighborhood.Min * z;
		instance.Neighborhood.Max += InfluencePoints[nPoint].setting.Neighborhood.Max * y + InfluencePoints[nPoint].border.Neighborhood.Max * z;
		instance.PeakSize += InfluencePoints[nPoint].setting.PeakSize * y + InfluencePoints[nPoint].border.PeakSize * z;
		instance.PeakProbability += InfluencePoints[nPoint].setting.PeakProbability * y + InfluencePoints[nPoint].border.PeakProbability * z;
	}
	return instance;
}