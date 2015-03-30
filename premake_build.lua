
solution "MainProject"
configurations {"Debug", "Release"}
location "build_premake"

global = require("buildsystem/Premake/libraries")

global.library_type = "StaticLib"

production = require("production/premake5")(global)
--tests = require("tests/premake5")(production, global)

project "executable"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  files {"executable/*.cpp"}
  dependson {"executor"}

includedirs {production.includes}