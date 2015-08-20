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

#include <boost/test/unit_test.hpp>

#include <test/math/vector.h>

BOOST_AUTO_TEST_SUITE(tVector)

BOOST_AUTO_TEST_CASE(calculateVectorLengthSq) {
	BOOST_CHECK_EQUAL(calculateVectorLengthSq({ 4, 4, 2 }), 36);
}

BOOST_AUTO_TEST_CASE(calculateVectorLengthSq-null) {
	BOOST_CHECK_EQUAL(calculateVectorLengthSq(NULL), 0);
}

BOOST_AUTO_TEST_CASE(calculateVectorLength) {
	BOOST_CHECK_EQUAL(calculateVectorLength({ 4, 4, 2 }), 6);
}

BOOST_AUTO_TEST_CASE(calculateVectorLength-null) {
	BOOST_CHECK_EQUAL(calculateVectorLength(NULL), 0);
}

BOOST_AUTO_TEST_CASE(isVectorsEqual) {
	BOOST_CHECK_EQUAL(isVectorsEqual({ 1, 2, 3 }, { 4, 5, 6 }), 0);
	BOOST_CHECK_EQUAL(isVectorsEqual({ 1, 2, 3 }, { 1, 2, 3 }), 1);
}

BOOST_AUTO_TEST_CASE(isVectorsEqual-null) {
	const Vector a = { 1, 2, 3 };
	BOOST_CHECK_EQUAL(isVectorsEqual(NULL, a), 0);
	BOOST_CHECK_EQUAL(isVectorsEqual(a, NULL), 0);
	BOOST_CHECK_EQUAL(isVectorsEqual(NULL, NULL), 1);
}

BOOST_AUTO_TEST_CASE(getOpposite) {
	BOOST_CHECK_EQUAL(isVectorsEqual(getOpposite({ 1, 2, 3 }), { -1, -2, -3 }), 1);
}

BOOST_AUTO_TEST_CASE(getOpposite-null) {
	BOOST_CHECK_EQUAL(getOpposite(NULL), 0);
}

BOOST_AUTO_TEST_CASE(sumVectors) {
	BOOST_CHECK_EQUAL(isVectorsEqual(sumVectors({ 1, 2, 3 }, { 4, 5, 6 }), { 5, 7, 9 }), 1);
}

BOOST_AUTO_TEST_CASE(sumVectors-null) {
	const Vector a = { 1, 2, 3 };
	BOOST_CHECK_EQUAL(isVectorsEqual(sumVectors(NULL, a), a), 1);
	BOOST_CHECK_EQUAL(isVectorsEqual(sumVectors(a, NULL), a), 1);
	BOOST_CHECK_EQUAL(isVectorsEqual(sumVectors(NULL, NULL), { 0, 0, 0 }), 1);
}

BOOST_AUTO_TEST_CASE(substractVectors) {
	BOOST_CHECK_EQUAL(isVectorsEqual(substractVectors({ 1, 2, 3 }, { 4, 5, 6 }), { -3, -3, -3 }), 1);
}

BOOST_AUTO_TEST_CASE(substractVectors-null) {
	const Vector a = { 1, 2, 3 };
	BOOST_CHECK_EQUAL(isVectorsEqual(substractVectors(NULL, a), getOpposite(a)), 1);
	BOOST_CHECK_EQUAL(isVectorsEqual(substractVectors(a, NULL), a), 1);
	BOOST_CHECK_EQUAL(isVectorsEqual(substractVectors(NULL, NULL), { 0, 0, 0 }), 1);
}

BOOST_AUTO_TEST_CASE(multiplyVector) {
	BOOST_CHECK_EQUAL(isVectorsEqual(multiplyVector({ 1, 2, 3 }, 4), { 4, 8, 12 }), 1);
}

BOOST_AUTO_TEST_CASE(multiplyVector-null) {
	BOOST_CHECK_EQUAL(isVectorsEqual(multiplyVector(NULL, 4), { 0, 0, 0 }), 1);
}

BOOST_AUTO_TEST_CASE(divideVector) {
	BOOST_CHECK_EQUAL(isVectorsEqual(divideVector({ 4, 8, 12 }, 4), { 1, 2, 3 }), 1);
}

BOOST_AUTO_TEST_CASE(divideVector-null) {
	BOOST_CHECK_EQUAL(isVectorsEqual(divideVector(NULL, 4), { 0, 0, 0 }), 1);
}

BOOST_AUTO_TEST_CASE(dotProduct) {
	BOOST_CHECK_EQUAL(dotProduct({ 1, 2, 3 }, { 4, 5, 6 }), 32);
}

BOOST_AUTO_TEST_CASE(dotProduct-null) {
	const Vector a = { 1, 2, 3 };
	BOOST_CHECK_EQUAL(dotProduct(NULL, a), 0);
	BOOST_CHECK_EQUAL(dotProduct(a, NULL), 0);
	BOOST_CHECK_EQUAL(dotProduct(NULL, NULL), 0);
}

BOOST_AUTO_TEST_CASE(crossProduct) {
	BOOST_CHECK_EQUAL(isVectorsEqual(crossProduct({ 1, 2, 3 }, { 4, 5, 6 }), { -3, 6, -3 }), 1);
}

BOOST_AUTO_TEST_CASE(crossProduct-null) {
	const Vector a = { 1, 2, 3 };
	const Vector o = { 0, 0, 0 };
	BOOST_CHECK_EQUAL(isVectorsEqual(crossProduct(NULL, a), o), 1);
	BOOST_CHECK_EQUAL(isVectorsEqual(crossProduct(a, NULL), o), 1);
	BOOST_CHECK_EQUAL(isVectorsEqual(crossProduct(NULL, NULL), o), 1);
}

BOOST_AUTO_TEST_CASE(normalizeVector) {
	BOOST_CHECK_EQUAL(calculateVectorLengthSq(normalizeVector({ 1, 2, 3 })), 1);
}

BOOST_AUTO_TEST_CASE(normalizeVector-null) {
	BOOST_CHECK_EQUAL(isVectorsEqual(normalizeVector(NULL), { 0, 0, 0 }), 1);
}

BOOST_AUTO_TEST_SUITE_END()
