
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl\gl.h>                                // Header File For The OpenGL32 Library




#define STEP 0.1
#define TORSO_LENGTH 6.0
#define TORSO_RADIUS 2.0
#define UPPER_FRONT_LEGS_HEIGHT 2.0
#define UPPER_FRONT_LEGS_RADIUS  0.5
#define LOWER_FRONT_LEGS_HEIGHT 3.0
#define LOWER_FRONT_LEGS_RADIUS  0.5
#define UPPER_BACK_LEGS_HEIGHT 2.0
#define UPPER_BACK_LEGS_RADIUS  0.5
#define LOWER_BACK_LEGS_HEIGHT 3.0
#define LOWER_BACK_LEGS_RADIUS  0.5
#define FEET_RADIUS 0.7
#define HEAD_HEIGHT 1.0
#define HEAD_RADIUS 1.2
#define NECK_HEIGHT 4.0
#define NECK_RADIUS 0.6

#define NULL 0

static int window;
int option = -1;
int animation = 4; //stable state
int done = 0; //checks if last animation has finished
double rotate = 0.0;

typedef struct treenode
{
	GLfloat m[16];
	void(*f)();
	struct treenode *sibling;
	struct treenode *child;
}treenode;

typedef treenode* t_ptr;

static GLfloat theta[7] = { 0.0,0.0,-45.0,180.0,0.0,180.0,0.0 }; /* initial joint angles */

GLUquadricObj *t, *h, *nk, *ful1, *fll1, *ff1, *ful2, *fll2, *ff2, *bul1, *bll1, *bf1, *bul2, *bll2, *bf2;

treenode torso_node, head_node, neck_node, fuleg1_node, flleg1_node, ffoot1_node, fuleg2_node, flleg2_node, ffoot2_node,
buleg1_node, blleg1_node, bfoot1_node, buleg2_node, blleg2_node, bfoot2_node;

void traverse(treenode* root)
{
	if (root == NULL) return;
	glPushMatrix();
	glMultMatrixf(root->m);
	root->f();
	if (root->child != NULL) traverse(root->child);
	glPopMatrix();
	if (root->sibling != NULL) traverse(root->sibling);
}

void torso()
{
	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);
	gluCylinder(t, TORSO_RADIUS / 1.2, TORSO_RADIUS, TORSO_LENGTH, 10, 10);
	glPopMatrix();
}

void neck()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(nk, NECK_RADIUS, NECK_RADIUS, NECK_HEIGHT, 10, 10);
	glPopMatrix();
}

void head()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0f, -0.4f, -0.15f);
	gluSphere(h, HEAD_RADIUS, 10, 10);
	glPopMatrix();
}

void front_left_upper_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(ful1, UPPER_FRONT_LEGS_RADIUS, UPPER_FRONT_LEGS_RADIUS, UPPER_FRONT_LEGS_HEIGHT, 10, 10);
	glPopMatrix();
}

void front_right_upper_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(ful2, UPPER_FRONT_LEGS_RADIUS, UPPER_FRONT_LEGS_RADIUS, UPPER_FRONT_LEGS_HEIGHT, 10, 10);
	glPopMatrix();
}

void front_left_lower_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(TORSO_RADIUS, -UPPER_FRONT_LEGS_HEIGHT, 0.0);
	gluCylinder(fll1, LOWER_FRONT_LEGS_RADIUS, LOWER_FRONT_LEGS_RADIUS, LOWER_FRONT_LEGS_HEIGHT, 10, 10);
	glPopMatrix();
}

void front_right_lower_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -UPPER_FRONT_LEGS_HEIGHT, 0.0);
	gluCylinder(fll2, LOWER_FRONT_LEGS_RADIUS, LOWER_FRONT_LEGS_RADIUS, LOWER_FRONT_LEGS_HEIGHT, 10, 10);
	glPopMatrix();
}

void back_right_upper_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(bul1, UPPER_BACK_LEGS_RADIUS, UPPER_BACK_LEGS_RADIUS, UPPER_BACK_LEGS_HEIGHT, 10, 10);
	glPopMatrix();
}

