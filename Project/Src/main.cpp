#include <iostream>

#include <Triangle.h>
#include <Quad.h>

int main(int argc, char **argv)
{
	Triangle t(Vector2(0, 5), Vector2(), Vector2(5, 0));
	std::cout << t.Area() << std::endl;
    Quad q(Vector2(0, 5), Vector2(5, 5), Vector2(5, 0), Vector2());

    std::ofstream obj;
    q.BuildBuilding (obj, 6, 12);

	return 0;
}
