#include <Triangle.h>
#include <Line.h>
#include <Object.h>
#include <Random.h>
#include <Quad.h>

#include <vector>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#define TRIANGLE_DIVIDE_TRI		0
#define TRIANGLE_DIVIDE_A		1
#define TRIANGLE_DIVIDE_B		2
#define TRIANGLE_DIVIDE_C		3
#define TRIANGLE_DIVIDE_QUAD_A	4
#define TRIANGLE_DIVIDE_QUAD_B	5
#define TRIANGLE_DIVIDE_QUAD_C	6

#define TRIANGLE_NEIGHBORHOOD_PARK			0
#define TRIANGLE_NEIGHBORHOOD_BUILDING		1
#define TRIANGLE_NEIGHBORHOOD_NEIGHBORHOOD	2

struct Type
{
	int type;
	double size;
};

int Triangle::GetSubdivisionType(void) const
{
	std::vector<Type> types;
	double sizes = 0.0;
	double a = (m_b - m_c).Length();
	double b = (m_c - m_a).Length();
	double c = (m_a - m_b).Length();
	double alpha = acos((b * b + c * c - a * a) / (2.0 * b * c));
	double beta = acos((c * c + a * a - b * b) / (2.0 * c * a));
	double gamma = acos((a * a + b * b - c * c) / (2.0 * a * b));

	double v = ((m_a - m_b).Length() / (m_c - m_b).Length()) / ((m_c - m_b).Length() + (m_a - m_c).Length());
	if (v >= 0.75 && v <= 1.25)
	{
		double s = Setting::EaseCentered(v, 0.75, 1.25);
		types.push_back({ TRIANGLE_DIVIDE_TRI, s });
		sizes += s;
	}
	if (alpha / (beta + gamma) >= 1.0)
	{
		types.push_back({ TRIANGLE_DIVIDE_A, 1.0 });
		sizes += 1.0;
	}
	if (beta / (alpha + gamma) >= 1.0)
	{
		types.push_back({ TRIANGLE_DIVIDE_B, 1.0 });
		sizes += 1.0;
	}
	if (gamma / (alpha + beta) >= 1.0)
	{
		types.push_back({ TRIANGLE_DIVIDE_C, 1.0 });
		sizes += 1.0;
	}
	alpha = 180.0 * alpha / M_PI;
	beta = 180.0 * beta / M_PI;
	gamma = 180.0 * gamma / M_PI;
	if (alpha >= 60.0 && alpha <= 120.0)
	{
		double s = Setting::EaseCentered(alpha, 60.0, 120.0);
		types.push_back({ TRIANGLE_DIVIDE_QUAD_A, s });
		sizes += s;
	}
	if (beta >= 60.0 && beta <= 120.0)
	{
		double s = Setting::EaseCentered(beta, 60.0, 120.0);
		types.push_back({ TRIANGLE_DIVIDE_QUAD_B, s });
		sizes += s;
	}
	if (gamma >= 60.0 && gamma <= 120.0)
	{
		double s = Setting::EaseCentered(gamma, 60.0, 120.0);
		types.push_back({ TRIANGLE_DIVIDE_QUAD_C, s });
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

void Triangle::Subdivide(Object & obj)
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

	//double stopChance = Setting::Ease(area, double(75ull * 75ull), double(300ull * 300ull));
	if (stopChance < Random::NextDouble())
	{
		if(setting.Height.Max > 0.0)
		{
			obj.m_obj << "v " << m_a.X() << " " << m_a.Y() << " 0\n";
			obj.m_obj << "v " << m_b.X() << " " << m_b.Y() << " 0\n";
			obj.m_obj << "v " << m_c.X() << " " << m_c.Y() << " 0\n";
			obj.m_obj << "f -3 -2 -1\n";
			Shrink(SIDEWALK_SIZE);
			BuildNeighborhood(obj, setting);
		}
	}
	else
	{
		double roadSize = Setting::Ease(area, double(200ull * 200ull), double(2000ull * 2000ull)) * ROAD_SIZE_COEF / 2.0 + SIDEWALK_SIZE;
		switch (type)
		{
		case TRIANGLE_DIVIDE_TRI: // Divide triangle in the triforce way! 
		{
			double abPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			double bcPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			double caPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			Vector2 pAB = m_a + (m_b - m_a) * abPosition;
			Vector2 pBC = m_b + (m_c - m_b) * bcPosition;
			Vector2 pCA = m_c + (m_a - m_c) * caPosition;
			Triangle t1(Random::NextUInt64(), m_a, pAB, pCA);
			t1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, roadSize, IsShrinkedCA() ? 0.0 : roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), pAB, m_b, pBC);
			t2.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, roadSize);
			t2.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t3(Random::NextUInt64(), pCA, pBC, m_c);
			t3.Shrink(roadSize, IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCA() ? 0.0 : roadSize);
			t3.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t4(Random::NextUInt64(), pAB, pBC, pCA);
			t4.Shrink(roadSize, roadSize, roadSize);
			t4.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			t1.Subdivide(obj);
			t2.Subdivide(obj);
			t3.Subdivide(obj);
			t4.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		case TRIANGLE_DIVIDE_A: // Divide triangle in two part, cutting angle A and edge BC
		{
			double bcPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			Vector2 pBC = m_b + (m_c - m_b) * bcPosition;
			Triangle t1(Random::NextUInt64(), m_a, m_b, pBC);
			t1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), m_a, pBC, m_c);
			t2.Shrink(roadSize, IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCA() ? 0.0 : roadSize);
			t2.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			t1.Subdivide(obj);
			t2.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		case TRIANGLE_DIVIDE_B: // Divide triangle in two part, cutting angle B and edge CA
		{
			double caPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			Vector2 pCA = m_c + (m_a - m_c) * caPosition;
			Triangle t1(Random::NextUInt64(), m_b, m_c, pCA);
			t1.Shrink(IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCA() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), m_b, pCA, m_a);
			t2.Shrink(roadSize, IsShrinkedCA() ? 0.0 : roadSize, IsShrinkedAB() ? 0.0 : roadSize);
			t2.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			t1.Subdivide(obj);
			t2.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		case TRIANGLE_DIVIDE_C: // Divide triangle in two part, cutting angle C and edge AB
		{
			double abPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			Vector2 pAB = m_a + (m_b - m_a) * abPosition;
			Triangle t1(Random::NextUInt64(), m_c, m_a, pAB);
			t1.Shrink(IsShrinkedCA() ? 0.0 : roadSize, IsShrinkedAB() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), m_c, pAB, m_b);
			t2.Shrink(roadSize, IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize);
			t2.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			t1.Subdivide(obj);
			t2.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		case TRIANGLE_DIVIDE_QUAD_A: // Divide triangle in two triangles for corners B and C and a quad in corner A
		{
			double abPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			double bcPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			double caPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			Vector2 pAB = m_a + (m_b - m_a) * abPosition;
			Vector2 pBC = m_b + (m_c - m_b) * bcPosition;
			Vector2 pCA = m_c + (m_a - m_c) * caPosition;
			Triangle t1(Random::NextUInt64(), pAB, m_b, pBC);
			t1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), pCA, pBC, m_c);
			t2.Shrink(roadSize, IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCA() ? 0.0 : roadSize);
			t2.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Quad q1(Random::NextUInt64(), m_a, pAB, pBC, pCA);
			q1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, roadSize, roadSize, IsShrinkedCA() ? 0.0 : roadSize);
			q1.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			t1.Subdivide(obj);
			t2.Subdivide(obj);
			q1.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		case TRIANGLE_DIVIDE_QUAD_B: // Divide triangle in two triangles for corners C and A and a quad in corner B
		{
			double abPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			double bcPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			double caPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			Vector2 pAB = m_a + (m_b - m_a) * abPosition;
			Vector2 pBC = m_b + (m_c - m_b) * bcPosition;
			Vector2 pCA = m_c + (m_a - m_c) * caPosition;
			Triangle t1(Random::NextUInt64(), m_a, pAB, pCA);
			t1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, roadSize, IsShrinkedCA() ? 0.0 : roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), pCA, pBC, m_c);
			t2.Shrink(roadSize, IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCA() ? 0.0 : roadSize);
			t2.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Quad q1(Random::NextUInt64(), pAB, m_b, pBC, pCA);
			q1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, roadSize, roadSize);
			q1.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			t1.Subdivide(obj);
			t2.Subdivide(obj);
			q1.Subdivide(obj);
			Random::Seed(seed);
		}
		break;
		case TRIANGLE_DIVIDE_QUAD_C: // Divide triangle in two triangles for corners A and B and a quad in corner C
		{
			double abPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			double bcPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			double caPosition = Random::NextDouble(TRIANGLE_EDGE_DIVISION_CENTER - TRIANGLE_EDGE_DIVISION_INTERVAL_HALF, TRIANGLE_EDGE_DIVISION_CENTER + TRIANGLE_EDGE_DIVISION_INTERVAL_HALF);
			Vector2 pAB = m_a + (m_b - m_a) * abPosition;
			Vector2 pBC = m_b + (m_c - m_b) * bcPosition;
			Vector2 pCA = m_c + (m_a - m_c) * caPosition;
			Triangle t1(Random::NextUInt64(), m_a, pAB, pCA);
			t1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, roadSize, IsShrinkedCA() ? 0.0 : roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), pAB, m_b, pBC);
			t2.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, roadSize);
			t2.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Quad q1(Random::NextUInt64(), pAB, pBC, m_c, pCA);
			q1.Shrink(roadSize, IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCA() ? 0.0 : roadSize, roadSize);
			q1.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			uint64_t seed = Random::NextUInt64();
			t1.Subdivide(obj);
			t2.Subdivide(obj);
			q1.Subdivide(obj);
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

