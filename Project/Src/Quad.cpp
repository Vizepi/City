#include <Quad.h>
#include <Line.h>
#include <Random.h>
#include <Object.h>
#include <iostream>
#include <vector>

struct Type
{
	int type;
	double size;
};

void Quad::Subdivide(Object & obj)
{
	Random::Seed(m_seed);
	uint64_t type = Random::NextDouble() < 0.5 ? 2 : Random::NextDouble() < 0.5 ? 0 : 1;
	double area = Area();

	// Change type
	std::vector<Type> types;
	types.push_back({ 2, 2.5 });
	types.push_back({ 3, 0.5 }); /*TESTEST*/types.pop_back();
	double sizes = 3.0; /*TESTEST*/sizes -= 0.5;
	double v = ((m_c - m_b).Length() + (m_a - m_d).Length()) / ((m_b - m_a).Length() + (m_d - m_c).Length());
	if (v >= 1.25 && v <= 2.5)
	{
		double s = Setting::Ease(v, 1.25, 2.5);
		types.push_back({ 1, s });
		sizes += s;
	}
	v = ((m_b - m_a).Length() + (m_d - m_c).Length()) / ((m_c - m_b).Length() + (m_a - m_d).Length());
	if (v >= 1.25 && v <= 2.5)
	{
		double s = Setting::Ease(v, 1.25, 2.5);
		types.push_back({ 0, s });
		sizes += s;
	}
	v = (m_c - m_a).Length() / (m_d - m_b).Length();
	if (v >= 0.75 && v <= 1.0)
	{
		double s = Setting::Ease(v, 0.75, 1.0);
		types.push_back({ 4, s }); /*TESTEST*/types.pop_back();
		sizes += s; /*TESTEST*/sizes -= s;
	}
	v = (m_d - m_b).Length() / (m_c - m_a).Length();
	if (v >= 0.75 && v <= 1.0)
	{
		double s = Setting::Ease(v, 0.75, 1.0);
		types.push_back({ 5, s }); /*TESTEST*/types.pop_back();
		sizes += s; /*TESTEST*/sizes -= s;
	}
	int currentType = -1;
	double size = Random::NextDouble(0.0, sizes);
	do
	{
		currentType++;
		sizes -= types[currentType].size;
	} while (sizes >= 0.0 && currentType < types.size() - 1);
	type = types[currentType].type;

	double stopChance = Setting::Ease(area, double(75ull * 75ull), double(300ull * 300ull));
	if (stopChance < Random::NextDouble())
	{
		//BuildNeighborhood(obj);
		obj.m_obj << "v " << m_a.X() << " " << m_a.Y() << " 0\n";
		obj.m_obj << "v " << m_b.X() << " " << m_b.Y() << " 0\n";
		obj.m_obj << "v " << m_c.X() << " " << m_c.Y() << " 0\n";
		obj.m_obj << "v " << m_d.X() << " " << m_d.Y() << " 0\n";
		obj.m_obj << "f -1 -2 -3 -4\n";
	}
	else
	{
		static int tab = 0;
		tab++;
		for(int i = 0; i < tab; ++i) std::cout << " ";
		std::cout << type << std::endl;
		double roadSize = Setting::Ease(area, double(200ull * 200ull), double(2000ull * 2000ull)) * ROAD_SIZE_COEF / 2.0 + SIDEWALK_SIZE;
		switch (type)
		{
		case 0: // Divided once edges AB and CD
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
			q1.Subdivide(obj);
			q2.Subdivide(obj);
		}
		break;
		case 1:
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
			q1.Subdivide(obj);
			q2.Subdivide(obj);
		}
		break;
		case 2:
		{
			double abPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			double bcPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			double cdPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			double daPosition = Random::NextDouble(QUAD_EDGE_DIVISION_CENTER - QUAD_EDGE_DIVISION_INTERVAL_HALF, QUAD_EDGE_DIVISION_CENTER + QUAD_EDGE_DIVISION_INTERVAL_HALF);
			Vector2 pAB = m_a + (m_b - m_a) * abPosition;
			Vector2 pBC = m_b + (m_c - m_b) * bcPosition;
			Vector2 pCD = m_d + (m_c - m_d) * cdPosition;
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
			q1.Subdivide(obj);
			q2.Subdivide(obj);
			q3.Subdivide(obj);
			q4.Subdivide(obj);
		}
		break;
		case 3:
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
			t1.Subdivide(obj);
			t2.Subdivide(obj);
			t3.Subdivide(obj);
			t4.Subdivide(obj);
		}
		break;
		case 4:
		{
			Triangle t1(Random::NextUInt64(), m_a, m_b, m_c);
			t1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), m_c, m_d, m_a);
			t2.Shrink(IsShrinkedCD() ? 0.0 : roadSize, IsShrinkedDA() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			t1.Subdivide(obj);
			t2.Subdivide(obj);
		}
			break;
		case 5:
		{
			Triangle t1(Random::NextUInt64(), m_b, m_c, m_d);
			t1.Shrink(IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCD() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			Triangle t2(Random::NextUInt64(), m_d, m_a, m_b);
			t2.Shrink(IsShrinkedDA() ? 0.0 : roadSize, IsShrinkedAB() ? 0.0 : roadSize, roadSize);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			t1.SetABShrinked(true).SetBCShrinked(true).SetCAShrinked(true);
			t1.Subdivide(obj);
			t2.Subdivide(obj);
		}
			break;
		default:
			break;
		}
		tab--;
	}
}

