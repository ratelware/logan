cmake_minimum_required(VERSION 3.5)

project(logan LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt6 COMPONENTS Widgets LinguistTools Core Xml REQUIRED)
find_package(LibXml2 REQUIRED)

set(TRANSLATIONS_TS translations/logan_en_US.ts)

file(GLOB SOURCES_CPP ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADERS_H ${PROJECT_SOURCE_DIR}/src/*.h)
file(GLOB DESIGNS_UI ${PROJECT_SOURCE_DIR}/src/*.ui)

include_directories(src)
include_directories(libs/libarchive/libarchive)
include_directories(libs/libssh2/include)
include_directories(${LIBXML2_INCLUDE_DIR})

qt6_add_resources(RESOURCES_QRC resources/resources.qrc)

if(ANDROID)
  add_library(logan SHARED
    ${SOURCES_CPP}
    ${HEADERS_H}
    ${DESIGNS_UI}
    ${TRANSLATIONS_TS}
    ${RESOURCES_QRC}
  )
elseif(WIN32)
  add_executable(logan WIN32
      ${SOURCES_CPP}
      ${HEADERS_H}
      ${DESIGNS_UI}
      ${TRANSLATIONS_TS}
      ${RESOURCES_QRC}
    )
else()
    add_executable(logan
        ${SOURCES_CPP}
        ${HEADERS_H}
        ${DESIGNS_UI}
        ${TRANSLATIONS_TS}
        ${RESOURCES_QRC}
    )
endif()

add_subdirectory(libs/libarchive)
add_subdirectory(libs/libssh2)

target_link_libraries(logan PRIVATE Qt::Widgets Qt::Xml Qt::Core archive_static libssh2 ${LIBXML2_LIBRARIES})

qt6_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

