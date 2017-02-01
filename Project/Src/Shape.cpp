#include <Shape.h>
#include <Random.h>
#include <iostream>
#include <Object.h>

Shape::FloorType Shape::BuildGroundLevel(uint32_t height, const BuildingSetting & setting)
{
    Shape::FloorType type;
    double r = Random::NextDouble();

    if (height * (setting.FloorSize + setting.FloorSpaceSize) <= setting.Height.Max)
    {
        type = (r < 0.95) ? Shape::FLOOR : Shape::ROOF;
    }
    else
    {
        type = Shape::ROOF;
    }

    return type;
}

Shape::FloorType Shape::BuildFloorLevel(uint32_t height, const BuildingSetting & setting)
{
    Shape::FloorType type;
    double r = Random::NextDouble();

    if (height * (setting.FloorSize + setting.FloorSpaceSize) <= setting.Height.Max)
    {
        type = (r < 0.95) ? Shape::FLOOR : Shape::ROOF;
    }
    else
    {
        type = Shape::ROOF;
    }

    return type;
}

void Shape::BuildBuilding(Object &obj, BuildingSetting & setting)
{
    uint32_t height = 0;
    Shape::FloorType type = Shape::GROUND;

    while (type != Shape::END)
    {
        switch (type)
        {
            case Shape::GROUND:
                DrawBuildingGround(obj, setting);
                type = BuildGroundLevel (height, setting);

                break;
            case Shape::FLOOR:
                DrawBuildingFloor(obj, setting, height);
                type = BuildFloorLevel (height, setting);

                break;
            case Shape::ROOF:
                DrawBuildingRoof(obj, setting, height);
                type = Shape::END;

                break;
            case Shape::END:
                break;
            default:
                break;
        }
        height++;
    }
}

void Shape::BuildEmptySpace(Object &obj, BuildingSetting & setting)
{
    DrawEmptySpace(obj, setting, 0);
}
