#include <Shape.h>
#include <Random.h>
#include <iostream>
#include <Object.h>

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

    if (height * (setting.FloorSize + setting.FloorSpaceSize) <= setting.Height.Max)
    {
        type = (r < 0.95) ? FLOOR : ROOF;
    }
    else
    {
        type = ROOF;
    }

    return type;
}

FloorType BuildFloorLevel(uint32_t height, const BuildingSetting & setting)
{
    FloorType type;
    double r = Random::NextDouble ();

    if (height * (setting.FloorSize + setting.FloorSpaceSize) <= setting.Height.Max)
    {
        type = (r < 0.95) ? FLOOR : ROOF;
    }
    else
    {
        type = ROOF;
    }

    return type;
}

void Shape::BuildBuilding(Object &obj, BuildingSetting & setting)
{
    //Random::Seed(m_seed);
    uint32_t height = 0;
    FloorType type = GROUND;

    while (type != END)
    {
        switch (type)
        {
            case GROUND:
                DrawBuildingGround(obj, setting);
                type = BuildGroundLevel (height, setting);

                break;
            case FLOOR:
                DrawBuildingFloor(obj, setting, height);
                type = BuildFloorLevel (height, setting);

                break;
            case ROOF:
                DrawBuildingRoof(obj, setting, height);
                type = END;

                break;
            case END:
                break;
            default:
                break;
        }
        height++;
    }
}

void Shape::BuildEmptySpace(Object &obj, BuildingSetting & setting)
{
    // Fill with trees/bushes/whatever
    DrawEmptySpace(obj, setting, 0);
}
