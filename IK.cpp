

#include "IK.h"
#include "mat.h"

Hand::Hand(int t)
{
	learning_rate = 0.05;
	theta_x = 0;
	theta_y = 0;
	theta_z = 0;
	phi = 0;

	type = t;

}

void Hand::init()
{
	theta_x = 0;
	theta_y = 0;
	theta_z = 0;
	phi = 0;
	UpdatePoints();
}

void Hand::UpdatePoints()
{

	Mat3f Rz = Mat3f(cos(theta_z), -sin(theta_z), 0,
					sin(theta_z), cos(theta_z), 0,
					0, 0, 1);
	Mat3f Rx= Mat3f(1, 0, 0,
					0, cos(theta_x), -sin(theta_x),
					0, sin(theta_x), cos(theta_x));
	Mat3f Ry = Mat3f(cos(theta_y),  0, sin(theta_y),
						0, 1, 0,
						-sin(theta_y), 0, cos(theta_y));
	Mat3f Rx_phi = Mat3f(1, 0, 0,
		0, cos(phi), -sin(phi),
		0, sin(phi), cos(phi));

	point1 = v1;
	point2 = Ry * (Rx * (Rz * v2)) + point1;
	point_end = Ry * (Rx * (Rz * ( Rx_phi * v3 + v2)))+point1;

	delta = (target - point_end).length();

	cout << point2 << point_end << endl;
	
}

void Hand::apply_Jacobian(int counter)
{
	Vec3f temp1 = (point_end - point1) ^ (target - point1);
	axis_theta_x = Vec3f(1, 0, 0);

	//if (temp1 * axis_theta_x < 0)
	//{ 
	//	//sign_theta_x = -1;
	//	axis_theta_x = -axis_theta_x;
	//}




	axis_theta_z = point1 ^ (point2 - point1);
	//if (temp1 * axis_theta_z < 0)
	//{
	//	//sign_theta_z = -1;
	//	axis_theta_z = -axis_theta_z;
	//}



	Vec3f temp2 = (point_end - point2) ^ (target - point2);
	axis_theta_y = Vec3f(0,1,0);

	//if (temp2 * axis_theta_y < 0)
	//{
	//	//sign_theta_y = -1;
	//	axis_theta_y = -axis_theta_y;
	//}

	axis_phi =  (point1 - point2)^ (point_end - point2);

	//if (temp2 * axis_phi < 0)
	//{ 
	//	//sign_phi = -1;
	//	axis_phi = -axis_phi;
	//}


	Vec3f J[4] = { axis_theta_x ^ (point_end - point1), axis_theta_z ^ (point_end - point1),
	axis_theta_y ^ (point_end - point1) , axis_phi ^ (point_end - point2) };


	float JTJ[16];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			JTJ[i * 4 + j] = J[i] * J[j];
		}
	}

	Mat4f inv = Mat4f(JTJ[0], JTJ[1], JTJ[2], JTJ[3],
						  JTJ[4], JTJ[5], JTJ[6], JTJ[7],
						  JTJ[8], JTJ[9], JTJ[10], JTJ[11],
						  JTJ[12], JTJ[13], JTJ[14], JTJ[15]).inverse();



	Vec3f delta_t = target - point_end;
	Vec4f JT_delta = Vec4f(0, 0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			JT_delta[i] += J[i][j] * delta_t[j];
		}
	}

	

	Vec4f delta_angle = inv * JT_delta;

	float x = theta_x + learning_rate * delta_angle[0] / sqrt(counter + 1)*(1+(type==0));
	if(x < M_PI && x > -M_PI / 2)
		theta_x += 0.5 * learning_rate * delta_angle[0] / sqrt(counter+1) * (1 + (type == 0));
	else if(x > M_PI )
		theta_x = M_PI;
	else
		theta_x=-M_PI / 2;

	float z = theta_z + learning_rate * delta_angle[1] / sqrt(counter + 1) * (1 + (type == 1));
	if ( z > -M_PI / 2 &&
		z < M_PI / 6)
		theta_z += learning_rate * delta_angle[1] / sqrt(counter + 1) * (1 + (type == 1));
	else if (z < -M_PI / 2)
		theta_z = -M_PI / 2;
	else
		theta_z = M_PI / 6;

	float y = theta_y + learning_rate * delta_angle[2] / sqrt(counter + 1) * (1 + (type == 2));
	if ( y > -M_PI / 2 &&
		y < M_PI / 6)
		theta_y += learning_rate * delta_angle[2] / sqrt(counter + 1) * (1 + (type == 2));
	else if (y < -M_PI / 2)
		theta_y = -M_PI / 2;
	else
		theta_y = M_PI / 6;


	float p = phi + learning_rate * delta_angle[3] / sqrt(counter + 1) * (1 + (type == 3));
	if ( p > -M_PI / 3 &&
		p < M_PI / 2)
		phi += learning_rate * delta_angle[3] / sqrt(counter + 1) * (1 + (type == 3));
	else if (p < -M_PI / 3)
		phi = -M_PI / 3;
	else
		phi = M_PI / 2;


	cout << theta_x << " " << theta_z << " " << theta_y << " " << phi << endl;;
}