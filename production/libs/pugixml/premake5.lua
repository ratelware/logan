libs.pugixml = lib.new({
  includes = {os.realpath("turtle")}
})

library "pugixml"
  files{"pugixml/src/**.cpp"}
  includedirs{libs.pugixml.includes}