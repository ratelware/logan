include "buildsystem/Premake/utilities"

solution "MainProject"
configurations {"Debug", "Release"}
location "build_premake"

global = {}
global.library_type = "StaticLib"

global.target = {}
global.target.libdir = _SCRIPT_DIR .. "/bin/%{cfg.buildcfg}/lib/"
global.target.exedir = _SCRIPT_DIR .. "/bin/%{cfg.buildcfg}/exe/"


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