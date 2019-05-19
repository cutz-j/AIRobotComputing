#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>
#include <conio.h>
#include <windows.h>
#include <iostream>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3dll.lib")

HANDLE hMapFile;
int *pMapView;

static int WIDTH = 640;
static int HEIGHT = 480;

float *xyz;
unsigned char *rgb;
int memSize = 312000;

GLfloat TranslateX;
GLfloat TranslateY;
GLfloat TranslateZ;
GLfloat RotateX;
GLfloat RotateY;
GLfloat RotateZ;
GLfloat ZoomScale;


// function init //
static void Initialize(void);
void load3DPointClouds(void);
void renderPointClouds(void);
static void RenderScene(GLFWwindow* window);
void renderCoordinates(void);


int main(void) {
	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int) * 3, L"OPENCV_MEMORY");
	pMapView = (int*)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);

	while (1) {
		if (pMapView[0] == 2) {
			GLFWwindow* window;

			glfwInit();
			window = glfwCreateWindow(WIDTH, HEIGHT, "SAMPLE WINDOWS", NULL, NULL);
			glfwMakeContextCurrent(window);

			Initialize();

			while (!glfwWindowShouldClose(window)) {
				RenderScene(window);
				glfwSwapBuffers(window);
				glfwPollEvents();
			}
			glfwDestroyWindow(window);
			break;
		}
	}
	return 0;
}

static void Initialize(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 1.0);

	TranslateX = 0;
	TranslateY = 0;
	TranslateZ = 0;
	RotateX = 0;
	RotateY = 0;
	RotateZ = 0;
	ZoomScale = 1.0;

	xyz = new float[memSize * 3];
	rgb = new unsigned char[memSize * 3];

	memset(xyz, 0, sizeof(float) * memSize * 3);
	memset(rgb, 0, sizeof(unsigned char) * memSize * 3);

	load3DPointClouds();

}

void load3DPointClouds() {
	FILE * fp = fopen("d:/data/milk_big.3dp", "r");
	char buffer[1024], *label, ct[] = "\t\n";
	int idx = 0;
	int u = 0, v = 0;
	float x = 0, y = 0, z = 0;
	int r = 0, g = 0, b = 0;

	while (fgets(buffer, 1024, fp)) {
		label = strtok(buffer, ct);

		if (label == NULL)
			continue;

		u = (int)atoi(label);
		v = (int)atoi(strtok(NULL, ct));

		x = (float)atof(strtok(NULL, ct));
		y = (float)atof(strtok(NULL, ct));
		z = (float)atof(strtok(NULL, ct));

		r = (int)atoi(strtok(NULL, ct));
		g = (int)atoi(strtok(NULL, ct));
		b = (int)atoi(strtok(NULL, ct));

		xyz[idx * 3] = x;
		xyz[idx * 3 + 1] = y;
		xyz[idx * 3 + 2] = z;

		rgb[idx * 3] = b;
		rgb[idx * 3 + 1] = g;
		rgb[idx * 3 + 2] = r;

		idx++;
	}
	fclose(fp);
}

void renderPointClouds() {
	glPushMatrix();

	glPointSize(1.0f);
	glBegin(GL_POINTS);

	for (int i = 0; i < memSize; i++) {
		glColor3ub(rgb[i * 3], rgb[i * 3 + 1], rgb[i * 3 + 2]);
		glVertex3f(xyz[i * 3], xyz[i * 3 + 1], xyz[i * 3 + 2]);
	}

	glEnd();
	glPopMatrix();
}

void renderCoordinates(void) {

    // X axis
	glPushMatrix();
	glLineWidth(2.0f);
	glColor3f(1, 0, 0); // red
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	// Y axis
	glPushMatrix();
	glLineWidth(2.0f);
	glColor3f(0, 1, 0); // green
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	glPopMatrix();

	// Z axis
	glPushMatrix();
	glLineWidth(2.0f);
	glColor3f(0, 0, 1); // blue
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glPopMatrix();
}

static void RenderScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();

	glTranslatef(TranslateX, TranslateY, TranslateZ);
	glRotatef(RotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(RotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(RotateZ, 0.0f, 0.0f, 1.0f);
	glScalef(ZoomScale, ZoomScale, ZoomScale);

	renderCoordinates(); // operation
	renderPointClouds();

	glPopMatrix();

}