void back_left_upper_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(TORSO_RADIUS, 0.0, 0.0);
	gluCylinder(bul2, UPPER_BACK_LEGS_RADIUS, UPPER_BACK_LEGS_RADIUS, UPPER_BACK_LEGS_HEIGHT, 10, 10);
	glPopMatrix();
}

void back_right_lower_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -UPPER_FRONT_LEGS_HEIGHT, 0.0);
	gluCylinder(bll1, LOWER_BACK_LEGS_RADIUS, LOWER_BACK_LEGS_RADIUS, LOWER_BACK_LEGS_HEIGHT, 10, 10);
	glPopMatrix();
}

void back_left_lower_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(TORSO_RADIUS, -UPPER_FRONT_LEGS_HEIGHT, 0.0);
	gluCylinder(bll2, LOWER_BACK_LEGS_RADIUS, LOWER_BACK_LEGS_RADIUS, LOWER_BACK_LEGS_HEIGHT, 10, 10);
	glPopMatrix();
}

void front_left_foot()
{
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(ff1, FEET_RADIUS, FEET_RADIUS, FEET_RADIUS, 10, 10);
	glPopMatrix();
}
void front_right_foot()
{
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(ff2, FEET_RADIUS, FEET_RADIUS, FEET_RADIUS, 10, 10);
	glPopMatrix();
}
void back_left_foot()
{
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(bf1, FEET_RADIUS, FEET_RADIUS, FEET_RADIUS, 10, 10);
	glPopMatrix();
}
void back_right_foot()
{
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(bf2, FEET_RADIUS, FEET_RADIUS, FEET_RADIUS, 10, 10);
	glPopMatrix();
}


void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15, 15, -15, 15, -15, 15);
	glRotatef(rotate, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0.4, 0.4, 0.4);

	traverse(&torso_node);

	glutSwapBuffers();
}

void inverseKinematics()
{
	switch (animation)
	{
	case 0:
		if (theta[0] > 0.0) theta[0] -= STEP;
		if (theta[1] < 0.0) theta[1] += STEP;
		if (theta[2] < -45.0) theta[2] += STEP;
		if (theta[3] < 180.0) theta[3] += STEP;
		if (theta[4] > 0.0) theta[4] -= STEP;
		if (theta[5] < 180.0) theta[5] += STEP;
		if (theta[6] > 0.0) theta[6] -= STEP;
		animation = option;
		break;
	case -1:
		if (theta[3] < 180.0)
		{
			theta[3] += STEP;
			if (theta[4] > 0.0) theta[4] -= STEP;
		}
		else animation = option;

		    glPushMatrix();
            glLoadIdentity();
			glTranslatef((2.0*TORSO_RADIUS + UPPER_FRONT_LEGS_RADIUS), -0.2*TORSO_LENGTH, 0.65 * TORSO_RADIUS);
			glRotatef(180.0,0.0,-1.0,0.0);
			glRotatef(theta[3], 0.0, 0.0, 1.0);

			glGetFloatv(GL_MODELVIEW_MATRIX, fuleg2_node.m);

			glLoadIdentity();
			glTranslatef((-0.25*TORSO_RADIUS + UPPER_FRONT_LEGS_RADIUS), UPPER_FRONT_LEGS_HEIGHT, -TORSO_RADIUS);
			glRotatef(theta[4], 0.0, 0.0, 1.0);
			//glRotatef(90.0,0.0,0.0,0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, flleg2_node.m);

			glPopMatrix();
		break;
	case -2:
		if (theta[0] > 0.0)
		{
			theta[0] -= STEP;
			theta[5] += STEP;
			theta[3] += STEP;
			if (theta[4] > 0.0 && theta[6] > 0.0)
			{
				theta[4] -= STEP;
				theta[6] -= STEP;
			}
		}
		else animation = option;

            glPushMatrix();

			glLoadIdentity();
			//glTranslatef(0.0, 0.0, 0.0);
			glRotatef(theta[0], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);

			glLoadIdentity();
			glTranslatef((-0.25*TORSO_RADIUS + UPPER_FRONT_LEGS_RADIUS), UPPER_FRONT_LEGS_HEIGHT, -TORSO_RADIUS);
			glRotatef(theta[4], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, flleg2_node.m);

			glLoadIdentity();
			glTranslatef((0.25*TORSO_RADIUS - UPPER_FRONT_LEGS_RADIUS), UPPER_BACK_LEGS_HEIGHT, -TORSO_RADIUS);
			glRotatef(theta[6], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, blleg2_node.m);

			glLoadIdentity();
			//glTranslatef(0.0,-0.2*TORSO_LENGTH,0.0);
			glTranslatef(2.5*UPPER_BACK_LEGS_RADIUS, -0.2*TORSO_LENGTH,-0.65*TORSO_RADIUS);

			glRotatef(theta[5], 0.0, 0.0, 1.0);
			glRotatef(-90.0,0.0,1.0,0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, buleg1_node.m);


			glLoadIdentity();
			glTranslatef((TORSO_RADIUS - UPPER_FRONT_LEGS_RADIUS), -0.2*TORSO_LENGTH, -0.65 * TORSO_RADIUS);
			glRotatef(theta[3], 0.0, 0.0, 1.0);
			glRotatef(-90.0,0.0,1.0,0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, fuleg1_node.m);

			glLoadIdentity();
            glTranslatef(0.0, LOWER_BACK_LEGS_HEIGHT + 0.4, 3.5 * FEET_RADIUS - 0.1);
	        glGetFloatv(GL_MODELVIEW_MATRIX, bfoot1_node.m);

            glLoadIdentity();
	        glTranslatef(1.5*LOWER_BACK_LEGS_HEIGHT, LOWER_FRONT_LEGS_HEIGHT + 0.65, FEET_RADIUS + 1.6);
            glGetFloatv(GL_MODELVIEW_MATRIX, ffoot1_node.m);

			glPopMatrix();
		break;
	case -3:
		if (theta[2] < -45.0)
		{
			theta[2] += STEP;
			if (theta[1] < 0.0) theta[1] += STEP;
		}
		else animation = option;

		glPushMatrix();

		glLoadIdentity();
		glTranslatef(TORSO_LENGTH - 0.1*NECK_HEIGHT, 0.0, 0.0);
		glRotatef(theta[2], 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, neck_node.m);

		glLoadIdentity();
		glTranslatef(0.0, 0.9*NECK_HEIGHT, -NECK_RADIUS / 2.0);
		glRotatef(theta[1], 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);

		glPopMatrix();
		break;
	default: animation = option;
	}
}

