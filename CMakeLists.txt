cmake_minimum_required(VERSION 3.11)

project(logan LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
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

find_package(Qt5 COMPONENTS Widgets LinguistTools Core REQUIRED)

set(TRANSLATIONS_TS translations/logan_en_US.ts)

file(GLOB SOURCES_CPP ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADERS_H ${PROJECT_SOURCE_DIR}/src/*.h)
file(GLOB DESIGNS_UI ${PROJECT_SOURCE_DIR}/src/*.ui)

include_directories(src)

if(ANDROID)
  add_library(logan SHARED
    ${SOURCES_CPP}
    ${HEADERS_H}
    ${DESIGNS_UI}
    ${TRANSLATIONS_TS}
  )
elseif(WIN32)
  add_executable(logan WIN32
      ${SOURCES_CPP}
      ${HEADERS_H}
      ${DESIGNS_UI}
      ${TRANSLATIONS_TS}
  )
else()
    add_executable(logan
        ${SOURCES_CPP}
        ${HEADERS_H}
        ${DESIGNS_UI}
        ${TRANSLATIONS_TS}
    )
endif()

target_link_libraries(logan PUBLIC Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
