project "executor"
kind(global.library_type)
language "C++"
files {"src/**.cpp"}
  
includedirs {production.includes, libs.boost.includes}
libdirs {libs.boost.libdir}
links {libs.boost.libraries.program_options.libname}