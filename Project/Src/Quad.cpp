#include <Quad.h>
#include <random>
#include <functional>
#include <chrono>
#include <iostream>

void Quad::Subdivide(std::vector<Shape>& mesh)
{

}

void Quad::BuildNeighborhood(std::vector<Shape>& mesh) // Add const vector3 &v with the downtown
{

}

void Quad::BuildBuilding(std::ofstream & obj, uint32_t minGlobalHeight, uint32_t maxGlobalHeight)
{
    enum FloorType { GROUND, FLOOR, ROOF, END };

    std::mt19937_64 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> dist(0.0, 0.1);
    auto rand = std::bind(dist, generator);

    FloorType type = GROUND;
    uint32_t height = 0;

    while (type != END)
    {
        switch (type)
        {
            case GROUND:
                // WriteGround(obj);
                height++;
                type = FLOOR;
                break;
            case FLOOR:
                // WriteFloor(obj);
                // draw
                height++;

                if (height < minGlobalHeight)
                {
                    type = (rand() < 0.9) ? FLOOR : ROOF;
                }
                else if (height < maxGlobalHeight)
                {
                    type = (rand() > 0.9) ? FLOOR : ROOF;
                }
                else
                {
                    type = (rand() < 0.7) ? FLOOR : ROOF;
                }

                break;
            case ROOF:
                // WriteRoof(obj);
                height++;
                type = END;
                break;
            case END:
            default:
               // std::cout << height;
                break;
        }
    }
}
