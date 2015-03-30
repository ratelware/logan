project "executor"
kind(global.library_type)
language "C++"
files {"src/**.cpp"}
  
includedirs {production.includes}