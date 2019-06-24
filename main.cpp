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
const float TRANSLATE_STEP = 0.5f;
const float SCALE_STEP = 0.3f;
std::string helper = "rX";
GLint passo = 3;

bool light = true;
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
static float translateHead[3] = {0, 0.75, -1};
static float translateLA[3] = {-1, 0.1, 0};
static float translateRA[3] = {1, 0.1, 0};
static float translateLL[3] = {-0.25, -1, 0};
static float translateRL[3] = {0.25, -1, 0};
static float scaleHead[3] = {0.75, 0.75, 0.75};
static float scaleLA[3] = {1, 0.2, 0.2};
static float scaleRA[3] = {1, 0.2, 0.2};
static float scaleLL[3] = {0.5, 1, 0.5};
static float scaleRL[3] = {0.5, 1, 0.5};

 GLfloat scaleWhole[3] = {1.5, 1.5, 1.5};


struct tipo_camera {
    GLfloat posx;               // posicao x da camera
    GLfloat posy;               // posicao y da camera
    GLfloat posz;               // posicao z da camera
    GLfloat alvox;              // alvo x da visualizacao
    GLfloat alvoy;              // alvo y da visualizacao
    GLfloat alvoz;              // alvo z da visualizacao
    GLfloat ang;                // abertura da 'lente' - efeito de zoom
    GLfloat inicio;             // inicio da area de visualizacao em profundidade
    GLfloat fim;                // fim da area de visualizacao em profundidade
};

struct tipo_janela{
    GLfloat largura;            // largura da janela
    GLfloat altura;             // altura da jaanela
    GLfloat aspecto;            // aspecto da janela (relacao entre largura e altura)
};

tipo_camera camera;
tipo_janela janela;


static RotatingPart currentRotatingPart = RotatingPart::WHOLE_ROBOT;


