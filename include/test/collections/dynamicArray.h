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

struct DynamicArray {
	void** rawArray = NULL;
	size_t length = 0;
	size_t capacity = 0;
};

inline void arrayReInit(struct DynamicArray* array, size_t capacity) {
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

inline struct DynamicArray* arrayNew(size_t initialCapacity) {
	struct DynamicArray* result = (struct DynamicArray*) malloc(sizeof(struct DynamicArray));
	arrayReInit(initialCapacity);
	return result;
}

inline void arrayFree(struct DynamicArray* array) {
	if (!array) {
		return;
	}
	free(array->rawArray);
	free(array);
}

inline void arrayFreeWithContents(struct DynamicArray* array) {
	if (!array) {
		return;
	}
	void** pointer = array->rawArray;
	for (size_t i = 0, count = array->length; i < count; ++i) {
		free(*pointer++);
	}
	arrayFree(array);
}

inline size_t arrayGetLength(const struct DynamicArray* array) {
	return array->length;
}

inline size_t arrayGetCapacity(const struct DynamicArray* array) {
	return array->capacity;
}

inline void* arrayGetAt(const struct DynamicArray* array, size_t index) {
	if (!array || index >= array->length) {
		return NULL;
	}
	return *(array->rawArray + index);
}

inline int arrayContains(const struct DynamicArray* array, void* elem) {
	if (!array) {
		return 0;
	}
	void** pointer = array->rawArray;
	for (size_t i = 0, count = array->length; i < count; ++i) {
		if (*pointer++ == elem) {
			return 1;
		}
	}
	return 0;
}

inline void arrayMoveContents(struct DynamicArray* array, size_t start, size_t end, size_t direction) {
	size_t newStart = start + direction;
	size_t newEnd = end + direction;
	if (!array || start >= end || end > array->length || !direction || newStart >= newEnd || newEnd > array->capacity) {
		return;
	}
	for (
		size_t i = direction < 0 ? start : end, count = direction < 0 ? newEnd : newStart;
		direction < 0 ? i < count : i > count;
		i += direction < 0 ? 1 : -1)
	{
		*(array->rawArray + i + (direction < 0 ? -1 : 1)) = *(array->rawArray + i);
	}
}

inline void arrayResize(struct DynamicArray* array, size_t newCapacity) {
	if (!array || newCapacity < array->length) {
		return;
	}
	array->rawArray = (void**) realloc(array->rawArray, sizeof(void*) * newCapacity);
	array->capacity = newCapacity;
}

inline void arrayInsert(struct DynamicArray* array, void* elem, size_t index) {
	if (!array || index > array->length) {
		return;
	}
	if (array->length == array->capacity) {
		arrayResize(array, array->length * 1.3);
	}
	arrayMoveContents(array, index, array->length, 1);
	*(array->rawArray + index) = newElem;
	++array->length;
}

inline void arrayPrepend(struct DynamicArray* array, void* elem) {
	arrayInsert(array, elem, 0);
}

inline void arrayAppend(struct DynamicArray* array, void* elem) {
	arrayInsert(array, elem, array->length);
}

inline void arrayUpdate(struct DynamicArray* array, size_t index, void* newElem) {
	if (!array || index >= array->length) {
		return;
	}
	*(array->rawArray + index) = newElem;
}

inline void arrayRemoveSome(struct DynamicArray* array, size_t index, size_t count) {
	if (!array || index >= array->length) {
		return;
	}
	if (array->length == array->capacity / 2) {
		arrayResize(array, array->length * 1.3);
	}
	arrayMoveContents(array, index + 1, array->length, -count);
	array->length -= count;
}

inline void arrayRemove(struct DynamicArray* array, size_t index) {
	arrayRemoveSome(array, index, 1);
}

inline void arrayDestroySome(struct DynamicArray* array, size_t index, size_t count) {
	if (!array || index + count > array->length || index >= index + count) {
		return;
	}
	void** pointer = array->rawArray + index;
	for (size_t i = index; i < count; ++i) {
		free(*pointer++);
	}
	arrayRemoveSome(index, count);
}

inline void arrayDestroy(struct DynamicArray* array, size_t index) {
	arrayDestroySome(array, index, 1);
}

inline void arrayForEach(const struct DynamicArray* array, void (*func)(void* elem, size_t index)) {
	if (!array || !func) {
		return;
	}
	void** pointer = array->rawArray;
	for (size_t i = 0, count = array->length; i < count; ++i) {
		func(*pointer++, i);
	}
}

inline int arrayCheck(const struct DynamicArray* array, int (*func)(void* elem, size_t index)) {
	if (!array || !func) {
		return 0;
	}
	void** pointer = array->rawArray;
	for (size_t i = 0, count = array->length; i < count; ++i) {
		if (func(*pointer++, i)) {
			return 1;
		}
	}
	return 0;
}

inline struct DynamicArray* arrayFilter(const struct DynamicArray* array, int (*func)(void* elem, size_t index)) {
	if (!array || !func) {
		return arrayNew(0);
	}
	struct DynamicArray* result = arrayNew(array->length);
	void** pointer = array->rawArray;
	for (size_t i = 0, count = array->length; i < count; ++i) {
		if (func(*pointer++, i)) {
			arrayAppend(result, pointer);
		}
	}
	return result;
}

inline struct DynamicArray* arrayMap(const struct DynamicArray* array, void* (*func)(void* elem, size_t index)) {
	if (!array || !func) {
		return arrayNew(0);
	}
	struct DynamicArray* result = arrayNew(array->length);
	void** pointer = array->rawArray;
	for (size_t i = 0, count = array->length; i < count; ++i) {
		arrayAppend(result, func(*pointer++, i));
	}
	return result;
}

inline void* arrayFold(const struct DynamicArray* array, int leftToRight, void (*func)(void* firstElem, void* secondElem)) {
	if (!array || !func) {
		return NULL;
	}
	void** pointer = array->rawArray + (leftToRight ? 0 : array->length - 1);
	void* result = NULL;
	for (
		size_t i = leftToRight ? 0 : array->length - 1, count = leftToRight ? 1 : array->length - 1;
		leftToRight ? i < count : i > count;
		i += leftToRight ? 1 : -1)
	{
		func(*pointer, *pointer += leftToRight ? 1 : -1);
	}
	return result;
}

inline void* arrayReduce(const struct DynamicArray* array, void (*func)(void* elem, size_t index, void* accum)) {
	if (!array || !func) {
		return NULL;
	}
	void** pointer = array->rawArray;
	void* result = NULL;
	for (size_t i = 0, count = array->length; i < count; ++i) {
		func(*pointer++, i, result);
	}
	return result;
}

inline struct DynamicArray* arraySlice(const struct DynamicArray* array, size_t start, size_t end) {
	if (!array || start >= end) {
		return arrayNew(0);
	}
	struct DynamicArray* result = arrayNew(end - start);
	void** pointer = array->rawArray + start;
	for (size_t i = 0, count = end - start; i < count; ++i) {
		arrayAppend(result, *pointer++);
	}
	return result;
}

#endif //TEST_DYNAMICARRAY_H
