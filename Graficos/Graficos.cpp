// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "time.h"

#include <iostream>
using namespace std;

//Declaración de ventana
GLFWwindow *window;

GLfloat red, green, blue;
GLfloat ty = 0.0f;
GLfloat tx = 0.0f;
int direccion = 1;

double tiempoAnterior = 0.0;
double velocidad = 0.6;

GLfloat angulo = 0.0f;
GLfloat velocidadAngular = 180.0f;

GLfloat SerpienteX = 0.0f;
GLfloat SerpienteY = 0.0f;

GLfloat balaX = 0.0f;
GLfloat balaY = 0.0f;
GLfloat balaDireccion = 0.0f;
bool balaDisparando = false;





void checarColisiones() {
	if (tx >= 1 - 0.06  ||
		tx <= -1 - 0.06 ||
		ty >= 1   -0.06 ||
		ty <= -1 - 0.06) {
		exit(0);
	}
}

void actualizarSerpiente(double tiempoTranscurrido) {
	
	if (direccion == 1) //Arriba
	{
		ty += velocidad * tiempoTranscurrido;
	}
	else if (direccion == 2) //Izquierda
	{
		tx -= velocidad * tiempoTranscurrido;
	}
	else if (direccion == 3) //Derecha
	{
		tx += velocidad * tiempoTranscurrido;
	}
	else if (direccion == 4) //Abajo
	{
		ty -= velocidad * tiempoTranscurrido;
	}

}

void actualizar() { 
	//Aquí esta bien para cambiar los valores
	//De las variables de mi programa!
	double tiempoActual = glfwGetTime();
	double tiempoTranscurrido = 
		tiempoActual - tiempoAnterior;
	
	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		direccion = 1;
	}
	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS) {
		direccion = 4;
	}

	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		direccion = 2;
	}

	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		direccion = 3;
	}

	actualizarSerpiente(tiempoTranscurrido);
	checarColisiones();
	tiempoAnterior = tiempoActual;

}

void dibujarComida() {
	float comida = rand();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	//glRotatef(angulo, 0.0f, 0.0f, 1.0f);
	glScalef(0.1f, 0.1f, 0.1f);
	glBegin(GL_POLYGON); //Inicia la rutina con un modo de dibujo
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-comida * 0.01, comida*0.01, 0.0f);
	glVertex3f(comida * 0.01, comida * 0.01, 0.0f);
	glVertex3f(comida * 0.01, -comida * 0.01, 0.0f);
	glVertex3f(-comida * 0.01,-comida*0.01, 0.0f);

	glEnd();//Finaliza la rutina
	glPopMatrix();
}

void dibujarSerpiente() {
	glPushMatrix();
	glTranslatef(tx, ty, 0.0f);
	glScalef(0.1f, 0.01f, 0.01f);
	glBegin(GL_QUADS); //Inicia la rutina con un modo de dibujo
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(0.1f, 1.0f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glVertex3f(-1.0, -0.1f, 0.0f);
	glEnd();//Finaliza la rutina
	glPopMatrix();
}

void dibujar() {
	//dibujarComida();
	dibujarSerpiente();
}

void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {

	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (ty < 1)
			ty += 0.05f;
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (ty > -1)
			ty -= 0.05f;
	}

	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (tx < 1)
			tx += 0.05f;
	}

	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (tx > -1)
			tx -= 0.05f;
	}


}

int main()
{
	
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicialización de GLFW
	if (!glfwInit()) {
		//Si no se inició bien, terminar la ejecución
		exit(EXIT_FAILURE);
	}

	//Inicializar la ventana
	window = glfwCreateWindow(ancho, alto, "Graficos", NULL, NULL);
	//Verficar si se creó bien la ventana
	if (!window) {
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecución
		exit(EXIT_FAILURE);
	}

	//Establecer "window" como contexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL Moderno
	glewExperimental = true;
	//Inicializar GLEW
	GLenum glewError = glewInit();
	//Verificar que GLEW se inicializó bien
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}



	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL: " << version << endl;


	red = green = blue = 0.0f;

	//glfwSetKeyCallback(window, key_callback);

	tiempoAnterior = glfwGetTime();

	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window)) {
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia la pantalla
		glClearColor(red, green, blue, 1);
		//Limpiar la pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//rutina de dibujo
		actualizar();
		dibujar();

		//Intercambio de buffers
		glfwSwapBuffers(window);
		//Buscar señales de entrada
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

