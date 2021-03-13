#ifndef L_SYSTEM_H
#define L_SYSTEM_H

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


char* instruction[4] = { "t","t","s","t" };
char* rule1[3] = { "abc","abc","abc" };
char* rule2[1] = { "abcd" };
char* rule3[5] = { "s" };
char* rule4[1] = { "t" };

char** rule[4] = { rule1,rule2,rule3,rule4 };


void draw3DLTree1(int type, float lastL, int incrAngle, int iter, const char* instr)
{
	float length = lastL;
	if (iter == 0)
		return;


	for (int i = 0; i < strlen(instr); i++)
	{
		switch (instr[i])
		{
		case 'a':

			glPushMatrix();
			{
				glTranslatef(length * (iter + 1) / iter, 0, 0);
				glRotatef(120, 1, 0, 0);
				glRotatef(45 + incrAngle, 0, 0, 1);
				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(length, 0, 0);
				glEnd();
				draw3DLTree1(type, lastL * iter / (iter + 1), incrAngle, iter - 1, rule[type][0]);
			}
			glPopMatrix();
			break;
		case 'b':

			glPushMatrix();
			{
				glTranslatef(length * (iter + 1) / iter, 0, 0);
				glRotatef(240, 1, 0, 0);
				glRotatef(45 + incrAngle, 0, 0, 1);
				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(length, 0, 0);
				glEnd();
				draw3DLTree1(type, lastL * iter / (iter + 1), incrAngle, iter - 1, rule[type][0]);
			}
			glPopMatrix();
			break;
		case 'c':
			glPushMatrix();
			{
				glTranslatef(length * (iter + 1) / iter, 0, 0);
				glRotatef(0, 1, 0, 0);
				glRotatef(45 + incrAngle, 0, 0, 1);
				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(length, 0, 0);
				glEnd();
				draw3DLTree1(type, lastL * iter / (iter + 1), incrAngle, iter - 1, rule[type][0]);
			}
			glPopMatrix();
			break;
		default:
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(length, 0, 0);
			glEnd();

			draw3DLTree1(type, lastL * iter / (iter + 1), incrAngle, iter - 1, rule[type][0]);

			break;
		}
	}

}


