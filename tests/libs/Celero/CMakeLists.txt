CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)

PROJECT(Celero)

MESSAGE(STATUS "Configuring Celero")
SET(CELERO_ENABLE_EXPERIMENTS OFF CACHE BOOL "Set to ON to automatically build all examples.")
SET(CELERO_ENABLE_TESTS OFF CACHE BOOL "Enable building and running unit tests.")

INCLUDE(FindCurses)
MESSAGE("Using curses from: ${CURSES_INCLUDE_DIRS} / ${CURSES_LIBRARIES}")
INCLUDE_DIRECTORIES(${CURSES_INCLUDE_DIRS} ${CURSES_INCLUDE_DIRS}/ncurses)

ADD_DEFINITIONS(-DCELERO_STATIC)
ADD_SUBDIRECTORY(Celero)

SET(CELERO_INCLUDE_DIR ${TEST_LIBRARIES_BASE_DIR}/Celero/Celero/include PARENT_SCOPE)
SET(CELERO_LIBRARIES celero PARENT_SCOPE)
SET(CELERO_EXTERNAL_LIBRARIES ${CURSES_LIBRARIES} celero PARENT_SCOPE)
