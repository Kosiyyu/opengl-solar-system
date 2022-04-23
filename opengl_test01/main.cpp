#include <iostream>
#include <GLFW/glfw3.h>
//#include <glad/glad.h>
#include <cmath>
#include <string>
#include <sstream>

//#define GL_MULTISAMPLE  0x809D

constexpr auto pi = 3.14159265358979323846;

//const int steps = 10;
const int sides = 9;
//const float angle = pi * 2.f / steps;
/*
void drawCircle(float startX = 0.0f, float startY = 0.0f,float radius = 0.5f, float red = 0.1f, float blue = 0.1f, float green = 0.1f) {
	float prevX = startX;
	float prevY = startY - radius;

	for (int i = 0; i < steps + 1; i++) {

		float newX = startX + (radius * sin(angle * i));
		float newY = startY + (- radius * cos(angle * i));

		//glShadeModel(GL_SMOOTH);
		glBegin(GL_TRIANGLES);
		glColor3f(red, blue, green);
		glVertex2f(startX, startY);
		glVertex2f(prevX, prevY);
		glVertex2f(newX, newY);
		glEnd();

		prevX = newX;
		prevY = newY;
	}
}
*/

/*
void drawCircletest(float startX = 0.0f, float startY = 0.0f, float radius = 0.5f, std::string hex = "#000000") {
	hex = hex.substr(1, hex.length() - 1);
	hex.insert(0, "0x");

	int hexInteger;

	std::stringstream ss;
	ss << std::hex << hex;
	ss >> hexInteger;

	//std::cout << hexInteger;
	//system("pause");

	float red = ((hexInteger >> 16) & 0xFF) / 255.0;
	float blue = ((hexInteger >> 8) & 0xFF) / 255.0;
	float green = ((hexInteger) & 0xFF) / 255.0;

	float prevX = startX;
	float prevY = startY - radius;

	for (int i = 0; i < steps + 1; i++) {

		float newX = startX + (radius * sin(angle * i));
		float newY = startY + (-radius * cos(angle * i));

		//glShadeModel(GL_SMOOTH);
		glBegin(GL_TRIANGLES);
		glColor3f(red, blue, green);
		glVertex2f(startX, startY);
		glVertex2f(prevX, prevY);
		glVertex2f(newX, newY);
		glEnd();

		prevX = newX;
		prevY = newY;
	}
}
*/


/*
void drawCircle1(float startX = 0.0f, float startY = 0.0f, float radius = 0.5f, std::string hex = "#000000") {
	hex = hex.substr(1, hex.length() - 1);
	hex.insert(0, "0x");

	int hexInteger;

	std::stringstream ss;
	ss << std::hex << hex;
	ss >> hexInteger;

	float red = ((hexInteger >> 16) & 0xFF) / 255.0;
	float blue = ((hexInteger >> 8) & 0xFF) / 255.0;
	float green = ((hexInteger) & 0xFF) / 255.0;

	float prevX = startX;
	float prevY = startY - radius;

	for (int i = 0; i < steps + 1; i++) {

		float newX = startX + (radius * sin(angle * i));
		float newY = startY + (-radius * cos(angle * i));

		//glShadeModel(GL_SMOOTH);
		glBegin(GL_POINTS);
		glColor3f(red, green, blue);
		glVertex3f(newX, newY, 0.0f);
		glEnd();

		prevX = newX;
		prevY = newY;
	}
}
*/

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint sides, std::string hex)
{
	hex = hex.substr(1, hex.length() - 1);
	hex.insert(0, "0x");

	int hexInteger;

	std::stringstream ss;
	ss << std::hex << hex;
	ss >> hexInteger;

	float red = ((hexInteger >> 16) & 0xFF) / 255.0;
	float green = ((hexInteger >> 8) & 0xFF) / 255.0;
	float blue = ((hexInteger) & 0xFF) / 255.0;
	/////////////////////////////////////////////////////////////////////////////
	int numberOfVertices = sides + 2;

	GLfloat twicePi = 2.0f * pi;

	GLfloat* circleVerticesX = new GLfloat[numberOfVertices];
	GLfloat* circleVerticesY = new GLfloat[numberOfVertices];
	GLfloat* circleVerticesZ = new GLfloat[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 1; i < numberOfVertices; i++)
	{
		circleVerticesX[i] = x + (radius * cos(i * twicePi / sides));
		circleVerticesY[i] = y + (radius * sin(i * twicePi / sides));
		circleVerticesZ[i] = z;
	}

	GLfloat* allCircleVertices = new GLfloat[numberOfVertices * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glColor3f(red, green, blue);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);

	delete[] circleVerticesX;
	delete[] circleVerticesY;
	delete[] circleVerticesZ;
	delete[] allCircleVertices;

}