void Quad::BuildNeighborhood(Object & obj) // Add const vector3 &v with the downtown
{
	uint64_t crtVersion = 1;
	//
	// Get settings
	BuildingSetting s = Setting::GetInstance(Center());

	//--------------
	// V0 - 1 Building
	//--------------
	if (0 == crtVersion)
	{
		BuildTerrain(obj, s);
	}

	//--------------
	// V1 - 1 Building + shrink
	//--------------
	else if (1 == crtVersion)
	{
		double walkWaySize = 5.0;
		Shrink(walkWaySize, walkWaySize, walkWaySize, walkWaySize);
		BuildTerrain(obj, s);
	}
	//--------------
	// V2 - Neighborhood
	//--------------
	else if (2 == crtVersion)
	{
		double walkWaySize = 5.0;
		Quad innerQuad(*this);
		innerQuad.Shrink(walkWaySize, walkWaySize, walkWaySize, walkWaySize);

		//
		// Bat 1
		Vector2 a = m_a;
		Vector2 b = Projection(Vector2(innerQuad.A() - m_a), Vector2(m_b - m_a)); // innerQuad.A() on m_a m_b
		Vector2 c = innerQuad.A();
		Vector2 d = Projection(Vector2(innerQuad.A() - m_a), Vector2(m_d - m_a));
		innerQuad.BuildTerrain(obj, s);
	}

	//
	// Random seed
	/*random::seed(m_seed);

	//
	// Attributs
	//double MaxQuadBuildingSize = 75.0;
	//double MinQuadBuildingSize = 20.0;

	Setting::GetINstance(VEC2

	bool isWellFormed = true;

	//
	// Check space for buildings
	double ab = (m_a - m_b).Length();
	double bc = (m_b - m_c).Length();
	double cd = (m_c - m_d).Length();
	double da = (m_d - m_a).Length();
	if(ab < MinQuadBuildingSize
		|| bc < MinQuadBuildingSize
		|| cd < MinQuadBuildingSize
		|| da < MinQuadBuildingSize)
	{
		isWellFormed = false;
	}

	//
	// Divide Neighborhood ans build buildings
	if(isWellFormed)
	{
		uint64_t nbBatAB = ab / MinQuadBuildingSize;
		if(ab > 2.0*MinQuadBuildingSize)
		{

		}
		while(crtLength < ab)
		{

		}
	}*/
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

void Quad::DrawBuildingGround (Object & obj, BuildingSetting & setting)
{
}

void Quad::DrawBuildingFloor  (Object & obj, BuildingSetting & setting)
{
}

void Quad::DrawBuildingRoof   (Object & obj, BuildingSetting & setting)
{
}

void Quad::DrawEmptySpace     (Object & obj, BuildingSetting & setting)
{
}
