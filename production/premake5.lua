local function configure(global)
  local targets = {}
  targets = {}
  targets.includes = {os.realpath("include")}
  targets.subsystems = require("subsystems/premake5")(global, targets)
  return targets
end
  
return configure