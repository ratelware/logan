local function configure(global, production_targets)
  local targets = {}
  targets.executor = require("executor/premake5")(global, production_targets)
end

return configure