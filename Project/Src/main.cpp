#include <iostream>

#include <Triangle.h>
#include <Quad.h>
#include <Random.h>
#include <Object.h>

int main(int argc, char **argv)
{
	Setting::InfluencePointsCount = 5;
	Setting::InfluencePoints[0] = { { { 30.0, 250.0 },{ 20.0, 250.0 }, 0.0, 0.0 }, Vector2(-3400.0, -2960.0), 1600.0 };
	Setting::InfluencePoints[1] = { { { 35.0, 300.0 },{ 20.0, 300.0 }, 0.0, 0.0 }, Vector2(2800.0, 3160.0), 1900.0 };
	Setting::InfluencePoints[2] = { { { 40.0, 350.0 },{ 35.0, 500.0 }, 0.0, 0.0 }, Vector2(320.0, -800.0), 3200.0 };
	Setting::InfluencePoints[3] = { { { 25.0, 250.0 },{ 15.0, 150.0 }, 0.0, 0.0 }, Vector2(-800.0, 3000.0), 1100.0 };
	Setting::InfluencePoints[4] = { { { 35.0, 300.0 },{ 25.0, 350.0 }, 0.0, 0.0 }, Vector2(2600.0, 2800.0), 2200.0 };

	Triangle t(Vector2(0, 5), Vector2(), Vector2(5, 0));
	t.Shrink(1);

	Random::Seed(0);
    Quad q(Random::NextUInt64(), Vector2(-500, 500), Vector2(-500, -500), Vector2(500, -500), Vector2(500, 500));

    Object obj("Output/test.obj");
	q.Subdivide(obj);
    //BuildingSetting s = Setting::GetInstance(q.A());
    //q.BuildTerrain (obj, s);

	std::cout << "Complete" << std::endl;
	getchar();

	return 0;
}
