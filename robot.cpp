// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

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

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void RobotModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();

	// draw the floor
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-25, -8, -25);
	drawBox(50, 0.01f, 50);
	glPopMatrix();

	// draw the model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(0.5f, 0.5f, 0);

	// parameters
	float r1 = 3; // r of the body
	float h_head = 1.8;
	float r_top = 1.5, r_bottom = 2;
	float h_middle = 0.8;
	float h_bottom = 2.5;
	float h_top = 2;
	float h_leg = 1.8;
	float h_feet = 0.8;
	float body_width_scale = 1.2;
	float body_depth_scale = 0.8;

	glPushMatrix();
	{
	    // middle body
	  glScaled(body_depth_scale, 1, body_width_scale);
	  glTranslated(VAL(XPOS), h_bottom+h_feet+h_leg+h_middle + VAL(YPOS), VAL(ZPOS));
	  glRotated(90, 1, 0, 0);
	  drawCylinder(h_middle, r1, r1);
	  glRotated(-90, 1, 0, 0);
	  glScaled(1 / body_depth_scale, 1, 1 / body_width_scale);
	  glPushMatrix();
	  {
		  // top body
		  glScaled(body_depth_scale, 1, body_width_scale);
		  glTranslated(0, h_top, 0);
		  glRotated(90, 1, 0, 0);
		  drawCylinder(h_top, r_top, r1);
		  glRotated(-90, 1, 0, 0);
		  glScaled(1 / body_depth_scale, 1, 1/body_width_scale);
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
		  // bottom body
		  glScaled(body_depth_scale, 1, body_width_scale);
		  glTranslated(0, -h_middle, 0);
		  glRotated(90, 1, 0, 0);
		  drawCylinder(h_bottom, r1, r_bottom);
		  glRotated(-90, 1, 0, 0);
		  glScaled(1 / body_depth_scale, 1, 1/ body_width_scale);

		  float leg_width = 0.9;
		  glPushMatrix();
		  {
			  // left leg
			  glTranslated(-0.6, -h_bottom - h_leg, -leg_width / 2 + 1.1);
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
			  glTranslated(-0.6, -h_bottom - h_leg, -leg_width / 2  -1.1);
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
	  {
		  float r_front = r1 - 1.5;
		  // front body
	      glTranslated(-r1 * body_depth_scale, -0.5, 0);
	      glRotated(90, 0, 1, 0);
	      drawCylinder(0.5, r_front, r_front);
		  glLineWidth(5);
		  glBegin(GL_LINE_STRIP);
		  setAmbientColor(.1f, .1f, .1f);
		  setDiffuseColor(0, 0, 0);
		  glVertex3d(0, r_front, -0.3);
		  glVertex3d(r_front / 3, r_front / 2, -0.1 );
		  glVertex3d(-r_front / 3, -r_front / 2, -0.1);
		  glVertex3d(0, -r_front, -0.1);
		  glEnd();
		  setAmbientColor(.1f, .1f, .1f);
		  setDiffuseColor(0.5f, 0.5f, 0);
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

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}
