CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)

PROJECT(TEST_LIBRARIES)

SET(TEST_LIBRARIES_BASE_DIR ${TEST_DIR}/libs)

ADD_SUBDIRECTORY(turtle)
SET(TURTLE_INCLUDE_DIR ${TURTLE_INCLUDE_DIR} PARENT_SCOPE)

ADD_SUBDIRECTORY(Celero)
SET(CELERO_INCLUDE_DIR ${CELERO_INCLUDE_DIR} PARENT_SCOPE)

SET(TEST_LIBRARIES "" PARENT_SCOPE)
SET(BENCHMARK_LIBRARIES ${CELERO_LIBRARIES} PARENT_SCOPE)
SET(BENCHMARK_EXTERNAL_LIBRARIES ${CELERO_EXTERNAL_LIBRARIES} PARENT_SCOPE)
