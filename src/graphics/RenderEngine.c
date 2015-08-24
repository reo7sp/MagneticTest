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

#include "test/graphics/RenderEngine.h"

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include "test/graphics/RenderContext.h"
#include "test/graphics/MagneticFieldRenderer.h"
#include "test/tools/TimeTools.h"
#include "test/tools/RenderTools.h"

#define MAX_FPS 60
#define MAX_DELTA_MS 1000 / MAX_FPS

static RenderContext _context = {
	.updateDelta = 0.0000001,
	.renderDelta = 0.0000001,
	.windowSize = { 0, 0, 0 },
	.camera = {
		.position = { -1, 0, -1 },
		.direction = { 1, 0, 1 }
	}
};
static double _lastUpdateDeltaUpdateTime = 0;
static double _lastRenderDeltaUpdateTime = 0;
static pthread_t _updateThread;
static pthread_mutex_t _updateThreadMutex;
static int _updateRequested = 0;
static int _updateThreadRunning = 0;

static inline float updateDelta(double* lastUpdateTime) {
	const double now = getTimeDetailed();
	const float delta = (float) (*lastUpdateTime ? now - *lastUpdateTime : 0.0000001);
	*lastUpdateTime = now;
	return delta;
}

static inline void go2D() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, _context.windowSize.x, 0, _context.windowSize.y);
	_context.windowSize.z = 1;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static inline void go3D() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, _context.windowSize.x / _context.windowSize.y, 0.00001, 128);
	_context.windowSize.z = 128;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		_context.camera.position.x, _context.camera.position.y, _context.camera.position.z,
		_context.camera.position.x + _context.camera.direction.x, _context.camera.position.y + _context.camera.direction.y, _context.camera.position.z + _context.camera.direction.z,
		0, 1, 0
	);
}

static inline void renderInfo() {
	static const Vector textPos = { 8, 8, 1 };
	static const Color textColor = { 1, 1, 1 };
	char text[128];
	sprintf(text, "FPS: %hd, maxFPS: %hd, rendDt: %dms, updDt: %dms, camPos: (%.1f, %.1f, %.1f), camDir: (%.1f, %.1f, %.1f)",
		(int) (1 / _context.renderDelta),
		MAX_FPS,
		(int) (_context.renderDelta * 1000),
		(int) (_context.updateDelta * 1000),
		_context.camera.position.x,
		_context.camera.position.y,
		_context.camera.position.z,
		_context.camera.direction.x,
		_context.camera.direction.y,
		_context.camera.direction.z
	);
	renderText(GLUT_BITMAP_HELVETICA_12, text, textPos, textColor);
}

static inline void renderOrigin() {
	static const Vector size = { 0.1, 0.1, 0.1 };
	static const Vector frameSize = { 0.11, 0.11, 0.11 };
	renderCube(vectorZero, size, colorGray);
	renderCubeFrame(vectorZero, frameSize, colorWhite);
}

static void onUpdate(int value) {
	glutPostRedisplay();
	glutTimerFunc(MAX_DELTA_MS, onUpdate, 0);

	pthread_mutex_lock(&_updateThreadMutex);
	_updateRequested = 1;
	pthread_mutex_unlock(&_updateThreadMutex);
}

static void* onBackgroundUpdate(void* arg) {
	while (1) {
		pthread_mutex_lock(&_updateThreadMutex);
		if (!_updateThreadRunning) {
			pthread_mutex_unlock(&_updateThreadMutex);
			break;
		}
		_context.updateDelta = updateDelta(&_lastUpdateDeltaUpdateTime);
		if (!_updateRequested) {
			pthread_mutex_unlock(&_updateThreadMutex);
			usleep((__useconds_t) 1.0e5);
			continue;
		}
		_updateRequested = 0;
		pthread_mutex_unlock(&_updateThreadMutex);

		updateMagneticField(&_context);
	}
}

static void onRender() {
	_context.renderDelta = updateDelta(&_lastRenderDeltaUpdateTime);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);

	go3D();
	renderOrigin();
	renderMagneticField(&_context);

	go2D();
	renderInfo();

	glutSwapBuffers();
}

static void onResize(int width, int height) {
	pthread_mutex_lock(&_updateThreadMutex);
	_context.windowSize.x = width;
	_context.windowSize.y = height;
	pthread_mutex_unlock(&_updateThreadMutex);
	glViewport(0, 0, width, height);
}

static void onKeyboard(unsigned char key, int x, int y) {
	static const float moveSpeed = 0.16;
	static const float rotateSpeed = 0.04;
	pthread_mutex_lock(&_updateThreadMutex);
	switch (key) {
		case 'w':
			_context.camera.position = vectorSum(_context.camera.position, vectorMultiply(_context.camera.direction, moveSpeed));
			break;
		case 's':
			_context.camera.position = vectorSubstract(_context.camera.position, vectorMultiply(_context.camera.direction, moveSpeed));
			break;
		case 'a':
			_context.camera.direction = vectorRotate(_context.camera.direction, vectorCreate(0, -rotateSpeed, 0));
			break;
		case 'd':
			_context.camera.direction = vectorRotate(_context.camera.direction, vectorCreate(0, rotateSpeed, 0));
			break;
		case 'h':
			_context.camera.position = vectorSum(_context.camera.position, vectorRotate(vectorMultiply(_context.camera.direction, moveSpeed), vectorCreate(0, -M_PI_2, 0)));
			break;
		case 'j':
			_context.camera.position.y -= moveSpeed;
			break;
		case 'k':
			_context.camera.position.y += moveSpeed;
			break;
		case 'l':
			_context.camera.position = vectorSum(_context.camera.position, vectorRotate(vectorMultiply(_context.camera.direction, moveSpeed), vectorCreate(0, M_PI_2, 0)));
			break;
		case 'r':
			_context.camera = (Camera) {
				.position = { -1, 0, -1 },
				.direction = { 1, 0, 1 }
			};
			break;
	}
	pthread_mutex_unlock(&_updateThreadMutex);
}

static int onInit() {
	// render
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glFogf(GL_FOG_DENSITY, 0.03);
	glFogf(GL_FOG_START, 10);
	glFogf(GL_FOG_END, 120);
	glEnable(GL_FOG);

	// update thread
	_updateThreadRunning = 1;
	pthread_mutex_init(&_updateThreadMutex, NULL);
	pthread_create(&_updateThread, NULL, onBackgroundUpdate, NULL);

	// user
	return initMagneticField();
}

static void onDeinit() {
	pthread_mutex_lock(&_updateThreadMutex);
	_updateThreadRunning = 0;
	pthread_mutex_unlock(&_updateThreadMutex);
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
		glutTimerFunc(MAX_DELTA_MS, onUpdate, 0);
		glutDisplayFunc(onRender);
		glutReshapeFunc(onResize);
		glutKeyboardFunc(onKeyboard);
		glutMainLoop();
	} else {
		fprintf(stderr, "error: Can't init renderer\n");
		onDeinit();
		return EXIT_FAILURE;
	}

	onDeinit();
	return EXIT_SUCCESS;
}
