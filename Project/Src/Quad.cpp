#include <Quad.h>
#include <Line.h>
#include <Random.h>
#include <Object.h>

#include <iostream>
#include <vector>
#include <algorithm>

#define QUAD_DIVIDE_GRID	0
#define QUAD_DIVIDE_CROSS	1
#define QUAD_DIVIDE_H_CUT	2
#define QUAD_DIVIDE_V_CUT	3
#define QUAD_DIVIDE_AC_CUT	4
#define QUAD_DIVIDE_BD_CUT	5

#define QUAD_NEIGHBORHOOD_PARK			0
#define QUAD_NEIGHBORHOOD_BUILDING		1
#define QUAD_NEIGHBORHOOD_NEIGHBORHOOD	2

struct Type
{
	int type;
	double size;
};

int Quad::GetSubdivisionType(void) const
{
	std::vector<Type> types;
	types.push_back({ QUAD_DIVIDE_GRID, 2.5 });
	types.push_back({ QUAD_DIVIDE_CROSS, 0.5 });
	double sizes = 3.0;
	double v = ((m_c - m_b).Length() + (m_a - m_d).Length()) / ((m_b - m_a).Length() + (m_d - m_c).Length());
	if (v >= 1.25 && v <= 2.5)
	{
		double s = Setting::EaseCentered(v, 1.25, 2.5);
		types.push_back({ QUAD_DIVIDE_H_CUT, s });
		sizes += s;
	}
	v = ((m_b - m_a).Length() + (m_d - m_c).Length()) / ((m_c - m_b).Length() + (m_a - m_d).Length());
	if (v >= 1.25 && v <= 2.5)
	{
		double s = Setting::EaseCentered(v, 1.25, 2.5);
		types.push_back({ QUAD_DIVIDE_V_CUT, s });
		sizes += s;
	}
	v = (m_c - m_a).Length() / (m_d - m_b).Length();
	if (v >= 0.75 && v <= 1.0)
	{
		double s = Setting::EaseCentered(v, 0.75, 1.0);
		types.push_back({ QUAD_DIVIDE_AC_CUT, s });
		sizes += s;
	}
	v = (m_d - m_b).Length() / (m_c - m_a).Length();
	if (v >= 0.75 && v <= 1.0)
	{
		double s = Setting::EaseCentered(v, 0.75, 1.0);
		types.push_back({ QUAD_DIVIDE_BD_CUT, s });
		sizes += s;
	}
	int currentType = -1;
	double size = Random::NextDouble(0.0, sizes);
	do
	{
		currentType++;
		size -= types[currentType].size;
	} while (size >= 0.0 && currentType < (int)types.size() - 1);
	return types[currentType].type;
}

