
local library_type = "StaticLib"

solution "MainProject"
configurations {"Debug", "Release"}
location "build_premake"

project "executable"
kind "ConsoleApp"
language "C++"
targetdir "bin/%{cfg.buildcfg}"
files {"executable/*.cpp"}
