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

typedef struct Vector {
	double x;
	double y;
	double z;
} Vector;

extern const Vector vectorZero;
extern const Vector vectorOne;

Vector vectorCreate(double x, double y, double z);
double vectorGetLengthSq(Vector a);
double vectorGetLength(Vector a);
int vectorIsEqual(Vector a, Vector b);
Vector vectorGetOpposite(Vector a);
Vector vectorSum(Vector a, Vector b);
Vector vectorSubstract(Vector a, Vector b);
Vector vectorMultiply(Vector a, double b);
Vector vectorDivide(Vector a, double b);
double vectorDotProduct(Vector a, Vector b);
Vector vectorCrossProduct(Vector a, Vector b);
Vector vectorNormalize(Vector a);
double vectorGetAngle(Vector a);
Vector vectorGetRotation(Vector a);
Vector vectorFromRotation(Vector r, double length);
Vector vectorRotate(Vector a, Vector rotation);
Vector vectorLerp(Vector from, Vector to, double time);

#endif //TEST_VECTOR_H
