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

#include <test/math/Vector.h>

BOOST_AUTO_TEST_SUITE(tVector)

BOOST_AUTO_TEST_CASE(tvectorCalculateLengthSq) {
	Vector a = { 4, 4, 2 };
	BOOST_CHECK_EQUAL(vectorGetLengthSq(a), 36);
}

BOOST_AUTO_TEST_CASE(tvectorCalculateLength) {
	Vector a = { 4, 4, 2 };
	BOOST_CHECK_EQUAL(vectorGetLength(a), 6);
}

BOOST_AUTO_TEST_CASE(tvectorIsEqual) {
	Vector a = { 1, 2, 3 };
	Vector b = { 4, 5, 6 };
	BOOST_CHECK(!vectorIsEqual(a, b));
	BOOST_CHECK(vectorIsEqual(a, a));
}

BOOST_AUTO_TEST_CASE(tvectorGetOpposite) {
	Vector a = { 1, 2, 3 };
	Vector r = { -1, -2, -3 };
	BOOST_CHECK(vectorIsEqual(vectorGetOpposite(a), r));
}

BOOST_AUTO_TEST_CASE(tvectorSum) {
	Vector a = { 1, 2, 3 };
	Vector b = { 4, 5, 6 };
	Vector r = { 5, 7, 9 };
	BOOST_CHECK(vectorIsEqual(vectorSum(a, b), r));
}

BOOST_AUTO_TEST_CASE(tvectorSubstract) {
	Vector a = { 1, 2, 3 };
	Vector b = { 4, 5, 6 };
	Vector r = { -3, -3, -3 };
	BOOST_CHECK(vectorIsEqual(vectorSubstract(a, b), r));
}

BOOST_AUTO_TEST_CASE(tvectorMultiply) {
	Vector a = { 1, 2, 3 };
	Vector r = { 4, 8, 12 };
	BOOST_CHECK(vectorIsEqual(vectorMultiply(a, 4), r));
}

BOOST_AUTO_TEST_CASE(tvectorDivide) {
	Vector a = { 4, 8, 12 };
	Vector r = { 1, 2, 3 };
	BOOST_CHECK(vectorIsEqual(vectorDivide(a, 4), r));
}

BOOST_AUTO_TEST_CASE(tvectorDotProduct) {
	Vector a = { 1, 2, 3 };
	Vector b = { 4, 5, 6 };
	BOOST_CHECK_EQUAL(vectorDotProduct(a, b), 32);
}

BOOST_AUTO_TEST_CASE(tvectorCrossProduct) {
	Vector a = { 1, 2, 3 };
	Vector b = { 4, 5, 6 };
	Vector r = { -3, 6, -3 };
	BOOST_CHECK(vectorIsEqual(vectorCrossProduct(a, b), r));
}

BOOST_AUTO_TEST_CASE(tvectorNormalize) {
	Vector a = { 1, 2, 3 };
	BOOST_CHECK_EQUAL(vectorGetLength(vectorNormalize(a)), 1);
}

BOOST_AUTO_TEST_SUITE_END()
