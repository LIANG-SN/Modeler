#pragma once

#include "Kinematics.h"

void CCD::updateCameraMatrix(double* m)
{
	for (int i = 0; i < 16; i++)
		c[i] = m[i];
}
void CCD::getWorld(double* m)
{
	// camera matrix
	Mat4d c44(c[0], c[4], c[8], c[12],
		c[1], c[5], c[9], c[13],
		c[2], c[6], c[10], c[14],
		c[3], c[7], c[11], c[15]);
	c44 = c44.inverse();
	glGetDoublev(GL_MODELVIEW_MATRIX, m);
	Mat4d m44(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7],
		m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
	m44 = m44.transpose();
	m44 = c44 * m44;
	m44.getGLMatrix(m); // this return transpose......
	
}
void CCD::updateJoint(double* j)
{
	double m[16];
	getWorld(m);
	j[0] = m[12];
	j[1] = m[13];
	j[2] = m[14];
}
void CCD::reset(double* d)
{
	for (int i = 0; i < 3; i++)
		destination[i] = d[i];
	for (int i = 0; i < maxLoop/2; i++)
	{
		rot_j0[i] = 0;
		rot_j1[i] = 0;
		for (int j = 0; j < 3; j++)
		{
			axis_j0[i][j] = 0;
			axis_j1[i][j] = 0;
		}
	}
}
void CCD::start(double* d)
{
	if (index == 0)
	{
		reset(d);
	}
	using namespace std;
	int i = index / 2;
	if ((index % 2) == 0)
	{
		Vec3d j12end(end[0] - j1[0], end[1] - j1[1], end[2] - j1[2]);
		Vec3d j12d(d[0] - j1[0], d[1] - j1[1], d[2] - j1[2]);
		j12end.normalize(); j12d.normalize();
		Vec3d norm = j12end ^ j12d;
		norm.normalize();
		for (int j = 0; j < 3; j++)
			axis_j1[i][j] = norm[j];
		rot_j1[i] = min(constrain_j1, acos(j12end * j12d) / M_PI * 180);
		cout << "j1: " <<  rot_j1[i] << endl;
	}
	else
	{
		// j0
		Vec3d j02end(end[0] - j0[0], end[1] - j0[1], end[2] - j0[2]);
		Vec3d j02d(d[0] - j0[0], d[1] - j0[1], d[2] - j0[2]);
		j02end.normalize(); j02d.normalize();
		Vec3d norm = j02end ^ j02d;
		norm.normalize();
		for (int j = 0; j < 3; j++)
			axis_j0[i][j] = (double)norm[j];
		rot_j0[i] = min(constrain_j0, acos(j02end * j02d) / M_PI * 180);
	    
		cout << "j0: " << rot_j0[i] << endl;
		/*cout << "j0 axis : " << axis_j0[0] << "," << axis_j0[1] << ", " 
			<< axis_j0[2] << endl;*/
		cout << "j0 coord: " << j0[0] << "," << j0[1] << ", " << j0[2] << endl;
		cout << "end coord: " << end[0] << "," << end[1] << ", " << end[2] << endl;
	}
	index++;
}

CCD ccd;