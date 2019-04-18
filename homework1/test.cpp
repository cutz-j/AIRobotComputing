#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

// 함수 & 변수 초기화 //

int program1(void);
int program2(void);
int program3(void);
static void Initialize(void);
static void RenderScene1(GLFWwindow* window);
static void RenderScene2(GLFWwindow* window);
static void RenderScene3(GLFWwindow* window);
static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
static void MouseMotionCallback(GLFWwindow* window, double x, double y);

float mousex = 0, mousey = 0; // mouse button 선언
bool dragging = false; // mouse drag 선언
int pressing = 0; // mouse press 선언

GLfloat RotateX, RotateY, RotateZ; // rotate 선언
GLfloat TranslateX, TranslateY, TranslateZ; // tranlate 선언


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
	function: 마우스 버튼 + 드래그 + 회전 / 3차원 정육각형
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

	// 1번째 면 ~ 6번째 면 //
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

	// 2번째
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

	// 3번째
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

	// 4번째
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

	// 5번째
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

	// 6번째
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