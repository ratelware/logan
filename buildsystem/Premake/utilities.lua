function library (name)
  project(name)
    kind(global.library_type)
    language "C++"
end

function executable (name)
  project(name)
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
end