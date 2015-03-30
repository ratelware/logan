include "buildsystem/Premake/utilities"

solution "MainProject"
configurations {"Debug", "Release"}
location "build_premake"

global = {}
global.library_type = "StaticLib"

libs = {}
include "buildsystem/Premake/libraries"

production = {}
include "production"

tests = {}
include "tests"

executable("exec")
  files {"executable/*.cpp"}
  dependson {"executor"}
  libdirs {libs.boost.libdir}
  links {"executor", libs.boost:libnames()}

includedirs {production.includes}