#ifndef METABALL_H
#define METABALL_H

#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <cmath>
#include <cstring>
#include "modelerglobals.h"
#include "bitmap.h"
#include <gl/glu.h>
#include <FL/fl_ask.H>
#include <iostream>
#include "vec.h"

class Vertix
{
public:
	Vec3f position=Vec3f(0.0f,0.0f,0.0f);
	float value=0.0f;
};

class Cube
{
public:
	Vertix* vertices[8];
};

const int CubeTable[256][13] = {
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//0
	//point 0 (0,0,0)
	{0,3,4, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//1


	//point 1 (0,0,1)
	{0,1,5, -1},//1,0

	{1,3,5, 3,5,4, -1},//1,1


	//point 2 (0,1,1)
	{1,2,6, -1},//1,0,0

	{1,2,6, 0,3,4,-1},//1,0,1

	{0,2,6, 6,5,0, -1},//1,1,0
	{5,6,4, 6,4,2, 4,2,3, -1},//1,1,1


	//point 3 (0,1,0)
	{2,3,7, -1},//1,0,0,0

	{2,0,7, 0,7,4, -1},//1,0,0,1

	{2,3,7, 0,1,5, -1},//1,0,1,0
	{4,7,5, 7,5,2, 5,2,1, -1},//1,0,1,1

	{7,3,6, 3,6,1, -1},//1,1,0,0
	{7,4,6, 4,6,0, 6,0,1, -1},//1,1,0,1
	{6,5,7, 5,7,0, 7,0,3, -1},//1,1,1,0
	{7,6,4, 6,4,5, -1},//1,1,1,1


	//point 4 (1,0,0)
	{4,8,11, -1},//1,0,0,0,0

	{3,0,11, 0,11,8, -1},//1,0,0,0,1

	{4,8,11, 0,1,5, -1},//1,0,0,1,0
	{5,8,1, 8,1,11, 1,11,3, -1},//1,0,0,1,1

	{4,8,11, 1,2,6, -1},//1,0,1,0,0
	{3,0,11, 0,11,8, 1,2,6, -1},//1,0,1,0,1
	{4,8,11, 0,2,6, 6,5,0, -1},//1,0,1,1,0
	{3,11,2, 11,2,8, 2,8,6, 8,6,5, -1},//1,0,1,1,1

	{8,4,11, 2,3,7, -1},//1,1,0,0,0
	{0,2,8, 2,8,7, 8,7,11, -1},//1,1,0,0,1
	{8,4,11, 0,1,5, 2,3,7, -1},//1,1,0,1,0
	{2,7,1, 7,1,11, 1,11,5, 11,5,8, -1},//1,1,0,1,1
	{8,4,11, 6,7,1, 7,1,3, -1},//1,1,1,0,0
	{7,6,11, 6,11,1, 11,1,8, 1,8,0, -1},//1,1,1,0,1
	{8,4,11, 6,5,7, 5,7,0, 7,0,3, -1},//1,1,1,1,0
	{6,5,7, 5,7,8, 7,8,11, -1},//1,1,1,1,1

	//point 5 (1,0,1)
	{5,8,9, -1},//1,0,0,0,0,0

	{5,8,9, 0,3,4, -1},//1,0,0,0,0,1

	{1,0,9, 0,9,8, -1},//1,0,0,0,1,0
	{1,3,9, 3,9,4, 9,4,8, -1},//1,0,0,0,1,1


	{5,8,9, 1,2,6, -1},//1,0,0,1,0,0
	{5,8,9, 1,2,6, 0,3,4, -1},//1,0,0,1,0,1
	{0,2,8, 2,8,6, 8,6,9, -1},//1,0,0,1,1,0
	{2,6,3, 6,3,9, 3,9,4, 9,4,8, -1},//1,0,0,1,1,1

	{5,8,9, 2,3,7, -1},//1,0,1,0,0,0
	{5,8,9, 4,0,7, 0,7,2, -1},//1,0,1,0,0,1
	{1,0,9, 0,9,8, 2,3,7, -1},//1,0,1,0,1,0
	{1,9,2, 9,2,8, 2,8,7, 8,7,4, -1},//1,0,1,0,1,1
	{5,8,9, 6,1,7, 1,7,3, -1},//1,0,1,1,0,0
	{5,8,9, 7,4,6, 4,6,0, 6,0,1, -1},//1,0,1,1,0,1
	{6,9,7, 9,7,0, 7,0,3, 9,0,8, -1},//1,0,1,1,1,0      p
	{7,4,6, 4,6,8, 6,8,9, -1},//1,0,1,1,1,1

	{9,5,11, 5,11,4, -1},//1,1,0,0,0,0,
	{11,9,3, 9,3,5, 3,5,0, -1},//1,1,0,0,0,1
	{9,1,11, 1,11,0, 11,0,4, -1},//1,1,0,0,1,0
	{9,1,11, 1,11,3, -1},//1,1,0,0,1,1
	{1,6,2, 9,5,11, 5,11,4, -1},//1,1,0,1,0,0
	{1,6,2, 11,9,3, 9,3,5, 3,5,0, -1},//1,1,0,1,0,1
	{0,2,4, 2,4,6, 4,6,11, 6,11,9, -1},//1,1,0,1,1,0     
	{11,9,3, 9,3,6, 3,6,2, -1},//1,1,0,1,1,1
	{2,3,7, 9,5,11, 5,11,4, -1},//1,1,1,0,0,0
	{2,7,0, 7,0,11, 0,11,5, 11,5,9, -1},//1,1,1,0,0,1
	{2,3,7, 9,11,1, 11,1,4, 1,4,0, -1},//1,1,1,0,1,0
	{9,1,11, 1,11,2, 11,2,7, -1},//1,1,1,0,1,1
	{9,5,11, 5,11,4, 6,1,7, 1,7,3, -1},//1,1,1,1,0,0
	{1,0,5, 6,7,9, 7,9,11, -1},//1,1,1,1,0,1
	{0,3,4, 6,7,9, 7,9,11, -1},//1,1,1,1,1,0
	{6,7,9, 7,9,11, -1},//1,1,1,1,1,1
	
	//point 6 (1,1,1)
	{6,9,10, -1},//1,0,0,0,0,0,0

	{6,9,10, 0,3,4, -1},//1,0,0,0,0,0,1

	{6,9,10, 0,1,5, -1 },//1,0,0,0,0,1,0
	{6,9,10, 1,3,5, 3,5,4, -1 },//1,0,0,0,0,1,1

	{2,1,10, 1,10,9, -1 },//1,0,0,0,1,0,0
	{2,1,10, 1,10,9, 0,3,4, -1 },//1,0,0,0,1,0,1
	{2,0,10, 0,10,5, 10,5,9, -1 },//1,0,0,0,1,1,0
	{2,10,3, 10,3,9, 3,9,4, 9,4,5, -1 },//1,0,0,0,1,1,1

	{6,9,10, 2,3,7, -1 },//1,0,0,1,0,0,0
	{6,9,10, 7,2,4, 2,4,0, -1 },//1,0,0,1,0,0,1
	{6,9,10, 2,3,7, 0,1,5, -1 },//1,0,0,1,0,1,0
	{6,9,10, 4,7,5, 7,5,2, 5,2,1, -1 },//1,0,0,1,0,1,1
	{1,3,9, 3,9,7, 9,7,10, -1 },//1,0,0,1,1,0,0
	{1,0,9, 0,9,4, 9,4,10, 4,10,7, -1 },//1,0,0,1,1,0,1
	{9,10,5, 10,5,7, 5,7,0, 7,0,3, -1 },//1,0,0,1,1,1,0
	{4,5,7, 5,7,9, 7,9,10, -1 },//1,0,0,1,1,1,1

	{6,9,10, 4,8,11, -1 },//1,0,1,0,0,0,0
	{6,9,10, 8,11,0, 11,0,3, -1 },//1,0,1,0,0,0,1
	{6,9,10, 4,8,11, 0,1,5, -1 },//1,0,1,0,0,1,0
	{6,9,10, 3,1,11, 1,11,5, 11,5,8, -1 },//1,0,1,0,0,1,1
	{4,8,11, 2,1,10, 1,10,9, -1 },//1,0,1,0,1,0,0
	{3,0,11, 0,11,8, 2,1,10, 1,10,9, -1 },//1,0,1,0,1,0,1
	{4,8,11, 2,0,10, 0,10,5, 10,5,9, -1 },//1,0,1,0,1,1,0
	{5,8,9, 2,3,10, 3,10,11, -1 },//1,0,1,0,1,1,1
	{2,3,7, 6,9,10, 4,8,11, -1 },//1,0,1,1,0,0,0
	{6,9,10, 0,2,8, 2,8,7, 8,7,11, -1 },//1,0,1,1,0,0,1
	{6,9,10, 2,3,7, 0,1,5, 4,8,11, -1 },//1,0,1,1,0,1,0
	{7,10,11, 5,8,9, 1,2,6, -1},//1,0,1,1,0,1,1
	{4,8,11, 1,3,9, 3,9,7, 9,7,10, -1 },//1,0,1,1,1,0,0
	{7,10,11, 1,9,0, 9,0,8, -1 },//1,0,1,1,1,0,1
	{0,3,4, 5,8,9, 7,10,11, -1 },//1,0,1,1,1,1,0
	{5,9,8, 7,10,11, -1 },//1,0,1,1,1,1,1

	{6,5,10, 5,10,8, -1 },//1,1,0,0,0,0,0
	{0,3,4, 6,5,10, 5,10,8, -1 },//1,1,0,0,0,0,1
	{8,10,0, 10,0,6, 0,6,1, -1 },//1,1,0,0,0,1,0
	{1,6,3, 6,3,10, 3,10,4, 10,4,8, -1 },//1,1,0,0,0,1,1
	{10,2,8, 2,8,1, 8,1,5, -1 },//1,1,0,0,1,0,0
	{0,3,4, 10,2,8, 2,8,1, 8,1,5, -1 },//1,1,0,0,1,0,1  p
	{2,0,10, 0,10,8, -1 },//1,1,0,0,1,1,0
	{3,1,11, 1,11,6 ,11,6,10, -1 },//1,1,0,0,1,1,1
	{2,3,7, 6,5,10, 5,10,8, -1 },//1,1,0,1,0,0,0
	{2,0,7, 0,7,4, 6,5,10, 5,10,8, -1 },//1,1,0,1,0,0,1  p
	{2,3,7, 8,10,0, 10,0,6, 0,6,1, -1 },//1,1,0,1,0,1,0  p
	{1,2,6, 10,7,8, 7,8,4, -1 },//1,1,0,1,0,1,1
	{1,3,5, 3,5,7, 5,7,8, 7,8,10,  -1 },//1,1,0,1,1,0,0
	{1,2,6, 7,4,10, 4,10,8, -1 },//1,1,0,1,1,0,1
	{8,10,0, 10,0,7, 0,7,3, -1 },//1,1,0,1,1,1,0
	{7,10,4, 10,4,8, -1 },//1,1,0,1,1,1,1

	{5,6,4, 6,4,10, 4,10,11, -1 },//1,1,1,0,0,0,0
	{5,0,6, 0,6,3, 6,3,10, 3,10,11, -1 },//1,1,1,0,0,0,1
	{6,10,1, 10,1,11, 1,11,0, 11,0,4, -1 },//1,1,1,0,0,1,0
	{3,1,11, 1,11,6, 11,6,10, -1 },//1,1,1,0,0,1,1
	{5,1,4, 1,4,2, 4,2,11, 2,11,10, -1 },//1,1,1,0,1,0,0
	{0,1,5, 2,3,10, 3,10,11, -1 },//1,1,1,0,1,0,1
	{2,0,10, 0,10,4, 10,4,11, -1 },//1,1,1,0,1,1,0
	{2,3,10, 3,10,11, -1 },//1,1,1,0,1,1,1
	{2,3,7, 5,6,4, 6,4,10, 4,10,11, -1 },//1,1,1,1,0,0,0
	{0,2,5, 2,5,6, 7,10,11, -1 },//1,1,1,1,0,0,1
	{1,2,6, 0,3,4, 7,10,11, -1 },//1,1,1,1,0,1,0
	{1,2,6, 7,10,11, -1 },//1,1,1,1,0,1,1
	{1,3,5, 3,5,4, 7,10,11, -1 },//1,1,1,1,1,0,0
	{0,1,5, 7,10,11, -1 },//1,1,1,1,1,0,1
	{0,3,4, 7,10,11, -1 },//1,1,1,1,1,1,0
	{7,10,11, -1 },//1,1,1,1,1,1,1




	//point 7 (1,1,0)
	{ 7,10,11, -1 },//1,0,0,0,0,0,0,0

	{ 0,3,4, 7,10,11, -1 },//1,0,0,0,0,0,0,1

	{ 0,1,5, 7,10,11, -1 },//1,0,0,0,0,0,1,0
	{ 1,3,5, 3,5,4, 7,10,11, -1 },//1,0,0,0,0,0,1,1

	{ 1,2,6, 7,10,11, -1 },//1,0,0,0,0,1,0,0
	{ 1,2,6, 0,3,4, 7,10,11, -1 },//1,0,0,0,0,1,0,1
	{ 0,2,5, 2,5,6, 7,10,11, -1 },//1,0,0,0,0,1,1,0
	{ 7,10,11, 5,6,4, 6,4,2, 4,2,3, -1 },//1,0,0,0,0,1,1,1
	
	{ 2,3,10, 3,10,11, -1 },//1,0,0,0,1,0,0,0
	{ 2,0,10, 0,10,4, 10,4,11, -1 },//1,0,0,0,1,0,0,1
	{ 0,1,5, 2,3,10, 3,10,11, -1 },//1,0,0,0,1,0,1,0
	{ 5,1,4, 1,4,2, 4,2,11, 2,11,10, -1 },//1,0,0,0,1,0,1,1
	{ 3,1,11, 1,11,6, 11,6,10, -1 },//1,0,0,0,1,1,0,0
	{ 6,10,1, 10,1,11, 1,11,0, 11,0,4, -1 },//1,0,0,0,1,1,0,1
	{ 5,0,6, 0,6,3, 6,3,10, 3,10,11, -1 },//1,0,0,0,1,1,1,0
	{ 5,6,4, 6,4,10, 4,10,11, -1 },//1,0,0,0,1,1,1,1

	{ 7,10,4, 10,4,8, -1 },//1,0,0,1,0,0,0,0
	{ 8,10,0, 10,0,7, 0,7,3, -1 },//1,0,0,1,0,0,0,1
	{ 1,2,6, 7,4,10, 4,10,8, -1 },//1,0,0,1,0,0,1,0
	{ 1,3,5, 3,5,7, 5,7,8, 7,8,10,  -1 },//1,0,0,1,0,0,1,1
	{ 1,2,6, 10,7,8, 7,8,4, -1 },//1,0,0,1,0,1,0,0
	{ 1,2,6, 8,10,0, 10,0,7, 0,7,3, -1 },//1,0,0,1,0,1,0,1
	{ 0,2,5, 2,5,6, 7,10,4, 10,4,8, -1 },//1,0,0,1,0,1,1,0
	{ 2,3,7, 6,5,10, 5,10,8, -1 },//1,0,0,1,0,1,1,1

	{ 3,1,11, 1,11,6 ,11,6,10, -1 },//1,0,0,1,1,0,0,0
	{ 2,0,10, 0,10,8, -1 },//1,0,0,1,1,0,0,1
	{ 1,5,0, 10,2,8, 2,8,3, 8,3,4, -1 },//1,0,0,1,1,0,1,0
	{ 10,2,8, 2,8,1, 8,1,5, -1 },//1,0,0,1,1,0,1,1
	{ 1,6,3, 6,3,10, 3,10,4, 10,4,8, -1 },//1,0,0,1,1,1,0,0
	{ 8,10,0, 10,0,6, 0,6,1, -1 },//1,0,0,1,1,1,0,1
	{ 0,3,4, 6,5,10, 5,10,8, -1 },//1,0,0,1,1,1,1,0
	{ 6,5,10, 5,10,8, -1 },//1,0,0,1,1,1,1,1

	{ 5,9,8, 7,10,11, -1 },//1,0,1,0,0,0,0,0
	{ 0,3,4, 5,8,9, 7,10,11, -1 },//1,0,1,0,0,0,0,1
	{ 7,10,11, 1,9,0, 9,0,8, -1 },//1,0,1,0,0,0,1,0
	{ 4,8,11, 1,3,9, 3,9,7, 9,7,10, -1 },//1,0,1,0,0,0,1,1
	{ 7,10,11, 5,8,9, 1,2,6, -1 },//1,0,1,0,0,1,0,0
	{ 0,3,4, 5,8,9, 1,2,6, 7,10,11, -1 },//1,0,1,0,0,1,0,1
	{ 7,10,11, 0,2,8, 2,8,6, 8,6,9, -1 },//1,0,1,0,0,1,1,0
	{ 2,3,7, 6,9,10, 4,8,11, -1 },//1,0,1,0,0,1,1,1

	{ 5,8,9, 2,3,10, 3,10,11, -1 },//1,0,1,0,1,0,0,0
	{ 5,9,8, 2,0,10, 0,10,4, 10,4,11, -1 },//1,0,1,0,1,0,0,1
	{ 1,9,0, 9,0,8, 2,3,10, 3,10,11, -1 },//1,0,1,0,1,0,1,0
	{ 4,8,11, 2,1,10, 1,10,9, -1 },//1,0,1,0,1,0,1,1
	{ 5,8,9, 3,1,11, 1,11,6, 11,6,10, -1 },//1,0,1,0,1,1,0,0
	{ 6,9,10, 4,8,11, 0,1,5, -1 },//1,0,1,0,1,1,0,1
	{ 6,9,10, 8,11,0, 11,0,3, -1 },//1,0,1,0,1,1,1,0
	{ 6,9,10, 4,8,11, -1 },//1,0,1,0,1,1,1,1

	{ 4,5,7, 5,7,9, 7,9,10, -1 },//1,0,1,1,0,0,0,0
	{ 9,10,5, 10,5,7, 5,7,0, 7,0,3, -1 },//1,0,1,1,0,0,0,1
	{ 1,0,9, 0,9,4, 9,4,10, 4,10,7, -1 },//1,0,1,1,0,0,1,0
	{ 1,3,9, 3,9,7, 9,7,10, -1 },//1,0,1,1,0,0,1,1
	{ 1,2,6, 4,5,7, 5,7,9, 7,9,10, -1 },//1,0,1,1,0,1,0,0
	{ 6,9,10, 2,3,7, 0,1,5, -1 },//1,0,1,1,0,1,0,1
	{ 6,9,10, 7,2,4, 2,4,0, -1 },//1,0,1,1,0,1,1,0
	{ 6,9,10, 2,3,7, -1 },//1,0,1,1,0,1,1,1

	{ 2,10,3, 10,3,9, 3,9,4, 9,4,5, -1 },//1,0,1,1,1,0,0,0
	{ 2,0,10, 0,10,5, 10,5,9, -1 },//1,0,1,1,1,0,0,1
	{ 2,1,10, 1,10,9, 0,3,4, -1 },//1,0,1,1,1,0,1,0
	{ 2,1,10, 1,10,9, -1 },//1,0,1,1,1,0,1,1
	{ 6,9,10, 1,3,5, 3,5,4, -1 },//1,0,1,1,1,1,0,0
	{ 6,9,10, 0,1,5, -1 },//1,0,1,1,1,1,0,1
	{ 6,9,10, 0,3,4, -1 },//1,0,1,1,1,1,1,0
	{ 6,9,10, -1 },//1,0,1,1,1,1,1,1

	{ 6,7,9, 7,9,11, -1 },//1,1,0,0,0,0,0,0
	{ 0,3,4, 6,7,9, 7,9,11, -1 },//1,1,0,0,0,0,0,1
	{ 1,0,5, 6,7,9, 7,9,11, -1 },//1,1,0,0,0,0,1,0
	{ 1,3,5, 3,5,4, 6,7,9, 7,9,11, -1 },//1,1,0,0,0,0,1,1
	{ 9,1,11, 1,11,2, 11,2,7, -1 },//1,1,0,0,0,1,0,0
	{ 0,3,4, 9,1,11, 1,11,2, 11,2,7, -1 },//1,1,0,0,0,1,0,1
	{ 2,7,0, 7,0,11, 0,11,5, 11,5,9, -1 },//1,1,0,0,0,1,1,0
	{ 2,3,7, 9,5,11, 5,11,4, -1 },//1,1,0,0,0,1,1,1

	{ 11,9,3, 9,3,6, 3,6,2, -1 },//1,1,0,0,1,0,0,0
	{ 0,2,4, 2,4,6, 4,6,11, 6,11,9, -1 },//1,1,0,0,1,0,0,1     
	{ 0,1,5, 11,3,9, 3,9,2, 9,2,6, -1 },//1,1,0,0,1,0,1,0
	{ 1,6,2, 9,5,11, 5,11,4, -1 },//1,1,0,0,1,0,1,1
	{ 9,1,11, 1,11,3, -1 },//1,1,0,0,1,1,0,0
	{ 9,1,11, 1,11,0, 11,0,4, -1 },//1,1,0,0,1,1,0,1
	{ 11,9,3, 9,3,5, 3,5,0, -1 },//1,1,0,0,1,1,1,0
	{ 9,5,11, 5,11,4, -1 },//1,1,0,0,1,1,1,1

	{ 7,4,6, 4,6,8, 6,8,9, -1 },//1,1,0,1,0,0,0,0
	{ 6,9,7, 9,7,0, 7,0,3, 9,0,8, -1 },//1,1,0,1,0,0,0,1
	{ 0,1,5, 7,6,4, 6,4,9, 4,9,8, -1 },//1,1,0,1,0,0,1,0
	{ 5,8,9, 6,1,7, 1,7,3, -1 },//1,1,0,1,0,0,1,1
	{ 1,9,2, 9,2,8, 2,8,7, 8,7,4, -1 },//1,1,0,1,0,1,0,0
	{ 1,0,9, 0,9,8, 2,3,7, -1 },//1,1,0,1,0,1,0,1
	{ 5,8,9, 4,0,7, 0,7,2, -1 },//1,1,0,1,0,1,1,0
	{ 5,8,9, 2,3,7, -1 },//1,1,0,1,0,1,1,1

	{ 2,6,3, 6,3,9, 3,9,4, 9,4,8, -1 },//1,1,0,1,1,0,0,0
	{ 0,2,8, 2,8,6, 8,6,9, -1 },//1,1,0,1,1,0,0,1
	{ 5,8,9, 1,2,6, 0,3,4, -1 },//1,1,0,1,1,0,1,0
	{ 5,8,9, 1,2,6, -1 },//1,1,0,1,1,0,1,1
	{ 1,3,9, 3,9,4, 9,4,8, -1 },//1,1,0,1,1,1,0,0
	{ 1,0,9, 0,9,8, -1 },//1,1,0,1,1,1,0,1
	{ 5,8,9, 0,3,4, -1 },//1,1,0,1,1,1,1,0
	{ 5,8,9, -1 },//1,1,0,1,1,1,1,1


	{ 6,5,7, 5,7,8, 7,8,11, -1 },//1,1,1,0,0,0,0,0
	{ 0,3,4, 6,5,7, 5,7,8, 7,8,11, -1 },//1,1,1,0,0,0,0,1
	{ 7,6,11, 6,11,1, 11,1,8, 1,8,0, -1 },//1,1,1,0,0,0,1,0
	{ 8,4,11, 6,7,1, 7,1,3, -1 },//1,1,1,0,0,0,1,1
	{ 2,7,1, 7,1,11, 1,11,5, 11,5,8, -1 },//1,1,1,0,0,1,0,0
	{ 8,4,11, 0,1,5, 2,3,7, -1 },//1,1,1,0,0,1,0,1
	{ 0,2,8, 2,8,7, 8,7,11, -1 },//1,1,1,0,0,1,1,0
	{ 8,4,11, 2,3,7, -1 },//1,1,1,0,0,1,1,1

	{ 3,11,2, 11,2,8, 2,8,6, 8,6,5, -1 },//1,1,1,0,1,0,0,0
	{ 4,8,11, 0,2,6, 6,5,0, -1 },//1,1,1,0,1,0,0,1
	{ 3,0,11, 0,11,8, 1,2,6, -1 },//1,1,1,0,1,0,1,0
	{ 4,8,11, 1,2,6, -1 },//1,1,1,0,1,0,1,1
	{ 5,8,1, 8,1,11, 1,11,3, -1 },//1,1,1,0,1,1,0,0
	{ 4,8,11, 0,1,5, -1 },//1,1,1,0,1,1,0,1
	{ 3,0,11, 0,11,8, -1 },//1,1,1,0,1,1,1,0
	{ 4,8,11, -1 },//1,1,1,0,1,1,1,1


	{ 7,6,4, 6,4,5, -1 },//1,1,1,1,0,0,0,0
	{ 6,5,7, 5,7,0, 7,0,3, -1 },//1,1,1,1,0,0,0,1
	{ 7,4,6, 4,6,0, 6,0,1, -1 },//1,1,1,1,0,0,1,0
	{ 7,3,6, 3,6,1, -1 },//1,1,1,1,0,0,1,1
	{ 4,7,5, 7,5,2, 5,2,1, -1 },//1,1,1,1,0,1,0,0
	{ 2,3,7, 0,1,5, -1 },//1,1,1,1,0,1,0,1
	{ 2,0,7, 0,7,4, -1 },//1,1,1,1,0,1,1,0
	{ 2,3,7, -1 },//1,1,1,1,0,1,1,1

	{ 5,6,4, 6,4,2, 4,2,3, -1 },//1,1,1,1,1,0,0,0
	{ 0,2,6, 6,5,0, -1 },//1,1,1,1,1,0,0,1
	{ 1,2,6, 0,3,4,-1 },//1,1,1,1,1,0,1,0
	{ 1,2,6, -1 },//1,1,1,1,1,0,1,1
	{ 1,3,5, 3,5,4, -1 },//1,1,1,1,1,1,0,0
	{ 0,1,5, -1 },//1,1,1,1,1,1,0,1
	{ 0,3,4, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },//1,1,1,1,1,1,1,0
	{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },//1,1,1,1,1,1,1,1

};

//middle point of each edge
const float edges[12][3] =
{
	{0.0,0.0,0.5},
	{0.0,0.5,1.0},
	{0.0,1.0,0.5},
	{0.0,0.5,0.0},
	{0.5,0.0,0.0},
	{0.5,0.0,1.0},
	{0.5,1.0,1.0},
	{0.5,1.0,0.0},
	{1.0,0.0,0.5},
	{1.0,0.5,1.0},
	{1.0,1.0,0.5},
	{1.0,0.5,0.0},
};

struct Metaball
{
	Vec3f position;
	float radius;
};


class CubeVertices
{
public:
	CubeVertices(int block);
	void add_metabll(Vec3f p, float r);
	void Update();
	void drawSurface();
	Metaball metaball[5];
private:
	const int max_blocks = 200;
	int n_metaball=0;
	int n_blocks;
	int n_cubes;
	float size;
	Vertix* vertices;
	Cube* cubes;

};


#endif