void idle()
{
	switch (option)
	{
	case 1:
		if (animation != option) inverseKinematics();
		else if (!done)
		{
			if (theta[3] > 100.0)
			{
				theta[3] -= STEP;
				if (theta[4] < 45.0) theta[4] += STEP;
				else theta[4] = 45.0;
			}
			else
			{
				done = 1;
				animation = -1;
			}

			glPushMatrix();

			glLoadIdentity();
			glTranslatef((2.0*TORSO_RADIUS + UPPER_FRONT_LEGS_RADIUS), -0.2*TORSO_LENGTH, 0.65 * TORSO_RADIUS);
			glRotatef(180.0,0.0,-1.0,0.0);
			glRotatef(theta[3], 0.0, 0.0, 1.0);

			glGetFloatv(GL_MODELVIEW_MATRIX, fuleg2_node.m);

			glLoadIdentity();
			glTranslatef((-0.25*TORSO_RADIUS + UPPER_FRONT_LEGS_RADIUS), UPPER_FRONT_LEGS_HEIGHT, -TORSO_RADIUS);
			glRotatef(theta[4], 0.0, 0.0, 1.0);
			//glRotatef(90.0,0.0,0.0,0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, flleg2_node.m);

			glPopMatrix();
		}
		break;
	case 2:
		if (animation != option) inverseKinematics();
		else if (!done)
		{
			if (theta[0] < 45.0)
			{
				theta[0] += STEP;
				theta[5] -= STEP;
				theta[3] -= STEP;
				if (theta[4] < 45.0 && theta[6] < 45.0)
				{
					theta[4] += STEP;
					theta[6] += STEP;
				}
				else
				{
					theta[4] = 45.0;
					theta[6] = 45.0;
				}
			}
			else
			{
				done = 1;
				animation = -2;
			}

			glPushMatrix();

			glLoadIdentity();
			//glTranslatef(0.0, 0.0, 0.0);
			glRotatef(theta[0], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);

			glLoadIdentity();
			glTranslatef((-0.25*TORSO_RADIUS + UPPER_FRONT_LEGS_RADIUS), UPPER_FRONT_LEGS_HEIGHT, -TORSO_RADIUS);
			glRotatef(theta[4], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, flleg2_node.m);

			glLoadIdentity();
			glTranslatef((0.25*TORSO_RADIUS - UPPER_FRONT_LEGS_RADIUS), UPPER_BACK_LEGS_HEIGHT, -TORSO_RADIUS);
			glRotatef(theta[6], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, blleg2_node.m);

			glLoadIdentity();
			//glTranslatef(0.0,-0.2*TORSO_LENGTH,0.0);
			glTranslatef(2.5*UPPER_BACK_LEGS_RADIUS, -0.2*TORSO_LENGTH,-0.65*TORSO_RADIUS);

			glRotatef(theta[5], 0.0, 0.0, 1.0);
			glRotatef(-90.0,0.0,1.0,0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, buleg1_node.m);


			glLoadIdentity();
			glTranslatef((TORSO_RADIUS - UPPER_FRONT_LEGS_RADIUS), -0.2*TORSO_LENGTH, -0.65 * TORSO_RADIUS);
			glRotatef(theta[3], 0.0, 0.0, 1.0);
			glRotatef(-90.0,0.0,1.0,0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, fuleg1_node.m);

			glLoadIdentity();
            glTranslatef(0.0, LOWER_BACK_LEGS_HEIGHT + 0.4, 3.5 * FEET_RADIUS - 0.1);
	        glGetFloatv(GL_MODELVIEW_MATRIX, bfoot1_node.m);

            glLoadIdentity();
	        glTranslatef(1.5*LOWER_BACK_LEGS_HEIGHT, LOWER_FRONT_LEGS_HEIGHT + 0.65, FEET_RADIUS + 1.6);
            glGetFloatv(GL_MODELVIEW_MATRIX, ffoot1_node.m);

			glPopMatrix();
		}
		break;
	case 3:
		if (animation != option) inverseKinematics();
		else if (!done)
		{
			 if (theta[2] > -120.0)
			 {
				 theta[2] -= STEP;
				 if (theta[1] > -40.0) theta[1] -= STEP;
				 else theta[1] = -40.0;
			 }
			 else
			 {
				 done = 1;
				 animation = -3;
			 }

			 glPushMatrix();

			 glLoadIdentity();
			 glTranslatef(TORSO_LENGTH - 0.1*NECK_HEIGHT, 0.0, 0.0);
			 glRotatef(theta[2], 0.0, 0.0, 1.0);
			 glGetFloatv(GL_MODELVIEW_MATRIX, neck_node.m);

			 glLoadIdentity();
			 glTranslatef(0.0, 0.9*NECK_HEIGHT, -NECK_RADIUS / 2.0);
			 glRotatef(theta[1], 0.0, 0.0, 1.0);
			 glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);

			 glPopMatrix();
		}
		break;
	}
	glutPostRedisplay();
}

