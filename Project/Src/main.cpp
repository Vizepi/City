#include <iostream>

#include <Triangle.h>
#include <Quad.h>
#include <Random.h>
#include <Object.h>

int main(int argc, char **argv)
{
	Setting::InfluencePointsCount = 5;
	Setting::InfluencePoints[0] = { { { 300.0, 1000.0 },{ 160.0, 540.0 }, 0.0, 0.0 }, Vector2(-3400.0, -2960.0), 1600.0 };
	Setting::InfluencePoints[1] = { { { 300.0, 1000.0 },{ 190.0, 570.0 }, 0.0, 0.0 }, Vector2(2800.0, 3160.0), 1900.0 };
	Setting::InfluencePoints[2] = { { { 300.0, 1000.0 },{ 320.0, 960.0 }, 0.0, 0.0 }, Vector2(320.0, -800.0), 3200.0 };
	Setting::InfluencePoints[3] = { { { 300.0, 1000.0 },{ 110.0, 330.0 }, 0.0, 0.0 }, Vector2(-800.0, 3000.0), 1100.0 };
	Setting::InfluencePoints[4] = { { { 300.0, 1000.0 },{ 220.0, 660.0 }, 0.0, 0.0 }, Vector2(2600.0, 2800.0), 2200.0 };

	Triangle t(Vector2(0, 5), Vector2(), Vector2(5, 0));
	t.Shrink(1);

	Random::Seed(0);
    Quad q(Random::NextUInt64(), Vector2(-5000, 5000), Vector2(-5000, -5000), Vector2(5000, -5000), Vector2(5000, 5000));

    Object obj("Output/test.obj");
	q.Subdivide(obj);
    //BuildingSetting s = Setting::GetInstance(q.A());
    //q.BuildTerrain (obj, s);

	std::cout << "Complete" << std::endl;
	getchar();

	return 0;
}
