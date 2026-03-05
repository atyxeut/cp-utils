-- Copyright (C) 2026 atyxeut
--
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program.  If not, see <https://www.gnu.org/licenses/>.

set_config("builddir", "build")

set_languages("cxx23") -- the project only requires C++11, change it if you want
add_includedirs("include")

set_toolchains("gcc")

if is_host("windows") then
  set_config("plat", "mingw")
elseif is_host("macosx") then
  -- gcc-14 from Homebrew
  local gcc_path = "/usr/local/opt/gcc@14/bin/g++-14" --`usr` is the username
  -- `--query-driver=/usr/local/opt/gcc@14/bin/g++-14` must be added to clangd's arguments to make it work
  set_toolset("cxx", gcc_path)
  set_toolset("ld", gcc_path)
end

target("build-test")
  set_default(false)
  set_kind("binary")
  add_files("template/sol_simple.cpp")
target_end()

target("sol")
  set_kind("binary")
  add_files("sol.cpp")
  set_optimize("faster")
target_end()

target("sol-debug")
  set_default(false)
  set_kind("binary")
  add_files("sol.cpp")
  set_optimize("none")
  set_symbols("debug")
  add_defines("IS_LOCAL_DEBUGGING") -- effectively #define IS_LOCAL_DEBUGGING 1 at the beginning
target_end()

target("std")
  set_default(false)
  set_kind("binary")
  add_files("std.cpp")
  set_optimize("faster")
target_end()

target("gen")
  set_default(false)
  set_kind("binary")
  add_files("gen.cpp")
  set_optimize("faster")
target_end()
