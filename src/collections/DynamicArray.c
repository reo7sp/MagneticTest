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

#include "test/collections/DynamicArray.h"

#include <stdlib.h>

void arrayReInit(DynamicArray* array, size_t capacity) {
	if (!array) {
		return;
	}
	if (array->rawArray) {
		free(array->rawArray);
	}
	array->rawArray = (void**) malloc(sizeof(void*) * capacity),
	array->length = 0;
	array->capacity = capacity;
}

DynamicArray* arrayNew(size_t initialCapacity) {
	DynamicArray* result = (DynamicArray*) malloc(sizeof(DynamicArray));
	result->rawArray = NULL;
	arrayReInit(result, initialCapacity);
	return result;
}

void arrayFree(DynamicArray* array) {
	if (!array) {
		return;
	}
	free(array->rawArray);
	free(array);
}

void arrayFreeWithContents(DynamicArray* array) {
	if (!array) {
		return;
	}
	void** pointer = array->rawArray;
	size_t i, count;
	for (i = 0, count = array->length; i < count; ++i) {
		free(*pointer++);
	}
	arrayFree(array);
}

size_t arrayGetLength(const DynamicArray* array) {
	if (!array) {
		return 0;
	}
	return array->length;
}

size_t arrayGetCapacity(const DynamicArray* array) {
	if (!array) {
		return 0;
	}
	return array->capacity;
}

void* arrayGetAt(const DynamicArray* array, size_t index) {
	if (!array || index >= array->length) {
		return NULL;
	}
	return *(array->rawArray + index);
}

int arrayContains(const DynamicArray* array, void* elem) {
	if (!array) {
		return 0;
	}
	void** pointer = array->rawArray;
	size_t i, count;
	for (i = 0, count = array->length; i < count; ++i) {
		if (*pointer++ == elem) {
			return 1;
		}
	}
	return 0;
}

void arrayMoveContents(DynamicArray* array, size_t start, size_t end, long direction) {
	size_t newStart = start + direction;
	size_t newEnd = end + direction;
	if (!array || start >= end || end > array->length || !direction || newStart >= newEnd || newEnd > array->capacity) {
		return;
	}
	size_t i, count;
	for (
		i = direction < 0 ? start : end, count = direction < 0 ? newEnd : newStart;
		direction < 0 ? i < count : i > count;
		i += direction < 0 ? 1 : -1)
	{
		*(array->rawArray + i + (direction < 0 ? -1 : 1)) = *(array->rawArray + i);
	}
}

void arrayResize(DynamicArray* array, size_t newCapacity) {
	if (!array || newCapacity < array->length || array->capacity == newCapacity) {
		return;
	}
	array->rawArray = (void**) realloc(array->rawArray, sizeof(void*) * newCapacity);
	array->capacity = newCapacity;
}

void arrayInsert(DynamicArray* array, void* elem, size_t index) {
	if (!array || index > array->length) {
		return;
	}
	if (array->length == array->capacity) {
		arrayResize(array, (size_t) (array->length * 1.3 + 1));
	}
	arrayMoveContents(array, index, array->length, 1);
	*(array->rawArray + index) = elem;
	++array->length;
}

void arrayPrepend(DynamicArray* array, void* elem) {
	arrayInsert(array, elem, 0);
}

void arrayAppend(DynamicArray* array, void* elem) {
	arrayInsert(array, elem, arrayGetLength(array));
}

void arrayUpdate(DynamicArray* array, size_t index, void* newElem) {
	if (!array || index >= array->length) {
		return;
	}
	*(array->rawArray + index) = newElem;
}

void arrayRemoveSome(DynamicArray* array, size_t index, size_t count) {
	if (!array || index + count > array->length) {
		return;
	}
	arrayMoveContents(array, index + 1, array->length, -count);
	array->length -= count;
	if (array->length < array->capacity / 2) {
		arrayResize(array, (size_t) (array->length * 0.7));
	}
}

void arrayRemove(DynamicArray* array, size_t index) {
	arrayRemoveSome(array, index, 1);
}

void arrayRemoveAll(DynamicArray* array) {
	arrayRemoveSome(array, 0, array->length);
}

void arrayDestroySome(DynamicArray* array, size_t index, size_t count) {
	if (!array || index + count > array->length || index >= index + count) {
		return;
	}
	size_t i;
	for (i = 0; i < count; ++i) {
		void* p = *(array->rawArray + index + i);
		free(p);
	}
	arrayRemoveSome(array, index, count);
}

void arrayDestroy(DynamicArray* array, size_t index) {
	arrayDestroySome(array, index, 1);
}

void arrayDestroyAll(DynamicArray* array) {
	arrayDestroySome(array, 0, array->length);
}