void Quad::Subdivide(Object & obj)
{
	Random::Seed(m_seed);
	double area = Area();
	uint64_t type = GetSubdivisionType();
	BuildingSetting setting = Setting::GetInstance(Center());

	double stopChance =
		area > (Setting::MaxNeighborhoodSize * Setting::MaxNeighborhoodSize) ?
		1.0 :
		Setting::Ease(
			area,
			setting.Neighborhood.Min * setting.Neighborhood.Min,
			setting.Neighborhood.Max * setting.Neighborhood.Max);

	if (stopChance < Random::NextDouble())
	{
		//BuildNeighborhood(obj);
		if (setting.Height.Max > 0.0)
		{
			//obj.WriteQuadBox(q, q, 0.0, Random::NextDouble(s.Height.Min, s.Height.Max), true, false);
			obj.m_obj << "v " << m_a.X() << " " << m_a.Y() << " 0\n";
			obj.m_obj << "v " << m_b.X() << " " << m_b.Y() << " 0\n";
			obj.m_obj << "v " << m_c.X() << " " << m_c.Y() << " 0\n";
			obj.m_obj << "v " << m_d.X() << " " << m_d.Y() << " 0\n";
			obj.m_obj << "f -4 -3 -2 -1\n";
			Shrink(SIDEWALK_SIZE);
			BuildNeighborhood(obj, setting);
			//BuildBuilding(obj, s);
		}
	}
	else
	{
		double roadSize = Setting::Ease(area, double(200ull * 200ull), double(2000ull * 2000ull)) * ROAD_SIZE_COEF / 2.0 + SIDEWALK_SIZE;
		switch (type)
		{
		case QUAD_DIVIDE_GRID: // Divide quad in four parts, cutting edges
		{
			double abPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			double bcPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			double cdPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			double daPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			Vector2 pAB = m_a + (m_b - m_a) * abPosition;
			Vector2 pBC = m_b + (m_c - m_b) * bcPosition;
			Vector2 pCD = m_c + (m_d - m_c) * cdPosition;
			Vector2 pDA = m_d + (m_a - m_d) * daPosition;
			Vector2 center = Line::Intersection(Line(pAB, pCD), Line(pBC, pDA));
			Quad q1(Random::NextUInt64(), m_a, pAB, center, pDA);
			q1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, roadSize, roadSize, IsShrinkedDA() ? 0.0 : roadSize);
			q1.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			Quad q2(Random::NextUInt64(), pAB, m_b, pBC, center);
			q2.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, roadSize, roadSize);
			q2.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			Quad q3(Random::NextUInt64(), center, pBC, m_c, pCD);
			q3.Shrink(roadSize, IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCD() ? 0.0 : roadSize, roadSize);
			q3.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			Quad q4(Random::NextUInt64(), pDA, center, pCD, m_d);
			q4.Shrink(roadSize, roadSize, IsShrinkedCD() ? 0.0 : roadSize, IsShrinkedDA() ? 0.0 : roadSize);
			q4.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			q1.Subdivide(obj);
			q2.Subdivide(obj);
			q3.Subdivide(obj);
			q4.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		case QUAD_DIVIDE_CROSS: // Divide quad in four parts, cuttings angles
		{
			Vector2 center = Line::Intersection(Line(m_a, m_c), Line(m_b, m_d));
			Triangle t1(Random::NextUInt64(), m_a, m_b, center);
			t1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), m_b, m_c, center);
			t2.Shrink(IsShrinkedBC() ? 0.0 : roadSize, roadSize, roadSize);
			t2.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t3(Random::NextUInt64(), m_c, m_d, center);
			t3.Shrink(IsShrinkedCD() ? 0.0 : roadSize, roadSize, roadSize);
			t3.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t4(Random::NextUInt64(), m_d, m_a, center);
			t4.Shrink(IsShrinkedDA() ? 0.0 : roadSize, roadSize, roadSize);
			t4.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			t1.Subdivide(obj);
			t2.Subdivide(obj);
			t3.Subdivide(obj);
			t4.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		case QUAD_DIVIDE_H_CUT: // Divide quad in two parts, cutting edges BC and AD
		{
			double bcPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			double daPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			Vector2 pBC = m_b + (m_c - m_b) * bcPosition;
			Vector2 pDA = m_d + (m_a - m_d) * daPosition;
			Quad q1(Random::NextUInt64(), m_a, m_b, pBC, pDA);
			q1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, roadSize, IsShrinkedDA() ? 0.0 : roadSize);
			q1.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			Quad q2(Random::NextUInt64(), pDA, pBC, m_c, m_d);
			q2.Shrink(roadSize, IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCD() ? 0.0 : roadSize, IsShrinkedDA() ? 0.0 : roadSize);
			q2.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			q1.Subdivide(obj);
			q2.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		case QUAD_DIVIDE_V_CUT: // Divide quad in two parts, cutting edges AB and CD
		{
			double abPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			double cdPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			Vector2 pAB = m_a + (m_b - m_a) * abPosition;
			Vector2 pCD = m_d + (m_c - m_d) * cdPosition;
			Quad q1(Random::NextUInt64(), m_a, pAB, pCD, m_d);
			q1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, roadSize, IsShrinkedCD() ? 0.0 : roadSize, IsShrinkedDA() ? 0.0 : roadSize);
			q1.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			Quad q2(Random::NextUInt64(), pAB, m_b, m_c, pCD);
			q2.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCD() ? 0.0 : roadSize, roadSize);
			q2.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			q1.Subdivide(obj);
			q2.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		case QUAD_DIVIDE_AC_CUT: // Divide quad in two part, cutting angles at corners A and C
		{
			Triangle t1(Random::NextUInt64(), m_a, m_b, m_c);
			t1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), m_c, m_d, m_a);
			t2.Shrink(IsShrinkedCD() ? 0.0 : roadSize, IsShrinkedDA() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			t1.Subdivide(obj);
			t2.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		case QUAD_DIVIDE_BD_CUT: // Divide quad in two part, cutting angles at corners B and D
		{
			Triangle t1(Random::NextUInt64(), m_b, m_c, m_d);
			t1.Shrink(IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCD() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), m_d, m_a, m_b);
			t2.Shrink(IsShrinkedDA() ? 0.0 : roadSize, IsShrinkedAB() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			t1.Subdivide(obj);
			t2.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		default:
		{

		}
		break;
		}
	}
}

