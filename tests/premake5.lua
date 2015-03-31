tests.includes = {os.realpath(".")}

library "TestHelpers"
  files {"helpers/**.cpp"}
  includedirs(tests.includes)
  
library "TestDoubles"
  files {"doubles/**.cpp"}
  includedirs(tests.includes)

include "libs"

include "testcases"

include "benchmarks"