void drawHollowCircle(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f, GLfloat radius = 0.5f, GLint sides = 50, std::string hex = "#000000")
{
	hex = hex.substr(1, hex.length() - 1);
	hex.insert(0, "0x");

	int hexInteger;

	std::stringstream ss;
	ss << std::hex << hex;
	ss >> hexInteger;

	float red = ((hexInteger >> 16) & 0xFF) / 255.0;
	float blue = ((hexInteger >> 8) & 0xFF) / 255.0;
	float green = ((hexInteger) & 0xFF) / 255.0;
	/////////////////////////////////////////////////////////////////////////////
	GLint numberOfVertices = sides + 1;

	GLfloat doublePi = 2.0f * pi;

	GLfloat *circleVerticesX = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesY = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesZ = new GLfloat[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 0; i < numberOfVertices; i++)
	{
		circleVerticesX[i] = x + (radius * cos(i * doublePi / sides));
		circleVerticesY[i] = y + (radius * sin(i * doublePi / sides));
		circleVerticesZ[i] = z;
	}

	GLfloat *allCircleVertices = new GLfloat[numberOfVertices * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glColor3f(red, blue, green);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_LINE_STRIP, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);

	delete[] circleVerticesX;
	delete[] circleVerticesY;
	delete[] circleVerticesZ;
	delete[] allCircleVertices;
}


int main() {
	GLFWwindow* window;
	if (!glfwInit()) {
		std::cout << "Init error";
		return -1;
	}

	window = glfwCreateWindow(1000, 1000, "Hello", 0, 0);
	if (!window) {
		std::cout << "Window creation error";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	float x = 0.0f, y = 0.0f;
	float sunX= 0.0f, sunY = 0.0f, sunOuterRadius = 0.15f, sunInnerRadius = 0.11f;

	//glEnable(GL_MULTISAMPLE);

	int newSides = 100;

	//////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////loop///////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	while (!glfwWindowShouldClose(window)) {


		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//glEnable(GL_LINE_SMOOTH);
		//glEnable(GL_POLYGON_SMOOTH);
		//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

		//my functions
		//drawCircletest(x, y, 0.15f, "#ffcc00");
		
		drawHollowCircle(x, y, 0.0f, 0.2f, newSides, "#ffcc00");
		drawHollowCircle(x, y, 0.0f, 0.3f, newSides, "#ffcc00");
		drawHollowCircle(x, y, 0.0f, 0.4f, newSides, "#ffcc00");
		drawHollowCircle(x, y, 0.0f, 0.5f, newSides, "#ffcc00");
		drawHollowCircle(x, y, 0.0f, 0.6f, newSides, "#ffcc00");
		drawHollowCircle(x, y, 0.0f, 0.7f, newSides, "#ffcc00");
		drawHollowCircle(x, y, 0.0f, 0.8f, newSides, "#ffcc00");
		drawHollowCircle(x, y, 0.0f, 0.9f, newSides, "#ffcc00");
		drawCircle(sunX, sunY, 0.0f, sunOuterRadius, sides, "#ffdf80");
		drawCircle(sunX, sunY, 0.0f, sunInnerRadius, sides, "#ffbf00");

		//x += 0.000001f;
		//y += 0.000001f;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}