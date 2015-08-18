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

#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H

#include <math.h>

struct Vector {
	int x;
	int y;
	int z;
};

inline int calculateVectorLengthSq(const struct Vector* a) {
	return a->x * a->x + a->y * a->y + a->z * a->z;
}

inline int calculateVectorLength(const struct Vector* a) {
	return sqrt(calculateVectorLengthSq(a));
}

inline struct Vector sumVectors(const struct Vector* a, const struct Vector* b) {
	return { a->x + b->x, a->y + b->y, a->z + b->z };
}

inline struct Vector substractVectors(const struct Vector* a, const struct Vector* b) {
	return { a->x - b->x, a->y - b->y, a->z - b->z };
}

inline struct Vector multiplyVector(const struct Vector* a, int b) {
	return { a->x * b, a->y * b, a->z * b };
}

inline int dotProduct(const struct Vector* a, const struct Vector* b) {
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

inline struct Vector crossProduct(const struct Vector* a, const struct Vector* b) {
	return { a->y * b->z - a->z * b->y, a->z * b->x - a->x * b->z, a->x * b->y - a->y * b->x };
}

#endif //TEST_VECTOR_H
