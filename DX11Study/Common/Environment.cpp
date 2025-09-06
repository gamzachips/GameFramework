#include "pch.h"
#include "Environment.h"

Environment::Environment(Texture* cubeMap, Texture* diffuse, Texture* specular, Texture* lookUpTable)
{
	_cubeMap = cubeMap;
	_diffuse = diffuse;
	_specular = specular;
	_lookUpTable = lookUpTable;
}
