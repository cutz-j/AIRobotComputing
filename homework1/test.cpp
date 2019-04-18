#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

// �Լ� & ���� �ʱ�ȭ //

int program1(void);
int program2(void);
int program3(void);
static void Initialize(void);
static void RenderScene1(GLFWwindow* window);
static void RenderScene2(GLFWwindow* window);
static void RenderScene3(GLFWwindow* window);
static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
static void MouseMotionCallback(GLFWwindow* window, double x, double y);

float mousex = 0, mousey = 0; // mouse button ����
bool dragging = false; // mouse drag ����
int pressing = 0; // mouse press ����

GLfloat RotateX, RotateY, RotateZ; // rotate ����
GLfloat TranslateX, TranslateY, TranslateZ; // tranlate ����


int main() {
	//program1();
	//program2();
	program3();
	return 0;
}

int program1(void) {
	GLFWwindow* window;
	glfwInit();
	window = glfwCreateWindow(640, 480, "DISPLAY1", NULL, NULL);
	glfwMakeContextCurrent(window);

	Initialize();

	while (!glfwWindowShouldClose(window)) {
		RenderScene1(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);


	return 0;
}

static void Initialize(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

static void RenderScene1(GLFWwindow* window) {
	
	float y = -1.0;
	int swit = 1;
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 3; i++) {
		for (float j = 0.0; j <= 2.0; j += 0.5) {
			float x = -1.0;
			glPushMatrix();
			glBegin(GL_POLYGON);
			glColor3f(swit % 2, 0, swit % 2);
			glVertex2f(x + j, y);
			glVertex2f(x + j + 0.5, y);
			glVertex2f(x + j + 0.5, y + 0.666);
			glVertex2f(x + j, y + 0.666);
			glEnd();
			glPopMatrix;
			swit += 1;
		}
		y += 0.666;
	}
}


int program2(void) {
	GLFWwindow* window;
	glfwInit();
	window = glfwCreateWindow(640, 480, "DISPLAY1", NULL, NULL);
	glfwMakeContextCurrent(window);

	Initialize();

	while (!glfwWindowShouldClose(window)) {
		RenderScene2(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);


	return 0;
}

static void RenderScene2(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(0, 1, 0);
	glVertex2f(0, 1);
	glVertex2f(-1, -0.5);
	glVertex2f(1, -0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1);
	glVertex2f(0, -1);
	glVertex2f(-1, 0.5);
	glVertex2f(1, 0.5);
	glEnd();
	glPopMatrix();

	
}

int program3(void) {
	/*
	function: ���콺 ��ư + �巡�� + ȸ�� / 3���� ��������
	*/
	GLFWwindow* window;
	glfwInit();
	window = glfwCreateWindow(640, 480, "DISPLAY1", NULL, NULL);
	glfwMakeContextCurrent(window);

	Initialize();

	glfwSetMouseButtonCallback(window, MouseClickCallback);
	glfwSetCursorPosCallback(window, MouseMotionCallback);


	while (!glfwWindowShouldClose(window)) {
		
		RenderScene3(window);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);


	return 0;
}

static void RenderScene3(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT);

	// 1��° �� ~ 6��° �� //
	glPushMatrix();
	// translate + rotate //
	glTranslatef(TranslateX, TranslateY, TranslateZ); 
	glRotatef(RotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(RotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(RotateZ, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0.5, 0.5, 0);
	glVertex3f(0, 0.5, 0);
	glEnd();
	glPopMatrix();

	// 2��°
	glPushMatrix();
	glTranslatef(TranslateX, TranslateY, TranslateZ);
	glRotatef(RotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(RotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(RotateZ, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0);
	glEnd();
	glPopMatrix();

	// 3��°
	glPushMatrix();
	glTranslatef(TranslateX, TranslateY, TranslateZ);
	glRotatef(RotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(RotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(RotateZ, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(0.5, 0.5, 0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0, 0.5, 0.5);
	glVertex3f(0, 0.5, 0);
	glEnd();
	glPopMatrix();

	// 4��°
	glPushMatrix();
	glTranslatef(TranslateX, TranslateY, TranslateZ);
	glRotatef(RotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(RotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(RotateZ, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0.5, 0);
	glVertex3f(0, 0.5, 0.5);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0, 0, 0);
	glEnd();
	glPopMatrix();

	// 5��°
	glPushMatrix();
	glTranslatef(TranslateX, TranslateY, TranslateZ);
	glRotatef(RotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(RotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(RotateZ, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0, 0);
	glEnd();
	glPopMatrix();

	// 6��°
	glPushMatrix();
	glTranslatef(TranslateX, TranslateY, TranslateZ);
	glRotatef(RotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(RotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(RotateZ, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 0);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0, 0.5, 0.5);
	glEnd();
	glPopMatrix();

}

static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods) {

	printf("button: %d\n", button);
	switch (button) {
	case GLFW_MOUSE_BUTTON_1:
		dragging = action;
		break;
	}
}

static void MouseMotionCallback(GLFWwindow* window, double x, double y) {
	double scale = 0.1;

	if (dragging){
		printf("x: %f, y: %f\n", (mousex - x), (mousey - y));
		RotateY += (mousex - x) * scale;
		RotateX += (mousey - y) * scale;
	}

	mousex = x;
	mousey = y;
}