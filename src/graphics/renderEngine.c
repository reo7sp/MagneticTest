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

#include "test/graphics/renderEngine.h"

#include <stdio.h>

#include <GL/glew.h>
#if defined(linux) || defined(_WIN32)
#include <GL/glut.h>
#else
#include <GLUT/GLUT.h>
#endif

#include "test/graphics/renderContext.h"
#include "test/graphics/magneticFieldRenderer.h"
#include "test/tools/timeTools.h"

#define MAX_FPS 30
#define MAX_DELTA_MS 1000 / MAX_FPS

static float _delta = 0;
static double _lastDeltaUpdateTime = 0;

static float updateDelta() {
	double now = getTimeDetailed();
	_delta = now - lastDeltaUpdateTime;
	lastDeltaUpdateTime = now;
	return delta;
}

static int onInit() {
	return initMagneticField();
}

static int onUpdate(int value) {
	updateDelta();
	glutPostRedisplay();
	glutTimerFunc(MAX_DELTA_MS, onUpdate, 0);

	updateMagneticField({ .delta = delta });
}

static void onRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);
	glEnd();

	renderMagneticField({ .delta = delta });

	glutSwapBuffers();
}

static void onResize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int renderEngineMain(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MagneticTest by Reo_SP");

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
