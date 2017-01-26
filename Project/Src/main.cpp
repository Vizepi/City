#include <iostream>

#include <Triangle.h>
#include <Quad.h>
#include <Random.h>

int main(int argc, char **argv)
{
	Triangle t(Vector2(0, 5), Vector2(), Vector2(5, 0));
	t.Shrink(1);

	Random::Seed(0);
    Quad q(Random::NextUInt64(), Vector2(0, 10000), Vector2(), Vector2(10000, 0), Vector2(10000, 10000));

    std::ofstream obj("Output/test.obj");
	q.Subdivide(obj);
	obj.close();
    //q.BuildTerrain (obj, Setting::GetInstance(q.A()));

	std::cout << "Complete" << std::endl;
	getchar();

	return 0;
}
