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

#include "test/physics/electromagnetism.h"

Vector calculateLorenzForce(double q, Vector E, Vector v, Vector B) {
	return vectorMultiply(vectorSum(E, vectorCrossProduct(v, B)), q);
}

Vector calculateCoulombForce(double q, Vector E) {
	return vectorMultiply(E, q);
}

Vector calculateElecticFieldPoint(double q, Vector r) {
	const double rLenSq = vectorGetLengthSq(r);
	const double rLen = sqrt(rLenSq);
	return vectorMultiply(r, COULOMB_CONSTANT * q / rLenSq / rLen);
}

Vector calculateMagneticFieldPoint(double I, double permeability, Vector l, Vector r) {
	const double constant = permeability / (4 * M_PI);
	const Vector r1 = vectorSubstract(r, l);
	const double r1LenSq = vectorGetLengthSq(r1);
	const double r1Len = sqrt(r1LenSq);
	return vectorMultiply(vectorCrossProduct(l, r1), constant * I / r1LenSq / r1Len);
}
