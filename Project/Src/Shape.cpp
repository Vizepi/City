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

FloorType BuildGroundLevel(uint32_t height, const BuildingSetting & setting)
{
    FloorType type;
    double r = Random::NextDouble ();

    if (height < setting.Height.Min)
    {
        type = (r < 0.9) ? FLOOR : ROOF;
    }
    else if (height > setting.Height.Max)
    {
        type = (r > 0.9) ? FLOOR : ROOF;
    }
    else
    {
        type = (r < 0.8) ? FLOOR : ROOF;
    }

    return type;
}

FloorType BuildFloorLevel(uint32_t height, const BuildingSetting & setting)
{
    FloorType type;
    double r = Random::NextDouble();

    if (height < setting.Height.Min)
    {
        type = (r < 0.9) ? FLOOR : ROOF;
    }
    else if (height > setting.Height.Max)
    {
        type = (r < 0.1) ? FLOOR : ROOF;
    }
    else
    {
        type = (r < 0.6) ? FLOOR : ROOF;
    }

    return type;
}

void Shape::BuildBuilding(Object obj, const BuildingSetting & setting)
{
    Random::Seed(m_seed);
    uint32_t height = 0;
    FloorType type = GROUND;
    double floorSize = 3.0;

    while (type != END)
    {
        switch (type)
        {
            case GROUND:
            {
                obj.WriteQuadBox(this, this, 0, height * floorSize, true, false);
                type = BuildGroundLevel (height, setting);

                break;
            }
            case FLOOR:
            {
//                Shrinked Quad
//                obj.WriteQuadBox(this, this, 0, height * floorSize, true, false);
                obj.WriteQuadBox(this, this, height * floorSize /*+ offset */, (height + 1) * floorSize, true, true);
                type = BuildFloorLevel (height, setting);

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

void Shape::BuildTerrain(std::ofstream & obj, const BuildingSetting & setting)
{
    FloorType type = (Random::NextDouble() > setting.Height.Min) ? NO_BUILDING : GROUND;
    switch (type)
    {
        case BUILDING:
            BuildBuilding(obj, setting);
            break;
        case NONE:
            // WriteEmptySpace(obj)
        default:
            break;
    }
}
