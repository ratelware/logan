local function configure(global, production_targets)
  local targets = {}
  project "executor"
  kind global.library_type
  language "C++"
  files {"src/**.cpp"}
  
  includedirs {production_targets.includes}
end

return cofigure