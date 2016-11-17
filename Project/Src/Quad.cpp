#include <Quad.h>
#include <Line.h>
#include <Random.h>

void Quad::Subdivide(std::vector<Shape>& mesh)
{
	
}

void Quad::BuildNeighborhood(std::vector<Shape>& mesh) // Add const vector3 &v with the downtown
{

}

void Quad::BuildBuilding(std::ofstream & obj, uint32_t minGlobalHeight, uint32_t maxGlobalHeight)
{
    Random::Seed();
    enum FloorType { GROUND, FLOOR, ROOF, END };

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
                    type = (Random.NextDouble() < 0.95) ? FLOOR : ROOF;
                }
                else if (height > maxGlobalHeight)
                {
                    type = (Random.NextDouble() > 0.95) ? FLOOR : ROOF;
                }
                else
                {
                    type = (Random.NextDouble() < 0.8) ? FLOOR : ROOF;
                }

                break;
            case ROOF:
                // WriteRoof(obj);
                height++;
                type = END;

            case END:
            default:
                break;
        }
    }
}

void Quad::Shrink(double roadSizeAB, double roadSizeBC, double roadSizeCD, double roadSizeDA)
{
	Line ab(m_a, m_b);
	Line bc(m_b, m_c);
	Line cd(m_c, m_d);
	Line da(m_d, m_a);

	ab.Translation(roadSizeAB / 2.0);
	bc.Translation(roadSizeBC / 2.0);
	cd.Translation(roadSizeCD / 2.0);
	da.Translation(roadSizeDA / 2.0);

	m_a = Line::Intersection(ab, da);
	m_b = Line::Intersection(ab, bc);
	m_c = Line::Intersection(bc, cd);
	m_d = Line::Intersection(cd, da);
}
