#include <Triangle.h>
#include <Line.h>
#include <Object.h>
#include <Random.h>
#include <Quad.h>

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

	double stopChance = Setting::Ease(area, double(75ull * 75ull), double(300ull * 300ull));
	if (stopChance < Random::NextDouble())
	{
		BuildingSetting s = Setting::GetInstance(Center());
		//BuildNeighborhood(obj);
		if(s.Height.Max > 0.0)
		{
			obj.m_obj << "v " << m_a.X() << " " << m_a.Y() << " 0\n";
			obj.m_obj << "v " << m_b.X() << " " << m_b.Y() << " 0\n";
			obj.m_obj << "v " << m_c.X() << " " << m_c.Y() << " 0\n";
			obj.m_obj << "f -3 -2 -1\n";
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
	uint64_t crtVersion = 1;
	
	//--------------
	// V0 - 1 Building
	//--------------
	if(0 == crtVersion)
	{
		BuildTerrain(obj, setting);
	}

	//--------------
	// V1 - 1 Building + shrink
	//--------------
	else if(1 == crtVersion)
	{
		double walkWaySize = 5.0;
		Shrink(walkWaySize);
		BuildTerrain(obj, setting);
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
