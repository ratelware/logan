QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bookmark.cpp \
    bookmarkslist.cpp \
    configuration_manager.cpp \
    doc_supervisor.cpp \
    emphasis_color_manager.cpp \
    grepwindow.cpp \
    linenumberarea.cpp \
    logfile_handler.cpp \
    logfile_manager.cpp \
    logsdisplay.cpp \
    main.cpp \
    logan.cpp \
    rootlogfiledisplay.cpp \
    searchwindow.cpp \
    singlelogdisplay.cpp

HEADERS += \
    bookmark.h \
    bookmark_structure.h \
    bookmarkslist.h \
    configuration_manager.h \
    constants.h \
    doc_supervisor.h \
    emphasis_color_manager.h \
    grep_structure.h \
    grepwindow.h \
    line_descriptor.h \
    linenumberarea.h \
    logan.h \
    logfile_handler.h \
    logfile_manager.h \
    logsdisplay.h \
    rootlogfiledisplay.h \
    search_structure.h \
    searchwindow.h \
    singlelogdisplay.h

FORMS += \
    bookmarkslist.ui \
    grepwindow.ui \
    linenumberarea.ui \
    logan.ui \
    logsdisplay.ui \
    rootlogfiledisplay.ui \
    searchwindow.ui \
    singlelogdisplay.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    example-empty-logfile