void Triangle::BuildNeighborhood(Object & obj, BuildingSetting& setting)
{
	Random::Seed(m_seed);
	uint64_t type = Random::NextDouble() < PARK_DENSITY ? TRIANGLE_NEIGHBORHOOD_PARK : TRIANGLE_NEIGHBORHOOD_NEIGHBORHOOD;

	if (type != TRIANGLE_NEIGHBORHOOD_PARK)
	{
		if (setting.Size.Min * 2.0 >= (m_b - m_a).Length() ||
			setting.Size.Min * 2.0 >= (m_c - m_b).Length() ||
			setting.Size.Min * 2.0 >= (m_a - m_c).Length())
		{
			type = TRIANGLE_NEIGHBORHOOD_BUILDING;
		}
	}

	switch (type)
	{
	case TRIANGLE_NEIGHBORHOOD_PARK:
	{
		BuildTerrain(obj, setting);
	}
	break;
	case TRIANGLE_NEIGHBORHOOD_BUILDING:
	{
		BuildBuilding(obj, setting);
		//Quad q = GetInscribedSquare();
		//obj.WriteQuadBox(q, q, 0.0, Random::NextDouble(setting.Height.Max, setting.PeakSize), true, false);
		obj.WriteTriangleBox(*this, *this, 0.0, Random::NextDouble(setting.Height.Max, setting.PeakSize), true, false);
	}
	break;
	case TRIANGLE_NEIGHBORHOOD_NEIGHBORHOOD:
	{
		Vector2 AB(m_b - m_a);
		Vector2 BC(m_c - m_b);
		Vector2 CA(m_a - m_c);

		Vector2 oAB = AB.Orthogonal();
		Vector2 oBC = (m_c - m_b).Orthogonal();
		Vector2 oCA = (m_a - m_c).Orthogonal();

		Line tA_B(Vector2(m_a), Vector2(m_a) + oAB);
		Line tB_A(Vector2(m_b), Vector2(m_b) + oAB);
		Line tB_C(Vector2(m_b), Vector2(m_b) + oBC);
		Line tC_B(Vector2(m_c), Vector2(m_c) + oBC);
		Line tC_A(Vector2(m_c), Vector2(m_c) + oCA);
		Line tA_C(Vector2(m_a), Vector2(m_a) + oCA);

		tA_B.Translation(-Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, AB.Length() / 2.0)));
		tB_A.Translation(Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, AB.Length() / 2.0)));
		tB_C.Translation(-Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, BC.Length() / 2.0)));
		tC_B.Translation(Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, BC.Length() / 2.0)));
		tC_A.Translation(-Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, CA.Length() / 2.0)));
		tA_C.Translation(Random::NextDouble(setting.Size.Min, fmin(setting.Size.Max, CA.Length() / 2.0)));

		Quad cornerA(
			m_a,
			Line::Intersection(Line(m_a, m_b), tA_B),
			Line::Intersection(tA_B, tA_C),
			Line::Intersection(tA_C, Line(m_a, m_c)));
		Quad cornerB(
			m_b,
			Line::Intersection(Line(m_b, m_c), tB_C),
			Line::Intersection(tB_C, tB_A),
			Line::Intersection(tB_A, Line(m_b, m_a)));
		Quad cornerC(
			m_c,
			Line::Intersection(Line(m_c, m_a), tC_A),
			Line::Intersection(tC_A, tC_B),
			Line::Intersection(tC_B, Line(m_b, m_c)));

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

		const Vector2 * as[3] = { &(cornerA.B()), &(cornerB.B()), &(cornerC.B()) };
		const Vector2 * bs[3] = { &(cornerB.D()), &(cornerC.D()), &(cornerA.D()) };
		const Vector2 * a, *b;


		for (uint64_t i = 0; i < 3; ++i)
		{
			a = as[i];
			b = bs[i];
			Vector2 direction(*b - *a);
			direction.Normalize();
			Vector2 ortho = direction.Orthogonal();

			double N = (*b - *a).Length();
			uint64_t buildingCount = 0;
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
						*a + direction * (currentPosition)+ortho * sizes[j] * 0.7);
					neighborhood.push_back(newBuilding);
				}
				currentPosition += fabs(sizes[j]);
			}
		}

		for (int64_t i = neighborhood.size() - 1; i >= 0; --i)
		{
			for (int64_t j = i - 1; j >= 0; --j)
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
				obj.WriteQuadBox(neighborhood[i], neighborhood[i], 0.0, Random::NextDouble(setting.Height.Min, setting.PeakSize), true, false);
			}
			else
			{
				obj.WriteQuadBox(neighborhood[i], neighborhood[i], 0.0, Random::NextDouble(setting.Height.Min, setting.Height.Max), true, false);
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

void Triangle::Shrink(double roadSizeAB, double roadSizeBC, double roadSizeCA)
{
	Line ab(m_a, m_b);
	Line bc(m_b, m_c);
	Line ca(m_c, m_a);

	ab.Translation(roadSizeAB / 2.0);
	bc.Translation(roadSizeBC / 2.0);
	ca.Translation(roadSizeCA / 2.0);

	m_a = Line::Intersection(ab, ca);
	m_b = Line::Intersection(ab, bc);
	m_c = Line::Intersection(bc, ca);
}

void Triangle::DrawBuildingGround (Object & obj, BuildingSetting & setting)
{
     obj.WriteTriangleGround(*this, setting);
}

void Triangle::DrawBuildingFloor (Object & obj, BuildingSetting & setting, int height)
{
     obj.WriteTriangleFloor(*this, setting, height);
}

void Triangle::DrawBuildingRoof (Object & obj, BuildingSetting & setting, int height)
{
     obj.WriteTriangleRoof(*this, setting, height);
}

void Triangle::DrawEmptySpace (Object & obj, BuildingSetting & setting, int height)
{
     obj.WriteTriangleEmptySpace(*this, setting, height);
}
