/* Copyright (c) 2015 Oleg Morozenkov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "test/renderer.h"

#include <stdio.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include "test/tools/timeTools.h"

#define MAX_FPS 30
#define MAX_DELTA_MS 1000 / MAX_FPS

unsigned long lastFpsUpdateTime = 0;
unsigned int fps = 0;
unsigned int fpsRaw = 0;
double lastDeltaUpdateTime = 0;


double calculateDelta() {
	double now = getTimeDetailed();
	double delta = now - lastDeltaUpdateTime;
	lastDeltaUpdateTime = now;
	return delta;
}

int updateFpsCounter() {
	++fpsRaw;
	unsigned long now = getTime();
	if (now - lastFpsUpdateTime > 1) {
		fps = fpsRaw;
		fpsRaw = 0;
		lastFpsUpdateTime = now;
		return 1;
	}
	return 0;
}

int writeFpsToStdout() {
	printf("FPS: %d\n", fps);
	//printf("FPS: %d\r", fps);
	//fflush(stdout);
}

int onInit() {
	return 1;
}

int onUpdate(int value) {
	double dt = calculateDelta();
	glutPostRedisplay();
	glutTimerFunc(MAX_DELTA_MS, onUpdate, 0);
}

void onRender() {
	if (updateFpsCounter()) {
		writeFpsToStdout();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);
	glEnd();

	glutSwapBuffers();
}

void onResize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}


int rendMain(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ComplexNumTest by Reo_SP");

	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK) {
		fprintf(stderr, "error: %s\n", glewGetErrorString(glewStatus));
		return EXIT_FAILURE;
	}

	if (onInit()) {
		calculateDelta();
		glutTimerFunc(MAX_DELTA_MS, onUpdate, 0);
		glutDisplayFunc(onRender);
		glutReshapeFunc(onResize);
		glutMainLoop();
	} else {
		fprintf(stderr, "error: Can't init renderer\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