void draw3DLTree2(int type, float lastL, int incrAngle, int iter, const char* instr)
{
	float length = lastL;
	if (iter == 0)
		return;


	for (int i = 0; i < strlen(instr); i++)
	{
		switch (instr[i])
		{
		case 'a':

			glPushMatrix();
			{
				glTranslatef(length * 1 / 4, 0, 0);
				glRotatef(0, 1, 0, 0);
				glRotatef(60 + incrAngle, 0, 0, 1);
				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(length / 3, 0, 0);
				glEnd();

				glTranslated(length / 3, 0, 0);

				glRotatef(-60, 0, 0, 1);

				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(length * 3 / 5, 0, 0);
				glEnd();

				glPushMatrix();
				{
					glRotated(80, 1, 0, 0);
					draw3DLTree2(type, length * 3 / 5 * 0.9, incrAngle, iter - 1, rule[type][0]);
				}

				glPopMatrix();

			}
			glPopMatrix();
			break;

		case 'b':

			glPushMatrix();
			{
				glTranslatef(length * 1 / 3, 0, 0);
				glRotatef(90, 1, 0, 0);
				glRotatef(60 + incrAngle, 0, 0, 1);

				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(length * 1 / 3 * 0.8, 0, 0);
				glEnd();

				glTranslated(length * 1 / 3 * 0.8, 0, 0);
				glRotatef(-60 - incrAngle, 0, 0, 1);

				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(length * 1 / 3, 0, 0);
				glEnd();

				glPushMatrix();
				{
					glRotated(10, 1, 0, 0);
					draw3DLTree2(type, length * 1 / 3 * 0.9, incrAngle, iter - 1, rule[type][0]);
				}

				glPopMatrix();
			}
			glPopMatrix();
			break;

		case 'c':

			glPushMatrix();
			{
				glTranslatef(length * 3 / 5, 0, 0);
				glRotatef(180, 1, 0, 0);
				glRotatef(60 + incrAngle, 0, 0, 1);

				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(length * 1 / 4, 0, 0);
				glEnd();

				glTranslated(length * 1 / 4, 0, 0);
				glRotatef(-60 - incrAngle, 0, 0, 1);
				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(length * 1 / 4, 0, 0);
				glEnd();

				glPushMatrix();
				{
					glRotated(57, 1, 0, 0);
					draw3DLTree2(type, length * 1 / 4 * 0.9, incrAngle, iter - 1, rule[type][0]);
				}
				glPopMatrix();

			}
			glPopMatrix();
			break;

		case 'd':

			glPushMatrix();
			{
				glTranslatef(length * 3 / 4, 0, 0);
				glRotatef(270, 1, 0, 0);
				glRotatef(60 + incrAngle, 0, 0, 1);
				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(length / 5, 0, 0);
				glEnd();

				glTranslated(length / 5, 0, 0);
				glRotatef(-60 - incrAngle, 0, 0, 1);

				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(length * 1 / 5, 0, 0);
				glEnd();

				glPushMatrix();
				{
					glRotated(30, 1, 0, 0);
					draw3DLTree2(type, length * 1 / 5 * 0.9, incrAngle, iter - 1, rule[type][0]);
				}
				glPopMatrix();
			}
			glPopMatrix();
			break;

		default:
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(length * 1.1, 0, 0);
			glEnd();

			draw3DLTree2(type, length * 0.9, incrAngle, iter - 1, rule[type][0]);
			glPushMatrix();
			{

				glRotated(45, 1, 0, 0);
				draw3DLTree2(type, length * 1.1, incrAngle, iter - 1, rule[type][0]);
			}
			glPopMatrix();
			break;
		}
	}

}



void draw2DLSnowflake(int type, float L, int incrAngle, int iter, const char* instr)
{
	float length = L * pow(2.0f, iter) * iter * 0.05;
	if (iter == 0)
		return;

	for (int i = 0; i < 6; i++)
	{
		glPushMatrix();
		{
			glRotated(60 * i, 0, 0, 1);
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(length, 0, 0);
			glEnd();
			glTranslated(length, 0, 0);
			draw2DLSnowflake(type, L, incrAngle, iter - 1, rule[type][0]);
		}
		glPopMatrix();
	}

}


void draw2DLTree(int type, float L, int incrAngle, int iter, const char* instr)
{
	float length1 = L * 0.5;
	float length2 = L * 0.3;
	if (iter == 0)
		return;


	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(L, 0, 0);
	glEnd();

	glPushMatrix();
	{
		glTranslated(L * 0.3, 0, 0);
		glRotated(70, 0, 0, 1);

		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(length1, 0, 0);
		glEnd();

		draw2DLTree(type, length1, incrAngle, iter - 1, rule[type][0]);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(L * 0.3, 0, 0);
		glRotated(-70, 0, 0, 1);

		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(length1, 0, 0);
		glEnd();

		draw2DLTree(type, length1, incrAngle, iter - 1, rule[type][0]);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(L * 0.7, 0, 0);
		glRotated(70, 0, 0, 1);

		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(length2, 0, 0);
		glEnd();

		draw2DLTree(type, length2, incrAngle, iter - 1, rule[type][0]);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(L * 0.7, 0, 0);
		glRotated(-70, 0, 0, 1);

		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(length2, 0, 0);
		glEnd();

		draw2DLTree(type, length2, incrAngle, iter - 1, rule[type][0]);
	}
	glPopMatrix();
}

typedef void(*FunctionPointer)(int, float, int, int, const char*);
FunctionPointer functionPointers[] = { draw3DLTree1 ,draw3DLTree2,draw2DLSnowflake, draw2DLTree };


#endif