void Quad::BuildNeighborhood(Object & obj, BuildingSetting& setting)
{
	Random::Seed(m_seed);
	uint64_t type = Random::NextDouble() < PARK_DENSITY ? QUAD_NEIGHBORHOOD_PARK : QUAD_NEIGHBORHOOD_NEIGHBORHOOD;

	if (type != QUAD_NEIGHBORHOOD_PARK)
	{
		if (setting.Size.Min * 2.0 >= (m_b - m_a).Length() ||
			setting.Size.Min * 2.0 >= (m_c - m_b).Length() ||
			setting.Size.Min * 2.0 >= (m_d - m_c).Length() ||
			setting.Size.Min * 2.0 >= (m_a - m_d).Length())
		{
			type = QUAD_NEIGHBORHOOD_BUILDING;
		}
	}

	switch (type)
	{
	case QUAD_NEIGHBORHOOD_PARK:
	{
		BuildEmptySpace(obj);
	}
	break;
	case QUAD_NEIGHBORHOOD_BUILDING:
	{
		//BuildBuilding(obj, setting);
		Quad q = GetInscribedSquare();
		setting.Height.Min = setting.Height.Max;
		setting.Height.Max = setting.PeakSize;
        BuildBuildingFromType(obj, setting);
		//obj.WriteQuadBox(q, q, 0.0, Random::NextDouble(setting.Height.Max, setting.PeakSize), true, false);
	}
	break;
	case QUAD_NEIGHBORHOOD_NEIGHBORHOOD:
	{
		Vector2 AB(m_b - m_a);
		Vector2 BC(m_c - m_b);
		Vector2 CD(m_d - m_c);
		Vector2 DA(m_a - m_d);

		Vector2 oAB = AB.Orthogonal();
		Vector2 oBC = (m_c - m_b).Orthogonal();
		Vector2 oCD = (m_d - m_c).Orthogonal();
		Vector2 oDA = (m_a - m_d).Orthogonal();

		Line tA_B(m_a, m_a + oAB);
		Line tB_A(m_b, m_b + oAB);
		Line tB_C(m_b, m_b + oBC);
		Line tC_B(m_c, m_c + oBC);
		Line tC_D(m_c, m_c + oCD);
		Line tD_C(m_d, m_d + oCD);
		Line tD_A(m_d, m_d + oDA);
		Line tA_D(m_a, m_a + oDA);

		tA_B.Translation(-Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, AB.Length() / 2.0)));
		tB_A.Translation(Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, AB.Length() / 2.0)));
		tB_C.Translation(-Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, BC.Length() / 2.0)));
		tC_B.Translation(Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, BC.Length() / 2.0)));
		tC_D.Translation(-Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, CD.Length() / 2.0)));
		tD_C.Translation(Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, CD.Length() / 2.0)));
		tD_A.Translation(-Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, DA.Length() / 2.0)));
		tA_D.Translation(Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, DA.Length() / 2.0)));

		Quad cornerA(
			m_a,
			Line::Intersection(Line(m_a, m_b), tA_B),
			Line::Intersection(tA_B, tA_D),
			Line::Intersection(tA_D, Line(m_a, m_d)));
		Quad cornerB(
			m_b,
			Line::Intersection(Line(m_b, m_c), tB_C),
			Line::Intersection(tB_C, tB_A),
			Line::Intersection(tB_A, Line(m_b, m_a)));
		Quad cornerC(
			m_c,
			Line::Intersection(Line(m_c, m_d), tC_D),
			Line::Intersection(tC_D, tC_B),
			Line::Intersection(tC_B, Line(m_c, m_b)));
		Quad cornerD(
			m_d,
			Line::Intersection(Line(m_d, m_a), tD_A),
			Line::Intersection(tD_A, tD_C),
			Line::Intersection(tD_C, Line(m_d, m_c)));

		std::vector<Quad> neighborhood;

		if (cornerA.IsWellFormed())
		{
			neighborhood.push_back(cornerA);
		}
		if (cornerB.IsWellFormed())
		{
			neighborhood.push_back(cornerB);
		}
		if (cornerC.IsWellFormed())
		{
			neighborhood.push_back(cornerC);
		}
		if (cornerD.IsWellFormed())
		{
			neighborhood.push_back(cornerD);
		}

		const Vector2 * as[4] = { &(cornerA.B()), &(cornerB.B()), &(cornerC.B()), &(cornerD.B()) };
		const Vector2 * bs[4] = { &(cornerB.D()), &(cornerC.D()), &(cornerD.D()), &(cornerA.D()) };
		const Vector2 * a, * b;


		for (uint64_t i = 0; i < 4; ++i)
		{
			a = as[i];
			b = bs[i];
			Vector2 direction(*b - *a);
			direction.Normalize();
			Vector2 ortho = direction.Orthogonal();

			double N = (*b - *a).Length();
			std::vector<double> sizes;
			for (;;)
			{
				if (N > setting.Size.Min + setting.Size.Max)
				{
					double size = Random::NextDouble(setting.Size.Min, setting.Size.Max);
					sizes.push_back(size);
					N -= size;
				}
				else if (N > setting.Size.Min)
				{
					double size = Random::NextDouble(setting.Size.Min, N);
					sizes.push_back(size);
					N -= size;
				}
				else
				{
					break;
				}
			}
			uint64_t gapCount = sizes.size() + 1;
			double gapSize = -N / gapCount;
			for (uint64_t i = 0; i < gapCount; ++i)
			{
				sizes.push_back(gapSize);
			}
			std::random_shuffle(sizes.begin(), sizes.end(), Shuffler);
			// Positives are buildings, negatives are gaps

			// Add buildings
			double currentPosition = 0.0;
			for (uint64_t j = 0; j < sizes.size(); ++j)
			{
				if (sizes[j] > 0.0)
				{
					Quad newBuilding = Quad(
						*a + direction * currentPosition, 
						*a + direction * (currentPosition + sizes[j]),
						*a + direction * (currentPosition + sizes[j]) + ortho * sizes[j] * 0.7,
						*a + direction * (currentPosition) + ortho * sizes[j] * 0.7);
						neighborhood.push_back(newBuilding);
				}
				currentPosition += fabs(sizes[j]);
			}
		}

		for (int i = neighborhood.size() - 1; i >= 0; --i)
		{
			for (int j = i - 1; j >= 0; --j)
			{
				if (neighborhood[i].Intersects(neighborhood[j]))
				{
					if (neighborhood[i].Area() > neighborhood[j].Area())
					{
						neighborhood.erase(neighborhood.begin() + j);
						i = neighborhood.size() - 1;
						j = i - 1;
					}
					else
					{
						neighborhood.erase(neighborhood.begin() + i);
						i = neighborhood.size() - 1;
						j = i - 1;
					}
				}
			}
		}

		for (uint64_t i = 0; i < neighborhood.size(); ++i)
		{
			if (GetPeakChance(neighborhood[i].Area(), setting))
			{
				BuildingSetting s = setting;
				double m = s.Height.Max;
				s.Height.Max = s.PeakSize;
				neighborhood[i].BuildBuildingFromType(obj, s);
				s.Height.Max = m;
				//obj.WriteQuadBox(neighborhood[i], neighborhood[i], 0.0, Random::NextDouble(setting.Height.Min, setting.PeakSize), true, false);
			}
			else
			{
				neighborhood[i].BuildBuildingFromType(obj, setting);
				//obj.WriteQuadBox(neighborhood[i], neighborhood[i], 0.0, Random::NextDouble(setting.Height.Min, setting.Height.Max), true, false);
			}
		}

	}
	break;
	default:
	{

	}
	break;
	}
}

