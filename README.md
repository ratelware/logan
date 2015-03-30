
ProjectTemplate
================
================
**Overview**
================

A template for starting with new C++ applications.

Some example libraries are included to make your life easier and understanding of "what happens where" simpler.
These libraries are listed below.

=================
**Installation**
=================

Just clone the repository (or even download and unpack)and template is ready.

=================
**Usage**
=================

Template uses CMake 

=================
**Dependencies**
=================

Template in first version requires boost for parsing command line options and as testing framework. Right now it is not
prepared for boostless projects, but we may consider it if a need arises. If you're interested in such feature, please
contact development team.

=================
**Libraries**
=================

There are a few libraries included so that you might get see an example of how the system was supposed to work.
These include:

 * Turtle (master branch) as mocking library (only in tests)
 * Celero (master branch) as benchmarking library (only in tests)
 * ChaiScript (develop branch) as scripting language (in production code)
 * PugiXML (master branch) as, well, XML library (in production code)
 * spdlog (master branch) as logger (in production code)
 * sqlite (3.8.8.3 amalgamation) as database management library (in production code)

Some or all might be included as submodules, so make sure you fetch them all before compiling

There is also embedded support for some common C++ libraries:
 * Boost for general-purpose utilities
 * OpenCV for stuff related to image processing

=================
**Building**
=================

Project uses CMake (version 2.8 is minimal supported) as its buildsystem, so it should work everywhere where CMake is supported and all required libraries are available.
Simply invoke `cmake .` in the main directory or - in case of out-of-source (recommended) builds, invoke it from a different directory. Just like any other CMake invocation.

If you wish to use provided libraries on MSVS, make sure you have installed at least MSVS 2013 Update 4, as some stuff in ChaiScript library requires it.

Additionally, an experimental support for building with Premake5 is supported. Please note that this will most likely remain experimental, as Premake5 itself is in alpha phase.