# logan
This project is a log analyzer, for text logs.

The goal is to provide a simple GUI-based tool for going through logs, including deep-dives.

Current features include:

 - opening local files
 - opening remote files (connection through ssh)
 - bookmarks
 - coloring selected texts
 - trimming content
 - tab-based grepping
 - search

Roadmap includes:

 - grepping and bookmarking profiles
 - merging multiple log files into one (sequential)
 - merging mutliple log files into one (time-based)
 - checkpoints and autosave
 - streaming support
 - decreasing memory consumption
 - tagging lines + selectable filters


=================
**Dependencies**
=================

There are a few libraries included so that you might get see an example of how the system was supposed to work.
These include:

 * **libssh2** for handling SSH connections (in production code)
 * **libarchive** for compression (in production code)
 * **Qt6** for UI-related stuff
 * **libxml2** for XML schemas (in production code)

You need to install those libraries prior to building source code, otherwise you won't be able to build.

=================
**Notes**
=================
When using Qt, remember to set and `-DCMAKE_PREFIX_PATH` to Qt6 installation and
`Qt6_DIR` variable to where `Qt6Config.cmake` lies (usually `./[toolchain]/lib/cmake/Qt6` in Qt6 installation directory)

If you use CLion, take a look here: https://www.jetbrains.com/help/clion/qt-tutorial.html#qt-setup-in-clion (perhaps on VS and other
editors it'll help too).
Or just use QtCreator, it works pretty well with Qt stuff.

=================
**Building**
=================

Project uses CMake (version 2.8 is minimal supported) as its buildsystem, so it should work everywhere where CMake is supported and all required libraries are available.
Simply invoke `cmake .` in the main directory or - in case of out-of-source (recommended) builds, invoke it from a different directory. Just like any other CMake invocation.

If you wish to use provided libraries on MSVS, make sure you have installed at least MSVS 2013 Update 4, as some stuff in ChaiScript library requires it.