void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;
    tX = 0.0f;
    tY = 0.0f;
    tZ = 0.0f;
    sX = 1.0f;
    sY = 2.0f;
    sZ = 1.0f;

    for(int i = 0; i < 3; i++){
        rotateHead[i] = 0;
        rotateLA[i] = 0;
        rotateRA[i] = 0;
        rotateLL[i] = 0;
        rotateRL[i] = 0;
    }
    translateHead[0] = {0};
    translateHead[1] = {0.75};
    translateHead[2] = {-1};

    translateLA[0] = {-1};
    translateLA[1] = {0.1};
    translateLA[2] = {0};

    translateRA[0] = {1};
    translateRA[1] = {0.1};
    translateRA[2] = {0};

    translateLL[0] = {-0.25};
    translateLL[1] = {-1};
    translateLL[2] = {0};


    translateRL[0] = {0.25};
    translateRL[1] = {-1};
    translateRL[2] = {0};

    scaleHead[0] = {0.75};
    scaleHead[1] = {0.75};
    scaleHead[2] = {0.75};

    scaleLA[0] = {1};
    scaleLA[1] = {0.2};
    scaleLA[2] = {0.2};


    scaleRA[0] = {1};
    scaleRA[1] = {0.2};
    scaleRA[2] = {0.2};

    scaleLL[0] = {0.5};
    scaleLL[1] = {1};
    scaleLL[2] = {0.5};

    scaleRL[0] = {0.5};
    scaleRL[1] = {1};
    scaleRL[2] = {0.5};

    scaleWhole[0] = {1.5};
    scaleWhole[1] = {1.5};
    scaleWhole[2] = {1.5};


	gluOrtho2D(-3.0f, 3.0, -3.0f, 3.0f);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// habilita a transparenica
    glEnable( GL_BLEND );

    janela.largura = WINDOW_WIDTH;
    janela.altura = WINDOW_HEIGHT;
    janela.aspecto = janela.largura / janela.altura;
    // define a forma de calculo da transparencia
    glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

    // Habilita antialiasing
    glEnable( GL_LINE_SMOOTH );

    // Solicita melhor qualidade
    glHint( GL_LINE_SMOOTH_HINT , GL_NICEST );

	GLfloat qaAmbientLight[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat qaDiffuseLight[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat qaSpecLight[] = {1.0, 1.0, 1.0, 1.0};

    camera.posx   = 0;
    camera.posy   = 0;
    camera.posz   = 0;
    camera.alvox  = 0;
    camera.alvoy  = 0;
    camera.alvoz  = 0;
    camera.inicio = 0.1;
    camera.fim    = 5000.0;
    camera.ang    = 45;


	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecLight);

	GLfloat qaLightPosition[] = {1.5, 1.5, 0.0, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
}

void displayRobotLeftArm() {
	glPushMatrix();
    glRotatef(rotateLA[0], 1.0, 0.0, 0.0);
	glRotatef(rotateLA[1], 0.0, 1.0, 0.0);
	glRotatef(rotateLA[2], 0.0, 0.0, 1.0);
	glTranslatef(translateLA[0], translateLA[1], translateLA[2]);
	glScalef(scaleLA[0], scaleLA[1], scaleLA[2]);
	glutSolidCube(1.0);
	glPopMatrix();
}

void displayRobotRightArm() {
	glPushMatrix();
	glRotatef(rotateRA[0], 1.0, 0.0, 0.0);
	glRotatef(rotateRA[1], 0.0, 1.0, 0.0);
	glRotatef(rotateRA[2], 0.0, 0.0, 1.0);
	glTranslatef(translateRA[0], translateRA[1], translateRA[2]);
	glScalef(scaleRA[0], scaleRA[1], scaleRA[2]);
	glutSolidCube(1.0);
	glPopMatrix();
}

void displayRobotLeftLeg() {
	glPushMatrix();
	glRotatef(rotateLL[0], 1.0, 0.0, 0.0);
	glRotatef(rotateLL[1], 0.0, 1.0, 0.0);
	glRotatef(rotateLL[2], 0.0, 0.0, 1.0);
	glTranslatef(translateLL[0], translateLL[1], translateLL[2]);
	glScalef(scaleLL[0], scaleLL[1], scaleLL[2]);
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobotRightLeg() {
	glPushMatrix();
	glRotatef(rotateRL[0], 1.0, 0.0, 0.0);
	glRotatef(rotateRL[1], 0.0, 1.0, 0.0);
	glRotatef(rotateRL[2], 0.0, 0.0, 1.0);
	glTranslatef(translateRL[0], translateRL[1], translateRL[2]);
	glScalef(scaleRL[0], scaleRL[1], scaleRL[2]);
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobotBody() {
	glPushMatrix();
	glutSolidCube(1.0);
	glPopMatrix();
}

void displayRobootHead() {
	glPushMatrix();
	glRotatef(rotateHead[0], 1, 0, 0);
	glRotatef(rotateHead[1], 0, 1, 0);
	glRotatef(rotateHead[2], 0, 0, 1);
	glTranslatef(translateHead[0], translateHead[1], translateHead[3]);
	glScalef(scaleHead[0], scaleHead[1], scaleHead[2]);
	glutSolidSphere(0.5, 15, 50);
	glScalef(1.0f, 2.0f, 1.0f);
	glPopMatrix();
}

void displayRobot() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	// set material prop

	GLfloat qaBlack[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0};
	GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, qaWhite);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);


	glTranslatef(tX, tY, tZ);

	glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);

	glScalef(scaleWhole[0], scaleWhole[1], scaleWhole[2]);

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
                rotateRL[0] += ROTATE_STEP;
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
                rotateRL[1] += ROTATE_STEP;
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
                rotateRL[2] += ROTATE_STEP;
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
                tX += TRANSLATE_STEP;
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
                tY += TRANSLATE_STEP;
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
                tZ += TRANSLATE_STEP;
            }
        }else if(helper == "sX"){
            if (currentRotatingPart == RotatingPart::HEAD){
                scaleHead[0] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                scaleLA[0] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                scaleRA[0] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                scaleLL[0] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                scaleRL[0] += SCALE_STEP;
            }else{
                scaleWhole[0] += SCALE_STEP;
            }
        }else if(helper == "sY"){
            if (currentRotatingPart == RotatingPart::HEAD){
                scaleHead[1] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                scaleLA[1] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                scaleRA[1] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                scaleLL[1] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                scaleRL[1] += SCALE_STEP;
            }else{
                scaleWhole[1] += SCALE_STEP;
            }
        }else if(helper == "sZ"){
            if (currentRotatingPart == RotatingPart::HEAD){
                scaleHead[2] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                scaleLA[2] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                scaleRA[2] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                scaleLL[2] += SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                scaleRL[2] += SCALE_STEP;
            }else{
                scaleWhole[2] += SCALE_STEP;
            }
        }
		break;
    case '-':
        if(helper == "rX"){
            if (currentRotatingPart == RotatingPart::HEAD){
                rotateHead[0] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                rotateLA[0] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                rotateRA[0] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                rotateLL[0] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                rotateRL[0] -= ROTATE_STEP;
            }else{
                rotateX -= ROTATE_STEP;
            }
        }else if(helper == "rY"){
            if (currentRotatingPart == RotatingPart::HEAD){
                rotateHead[1] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                rotateLA[1] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                rotateRA[1] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                rotateLL[1] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                rotateRL[1] -= ROTATE_STEP;
            }else{
                rotateY -= ROTATE_STEP;
            }
        }else if(helper == "rZ"){
            if (currentRotatingPart == RotatingPart::HEAD){
                rotateHead[2] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                rotateLA[2] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                rotateRA[2] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                rotateLL[2] -= ROTATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                rotateRL[2] -= ROTATE_STEP;
            }else{
                rotateZ -= ROTATE_STEP;
            }
        }else if(helper == "tX"){
            if (currentRotatingPart == RotatingPart::HEAD){
                translateHead[0] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                translateLA[0] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                translateRA[0] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                translateLL[0] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                translateRL[0] -= TRANSLATE_STEP;
            }else{
                tX -= ROTATE_STEP;
            }
        }else if(helper == "tY"){
            if (currentRotatingPart == RotatingPart::HEAD){
                translateHead[1] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                translateLA[1] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                translateRA[1] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                translateLL[1] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                translateRL[1] -= TRANSLATE_STEP;
            }else{
                tY -= ROTATE_STEP;
            }
        }else if(helper == "tZ"){
            if (currentRotatingPart == RotatingPart::HEAD){
                translateHead[2] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                translateLA[2] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                translateRA[2] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                translateLL[2] -= TRANSLATE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                translateRL[2] -= TRANSLATE_STEP;
            }else{
                tZ += TRANSLATE_STEP;
            }
        }else if(helper == "sX"){
            if (currentRotatingPart == RotatingPart::HEAD){
                scaleHead[0] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                scaleLA[0] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                scaleRA[0] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                scaleLL[0] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                scaleRL[0] -= SCALE_STEP;
            }else{
                scaleWhole[0] -= SCALE_STEP;
            }
        }else if(helper == "sY"){
            if (currentRotatingPart == RotatingPart::HEAD){
                scaleHead[1] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                scaleLA[1] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                scaleRA[1] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                scaleLL[1] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                scaleRL[1] -= SCALE_STEP;
            }else{
                scaleWhole[1] -= SCALE_STEP;
            }
        }else if(helper == "sZ"){
            if (currentRotatingPart == RotatingPart::HEAD){
                scaleHead[2] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_ARM){
                scaleLA[2] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_ARM){
                scaleRA[2] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::LEFT_LEG){
                scaleLL[2] -= SCALE_STEP;
            }else if(currentRotatingPart == RotatingPart::RIGHT_LEG){
                scaleRL[2] -= SCALE_STEP;
            }else{
                scaleWhole[2] -= SCALE_STEP;
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
