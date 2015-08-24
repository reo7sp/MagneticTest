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

#include "test/graphics/MagneticFieldRenderer.h"

#include <GL/glut.h>
#include <pthread.h>

#include "test/physics/electromagnetism.h"
#include "test/collections/DynamicArray.h"
#include "test/tools/RenderTools.h"

typedef struct Conductor {
	Vector position;
	double I;
	double permeability;
	Vector l;
} Conductor;

typedef struct VectorFieldPoint {
	Vector position;
	Vector direction;
} VectorFieldPoint;

static DynamicArray* _conductors;
static DynamicArray* _fieldPoints;
static pthread_mutex_t _fieldPointsMutex;

static inline void drawVector(Vector position, Vector vector, Color lineColor, Color endColor) {
	if (vectorGetLengthSq(vector) < 0.001) {
		return;
	}

	Vector sum = vectorSum(position, vector);
	glColor3f(lineColor.r, lineColor.g, lineColor.b);
	glBegin(GL_LINES);
		glVertex3d(position.x, position.y, position.z);
		glVertex3d(sum.x, sum.y, sum.z);
	glEnd();

	static double endSize = 0.05;
	renderCube(sum, vectorCreate(endSize, endSize, endSize), endColor);
}

int initMagneticField() {
	_conductors = arrayNew(1);
	_fieldPoints = arrayNew(2048);
	pthread_mutex_init(&_fieldPointsMutex, NULL);

	Conductor* conductor1 = (Conductor*) malloc(sizeof(Conductor));
	conductor1->position = (Vector) { 12, -12, -12 };
	conductor1->I = 6000;
	conductor1->permeability = 2.5 * 1.0e-1;
	conductor1->l = (Vector) { 4, 0.6, 0.6 };
	arrayAppend(_conductors, conductor1);

	Conductor* conductor2 = (Conductor*) malloc(sizeof(Conductor));
	conductor2->position = (Vector) { 12, 12, -12 };
	conductor2->I = 3000;
	conductor2->permeability = 2.5 * 1.0e-1;
	conductor2->l = (Vector) { 4, 0.4, 0.4 };
	arrayAppend(_conductors, conductor2);

	Conductor* conductor3 = (Conductor*) malloc(sizeof(Conductor));
	conductor3->position = (Vector) { 12, 12, 12 };
	conductor3->I = 9000;
	conductor3->permeability = 2.5 * 1.0e-1;
	conductor3->l = (Vector) { 4, 0.9, 0.9 };
	arrayAppend(_conductors, conductor3);

	Conductor* conductor4 = (Conductor*) malloc(sizeof(Conductor));
	conductor4->position = (Vector) { 12, -12, 12 };
	conductor4->I = 1000;
	conductor4->permeability = 2.5 * 1.0e-1;
	conductor4->l = (Vector) { 4, 0.3, 0.3 };
	arrayAppend(_conductors, conductor4);

	return 1;
}

void updateMagneticField(const RenderContext* context) {
	static const Vector minCellPosRel = { -48, -48, -48 };
	static const Vector maxCellPosRel = { 48, 48, 48 };
	static const int cellStep = 8;
	Vector minCellPos = vectorSum(context->camera.position, minCellPosRel);
	Vector maxCellPos = vectorSum(context->camera.position, maxCellPosRel);
	size_t i, count;

	// remove points which is too far from camera
	for (i = 0, count = arrayGetLength(_fieldPoints); i < count; ++i) {
		pthread_mutex_lock(&_fieldPointsMutex);
		VectorFieldPoint* point = (VectorFieldPoint*) arrayGetAt(_fieldPoints, i);
		if (point->position.x < minCellPos.x + minCellPosRel.x || point->position.x > maxCellPos.x + maxCellPosRel.x ||
			point->position.y < minCellPos.y + minCellPosRel.y || point->position.y > maxCellPos.y + maxCellPosRel.y ||
			point->position.z < minCellPos.z + minCellPosRel.z || point->position.z > maxCellPos.z + maxCellPosRel.z) {
			arrayDestroy(_fieldPoints, i);
			--i;
			--count;
		}
		pthread_mutex_unlock(&_fieldPointsMutex);
	}

	// compute points
	int x, y, z;
	for (x = (int) (minCellPos.x / cellStep) * cellStep; x <= maxCellPos.x; x += cellStep) {
		for (y = (int) (minCellPos.y / cellStep) * cellStep; y <= maxCellPos.y; y += cellStep) {
			for (z = (int) (minCellPos.z / cellStep) * cellStep; z <= maxCellPos.z; z += cellStep) {
				const Vector position = { x, y, z };

				// try to find
				int pointExists = 0;
				for (i = 0, count = arrayGetLength(_fieldPoints); i < count; ++i) {
					pthread_mutex_lock(&_fieldPointsMutex);
					VectorFieldPoint* point = (VectorFieldPoint*) arrayGetAt(_fieldPoints, i);
					if (point->position.x >= x && point->position.x <= x + cellStep &&
						point->position.y >= y && point->position.y <= y + cellStep &&
						point->position.z >= z && point->position.z <= z + cellStep) {
						pointExists = 1;
						pthread_mutex_unlock(&_fieldPointsMutex);
						break;
					}
					pthread_mutex_unlock(&_fieldPointsMutex);
				}
				if (pointExists) {
					continue;
				}

				// compute if not exist
				VectorFieldPoint* result = (VectorFieldPoint*) malloc(sizeof(VectorFieldPoint));
				result->position = position;
				result->direction = vectorZero;
				for (i = 0, count = arrayGetLength(_conductors); i < count; ++i) {
					Conductor* conductor = (Conductor*) arrayGetAt(_conductors, i);
					result->direction = vectorSum(
						result->direction,
						calculateMagneticFieldPoint(conductor->I, conductor->permeability, conductor->l, vectorSubstract(position, conductor->position))
					);
				}
				pthread_mutex_lock(&_fieldPointsMutex);
				arrayAppend(_fieldPoints, result);
				pthread_mutex_unlock(&_fieldPointsMutex);
			}
		}
	}
}

void renderMagneticField(const RenderContext* context) {
	size_t i, count;
	pthread_mutex_lock(&_fieldPointsMutex);
	for (i = 0, count = arrayGetLength(_fieldPoints); i < count; ++i) {
		VectorFieldPoint* point = (VectorFieldPoint*) arrayGetAt(_fieldPoints, i);
		drawVector(point->position, point->direction, colorWhite, colorRed);
	}
	pthread_mutex_unlock(&_fieldPointsMutex);
	for (i = 0, count = arrayGetLength(_conductors); i < count; ++i) {
		Conductor* conductor = (Conductor*) arrayGetAt(_conductors, i);
		renderParallelepiped(conductor->position, vectorSum(conductor->position, conductor->l), colorBlue);
	}
}
