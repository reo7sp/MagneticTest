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

#include <test/math/functions.h>

BOOST_AUTO_TEST_SUITE(tFunctions)

BOOST_AUTO_TEST_CASE(min) {
	BOOST_CHECK_EQUAL(min(1, 2), 1);
}

BOOST_AUTO_TEST_CASE(max) {
	BOOST_CHECK_EQUAL(max(1, 2), 2);
}

BOOST_AUTO_TEST_CASE(clamp) {
	BOOST_CHECK_EQUAL(clamp(-0.5, 0, 1), 0);
	BOOST_CHECK_EQUAL(clamp(0.5, 0, 1), 0.5);
	BOOST_CHECK_EQUAL(clamp(1.5, 0, 1), 1);
}

BOOST_AUTO_TEST_CASE(sign2) {
	BOOST_CHECK_EQUAL(sign2(1, 2), -1);
	BOOST_CHECK_EQUAL(sign2(2, 2), 0);
	BOOST_CHECK_EQUAL(sign2(3, 2), 1);
}

BOOST_AUTO_TEST_CASE(sign) {
	BOOST_CHECK_EQUAL(sign(-4), -1);
	BOOST_CHECK_EQUAL(sign(0), 0);
	BOOST_CHECK_EQUAL(sign(4), 1);
}

BOOST_AUTO_TEST_SUITE_END()
