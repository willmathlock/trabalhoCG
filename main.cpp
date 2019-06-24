/*
Trabalho Discente CG
Robo chave 0.1

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>

#include <GL/glut.h>
#define INT_MAX 5

#include "RotatingPart.h"
#include "ScalingPart.h"

using namespace OpenGlRobot;
using namespace scaleRobot;

const int WINDOW_WIDTH = 700, WINDOW_HEIGHT = 500;
const float ROTATE_STEP = 1.0f;
const float TRANSLATE_STEP = 1.0f;
const float SCALE_STEP = 0.3f;
std::string helper = "rX";

static float rotateX = 0;
static float rotateY = 0;
static float rotateZ = 0;
float tX = 0.0f;
float tY = 0.0f;
float tZ = 0.0f;
float sX = 1.0f;
float sY = 2.0f;
float sZ = 1.0f;
static float rotateHead[3] = {0, 0, 0};
static float rotateLA[3] = {0, 0, 0};
static float rotateRA[3] = {0, 0, 0};
static float rotateLL[3] = {0, 0, 0};
static float rotateRL[3] = {0, 0, 0};
static float translateHead[3] = {0, 0.75, 0};
static float translateLA[3] = {0, 0, 0};
static float translateRA[3] = {0, 0, 0};
static float translateLL[3] = {0, 0, 0};
static float translateRL[3] = {0, 0, 0};
static float scaleHead[3] = {1, 1, 1};
static float scaleLA[3] = {1, 1, 1};
static float scaleRA[3] = {1, 1, 1};
static float scaleLL[3] = {1, 1, 1};
static float scaleRL[3] = {1, 1, 1};

static float rotateLeftArmX = 0;
static float rotateRightArmX = 0;
//static float scaleHead = 0.5;
static float scaleLeftArm = 1;
static float scaleRightArm = 1;
static float scaleWhole = 1.5f;


static RotatingPart currentRotatingPart = RotatingPart::WHOLE_ROBOT;
static ScalingPart currentScalingpart = ScalingPart::WHOLE_ROBOT;

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-3.0f, 3.0, -3.0f, 3.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
}

void displayRobotLeftArm() {
	glPushMatrix();
	glRotatef(rotateLeftArmX, 1.0, 0.0, 0.0);
	glTranslatef(-1.0f, 0.1f, 0.0f);
	glScalef(scaleLeftArm, 0.2f, 0.2f);
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobotRightArm() {
	glPushMatrix();
	glRotatef(rotateRightArmX, 1.0, 0.0, 0.0);
	glTranslatef(1.0f, 0.1f, 0.0f);
	glScalef(scaleRightArm, 0.2f, 0.2f);
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobotLeftLeg() {
	glPushMatrix();
	glTranslatef(-0.75, -0.5, 0.0);
	glScalef(0.5f, 0.5f, 0.5f);
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobotRightLeg() {
	glPushMatrix();
	glTranslatef(0.75, -0.5, 0.0);
	glScalef(0.5f, 0.5f, 0.5f);
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobotBody() {
	glPushMatrix();
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobootHead() {
	glPushMatrix();
	glRotatef(rotateHead[0], 1, 0, 0);
	glRotatef(rotateHead[1], 0, 1, 0);
	glRotatef(rotateHead[2], 0, 0, 1);
	glTranslatef(translateHead[0], translateHead[1], translateHead[3]);
	glScalef(scaleHead[0], scaleHead[1], scaleHead[2]);
	glutWireSphere(0.5, 15, 50);
	glScalef(1.0f, 2.0f, 1.0f);
	glPopMatrix();
}

void displayRobot() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(tX, tY, tZ);

	glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);

	glScalef(scaleWhole, scaleWhole, scaleWhole);

	displayRobootHead();
	displayRobotBody();
	displayRobotLeftArm();
	displayRobotRightArm();
	displayRobotLeftLeg();
	displayRobotRightLeg();

	glutSwapBuffers();
}

void onKeyPressed(unsigned char key, int x, int y) {
	switch (key) {
    case '+':
            if(helper == "rX"){
                if (currentRotatingPart == RotatingPart::HEAD){
                    rotateHead[0] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                    rotateLA[0] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                    rotateRA[0] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                    rotateLL[0] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                    rotateLL[0] += ROTATE_STEP;
                }else{
                    rotateX += ROTATE_STEP;
                }
            }else if(helper == "rY"){
                if (currentRotatingPart == RotatingPart::HEAD){
                    rotateHead[1] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                    rotateLA[1] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                    rotateRA[1] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                    rotateLL[1] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                    rotateLL[1] += ROTATE_STEP;
                }else{
                    rotateY += ROTATE_STEP;
                }
            }else if(helper == "rZ"){
                if (currentRotatingPart == RotatingPart::HEAD){
                    rotateHead[2] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                    rotateLA[2] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                    rotateRA[2] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                    rotateLL[2] += ROTATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                    rotateLL[2] += ROTATE_STEP;
                }else{
                    rotateZ += ROTATE_STEP;
                }
            }else if(helper == "tX"){
                if (currentRotatingPart == RotatingPart::HEAD){
                    translateHead[0] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                    translateLA[0] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                    translateRA[0] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                    translateLL[0] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                    translateRL[0] += TRANSLATE_STEP;
                }else{
                    tX += ROTATE_STEP;
                }
            }else if(helper == "tY"){
                if (currentRotatingPart == RotatingPart::HEAD){
                    translateHead[1] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                    translateLA[1] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                    translateRA[1] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                    translateLL[1] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                    translateRL[1] += TRANSLATE_STEP;
                }else{
                    tY += ROTATE_STEP;
                }
            }else if(helper == "tZ"){
                if (currentRotatingPart == RotatingPart::HEAD){
                    translateHead[2] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                    translateLA[2] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                    translateRA[2] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                    translateLL[2] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                    translateRL[2] += TRANSLATE_STEP;
                }else{
                    tZ += ROTATE_STEP;
                }
            }else if(helper == "sX"){
                if (currentRotatingPart == RotatingPart::HEAD){
                    scaleHead[0] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                    translateLA[2] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                    translateRA[2] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                    translateLL[2] += TRANSLATE_STEP;
                }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                    translateRL[2] += TRANSLATE_STEP;
                }else{
                    tZ += ROTATE_STEP;
                }
            }
		break;

	case 27: // ESC
		exit(0);
		return;

	default:
		return;
	}

	glutPostRedisplay();
}

void resize(int width, int height) {
	double aspect = WINDOW_WIDTH / WINDOW_HEIGHT;
	if (aspect > (double) width / height) {
		glViewport(0, 0, width, width / aspect);
	}
	else {
		glViewport(0, 0, height * aspect, height);
	}
}

void menu(int menuItem) {
	switch (menuItem) {
	case 0:
		currentRotatingPart = RotatingPart::WHOLE_ROBOT;
		break;
	case 1:
		currentRotatingPart = RotatingPart::HEAD;
		break;
	case 2:
		currentRotatingPart = RotatingPart::LEFT_ARM;
		break;
	case 3:
		currentRotatingPart = RotatingPart::RIGHT_ARM;
		break;
	case 4:
		currentRotatingPart = RotatingPart::LEFT_LEG;
		break;
    case 5:
        currentRotatingPart = RotatingPart::RIGHT_LEG;
        break;
    case 6:
        exit(0);
        return;
	default:
		return;
	}

	glutPostRedisplay();
}

void menu2(int menuItem){
    switch(menuItem){
        case 10:
            helper = "rX";
            break;
        case 11:
            helper = "rY";
            break;
        case 12:
            helper = "rZ";
            break;
        case 13:
            helper = "tX";
            break;
        case 14:
            helper = "tY";
            break;
        case 15:
            helper = "tZ";
            break;
        case 16:
            helper = "sX";
            break;
        case 17:
            helper = "sY";
            break;
        case 18:
            helper = "tZ";
            break;
        default:
            return;

    }
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("OpenGL Robot");

	init();
	glutDisplayFunc(displayRobot);
	glutKeyboardFunc(onKeyPressed);
	glutReshapeFunc(resize);

	glutCreateMenu(menu);
    glutAddMenuEntry("---Select current moving part---", INT_MAX);
	glutAddMenuEntry("Whole robot", 0);
	glutAddMenuEntry("Head", 1);
	glutAddMenuEntry("Left arm", 2);
	glutAddMenuEntry("Right arm", 3);
	glutAddMenuEntry("Left Leg", 4);
	glutAddMenuEntry("Right Leg", 5);
	glutAddMenuEntry("Quit", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutCreateMenu(menu2);
	glutAddMenuEntry("---Select current axis---", INT_MAX);
	glutAddMenuEntry("rX", 10);
	glutAddMenuEntry("rY", 11);
	glutAddMenuEntry("rZ", 12);
	glutAddMenuEntry("tX", 13);
	glutAddMenuEntry("tY", 14);
	glutAddMenuEntry("tZ", 15);
	glutAddMenuEntry("sX", 16);
	glutAddMenuEntry("sY", 17);
	glutAddMenuEntry("sZ", 18);
	glutAttachMenu(GLUT_LEFT_BUTTON);


	glutMainLoop();
}
