cmake_minimum_required(VERSION 2.8.4)
project(MagneticTest)

### options
option(ENABLE_TESTS "Set to ON to enable building of tests" ON)

### source
include_directories(include)
set(SRC_LIST
	src/collections/DynamicArray.c
	src/graphics/Color.c
	src/graphics/RenderEngine.c
	src/graphics/MagneticFieldRenderer.c
	src/math/Vector.c
	src/physics/electromagnetism.c
	src/tools/RenderTools.c
	src/tools/TimeTools.c
)

### libs
# pthread
find_package(Threads REQUIRED)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})

set(LIB_LIST
	${CMAKE_THREAD_LIBS_INIT}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLUT_LIBRARY}
	-lm
)

### result
add_library(_${PROJECT_NAME} STATIC ${SRC_LIST})
target_link_libraries(_${PROJECT_NAME} ${LIB_LIST})

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} _${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)

### tests
if (ENABLE_TESTS)
	enable_testing()

	### source
	set(TEST_SRC_LIST
		test/main.cpp
		test/math/MathFunctions.cpp
		test/math/Vector.cpp
	)

	### libs
	# boost
	find_package(Boost COMPONENTS unit_test_framework REQUIRED)
	include_directories(${Boost_INCLUDE_DIR})

	set(TEST_LIB_LIST
		${Boost_LIBRARIES}
	)

	### result
	include_directories(test)
	add_executable(${PROJECT_NAME}_test ${TEST_SRC_LIST})
	target_link_libraries(${PROJECT_NAME}_test _${PROJECT_NAME} ${TEST_LIB_LIST})
	add_test(${PROJECT_NAME}_test ${PROJECT_NAME}_test)
endif()
