library_metatable = {}
library_metatable.__index = library_metatable
library_metatable.libnames = function(self) 
  names = {}
  for _,lib in pairs(self.libraries) do
    table.insert(names, lib.libname)
  end
  return table.concat(names)
end

lib = {}
function lib.new(data)
  t = data or {}
  setmetatable(t, library_metatable)
  return t 
end

libs.boost = lib.new({
  includes = "E:/Boost/boost_1_55_0",
  libdir = "E:/Boost/boost_1_55_0/stage/lib",
  libraries = {
    program_options = {
      libname = "libboost_program_options-vc120-mt-gd-1_55.lib"
    },
    unit_test_framework = {
      libname = "libboost_unit_test_framework-vc120-mt-gd-1_55.lib"
    }
  }
})
