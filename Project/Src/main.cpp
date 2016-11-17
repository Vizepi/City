#include <iostream>

#include <Triangle.h>

int main(int argc, char **argv)
{
	Triangle t(Vector2(0, 5), Vector2(), Vector2(5, 0));
	std::cout << t.Area() << std::endl;
	return 0;
}
