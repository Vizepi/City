#include <iostream>

#include <Triangle.h>
#include <Quad.h>
#include <Random.h>
#include <Object.h>

int main(int argc, char **argv)
{
	Setting::InfluencePointsCount = 5;
	Setting::InfluencePoints[0] = {
		{ { 25.0, 35.0 }, { 20.0, 125.0 }, { 100.0, 200.0 }, 250.0, 0.01, 0.0, 0.0 },
		{ { 10.0, 20.0 }, { 10.0, 30.0 }, { 40.0, 120.0 }, 50.0, 0.001, 0.0, 0.0 },
		Vector2(-3400.0, -3000.0),
		1600.0 };
	Setting::InfluencePoints[1] = {
		{ { 35.0, 70.0 }, { 20.0, 150.0 }, { 140.0, 300.0 }, 300.0, 0.02, 0.0, 0.0 },
		{ { 15.0, 30.0 }, { 10.0, 30.0 }, { 60.0, 160.0 }, 60.0, 0.001, 0.0, 0.0 },
		Vector2(2800.0, 3200.0),
		1900.0 };
	Setting::InfluencePoints[2] = {
		{ { 40.0, 75.0 }, { 35.0, 250.0 }, { 160.0, 400.0 }, 500.0, 0.05, 0.0, 0.0 },
		{ { 15.0, 35.0 }, { 15.0, 50.0 }, { 80.0, 200.0 }, 75.0, 0.005, 0.0, 0.0 },
		Vector2(300.0, -800.0),
		3200.0 };
	Setting::InfluencePoints[3] = {
		{ { 25.0, 100.0 }, { 15.0, 75.0 }, { 100.0, 400.0 }, 150.0, 0.03, 0.0, 0.0 },
		{ { 10.0, 25.0 }, { 15.0, 30.0 }, { 80.0, 160.0 }, 50.0, 0.002, 0.0, 0.0 },
		Vector2(-800.0, 3000.0),
		1100.0 };
	Setting::InfluencePoints[4] = {
		{ { 30.0, 60.0 }, { 25.0, 175.0 }, { 150.0, 350.0 }, 350.0, 0.01, 0.0, 0.0 },
		{ { 15.0, 40.0 }, { 15.0, 30.0 }, { 60.0, 200.0 }, 30.0, 0.005, 0.0, 0.0 },
		Vector2(2600.0, 2800.0),
		2200.0 };
	Setting::MaxNeighborhoodSize = 400.0;

	Triangle t(Vector2(0, 5), Vector2(), Vector2(5, 0));
	t.Shrink(1);

	Random::Seed(0);
	Quad q(Random::NextUInt64(), Vector2(-5000, 5000), Vector2(-5000, -5000), Vector2(5000, -5000), Vector2(5000, 5000));

    Object obj("Output/test.obj");
	//q.Subdivide(obj);
    BuildingSetting s = Setting::GetInstance(q.A());
    q.BuildTerrain (obj, s);

	std::cout << "Complete" << std::endl;
	getchar();

	return 0;
}
