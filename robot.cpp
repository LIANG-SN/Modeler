// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <cmath>
#include "modelerglobals.h"

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// To make a SampleModel, we inherit off of ModelerView
class RobotModel : public ModelerView
{
public:
	RobotModel(int x, int y, int w, int h, char* label)
		: ModelerView(x, y, w, h, label) { }

	virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char* label)
{
	return new RobotModel(x, y, w, h, label);
}

void draw_feet_helper(float v[][3])
{
	// actually a Triangular prism
	glBegin(GL_TRIANGLES);
	glVertex3fv(v[1]);
	glVertex3fv(v[5]);
	glVertex3fv(v[3]);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3fv(v[0]);
	glVertex3fv(v[4]);
	glVertex3fv(v[2]);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3fv(v[0]);
	glVertex3fv(v[1]);
	glVertex3fv(v[5]);
	glVertex3fv(v[4]);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3fv(v[0]);
	glVertex3fv(v[1]);
	glVertex3fv(v[3]);
	glVertex3fv(v[2]);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3fv(v[2]);
	glVertex3fv(v[3]);
	glVertex3fv(v[5]);
	glVertex3fv(v[4]);

	glEnd();

}
void draw_prism5_helper(float v[][3])
{
	// pentagonal prism
	// up surface
	glBegin(GL_TRIANGLES);
	glVertex3fv(v[0]);
	glVertex3fv(v[1]);
	glVertex3fv(v[4]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(v[1]);
	glVertex3fv(v[2]);
	glVertex3fv(v[3]);
	glVertex3fv(v[4]);
	glEnd();
	
	// lower surface
	glBegin(GL_TRIANGLES);
	glVertex3fv(v[5]);
	glVertex3fv(v[1+5]);
	glVertex3fv(v[4+5]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(v[1+5]);
	glVertex3fv(v[2+5]);
	glVertex3fv(v[3+5]);
	glVertex3fv(v[4+5]);
	glEnd();

	// draw side surfaces
	glBegin(GL_QUADS);
	glVertex3fv(v[0]);
	glVertex3fv(v[1]);
	glVertex3fv(v[6]);
	glVertex3fv(v[5]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(v[0+1]);
	glVertex3fv(v[1+1]);
	glVertex3fv(v[6+1]);
	glVertex3fv(v[5+1]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(v[0+2]);
	glVertex3fv(v[1+2]);
	glVertex3fv(v[6+2]);
	glVertex3fv(v[5+2]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(v[0+3]);
	glVertex3fv(v[1+3]);
	glVertex3fv(v[6+3]);
	glVertex3fv(v[5+3]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(v[4]);
	glVertex3fv(v[0]);
	glVertex3fv(v[5]);
	glVertex3fv(v[9]);
	glEnd();
}

void drawShouder()
{
	glPushMatrix();
	glScaled(3, 3, 0.5);

	//First part of arm
	float points[5][2] = {
		{0.0f, 0.0f},
		{0.5f, 0.0f},
		{0.8f, 0.7f},
		{0.3f, 0.7f},
		{-0.2f, 0.2f}
	};
	//Upper part
	glBegin(GL_POLYGON);
	for (int i = 0; i < 5; i++)
		glVertex3f(points[i][0], points[i][1], -2.5);
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 5; i++)
		glVertex3f(points[i][0], points[i][1], 0);
	glEnd();

	for (int i = 0; i < 5; i++)
	{
		glBegin(GL_POLYGON);
		glVertex3f(points[i % 5][0], points[i % 5][1], -2.5);
		glVertex3f(points[(i + 1) % 5][0], points[(i + 1) % 5][1], -2.5);
		glVertex3f(points[(i + 1) % 5][0], points[(i + 1) % 5][1], 0);
		glVertex3f(points[i % 5][0], points[i % 5][1], 0);
		glEnd();
	}

	glPopMatrix();

	glPushMatrix();
	glTranslated(1.5, 0, -1);
	drawBox(2, 1, 1);
	glPopMatrix();
}

void drawUpperArm()
{
	//Lower part
	drawBox(0.5,2.5, 0.5);
}

void drawHexagonalPrisms()
{
	float s_60 = sin(M_PI / 3);

	float points[6][2] = { {2,0},
		{1, 2 * s_60},
		{-1, 2 * s_60},
		{-2, 0},
		{-1, -2 * s_60},
		{1, -2 * s_60} };

	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; i++)
		glVertex3f(points[i][0], points[i][1], -2.5);
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; i++)
		glVertex3f(points[i][0], points[i][1], 0);
	glEnd();

	for (int i = 0; i < 6; i++)
	{
		glBegin(GL_POLYGON);
		glVertex3f(points[i % 6][0], points[i % 6][1], -2.5);
		glVertex3f(points[(i + 1) % 6][0], points[(i + 1) % 6][1], -2.5);
		glVertex3f(points[(i + 1) % 6][0], points[(i + 1) % 6][1], 0);
		glVertex3f(points[i % 6][0], points[i % 6][1], 0);
		glEnd();
	}

}

void drawLowerArm() {
	glPushMatrix();
	glScaled(0.4, 0.4, 0.4);

	setDiffuseColor(0.8f, 0.8f, 0.8f);
	glPushMatrix();
	glRotated(90, 0.0, 1.0, 0.0);
	drawCylinder(1.2, 0.8, 0.8);
	glPopMatrix();

	float delta = 0.25;

	setDiffuseColor(1.0f, 1.0f, 0.0f);

	glPushMatrix();
	glTranslated(0.6, 0, 0.5 * 2.5 + delta);
	glRotated(30, 0.0, 0.0, 1.0);
	glScaled(0.7, 0.7, 0.5);
	drawHexagonalPrisms();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.6, 0, (0.5 + 0.7) * 2.5 + delta);
	glRotated(30, 0.0, 0.0, 1.0);
	glScaled(1, 1, 0.7);
	drawHexagonalPrisms();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.6, 0, (0.5 + 0.7 + 1) * 2.5 + delta);
	glRotated(30, 0.0, 0.0, 1.0);
	glScaled(1.3, 1.3, 1);
	drawHexagonalPrisms();
	glPopMatrix();

	glPopMatrix();

}

void drawHand()
{
	setDiffuseColor(0.8f, 0.8f, 0.8f);
	drawBox(1, 1, 0.6);

	setDiffuseColor(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslated(-0.25, -0.5, 0.6);
	drawBox(1.5, 2, 1.7);

	//glPushMatrix();
	//glTranslated(0.15,1.4, 1.7);
	//drawBox(0.2, 0.5, 0.5);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslated(0.15, 0.75, 1.7);
	//drawBox(0.2, 0.5, 0.5);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslated(0.15, 0.1, 1.7);
	//drawBox(0.2, 0.5, 0.5);
	//glPopMatrix();

	glPopMatrix();


}

void drawFinger() {

	glPushMatrix();
	glRotated(90, 1.0, 0.0, 0.0);
	setDiffuseColor(0.8f, 0.8f, 0.8f);
	drawCylinder(0.5, 0.2, 0.2);

	setDiffuseColor(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslated(0, -0.1, 0);
	drawBox(1.4, 0.4, 0.5);
	glPopMatrix();


	setDiffuseColor(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslated(1.4, -1.1, 0);
	drawBox(0.4, 1.0, 0.5);
	glPopMatrix();

	setDiffuseColor(0.8f, 0.8f, 0.8f);
	glPushMatrix();
	glTranslated(1.4, 0.0, 0);
	drawCylinder(0.5, 0.2, 0.2);
	glPopMatrix();
	glPopMatrix();

}

void drawThumb()
{
	glPushMatrix();
	glRotated(-90, 0.0, 1.0, 0.0);

	setDiffuseColor(0.8f, 0.8f, 0.8f);
	drawCylinder(1, 0.2, 0.2);

	setDiffuseColor(1.0f, 1.0f, 0.0f);

	glPushMatrix();
	glRotated(20, 0.0, 0.0, 1.0);
	glTranslated(0, -0.1, 0);
	drawBox(0.8, 0.4, 1);

	setDiffuseColor(0.8f, 0.8f, 0.8f);
	glPushMatrix();
	glTranslated(0.8, 0.1, 0);
	drawCylinder(1, 0.2, 0.2);

	setDiffuseColor(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotated(-20, 0.0, 0.0, 1.0);
	glTranslated(0, -0.1, 0);
	drawBox(1.0, 0.4, 1);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();


	glPopMatrix();
}

void drawArm()
{
	drawShouder();
	glPushMatrix();
	glTranslated(0.5, -2, -0.75);
	drawUpperArm();

	glPushMatrix();
	glTranslated(0, 0, 0.5);
	drawLowerArm();

	glPushMatrix();
	glTranslated(-0.2, -0.5, (0.5 + 0.7 + 1) * 2.5 * 0.4);
	drawHand();

	glPushMatrix();
	glTranslated(-0.25, -0.5, 0.6);
	glPushMatrix();
	glTranslated(0.15, 1.4, 1.7);
	glTranslated(0.2, 0.5, 0.2);
	drawFinger();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.15, 0.75, 1.7);
	glTranslated(0.2, 0.5, 0.2);
	drawFinger();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.15, 0.1, 1.7);
	glTranslated(0.2, 0.5, 0.2);
	drawFinger();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.15, 0.1, 0.5);
	glTranslated(1.2, 1.9, 0);
	drawThumb();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}
// given a curve, draw the shape by rotating the curve 360'
void draw_curve_shape(float h, float(*curve)(float))
{
	const int h_sample = 300;
	float v[360][h_sample][3];

	for (int i = 0; i < h_sample; i++)
	{
		v[0][i][0] = 0;
		v[0][i][1] = h * i / (h_sample - 1);
		v[0][i][2] = curve(h * i / h_sample);
	}
	for (int theta = 1; theta < 360; theta++)
	{
		for (int i = 0; i < h_sample; i++)
		{
			v[theta][i][0] = v[0][i][2] * sinf(theta / 360.0 * 2 * M_PI);
			v[theta][i][1] = h * i / h_sample;
			v[theta][i][2] = v[0][i][2] * cosf(theta / 360.0 * 2 * M_PI);
		}
	}

	for (int t = 0; t < 359; t += 1)
	{
		for (int i = 0; i < h_sample - 1; i++)
		{
			glBegin(GL_TRIANGLES);
			glVertex3fv(v[t][i]);
			glVertex3fv(v[t + 1][i]);
			glVertex3fv(v[t][i + 1]);
			glEnd();
			glBegin(GL_TRIANGLES);
			glVertex3fv(v[t + 1][i + 1]);
			glVertex3fv(v[t][i + 1]);
			glVertex3fv(v[t + 1][i]);
			glEnd();

		}
	}
	// the 359 to 0
	for (int i = 0; i < h_sample - 1; i++)
	{
		glBegin(GL_TRIANGLES);
		glVertex3fv(v[359][i]);
		glVertex3fv(v[0][i]);
		glVertex3fv(v[359][i + 1]);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex3fv(v[0][i + 1]);
		glVertex3fv(v[359][i + 1]);
		glVertex3fv(v[0][i]);
		glEnd();
	}
}
// need push/pop matrix outside
void drawBodyOut(float h)
{

		//glTranslated(10, -3, 0);
	    setDiffuseColor(140 / 255.0, 243 / 255.0, 252 / 255.0);
		glPushMatrix();
		glTranslated(-2, h / 2, 0);
		drawSphere(h / 4.5);
		glPopMatrix();

		const int h_sample = 100;
		float v[360][h_sample][3];
		// float h = 6;
		for (int i = 0; i < h_sample; i++)
		{
			v[0][i][0] = 0;
			v[0][i][1] = h * i / (h_sample - 1);
			v[0][i][2] = 3.5 - (h * i / h_sample - 3) * (h * i / h_sample - 3) * 2.0 / 9;
		}
		for (int theta = 1; theta < 360; theta++)
		{
			for (int i = 0; i < h_sample; i++)
			{
				v[theta][i][0] = v[0][i][2] * sinf(theta / 360.0 * 2 * M_PI);
				v[theta][i][1] = h * i / h_sample;
				v[theta][i][2] = v[0][i][2] * cosf(theta / 360.0 * 2 * M_PI);
			}
		}
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		setDiffuseColor(0.5f, 0.5f, 0);
		for (int t = 0; t < 359; t += 1)
		{
			for (int i = 0; i < h_sample - 1; i++)
			{
				if ((t - 270) * (t - 270) / 625.0 + (i - h_sample / 2.0) * (i - h_sample / 2.0) / 625 < 1)
					continue;

				// draw outside
				

				glBegin(GL_TRIANGLES);
				glVertex3fv(v[t][i]);
				glVertex3fv(v[t + 1][i]);
				glVertex3fv(v[t][i + 1]);
				glEnd();
				glBegin(GL_TRIANGLES);
				glVertex3fv(v[t + 1][i + 1]);
				glVertex3fv(v[t][i + 1]);
				glVertex3fv(v[t + 1][i]);
				glEnd();

			}
		}
		for (int t = 1; t < 359; t++)
		{
			for (int i = 0; i < h_sample - 1; i++)
			{
				// inside 
				if (t % 2 == 0)
					setDiffuseColor(0, 0, 0);
				else
					setDiffuseColor(0.2, 0.2, 0.2);

				glBegin(GL_TRIANGLES);
				glVertex3fv(v[t][i]);
				glVertex3fv(v[t][i + 1]);
				glVertex3fv(v[t + 1][i]);
				glEnd();
				glBegin(GL_TRIANGLES);
				glVertex3fv(v[t + 1][i + 1]);
				glVertex3fv(v[t + 1][i]);
				glVertex3fv(v[t][i + 1]);
				glEnd();
			}
		}

		// the 359 to 0
		for (int i = 0; i < h_sample - 1; i++)
		{
			setDiffuseColor(0.5f, 0.5f, 0);
			glBegin(GL_TRIANGLES);
			glVertex3fv(v[359][i]);
			glVertex3fv(v[0][i]);
			glVertex3fv(v[359][i + 1]);
			glEnd();
			glBegin(GL_TRIANGLES);
			glVertex3fv(v[0][i + 1]);
			glVertex3fv(v[359][i + 1]);
			glVertex3fv(v[0][i]);
			glEnd();

		}
		setDiffuseColor(0.5f, 0.5f, 0);
		glDisable(GL_CULL_FACE);
}


// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void RobotModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();

	// set light source
	GLfloat light_pos[] = { VAL(LIGHT_POS_X), VAL(LIGHT_POS_Y), VAL(LIGHT_POS_Z), 0 };
	GLfloat light1_pos[] = { VAL(LIGHT1_POS_X), VAL(LIGHT1_POS_Y), VAL(LIGHT1_POS_Z), 0 };
	float intensity = VAL(LIGHT_INTENSITY);
	GLfloat light_intensity[] = { intensity, intensity, intensity, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_intensity);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_intensity);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_intensity);

	// draw the floor
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-25, -8, -25);
	drawBox(50, 0.01f, 50);
	glPopMatrix();


	// draw the model
	setDiffuseColor(0.5f, 0.5f, 0);

	// parameters
	float r1 = 3; // r of the body
	float h_head = 1.8;
	float r_top = 1.5, r_bottom = 2;
	float h_middle = 6;
	float h_bottom = 1.5;
	float h_top = 1;
	float h_leg = 1.8;
	float h_feet = 0.8;
	float body_width_scale = 1;
	float body_depth_scale = 0.8;

	glPushMatrix();
	{
	    // middle body
	  glScaled(body_depth_scale, 1, body_width_scale);
	  glTranslated(VAL(XPOS), h_bottom+h_feet+h_leg + VAL(YPOS), VAL(ZPOS));
	  glTranslated(0, -h_middle, 0);
	  drawBodyOut(h_middle);
	  glTranslated(0, h_middle, 0);
	  glScaled(1 / body_depth_scale, 1, 1 / body_width_scale);
	  
	  float delta1 = 1.5;
	  glPushMatrix();
	  {
		  glRotated(-90, 0, 1.0, 0);
		  glTranslated(-4 - delta1, -1, 0);
		  drawArm();
	  }
	  glPopMatrix();

	  glPushMatrix();
	  {
		  glRotated(-90, 0, 1.0, 0);
		  glScaled(-1, 1, 1);
		  glTranslated(-4 - delta1, -1, 0);
		  drawArm();
	  }
	  glPopMatrix();
	  
	  glPushMatrix();
	  {
		  // head
		  float diff = 0.12;
	      float w_head = 2.2;
	      float h1 = 0.2, h2 = 1.3, h3 = h_head - h1- h2;
	      float w1 = 0.1, w2 = w_head/2 - w1;
		  float h_depth = 1.3;
		  
		  glPushMatrix();  // whole head
		  {
			  glRotated(VAL(HEAD_ROTATE), 0, 1, 0);

		  glPushMatrix();
		  {
			  
			  // left head
			  float v[10][3] =
			  {
				  {0,       0,       0},
				  {0,       h_head,  0},
				  {0,       h2+h3,   -w_head/2},
				  {0,       h3,      -w_head/2},
				  {0,       0,       -w2},
				  {h_depth, 0,       0},
				  {h_depth, h_head,  0},
				  {h_depth, h2 + h3, -w_head/2},
				  {h_depth, h3,      -w_head/2},
				  {h_depth, 0,       -w2}
			  };
			  glTranslated(-h_depth/2, 0, -diff/2);
			  draw_prism5_helper(v);
			  
			  glPushMatrix();
			  {
				  // eye
				  setAmbientColor(.1f, .1f, .1f);
				  setDiffuseColor(140 / 255.0, 243 / 255.0, 252 / 255.0);
				  
				  glTranslated(0, h_head / 2, -w_head / 4);
				  drawSphere(0.2);
				  
				  setAmbientColor(.1f, .1f, .1f);
				  setDiffuseColor(0.5f, 0.5f, 0);

			  }
			  glPopMatrix();
			  
		  }
		  glPopMatrix();
		  glPushMatrix();
		  {
			  // right head
			  float v[10][3] =
			  {
				  {0,       0,       0},
				  {0,       h_head,  0},
				  {0,       h2 + h3, w_head/2},
				  {0,       h3,      w_head/2},
				  {0,       0,       w2},
				  {h_depth, 0,       0},
				  {h_depth, h_head,  0},
				  {h_depth, h2 + h3, w_head/2},
				  {h_depth, h3,      w_head/2},
				  {h_depth, 0,       w2}
			  };
			  glTranslated(-h_depth/2 , 0, diff / 2);
			  draw_prism5_helper(v);

			  glPushMatrix();
			  {
				  // eye
				  setAmbientColor(.1f, .1f, .1f);
				  setDiffuseColor(140 / 255.0, 243 / 255.0, 252 / 255.0);

				  glTranslated(0, h_head / 2, w_head / 4);
				  drawSphere(0.28);

				  setAmbientColor(.1f, .1f, .1f);
				  setDiffuseColor(0.5f, 0.5f, 0);

			  }
			  glPopMatrix();

		  }
		  glPopMatrix();
		  }
		  glPopMatrix();
	  }
	  glPopMatrix();
	  glPushMatrix();
	  {
		  //// bottom body

		  float leg_width = 0.9;
		  glPushMatrix();
		  {
			  // left leg
			  glTranslated(-0.6, -h_middle - h_leg, -leg_width / 2 + 1.1);
			  glRotated(20, 0, 1, 0);
			  drawBox(leg_width, h_leg, leg_width);
			  glPushMatrix();
			  {
				  // feet
				  glRotated(VAL(LEFT_FEET_ROTATE), 0, 0, 1);
				  float v[6][3] =
				  {
					  {0 + leg_width, 0, 0},
					  {0 + leg_width, 0, leg_width},
					  {-2, -h_feet, 0 - 0.5},
					  {-2, -h_feet, leg_width + 0.5},
					  {0 + leg_width, -h_feet, 0},
					  {0 + leg_width, -h_feet, leg_width},
				  };
				  
				  draw_feet_helper(v);
			  }
			  glPopMatrix();
		  }
		  glPopMatrix();
		  glPushMatrix();
		  {
			  // right leg
			  glTranslated(-0.6, -h_middle- h_leg, -leg_width / 2  -1.1);
			  glRotated(-20, 0, 1, 0);
			  drawBox(leg_width, h_leg, leg_width);

			  // feet
			  glRotated(VAL(RIGHT_FEET_ROTATE), 0, 0, 1);
			  float v[6][3] =
			  {
				  {0 + leg_width, 0, 0},
				  {0 + leg_width, 0, leg_width},
				  {-2, -h_feet, 0 - 0.5},
				  {-2, -h_feet, leg_width + 0.5},
				  {0 + leg_width, -h_feet, 0},
				  {0 + leg_width, -h_feet, leg_width},
			  };

			  draw_feet_helper(v);
		  }
		  glPopMatrix();
	  }
	  glPopMatrix();

	  glPushMatrix();
	  int h = r1 + 2, h2 = 2.5;
	  {
		  // left jet
	      glTranslated(r1 * body_depth_scale, r1/2 + 2, -2);
	      glRotated(90, 1, 0, 0);
	      drawCylinder(h, 0.35, 0.35);
		  glPushMatrix();
		  {
		  	// jet header
		  	drawCylinder(h2, 0.15, 0.55);
		  }
	      glPopMatrix();
	  }
	  glPopMatrix();
	  glPushMatrix();
	  {
		  // right jet
		  glTranslated(r1 * body_depth_scale, r1 / 2 + 2, 2);
		  glRotated(90, 1, 0, 0);
		  drawCylinder(h, 0.35, 0.35);
		  glPushMatrix();
		  {
			  // jet header
			  drawCylinder(h2, 0.15, 0.5);
		  }
		  glPopMatrix();
	  }
	  glPopMatrix();
	}
	glPopMatrix();


	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", -5, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[HEAD_ROTATE] = ModelerControl("Head Rotate", -90, 90, 0.2f, 0);
	controls[LEFT_FEET_ROTATE] = ModelerControl("Left Feet Rotate", 0, 45, 0.2f, 0);
	controls[RIGHT_FEET_ROTATE] = ModelerControl("Right Feet Rotate", 0, 45, 0.2f, 0);
	controls[LIGHT_POS_X] = ModelerControl("Light 0 source position X", -100, 100, 1, 50);
	controls[LIGHT_POS_Y] = ModelerControl("Light 0 source position Y", -100, 100, 1, 50);
	controls[LIGHT_POS_Z] = ModelerControl("Light 0 source position Z", -100, 100, 1, 50);
	controls[LIGHT1_POS_X] = ModelerControl("Light 1 source position X", -100, 100, 1, -100);
	controls[LIGHT1_POS_Y] = ModelerControl("Light 1 source position Y", -100, 100, 1, -100);
	controls[LIGHT1_POS_Z] = ModelerControl("Light 1 source position Z", -100, 100, 1, -100);
	controls[LIGHT_INTENSITY] = ModelerControl("Light intensity", 0, 1, 0.01f, 1);

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}
