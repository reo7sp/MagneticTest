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

#include "test/tools/RenderTools.h"

#include <GL/glut.h>

void renderText(void* font, char* text, Vector position, Color color) {
	glColor3f(color.r, color.g, color.b);
	glRasterPos3d(position.x, position.y, position.z);
	char* c;
	for (c = text; *c != '\0'; ++c) {
		glutBitmapCharacter(font, *c);
	}
}

void renderCube(Vector center, Vector size, Color color) {
	double x1 = center.x - size.x / 2;
	double x2 = center.x + size.x / 2;
	double y1 = center.y - size.y / 2;
	double y2 = center.y + size.y / 2;
	double z1 = center.z - size.z / 2;
	double z2 = center.z + size.z / 2;
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_QUADS);
		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y2, z1);
		glVertex3d(x1, y2, z2);
		glVertex3d(x1, y1, z2);

		glVertex3d(x2, y1, z1);
		glVertex3d(x2, y2, z1);
		glVertex3d(x2, y2, z2);
		glVertex3d(x2, y1, z2);

		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y1, z2);
		glVertex3d(x2, y1, z2);
		glVertex3d(x2, y1, z1);

		glVertex3d(x1, y2, z1);
		glVertex3d(x1, y2, z2);
		glVertex3d(x2, y2, z2);
		glVertex3d(x2, y2, z1);

		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y2, z1);
		glVertex3d(x2, y2, z1);
		glVertex3d(x2, y1, z1);

		glVertex3d(x1, y1, z2);
		glVertex3d(x1, y2, z2);
		glVertex3d(x2, y2, z2);
		glVertex3d(x2, y1, z2);
	glEnd();
}

void renderParallelepiped(Vector from, Vector to, Color color) {
	double x1 = from.x;
	double x2 = to.x;
	double y1 = from.y;
	double y2 = to.y;
	double z1 = from.z;
	double z2 = to.z;
	if (x1 > x2) {
		double t = x1;
		x1 = x2;
		x2 = t;
	}
	if (y1 > y2) {
		double t = y1;
		y1 = y2;
		y2 = t;
	}
	if (z1 > z2) {
		double t = z1;
		z1 = z2;
		z2 = t;
	}
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_QUADS);
		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y2, z1);
		glVertex3d(x1, y2, z2);
		glVertex3d(x1, y1, z2);

		glVertex3d(x2, y1, z1);
		glVertex3d(x2, y2, z1);
		glVertex3d(x2, y2, z2);
		glVertex3d(x2, y1, z2);

		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y1, z2);
		glVertex3d(x2, y1, z2);
		glVertex3d(x2, y1, z1);

		glVertex3d(x1, y2, z1);
		glVertex3d(x1, y2, z2);
		glVertex3d(x2, y2, z2);
		glVertex3d(x2, y2, z1);

		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y2, z1);
		glVertex3d(x2, y2, z1);
		glVertex3d(x2, y1, z1);

		glVertex3d(x1, y1, z2);
		glVertex3d(x1, y2, z2);
		glVertex3d(x2, y2, z2);
		glVertex3d(x2, y1, z2);
	glEnd();
}

void renderCubeFrame(Vector center, Vector size, Color color) {
	double x1 = center.x - size.x / 2;
	double x2 = center.x + size.x / 2;
	double y1 = center.y - size.y / 2;
	double y2 = center.y + size.y / 2;
	double z1 = center.z - size.z / 2;
	double z2 = center.z + size.z / 2;
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINE_LOOP);
		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y2, z1);
		glVertex3d(x1, y2, z2);
		glVertex3d(x1, y1, z2);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(x2, y1, z1);
		glVertex3d(x2, y2, z1);
		glVertex3d(x2, y2, z2);
		glVertex3d(x2, y1, z2);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y1, z2);
		glVertex3d(x2, y1, z2);
		glVertex3d(x2, y1, z1);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(x1, y2, z1);
		glVertex3d(x1, y2, z2);
		glVertex3d(x2, y2, z2);
		glVertex3d(x2, y2, z1);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y2, z1);
		glVertex3d(x2, y2, z1);
		glVertex3d(x2, y1, z1);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(x1, y1, z2);
		glVertex3d(x1, y2, z2);
		glVertex3d(x2, y2, z2);
		glVertex3d(x2, y1, z2);
	glEnd();
}
