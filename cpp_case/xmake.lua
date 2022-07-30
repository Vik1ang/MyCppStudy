set_project("cpp_case")

set_languages("cxx17")

add_rules("mode.debug", "mode.release")

if is_mode("release") then
    set_optimize("fastest")
end

includes("**/xmake.lua")