library_metatable = {}
library_metatable.__index = library_metatable
library_metatable.libnames = function(t) 
  names = {}
  for _,v in pairs(t.libraries) do
    table.insert(names, v.libname)
  end
  return table.concat(names)
end

libs.boost = {
  includes = "E:/Boost/boost_1_55_0",
  libdir = "E:/Boost/boost_1_55_0/stage/lib",
  libraries = {
    program_options = {
      libname = "libboost_program_options-vc120-mt-gd-1_55.lib"
    }
  }
}

setmetatable(libs.boost, library_metatable)