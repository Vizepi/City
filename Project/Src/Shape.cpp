#include <Shape.h>
#include <Random.h>
#include <iostream>

enum TerrainType
{
    NONE,
    BUILDING
};

enum FloorType
{
    GROUND,
    NO_BUILDING,
    FLOOR,
    ROOF,
    END
};

FloorType BuildGroundLevel(uint32_t height, uint32_t minGlobalHeight, uint32_t maxGlobalHeight)
{
    FloorType type;
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

    return type;
}

FloorType BuildFloorLevel(uint32_t height, uint32_t minGlobalHeight, uint32_t maxGlobalHeight)
{
    FloorType type;
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

    return type;
}

void Shape::BuildBuilding(std::ofstream & obj, uint32_t minGlobalHeight, uint32_t maxGlobalHeight)
{
    Random::Seed(m_seed);
    uint32_t height = 0;
    FloorType type = GROUND;

    while (type != END)
    {
        switch (type)
        {
            case GROUND:
            {
                // WriteGround(obj);
                type = BuildGroundLevel (height, minGlobalHeight, maxGlobalHeight);

                break;
            }
            case FLOOR:
            {
                // WriteFloor(obj);
                type = BuildFloorLevel (height, minGlobalHeight, maxGlobalHeight);

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

void Shape::BuildTerrain(std::ofstream & obj, uint32_t minGlobalHeight, uint32_t maxGlobalHeight)
{
    FloorType type = (Random::NextDouble() > minGlobalHeight) ? NO_BUILDING : GROUND;
    switch (type)
    {
        case BUILDING:
            BuildBuilding(obj, minGlobalHeight, maxGlobalHeight);
            break;
        case NONE:
            // WriteEmptySpace(obj)
        default:

            break;
        
    }
}