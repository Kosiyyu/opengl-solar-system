#include <iostream>
#include <GLFW/glfw3.h>
//#include <glad/glad.h>
#include <cmath>
#include <string>
#include <sstream>
#include <ctime>

//#define GL_MULTISAMPLE  0x809D

constexpr auto pi = 3.14159265358979323846;

constexpr auto backgroundColor = "#000033";
constexpr auto orbitColor = "#000033";

const int sides = 9;

int fps = 60;

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

	GLfloat* circleVerticesX = new GLfloat[numberOfVertices];
	GLfloat* circleVerticesY = new GLfloat[numberOfVertices];
	GLfloat* circleVerticesZ = new GLfloat[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 0; i < numberOfVertices; i += 1)
	{
		circleVerticesX[i] = x + (radius * cos(i * doublePi / sides));
		circleVerticesY[i] = y + (radius * sin(i * doublePi / sides));
		circleVerticesZ[i] = z;
	}

	GLfloat* allCircleVertices = new GLfloat[numberOfVertices * 3];

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

void drawSun(float sunX, float sunY, float sunOuterRadius, float sunInnerRadius, int sides, std::string outerColor = "#ffdf80", std::string innerColor = "#ffbf00")
{
	drawCircle(sunX, sunY, 0.0f, sunOuterRadius, sides, outerColor);
	drawCircle(sunX, sunY, 0.0f, sunInnerRadius, sides, innerColor);
}

void drawMercury(float mercuryX, float mercuryY, float mercuryRadius, int sides, std::string color = "#ffdf80")
{
	drawCircle(mercuryX, mercuryY, 0.0f, mercuryRadius, sides, color);
}

void drawPlanet(float planetX, float planetY, float planetRadius, int sides, std::string color = "#ffdf80")
{
	drawCircle(planetX, planetY, 0.0f, planetRadius, sides, color);
}


int main()
{
	GLFWwindow* window;
	if (!glfwInit())
	{
		std::cout << "Init error";
		return -1;
	}

	window = glfwCreateWindow(1000, 1000, "Hello", 0, 0);
	if (!window)
	{
		std::cout << "Window creation error";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	float x = 0.0f, y = 0.0f;
	float sunX = 0.0f, sunY = 0.0f, sunOuterRadius = 0.15f, sunInnerRadius = 0.11f;
	float mercuryX = 0.2f, mercuryY = 0.0f, mercuryRadius = 0.02f, mercuryOrbit = 0.2f, mercurySpeed = 0.001f;
	float wenusX = 0.3f, wenusY = 0.0f, wenusRadius = 0.03f, wenusOrbit = 0.3f, wenusSpeed = 0.0007f;
	float earthX = 0.4f, earthY = 0.0f, earthRadius = 0.04f, earthOrbit = 0.4f, earthSpeed = 0.0005f;
	float marsX = 0.5f, marsY = 0.0f, marsRadius = 0.03f, marsOrbit = 0.5f, marsSpeed = 0.0005f;
	float jowiszX = 0.6f, jowiszY = 0.0f, jowiszRadius = 0.05f, jowiszOrbit = 0.6f, jowiszSpeed = 0.0008f;
	float saturnX = 0.7f, saturnY = 0.0f, saturnRadius = 0.045f, saturnOrbit = 0.7f, saturnSpeed = 0.0003f;
	float uranX = 0.8f, uranY = 0.0f, uranRadius = 0.042f, uranOrbit = 0.8f, uranSpeed = 0.0001f;
	float neptunX = 0.9f, neptunY = 0.0f, neptunRadius = 0.042f, neptunOrbit = 0.9f, neptunSpeed = 0.00005f;
	// glEnable(GL_MULTISAMPLE);

	int newSides = 100;
	//////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////loop///////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0, 0.0, 0.10f, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// glEnable(GL_LINE_SMOOTH);
		// glEnable(GL_POLYGON_SMOOTH);
		// glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		// glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

		// my functions
		// drawCircletest(x, y, 0.15f, "#ffcc00");

		drawHollowCircle(x, y, 0.0f, 0.2f, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, 0.3f, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, 0.4f, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, 0.5f, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, 0.6f, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, 0.7f, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, 0.8f, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, 0.9f, newSides, "#ffffff");

		drawSun(sunX, sunY, sunOuterRadius, sunInnerRadius, sides);
		drawPlanet(mercuryX, mercuryY, mercuryRadius, newSides, "#AAAB97");
		drawPlanet(wenusX, wenusY, wenusRadius, newSides, "#E3BFA0");
		drawPlanet(earthX, earthY, earthRadius, newSides, "#255998");
		drawPlanet(marsX, marsY, marsRadius, newSides, "#EA7F5E");
		drawPlanet(jowiszX, jowiszY, jowiszRadius, newSides, "#FCE0A5");
		drawPlanet(saturnX, saturnY, saturnRadius, newSides, "#FACB93");
		drawPlanet(uranX, uranY, uranRadius, newSides, "#1B83D8");
		drawPlanet(neptunX, neptunY, neptunRadius, newSides, "#82BAE7");

		mercuryX = (mercuryOrbit * cos(mercurySpeed * (2.0f * pi) / sides));
		mercuryY = (mercuryOrbit * sin(mercurySpeed * ((2.0f * pi)) / sides));
		wenusX = (wenusOrbit * cos(wenusSpeed * (2.0f * pi) / sides));
		wenusY = (wenusOrbit * sin(wenusSpeed * ((2.0f * pi)) / sides));
		earthX = (earthOrbit * cos(earthSpeed * (2.0f * pi) / sides));
		earthY = (earthOrbit * sin(earthSpeed * ((2.0f * pi)) / sides));
		marsX = (marsOrbit * cos(marsSpeed * (2.0f * pi) / sides));
		marsY = (marsOrbit * sin(marsSpeed * ((2.0f * pi)) / sides));
		jowiszX = (jowiszOrbit * cos(jowiszSpeed * (2.0f * pi) / sides));
		jowiszY = (jowiszOrbit * sin(jowiszSpeed * ((2.0f * pi)) / sides));
		saturnX = (saturnOrbit * cos(saturnSpeed * (2.0f * pi) / sides));
		saturnY = (saturnOrbit * sin(saturnSpeed * ((2.0f * pi)) / sides));
		uranX = (uranOrbit * cos(uranSpeed * (2.0f * pi) / sides));
		uranY = (uranOrbit * sin(uranSpeed * ((2.0f * pi)) / sides));
		neptunX = (neptunOrbit * cos(neptunSpeed * (2.0f * pi) / sides));
		neptunY = (neptunOrbit * sin(neptunSpeed * ((2.0f * pi)) / sides));
		
		mercurySpeed += 0.0005f;
		wenusSpeed += 0.0003f;
		earthSpeed += 0.0002f;
		marsSpeed += 0.0001f;
		jowiszSpeed += 0.00002f;
		saturnSpeed += 0.00001f;
		uranSpeed += 0.00001f;
		neptunSpeed += 0.000009f;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}