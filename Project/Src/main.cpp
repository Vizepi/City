#include <iostream>

#include <Triangle.h>
#include <Quad.h>

int main(int argc, char **argv)
{
	Triangle t(Vector2(0, 5), Vector2(), Vector2(5, 0));
	t.Shrink(1);
	std::cout << t.Area() << std::endl;

    Quad q(Vector2(0, 5), Vector2(5, 5), Vector2(5, 0), Vector2());
    std::ofstream obj;
    q.BuildBuilding (obj, 6, 12);

	std::cout << t.A().X() << " " << t.A().Y() << " ; " << t.B().X() << " " << t.B().Y() << " ; " << t.C().X() << " " << t.C().Y() << std::endl;

	return 0;
}
