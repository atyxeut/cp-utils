-- SPDX-FileCopyrightText: 2026 atyxeut <atyxeut@outlook.com>
-- SPDX-License-Identifier: GPL-3.0-or-later

set_config("builddir", "build")

set_languages("cxx23") -- the project only requires C++11, change it if you want
add_includedirs("include")

set_toolchains("gcc")

if is_host("windows") then
  set_config("plat", "mingw")
  add_syslinks("stdc++exp")
elseif is_host("macosx") then
  -- gcc-14 from Homebrew
  local gcc_path = "/usr/local/opt/gcc@14/bin/g++-14" --`usr` is the username
  -- `--query-driver=/usr/local/opt/gcc@14/bin/g++-14` must be added to clangd's arguments to make it work
  set_toolset("cxx", gcc_path)
  set_toolset("ld", gcc_path)
end

target("init")
  set_default(false)
  set_kind("binary")
  add_files("template/simple_sol.cpp")
target_end()

target("sol")
  set_kind("binary")
  add_files("sol.cpp")
  set_optimize("faster")
target_end()

target("sol.debug")
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
