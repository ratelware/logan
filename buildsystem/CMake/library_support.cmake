FUNCTION(ADD_DEPENDENCY_TO_BOOST VERSION REQUIRED_LIBRARIES)
    IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        SET_CLANG_BOOST_COMPILER_FLAGS() #because FindBoost sucks at finding boost compiled with versioned layout by Clang
    ENDIF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	
	#We might get a string - need list here
	STRING(REPLACE " " ";" LIBRARIES ${REQUIRED_LIBRARIES})

    SET(Boost_USE_MULTITHREADED ON)
    SET(Boost_USE_STATIC_LIBS ON)
    SET(Boost_USE_STATIC_RUNTIME OFF)
	
    FIND_PACKAGE(Boost ${VERSION} REQUIRED COMPONENTS ${LIBRARIES})
    IF(NOT ("${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}" STREQUAL ${VERSION}))
        MESSAGE(WARNING "Using Boost ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION} - application is not tested with ${VERSION}, so keep cautious!")
    ENDIF(NOT ("${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}" STREQUAL ${VERSION}))

    MESSAGE(STATUS "Using Boost version: ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}")
    MESSAGE(STATUS "Using Boost libraries: ${Boost_LIBRARIES}")
    MESSAGE(STATUS "Using Boost libraries from: ${Boost_LIBRARY_DIRS}")
    MESSAGE(STATUS "Using Boost headers from: ${Boost_INCLUDE_DIRS}")
	
	SET(Boost_LIBRARIES ${Boost_LIBRARIES} PARENT_SCOPE)
	SET(Boost_LIBRARY_DIRS ${Boost_LIBRARY_DIRS} PARENT_SCOPE)
	SET(Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS} PARENT_SCOPE)

    SET(EXTERNAL_LIBRARIES "${EXTERNAL_LIBRARIES};${Boost_LIBRARIES}" PARENT_SCOPE)

	LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDFUNCTION(ADD_DEPENDENCY_TO_BOOST VERSION LIBRARIES)

FUNCTION(ADD_DEPENDENCY_TO_OPEN_CV)
    FIND_PACKAGE(OpenCV REQUIRED COMPONENTS core imgproc highgui)
    
	MESSAGE(STATUS "Using OpenCV version: ${OpenCV_VERSION}")
    MESSAGE(STATUS "Using OpenCV libraries: ${OpenCV_LIBS}")
    MESSAGE(STATUS "Using OpenCV libraries from: ${OpenCV_LIB_DIR}")
    MESSAGE(STATUS "Using OpenCV headers from: ${OpenCV_INCLUDE_DIRS}")
	
	SET(OpenCV_LIBS ${OpenCV_LIBS} PARENT_SCOPE)
	SET(OpenCV_LIB_DIR ${OpenCV_LIB_DIR} PARENT_SCOPE)
	SET(OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS} PARENT_SCOPE)
	
    SET(EXTERNAL_LIBRARIES "${EXTERNAL_LIBRARIES};${OpenCV_LIBS}" PARENT_SCOPE)

	LINK_DIRECTORIES(${OpenCV_LIB_DIR})
ENDFUNCTION(ADD_DEPENDENCY_TO_OPEN_CV)
