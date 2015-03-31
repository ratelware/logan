tests.libs.celero = {}
tests.libs.celero.includes = {os.realpath("Celero/include")}

setmetatable(tests.libs.celero, library_metatable)

library "Celero"
  files{"Celero/src/**.cpp"}
  includedirs{tests.libs.celero.includes}
  defines {"CELERO_STATIC", "WIN32"}