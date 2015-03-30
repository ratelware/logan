
solution "MainProject"
configurations {"Debug", "Release"}
location "build_premake"

global = {}
global.library_type = "StaticLib"

production = {}
include "production"

tests = {}
--tests = require("tests/premake5")(production, global)

project "executable"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  files {"executable/*.cpp"}
  dependson {"executor"}

includedirs {production.includes}