#pragma once

#ifndef IK_H
#define IK_H

#include <FL/gl.h>
#include <cmath>
#include <cstring>
#include "bitmap.h"
#include <gl/glu.h>
#include <FL/fl_ask.H>
#include <iostream>
#include "Metaball.h"

class Hand {
public:
	Hand(int t);

	static Vec3f target;
	static Vec3f v1;
	static Vec3f v2 ;
	static Vec3f v3;

	float learning_rate;
	float theta_x = 0;
	float theta_y = 0;
	float theta_z = 0;
	float phi = 0;
	float delta;

	int type;


	Vec3f point1;
	Vec3f point2;
	Vec3f point_end;

	Vec3f axis_theta_x;
	Vec3f axis_theta_y;
	Vec3f axis_theta_z;
	Vec3f axis_phi;
	void init();
	void UpdatePoints();
	void apply_Jacobian(int counter = 1);
};



#endif IK_H

