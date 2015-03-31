tests.libs.celero = lib.new({
    includes = {os.realpath("Celero/include")}
})

library "Celero"
  files{"Celero/src/**.cpp"}
  includedirs{tests.libs.celero.includes}
  defines {"CELERO_STATIC", "WIN32"}