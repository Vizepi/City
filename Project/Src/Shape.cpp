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

void Shape::BuildBuilding(Object &obj, BuildingSetting & setting)
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
                DrawBuildingGround(obj, setting, height);
                //obj.WriteQuadBox(this, this, 0, height * floorSize, true, false);
                type = BuildGroundLevel (height, setting);

                break;
            }
            case FLOOR:
            {
                DrawBuildingFloor(obj, setting, height);
                // Shrink shape
                DrawBuildingFloor(obj, setting, height);
                type = BuildFloorLevel (height, setting);

                break;
            }
            case ROOF:
                DrawBuildingRoof(obj, setting, height);
                type = END;

            case END:
            default:
                break;
        }
        /*std::cout << "Height level: " << height << "\n";
        std::cout << "current case: " << type << "\n";*/
        height++;
    }
}

void Shape::BuildEmptySpace(Object &obj, BuildingSetting & setting)
{
    // Fill with trees/bushes/whatever
    DrawEmptySpace(obj, setting, 0);
}

void Shape::BuildTerrain(Object &obj, BuildingSetting & setting)
{
    FloorType type = (Random::NextDouble() > setting.Height.Min) ? NO_BUILDING : GROUND;

    switch (type)
    {
        case BUILDING:
            BuildBuilding(obj, setting);
            break;
        case NONE:
            BuildEmptySpace(obj, setting);
        default:
            break;
    }
}
