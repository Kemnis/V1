#include "stdafx.h"

Colision::Colision(GameObject*Go1,GameObject*Go2)
{

}


bool Colision::Initialize(GameObject*Go1,GameObject*Go2)
{
	//float SizeX = 256.0f, SizeZ = 256.0f;

	//vec3 GridQuadSize = vec3(1.0f / SizeX * SizeX, 0.0f, 1.0f / SizeZ * SizeZ);

	//vec2 GridCoord = vec2((int)(pos.x / GridQuadSize.x), (int)(pos.z / GridQuadSize.z));

	//if (GridCoord.x>(SizeX / 2) || GridCoord.x<-(SizeX / 2) || GridCoord.y>(SizeZ / 2) || GridCoord.y <-(SizeZ / 2))
	//{
	//	return false;
	//}

	//int index = ((SizeZ/2)*SizeX) + GridCoord.y *SizeX + (SizeX/2) + GridCoord.x;
	//pos.y = Mesh.GetVertex(index).y + 3;

	return true;
}