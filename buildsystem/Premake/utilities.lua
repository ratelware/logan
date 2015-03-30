function library (name)
  project(name)
    kind(global.library_type)
    language "C++"
	targetdir(global.target.libdir)
end

function executable (name)
  project(name)
    kind "ConsoleApp"
    language "C++"
    targetdir (global.target.exedir)
end