#pragma once

class Texture;

class Environment
{
public:
	Environment(Texture* cubeMap, Texture* diffuse, Texture* specular, Texture* lookUpTable);

	Texture* GetCubeMap() { return _cubeMap; }
	Texture* GetDiffuse() { return _diffuse; }
	Texture* GetSpecular() { return _specular; }
	Texture* GetLookUpTable() { return _lookUpTable; }

private:
	Texture* _cubeMap = nullptr;
	Texture* _diffuse = nullptr;
	Texture* _specular = nullptr;
	Texture* _lookUpTable = nullptr;

};

