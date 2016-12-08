#include <Shape.h>
#include <Random.h>
#include <iostream>

void Shape::BuildBuilding(std::ofstream & obj, uint32_t minGlobalHeight, uint32_t maxGlobalHeight)
{
    Random::Seed(m_seed);
    enum FloorType { GROUND, NO_BUILDING, FLOOR, ROOF, END };

    FloorType type = (Random::NextDouble() > minGlobalHeight) ? NO_BUILDING : GROUND;
    uint32_t height = 0;

    while (type != END)
    {
        switch (type)
        {
            case GROUND:
            {
                // WriteGround(obj);
                double r = Random::NextDouble ();

                if (height < minGlobalHeight)
                {
                    type = (r < 0.9) ? FLOOR : ROOF;
                }
                else if (height > maxGlobalHeight)
                {
                    type = (r > 0.9) ? FLOOR : ROOF;
                }
                else
                {
                    type = (r < 0.8) ? FLOOR : ROOF;
                }

                break;
            }
            case NO_BUILDING:
                // WriteEmptyBuilding(obj)

                break;
            case FLOOR:
            {
                // WriteFloor(obj);
                double r = Random::NextDouble();

                if (height < minGlobalHeight)
                {
                    type = (r < 0.9) ? FLOOR : ROOF;
                }
                else if (height > maxGlobalHeight)
                {
                    type = (r < 0.1) ? FLOOR : ROOF;
                }
                else
                {
                    type = (r < 0.6) ? FLOOR : ROOF;
                }

                break;
            }
            case ROOF:
                // WriteRoof(obj);
                type = END;

            case END:
            default:
                break;
        }
        std::cout << "Height level: " << height << std::endl;
        std::cout << "current case: " << type << std::endl;
        height++;
    }
}
