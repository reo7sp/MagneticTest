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

#ifndef TEST_DYNAMICARRAY_H
#define TEST_DYNAMICARRAY_H

#include <stddef.h>

typedef struct DynamicArray {
	void** rawArray;
	size_t length;
	size_t capacity;
} DynamicArray;

void arrayReInit(DynamicArray* array, size_t capacity);
DynamicArray* arrayNew(size_t initialCapacity);
void arrayFree(DynamicArray* array);
void arrayFreeWithContents(DynamicArray* array);
size_t arrayGetLength(const DynamicArray* array);
size_t arrayGetCapacity(const DynamicArray* array);
void* arrayGetAt(const DynamicArray* array, size_t index);
int arrayContains(const DynamicArray* array, void* elem);
void arrayMoveContents(DynamicArray* array, size_t start, size_t end, long direction);
void arrayResize(DynamicArray* array, size_t newCapacity);
void arrayInsert(DynamicArray* array, void* elem, size_t index);
void arrayPrepend(DynamicArray* array, void* elem);
void arrayAppend(DynamicArray* array, void* elem);
void arrayUpdate(DynamicArray* array, size_t index, void* newElem);
void arrayRemoveSome(DynamicArray* array, size_t index, size_t count);
void arrayRemove(DynamicArray* array, size_t index);
void arrayRemoveAll(DynamicArray* array);
void arrayDestroySome(DynamicArray* array, size_t index, size_t count);
void arrayDestroy(DynamicArray* array, size_t index);
void arrayDestroyAll(DynamicArray* array);

#endif //TEST_DYNAMICARRAY_H
