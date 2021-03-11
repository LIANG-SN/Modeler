#ifndef _MODELER_GLOBALS_H
#define _MODELER_GLOBALS_H

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// This is a list of the controls for the SampleModel
// We'll use these constants to access the values 
// of the controls from the user interface.
enum SampleModelControls
{ 
	LIGHT_POS_X, LIGHT_POS_Y, LIGHT_POS_Z, LIGHT1_POS_X, LIGHT1_POS_Y, LIGHT1_POS_Z,
	LIGHT_INTENSITY,
	XPOS, YPOS, ZPOS, 



	HEAD_ROTATE, LEFT_FEET_ROTATE, RIGHT_FEET_ROTATE,

	LEFT_ARM_X_ROTATE, RIGHT_ARM_X_ROTATE,
	LEFT_ARM_Y_ROTATE, RIGHT_ARM_Y_ROTATE,
	LEFT_ARM_Z_ROTATE, RIGHT_ARM_Z_ROTATE,

	LEFT_LOWER_ARM_ROTATE, RIGHT_LOWER_ARM_ROTATE,

	ROCKET_GRAB,

	LEFT_HAND_ROTATE, RIGHT_HAND_ROTATE,



	LEFT_THUMB_UP, RIGHT_THUMB_UP,

	LEFT_FINGER1_FIRST_JOINT_ROTATE, LEFT_FINGER1_SECOND_JOINT_ROTATE,
	RIGHT_FINGER1_FIRST_JOINT_ROTATE, RIGHT_FINGER1_SECOND_JOINT_ROTATE,

	LEFT_FINGER2_FIRST_JOINT_ROTATE, LEFT_FINGER2_SECOND_JOINT_ROTATE,
	RIGHT_FINGER2_FIRST_JOINT_ROTATE, RIGHT_FINGER2_SECOND_JOINT_ROTATE,

	LEFT_FINGER3_FIRST_JOINT_ROTATE, LEFT_FINGER3_SECOND_JOINT_ROTATE,
	RIGHT_FINGER3_FIRST_JOINT_ROTATE, RIGHT_FINGER3_SECOND_JOINT_ROTATE,

	CHANGE_HAND,

	NUMCONTROLS
};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))

#endif