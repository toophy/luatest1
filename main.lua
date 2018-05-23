package.cpath = "C:\\Program Files (x86)\\Lua\\5.1\\clibs\\?.dll;" .. package.cpath
require("lfs")
package.path = lfs.currentdir() .. "\\;" .. "?/init.lua" .. package.path


require("mods.frame"):new():Run()