void Quad::BuildBuildingRotation(Object &obj, BuildingSetting & setting)
{
    uint32_t height = 0;
    Shape::FloorType type = Shape::GROUND;

    while (type != Shape::END)
    {
        switch (type)
        {
            case Shape::GROUND:
                DrawBuildingGroundRotation(obj, setting);
                type = Shape::BuildGroundLevel (height, setting);

                break;
            case Shape::FLOOR:
                DrawBuildingFloorRotation(obj, setting, height);
                type = Shape::BuildFloorLevel (height, setting);

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

void Quad::BuildBuildingShrink(Object &obj, BuildingSetting & setting)
{
    uint32_t height = 0;
    Shape::FloorType type = Shape::GROUND;

    while (type != Shape::END)
    {
        switch (type)
        {
            case Shape::GROUND:
                DrawBuildingFloorShrink(obj, setting, 0);
                type = Shape::BuildGroundLevel (height, setting);

                break;
            case Shape::FLOOR:
                DrawBuildingFloorShrink(obj, setting, height);
                type = Shape::BuildFloorLevel (height, setting);

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

void Quad::BuildBuildingFromType(Object &obj, BuildingSetting & setting)
{
    double r = Random::NextDouble();

    if (r < 0.45)
    {
        BuildBuilding(obj, setting);
    }
    else if (0.95)
    {
        BuildBuildingRotation(obj, setting);
    }
    else
    {
        BuildBuildingShrink(obj, setting);
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

Quad Quad::GetInscribedRectangle(void) const
{
	Line ab_cd = Line(m_a + (m_b - m_a) / 2.0, m_c + (m_d - m_c) / 2.0);
	Line bc_da = Line(m_b + (m_c - m_b) / 2.0, m_d + (m_a - m_d) / 2.0);
	Line o_ab_cd(ab_cd.Center(), ab_cd.Center() + ab_cd.Orthogonal());
	Line o_bc_da(bc_da.Center(), bc_da.Center() + bc_da.Orthogonal());
	double d_ab_cd = (ab_cd.A() - ab_cd.B()).Length();
	double d_bc_da = (bc_da.A() - bc_da.B()).Length();

	// Select shortest distance between opposite edges centers
	Line* l = nullptr;
	Line* o = nullptr;
	const Vector2* a = nullptr, *b = nullptr, *c = nullptr, *d = nullptr;
	if (d_ab_cd > d_bc_da)
	{
		l = &ab_cd;
		o = &o_ab_cd;
		a = &m_a;
		b = &m_b;
		c = &m_c;
		d = &m_d;
	}
	else
	{
		l = &bc_da;
		o = &o_bc_da;
		a = &m_b;
		b = &m_c;
		c = &m_d;
		d = &m_a;
	}

	double distA = 0.0, distB = 0.0, distC = 0.0, distD = 0.0;

	double d1 = Line::Distance(*l, *a);
	double d2 = Line::Distance(*l, *d);
	if (d1 < d2)
	{
		distA = -Line::OrientedDistance(*l, *a);
	}
	else
	{
		distA = -Line::OrientedDistance(*l, *d);
	}
	d1 = Line::Distance(*l, *b);
	d2 = Line::Distance(*l, *c);
	if (d1 < d2)
	{
		distB = -Line::OrientedDistance(*l, *b);
	}
	else
	{
		distB = -Line::OrientedDistance(*l, *c);
	}
	d1 = Line::Distance(*o, *a);
	d2 = Line::Distance(*o, *b);
	if (d1 < d2)
	{
		distC = Line::OrientedDistance(*o, *a);
	}
	else
	{
		distC = Line::OrientedDistance(*o, *b);
	}
	d1 = Line::Distance(*o, *c);
	d2 = Line::Distance(*o, *d);
	if (d1 < d2)
	{
		distD = Line::OrientedDistance(*o, *c);
	}
	else
	{
		distD = Line::OrientedDistance(*o, *d);
	}

	Line l1(*l), l2(*l);
	Line l3(*o), l4(*o);
	l1.Translation(distA);
	l2.Translation(distB);
	l3.Translation(distC);
	l4.Translation(distD);

	return Quad(
		Line::Intersection(l1, l3),
		Line::Intersection(l4, l1),
		Line::Intersection(l2, l4),
		Line::Intersection(l3, l2));
}

Quad Quad::GetInscribedSquare(void) const
{
	Quad q = GetInscribedRectangle();
	double lAB = (q.A() - q.B()).Length();
	double lAD = (q.A() - q.D()).Length();
	if (lAB < lAD)
	{
		q.Shrink((lAD - lAB) / 1.0, 0.0, (lAD - lAB) / 1.0, 0.0);
	}
	else
	{
		q.Shrink(0.0, (lAB - lAD) / 1.0, 0.0, (lAB - lAD) / 1.0);
	}
	return q;
}

bool Quad::IsWellFormed(void) const
{
	return
		CrossProduct(m_b - m_a, m_d - m_a) > 0.0 &&
		CrossProduct(m_c - m_b, m_a - m_b) > 0.0 &&
		CrossProduct(m_d - m_c, m_b - m_c) > 0.0 &&
		CrossProduct(m_a - m_d, m_c - m_d) > 0.0;
}

bool Quad::Intersects(const Quad & rhs) const
{
	Line a[4] = { Line(m_a, m_b), Line(m_b, m_c), Line(m_c, m_d), Line(m_d, m_a) };
	Line b[4] = { Line(rhs.m_a, rhs.m_b), Line(rhs.m_b, rhs.m_c), Line(rhs.m_c, rhs.m_d), Line(rhs.m_d, rhs.m_a) };
	if (Contains(rhs.A()) ||
		Contains(rhs.B()) ||
		Contains(rhs.C()) ||
		Contains(rhs.D()) ||
		rhs.Contains(m_a) ||
		rhs.Contains(m_b) ||
		rhs.Contains(m_c) ||
		rhs.Contains(m_c))
	{
		return true;
	}
	for (uint64_t j = 0; j < 4; ++j)
	{
		for (uint64_t i = 0; i < 4; ++i)
		{
			Vector2 v = Line::Intersection(a[i], b[j]);
			if (std::isnan(v.X()) || std::isnan(v.Y()))
			{
				continue;
			}
			double lA = (a[i].B() - a[i].A()).SquareLength();
			double lB = (b[i].B() - b[i].A()).SquareLength();
			if (
				((v - a[i].A()).SquareLength() < lA) &&
				((v - a[i].B()).SquareLength() < lA) &&
				((v - b[i].A()).SquareLength() < lB) &&
				((v - b[i].B()).SquareLength() < lB))
			{
				return true;
			}
		}
	}
	return false;
}

#ifndef M_PI
#define M_PI 3.14159265359
#endif

void Quad::Rotate(double angle)
{
	Vector2 c = Center();

	Vector2 d = (m_a - c);
	double l = d.Length();
	d.Normalize();
	double alpha = atan2(d.Y(), d.X());
	alpha += angle * M_PI / 180.0;
	d.SetX(cos(alpha));
	d.SetY(sin(alpha));
	m_a = c + d * l;

	d = (m_b - c);
	l = d.Length();
	d.Normalize();
	alpha = atan2(d.Y(), d.X());
	alpha += angle * M_PI / 180.0;
	d.SetX(cos(alpha));
	d.SetY(sin(alpha));
	m_b = c + d * l;

	d = (m_c - c);
	l = d.Length();
	d.Normalize();
	alpha = atan2(d.Y(), d.X());
	alpha += angle * M_PI / 180.0;
	d.SetX(cos(alpha));
	d.SetY(sin(alpha));
	m_c = c + d * l;

	d = (m_d - c);
	l = d.Length();
	d.Normalize();
	alpha = atan2(d.Y(), d.X());
	alpha += angle * M_PI / 180.0;
	d.SetX(cos(alpha));
	d.SetY(sin(alpha));
	m_d = c + d * l;
}

void Quad::DrawBuildingGround (Object & obj, BuildingSetting & setting)
{
     obj.WriteQuadGround(*this, setting);
}

void Quad::DrawBuildingGroundRotation (Object & obj, BuildingSetting & setting)
{
     obj.WriteQuadGroundRotation(*this, setting);
}

void Quad::DrawBuildingFloor (Object & obj, BuildingSetting & setting, int height)
{
     obj.WriteQuadFloor(*this, setting, height);
}

void Quad::DrawBuildingFloorRotation (Object & obj, BuildingSetting & setting, int height)
{
     obj.WriteQuadFloorRotation(*this, setting, height);
}

void Quad::DrawBuildingFloorShrink (Object & obj, BuildingSetting & setting, int height)
{
     obj.WriteQuadFloorShrink(*this, setting, height);
}

void Quad::DrawBuildingRoof (Object & obj, BuildingSetting & setting, int height)
{
     obj.WriteQuadRoof(*this, setting, height);
}

void Quad::DrawEmptySpace (Object & obj, int height)
{
     obj.WriteQuadEmptySpace(*this, height);
}
