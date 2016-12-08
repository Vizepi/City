#pragma once

#include <fstream>

class Object
{

public:

	Object(const std::string & filename);
    ~Object();

	void WriteGround();
	void WriteFloor();
	void WriteRoof();
	void WriteEmptySpace();

private:

	std::ofstream m_obj;

};