void menu(int num) {
	if (num == 0) {
		glutDestroyWindow(window);
		exit(0);
	}
	if (num == 5) rotate = -90;
	if (num == 6) rotate = -45;
	if (num == 4)
	{
		rotate = 0;
		animation = 0;
		inverseKinematics();
	}
	option = num;
	done = 0;
	glutPostRedisplay();
}


void createMenu(void)
{
	glutAddMenuEntry("Lift front leg", 1);
	glutAddMenuEntry("Stay on back legs and bend front legs", 2);
	glutAddMenuEntry("Stoop head", 3);
	glutAddMenuEntry("Reset/Side View", 4);
	glutAddMenuEntry("Front View", 5);
	glutAddMenuEntry("3/4 View", 6);
	glutAddMenuEntry("Exit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-10.0, 10.0, -10.0 * (GLfloat)h / (GLfloat)w,
			10.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-10.0 * (GLfloat)w / (GLfloat)h,
			10.0 * (GLfloat)w / (GLfloat)h, 0.0, 10.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myinit()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess = { 100.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.8, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);

	/* allocate quadrics with filled drawing style */

	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	t = gluNewQuadric();
	gluQuadricDrawStyle(t, GLU_FILL);
	nk = gluNewQuadric();
	gluQuadricDrawStyle(nk, GLU_FILL);
	///////////////////////////////
	ful1 = gluNewQuadric();
	gluQuadricDrawStyle(ful1, GLU_FILL);
	fll1 = gluNewQuadric();
	gluQuadricDrawStyle(fll1, GLU_FILL);
	ful2 = gluNewQuadric();
	gluQuadricDrawStyle(ful2, GLU_FILL);
	fll2 = gluNewQuadric();
	gluQuadricDrawStyle(fll2, GLU_FILL);
	///////////////////////////////
	bul1 = gluNewQuadric();
	gluQuadricDrawStyle(bul1, GLU_FILL);
	bul2 = gluNewQuadric();
	gluQuadricDrawStyle(bul2, GLU_FILL);
	bll1 = gluNewQuadric();
	gluQuadricDrawStyle(bll1, GLU_FILL);
	bll2 = gluNewQuadric();
	gluQuadricDrawStyle(bll2, GLU_FILL);
	///////////////////////////////
	ff1 = gluNewQuadric();
	gluQuadricDrawStyle(ff1, GLU_FILL);
	ff2 = gluNewQuadric();
	gluQuadricDrawStyle(ff2, GLU_FILL);
	bf1 = gluNewQuadric();
	gluQuadricDrawStyle(bf1, GLU_FILL);
	bf2 = gluNewQuadric();
	gluQuadricDrawStyle(bf2, GLU_FILL);

	/* Set up tree */

	glLoadIdentity();
	glRotatef(theta[0], 0.0, 1.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);
	torso_node.f = torso;
	torso_node.sibling = NULL;
	torso_node.child = &neck_node;

	glLoadIdentity();
	glTranslatef(TORSO_LENGTH - 0.1*NECK_HEIGHT, 0.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, neck_node.m);
	neck_node.f = neck;
	neck_node.sibling = &fuleg1_node;
	neck_node.child = &head_node;

	glLoadIdentity();
	glTranslatef(0.0, 0.9*NECK_HEIGHT, -NECK_RADIUS / 2.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
	head_node.f = head;
	head_node.sibling = NULL;
	head_node.child = NULL;

	// prepei na ta exoume orisei me anapodi seira, ta front einai back kai ta back einai front
	glLoadIdentity();
	glTranslatef((TORSO_RADIUS - UPPER_FRONT_LEGS_RADIUS), -0.2*TORSO_LENGTH, -0.65 * TORSO_RADIUS);
	glRotatef(theta[3], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, fuleg1_node.m);
	fuleg1_node.f = front_left_upper_leg; //back left
	fuleg1_node.sibling = &fuleg2_node;
	fuleg1_node.child = &flleg1_node;

	glLoadIdentity();
	glRotatef(theta[3], 1.0, 0.0, 0.0);
	glTranslatef((2.0*TORSO_RADIUS + UPPER_FRONT_LEGS_RADIUS), 0.2*TORSO_LENGTH, -0.65 * TORSO_RADIUS);
	glGetFloatv(GL_MODELVIEW_MATRIX, fuleg2_node.m);
	fuleg2_node.f = front_right_upper_leg; //front right
	fuleg2_node.sibling = &buleg1_node;
	fuleg2_node.child = &flleg2_node;

	glLoadIdentity();
	glRotatef(theta[5], 1.0, 0.0, 0.0);
	glTranslatef(- UPPER_FRONT_LEGS_RADIUS, 0.2*TORSO_LENGTH, -0.65 * TORSO_RADIUS);
	glGetFloatv(GL_MODELVIEW_MATRIX, buleg1_node.m);
	buleg1_node.f = back_left_upper_leg; //back right
	buleg1_node.sibling = &buleg2_node;
	buleg1_node.child = &blleg1_node;

	glLoadIdentity();
	glRotatef(theta[5], 1.0, 0.0, 0.0);
	glTranslatef((2.0*TORSO_RADIUS + UPPER_FRONT_LEGS_RADIUS), 0.2*TORSO_LENGTH, 0.65 * TORSO_RADIUS);
	glGetFloatv(GL_MODELVIEW_MATRIX, buleg2_node.m);
	buleg2_node.f = back_right_upper_leg; //front left
	buleg2_node.sibling = NULL;
	buleg2_node.child = &blleg2_node;

	glLoadIdentity();
	glRotatef(theta[4], 1.0, 0.0, 0.0);
	glTranslatef((-0.75*TORSO_RADIUS - UPPER_FRONT_LEGS_RADIUS), UPPER_FRONT_LEGS_HEIGHT, -TORSO_RADIUS);
	glGetFloatv(GL_MODELVIEW_MATRIX, flleg1_node.m);
	flleg1_node.f = front_left_lower_leg;
	flleg1_node.sibling = NULL;
	flleg1_node.child = &ffoot1_node;

	glLoadIdentity();
	glRotatef(theta[4], 1.0, 0.0, 0.0);
	glTranslatef((-0.25*TORSO_RADIUS + UPPER_FRONT_LEGS_RADIUS), UPPER_FRONT_LEGS_HEIGHT, -TORSO_RADIUS);
	glGetFloatv(GL_MODELVIEW_MATRIX, flleg2_node.m);
	flleg2_node.f = front_right_lower_leg;
	flleg2_node.sibling = NULL;
	flleg2_node.child = &ffoot2_node;

	glLoadIdentity();
	glRotatef(theta[6], 1.0, 0.0, 0.0);
	glTranslatef((0.25*TORSO_RADIUS - UPPER_FRONT_LEGS_RADIUS), UPPER_BACK_LEGS_HEIGHT, -TORSO_RADIUS);
	glGetFloatv(GL_MODELVIEW_MATRIX, blleg1_node.m);
	blleg1_node.f = back_left_lower_leg;
	blleg1_node.sibling = NULL;
	blleg1_node.child = &bfoot1_node;

	glLoadIdentity();
	glRotatef(theta[6], 1.0, 0.0, 0.0);
	glTranslatef((0.25*TORSO_RADIUS - UPPER_FRONT_LEGS_RADIUS), UPPER_BACK_LEGS_HEIGHT, -TORSO_RADIUS);
	glGetFloatv(GL_MODELVIEW_MATRIX, blleg2_node.m);
	blleg2_node.f = back_right_lower_leg;
	blleg2_node.sibling = NULL;
	blleg2_node.child = &bfoot2_node;

	glLoadIdentity();
	glTranslatef(0.7*LOWER_BACK_LEGS_HEIGHT, LOWER_FRONT_LEGS_HEIGHT + 0.7, -FEET_RADIUS + 0.3);
	glGetFloatv(GL_MODELVIEW_MATRIX, ffoot1_node.m);
	ffoot1_node.f = front_left_foot;
	ffoot1_node.sibling = NULL;
	ffoot1_node.child = NULL;

	glLoadIdentity();
	glTranslatef(0.2, LOWER_FRONT_LEGS_HEIGHT + 0.7, 3.0 * FEET_RADIUS - 0.1);
	glGetFloatv(GL_MODELVIEW_MATRIX, ffoot2_node.m);
	ffoot2_node.f = front_right_foot;
	ffoot2_node.sibling = NULL;
	ffoot2_node.child = NULL;

	glLoadIdentity();
	glTranslatef(0.7*LOWER_BACK_LEGS_HEIGHT, LOWER_BACK_LEGS_HEIGHT + 0.7, 7.0 * FEET_RADIUS - 0.1);
	glGetFloatv(GL_MODELVIEW_MATRIX, bfoot1_node.m);
	bfoot1_node.f = back_left_foot;
	bfoot1_node.sibling = NULL;
	bfoot1_node.child = NULL;

	glLoadIdentity();
	glTranslatef(0.1*LOWER_BACK_LEGS_HEIGHT, LOWER_BACK_LEGS_HEIGHT + 0.7, 3.0 * FEET_RADIUS -0.1);
	glGetFloatv(GL_MODELVIEW_MATRIX, bfoot2_node.m);
	bfoot2_node.f = back_right_foot;
	bfoot2_node.sibling = NULL;
	bfoot2_node.child = NULL;

	glLoadIdentity();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	window = glutCreateWindow("Dog");
	myinit();
	glutCreateMenu(menu);
	createMenu();
	glutReshapeFunc(myReshape);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
