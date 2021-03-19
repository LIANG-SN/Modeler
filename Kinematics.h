#pragma once

#include "mat.h"
#include "vec.h"
#include <FL/gl.h>
#include <iostream>
//#include "modelerglobals.h"
#include "modelerapp.h"
#include "modelerui.h"
class CCD
{
public:
	CCD() {};
	void start(double* destination);
	void getWorld(double*);
	void reset(double *);
	void updateCameraMatrix(double* m);
	void updateJ0() { updateJoint(j0); }
	void updateJ1() { updateJoint(j1); }
	void updateEnd() { updateJoint(end);}
	double c[16]; // camera mat, column major
	double j0[3]; // joint
	double j1[3];
	double end[3];
	const double constrain_j1{ 15 };
	const double constrain_j0{ 180 };
	const double maxLoop{ 20 };
	double axis_j0[20][3];
	double axis_j1[20][3];
	double  rot_j1[20] = { 0 };
	double  rot_j0[20] = { 0 };
	double destination[3];
	unsigned int index{ 0 };
	//int flag{ 1 };
private:
	void updateJoint(double*); // length: 3
};

extern CCD ccd;