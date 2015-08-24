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

#include "test/math/Vector.h"

#include <math.h>

#include "test/math/MathFunctions.h"

const Vector vectorZero = { 0, 0, 0 };
const Vector vectorOne = { 1, 1, 1 };

Vector vectorCreate(double x, double y, double z) {
	Vector result = { x, y, z };
	return result;
}

double vectorGetLengthSq(Vector a) {
	return a.x * a.x + a.y * a.y + a.z * a.z;
}

double vectorGetLength(Vector a) {
	return sqrt(vectorGetLengthSq(a));
}

int vectorIsEqual(Vector a, Vector b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

Vector vectorGetOpposite(Vector a) {
	Vector result = { -a.x, -a.y, -a.z };
	return result;
}

Vector vectorSum(Vector a, Vector b) {
	Vector result = { a.x + b.x, a.y + b.y, a.z + b.z };
	return result;
}

Vector vectorSubstract(Vector a, Vector b) {
	Vector result = { a.x - b.x, a.y - b.y, a.z - b.z };
	return result;
}

Vector vectorMultiply(Vector a, double b) {
	Vector result = { a.x * b, a.y * b, a.z * b };
	return result;
}

Vector vectorDivide(Vector a, double b) {
	Vector result = { a.x / b, a.y / b, a.z / b };
	return result;
}

double vectorDotProduct(Vector a, Vector b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector vectorCrossProduct(Vector a, Vector b) {
	Vector result = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
	return result;
}

Vector vectorNormalize(Vector a) {
	return vectorDivide(a, vectorGetLength(a));
}

Vector vectorGetRotation(Vector a) {
	Vector normalizedA = vectorNormalize(a);
	Vector result = {
		normalizedA.z > 0 ? asin(normalizedA.y) : sign(normalizedA.y) * M_PI - asin(normalizedA.y),
		normalizedA.x > 0 ? asin(normalizedA.z) : sign(normalizedA.z) * M_PI - asin(normalizedA.z),
		normalizedA.x < 0 ? asin(normalizedA.y) : sign(normalizedA.y) * M_PI - asin(normalizedA.y)
	};
	return result;
}

Vector vectorFromRotation(Vector r, double length) {
	Vector result = {
		cos(r.y) * length,
		sin(r.x) * length,
		sin(r.y) * length
	};
	return result;
}

Vector vectorRotate(Vector a, Vector rotation) {
	return vectorFromRotation(vectorSum(vectorGetRotation(a), rotation), vectorGetLength(a));
}

Vector vectorLerp(Vector from, Vector to, double time) {
	Vector result = {
			lerp(from.x, to.x, time),
			lerp(from.x, to.y, time),
			lerp(from.x, to.z, time)
	};
	return result;
}