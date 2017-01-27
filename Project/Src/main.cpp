#include <iostream>

#include <Triangle.h>
#include <Quad.h>
#include <Random.h>
#include <Object.h>

int main(int argc, char **argv)
{
	Triangle t(Vector2(0, 5), Vector2(), Vector2(5, 0));
	t.Shrink(1);

	Random::Seed(0);
    Quad q(Random::NextUInt64(), Vector2(0, 10000), Vector2(), Vector2(10000, 0), Vector2(10000, 10000));

    Object obj("Output/test.obj");
	q.Subdivide(obj);
    //BuildingSetting s = Setting::GetInstance(q.A());
    //q.BuildTerrain (obj, s);

	std::cout << "Complete" << std::endl;
	getchar();

	return 0;
}
