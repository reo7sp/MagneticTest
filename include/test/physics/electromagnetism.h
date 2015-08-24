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

#include "test/math/Vector.h"

#define ELECTRIC_PERMEABILITY 8.854187817 * 1.0e-12
#define COULOMB_CONSTANT 1 / (4 * M_PI * ELECTRIC_PERMEABILITY)

struct Vector calculateLorenzForce(double q, Vector E, Vector v, Vector B);
struct Vector calculateCoulombForce(double q, Vector E);
struct Vector calculateElecticFieldPoint(double q, Vector r);
struct Vector calculateMagneticFieldPoint(double I, double permeability, Vector l, Vector r);

#endif //TEST_ELECTOMAGNETISM_H
