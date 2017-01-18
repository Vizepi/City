#include <iostream>

#include <Triangle.h>
#include <Quad.h>
#include <Random.h>

int main(int argc, char **argv)
{
	Triangle t(Vector2(0, 5), Vector2(), Vector2(5, 0));
	t.Shrink(1);
	std::cout << t.Area() << std::endl;

    Quad q(Random::NextUInt64(), Vector2(0, 1000), Vector2(1000, 1000), Vector2(1000, 0), Vector2());
	std::cout << q.Area() << std::endl;
	q.Shrink(1);
	std::cout << q.Area() << std::endl;

    std::ofstream obj;
	q.Subdivide(obj);
    q.BuildTerrain (obj, Setting::GetInstance(q.A()));

	std::cout << t.A().X() << " " << t.A().Y() << " ; " << t.B().X() << " " << t.B().Y() << " ; " << t.C().X() << " " << t.C().Y() << std::endl;

	getchar();

	return 0;
}
