// universo_relativo.cpp: define el punto de entrada de la aplicación de consola.
//
#include <iostream>
#include "GL/glut.h"
#include "stdafx.h"

//--------------------------
//Declaracion de variables
GLfloat Radio_int_toroide, Radio_ext_toroide;
GLfloat Radio_planeta, Radio_sol;
GLfloat Altura_cono, Base_cono;
GLfloat orbita_planeta, orbita_luna;
GLfloat Theta, Omega, Miu, Alfa, Gamma, Lambda, Epsilon, Delta;
GLfloat trasla_cam_z;
//--------------------------

//--------------------------
//Prototipo de las funciones
void Entero();
void Render();
void Timer();
void Camara_ortogonal_frontal();
void Camara_perspectiva();
void Inclinacion();
void Inclinacion_orbitas();
void Coordenadas_luna();
void Coordenadas_planeta();
void Luna();
void Planeta();
void Sol();
//--------------------------

//--------------------------
//Callback de las funciones
void Teclado(unsigned char key, int x, int y);
void Flechas(int key, int x, int y);
//--------------------------

//--------------------------
//Funcion inicializadora de variables
void Entero()
{
	Radio_int_toroide = 0.05;
	Radio_ext_toroide = 0.5;
	Radio_planeta = 0.6;
	Radio_sol = 1.0;
	orbita_planeta = 2.0;
	orbita_luna = 1.0;
	trasla_cam_z = 0.0;
	Alfa = 0.0;
	Theta = 0.0; //Ángulo de giro de la esfera en las coordenadas respectivas al toroide
	Omega = 0.0; //Ángulo de giro del toroide en el eje y, en las coordenadas globales
	Miu = 0.0; //Ángulo de rotacion del cono sobre su eje
	Gamma = 0.0; //Ángulo de rotación del planeta
	Lambda = 0.0; //Ángulo para girar el planeta alrededor del sol
	Epsilon = 0.0; //Ángulo de rotación del sol
}
//--------------------------

//--------------------------
//Método con el proposito de inclinar cada figura ciertos grados
void Inclinacion()
{
	glRotatef(315, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
}
//--------------------------

//--------------------------
//Método con el proposito de inclinar cada figura ciertos grados con respecto a las orbitas
void Inclinacion_orbitas()
{
	glRotatef(120, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
}
//--------------------------

//--------------------------
//Método con el proposito de referenciar la luna en el sistema general
void Coordenadas_luna()
{	
	Alfa += 2.0;
	Coordenadas_planeta();
	glRotatef(Alfa, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, orbita_luna);
}
//--------------------------

//--------------------------
//Método para referenciar al planeta en el sistema general
void Coordenadas_planeta()
{
	Gamma += 0.4;
	Inclinacion_orbitas();	
	glRotatef(Gamma, 0.0, 0.0, 1.0);
	glTranslatef(orbita_planeta, 0.0, 0.0);
}
//--------------------------

//--------------------------
//Método para crear la representación del sol
void Sol()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3ub(254, 210, 50);
	Epsilon += 1;
	glRotatef(Epsilon, 0.0, 1.0, 0.0);
	glutWireSphere(Radio_sol, 50, 50);
}
//--------------------------

//--------------------------
//Método para crear la representación del planeta
void Planeta()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3ub(62, 255, 206);
	Coordenadas_planeta();
	glRotatef(Gamma, 0.0, 0.0, 1.0);
	glutWireSphere(Radio_planeta, 50, 50);
}
//--------------------------

//--------------------------
//Método para crear la representación de la luna 
void Luna()
{
	glMatrixMode(GL_MODELVIEW);
	//Creación del toroide
	glLoadIdentity();
	glColor3ub(255, 0, 0);
	Coordenadas_luna();
	Omega += 3.5;
	glRotatef(Omega, 0.0, 1.0, 0.0);
	Inclinacion();
	glutWireTorus(Radio_int_toroide, Radio_ext_toroide, 50, 50);
	//Creación de la esfera
	glColor3ub(0, 0, 255);	
	Theta += 4.0;
	glRotatef(Theta, 0.0, 0.0, 1.0);
	glTranslatef(Radio_ext_toroide, 0, 0);
	glutWireSphere(Radio_int_toroide, 20, 20);

	//Creación del cono
	glLoadIdentity();
	glColor3ub(0, 250, 0);

	Miu += 1;
	Coordenadas_luna();
	Inclinacion();
	glRotatef(Miu, 0.0, 0.0, 1.0);
	glutWireCone(0.35, 0.35, 50, 50);	
}
//--------------------------

//--------------------------
//Método mediante el cual con instrucciones de OpenGL determinamos la cámara y la proyección en perspectiva
void Camara_ortogonal_frontal()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, trasla_cam_z);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -4.0, 4.0);
	gluLookAt(0.0f, 0.0f, -0.5f, 
		      0.0f, 0.0f, 0.0f, 
			  0.0f, 1.0f, 0.0f);
}
//--------------------------

//--------------------------
//Método mediante el cual con instrucciones de OpenGL determinamos la cámara y la proyección en perspectiva
void Camara_perspectiva()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, trasla_cam_z);
	gluPerspective(90, 1, -1.0, 1.0);
	glTranslatef(0.0, 0.0, -2.0);
	gluLookAt(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}
//--------------------------

//--------------------------
//Método para generar un movimiento continuo y que se ejecute cada cierto tiempo
void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 0);
}
//--------------------------

//--------------------------
//Funcion para implementar el teclado
void Teclado(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // Escape
		exit(0);
	default:
		break;
	}
	glutPostRedisplay();
}
//--------------------------

//--------------------------
//Funcion para implementar el manejo de las flechas del teclado
void Flechas(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		trasla_cam_z += 0.1f;
		break;
	case GLUT_KEY_DOWN:
		trasla_cam_z -= 0.1f;
		break;
	case GLUT_KEY_LEFT:
		Camara_ortogonal_frontal();
		break;
	case GLUT_KEY_RIGHT:
		Camara_perspectiva();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
//--------------------------

//--------------------------
//Funcion que grafica lo que se indica
void Render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 400, 400);
	Luna();
	Planeta();
	Sol();
	glutSwapBuffers();
}
//--------------------------

//--------------------------
//Funcion principal
int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	Entero();
	glutCreateWindow("Escena con coordenadas relativas");
	glutReshapeWindow(400, 400);
	glutDisplayFunc(Render);
	glutTimerFunc(0, Timer, 0);
	glutKeyboardFunc(Teclado);
	glutSpecialFunc(Flechas);
	glutMainLoop();
	return 0;
}
//-------------------------

