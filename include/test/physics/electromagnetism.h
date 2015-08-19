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

#ifndef TEST_ELECTOMAGNETISM_H
#define TEST_ELECTOMAGNETISM_H

#include <math.h>

#include "test/math/vector.h"

#define ELECTRIC_PERMEABILITY 8.854187817 * 1.0e-12
#define MAGNETIC_PERMEABILITY 4 * PI * 1.0e-7
#define COULOMB_CONSTANT 1 / (4 * PI * ELECTRIC_PERMEABILITY)

inline struct Vector calculateLorenzForce(double q, const Vector* E, const Vector* v, const Vector* B) {
	return multiplyVector(sumVectors(E, crossProduct(v, B)), q);
}

inline struct Vector calculateCoulombForce(double q, const Vector* E) {
	return calculateLorenzForce(q, E, NULL, NULL);
}

inline struct Vector calculateElecticFieldPoint(double q, const Vector* r) {
	const double rLenSq = calculateVectorLengthSq(r);
	const double rLen = sqrt(rLenSq);
	return multiplyVector(r, COULOMB_CONSTANT * q / rLenSq / rLen);
}

inline struct Vector calculateMagneticFieldPoint(double I, const Vector* l, const Vector* r) {
	static const constant = MAGNETIC_PERMEABILITY / (4 * PI);
	const Vector r1 = substractVectors(r, l);
	const double r1LenSq = calculateVectorLengthSq(r1);
	const double r1Len = sqrt(r1LenSq);
	return multiplyVector(crossProduct(l, &r1), constant * I * / r1LenSq / r1Len);
}

#endif //TEST_ELECTOMAGNETISM_H
