#pragma once

struct BuildingSize
{
	double Min;
	double Max;
};

struct BuildingSetting
{
	BuildingSize Size;
	BuildingSize Height;
};

struct Setting
{
	
	static BuildingSetting Outskirt;
	static BuildingSetting Citycenter;

};
