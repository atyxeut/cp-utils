# Copyright (C) 2026 atyxeut
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import re
import subprocess
from pathlib import Path

# > python3 pp.py
# expand all #include <***.hpp> directives in sol.cpp, output the result into sub.cpp
parser = argparse.ArgumentParser(add_help=False)
# > python3 pp.py -t
# select the target compiler, -t gcc or -t msvc, defaults to gcc
# -t msvc when you want to debug your program in Visual Studio (only support template/sol.cpp)
parser.add_argument("-t", "--target", default="gcc", choices=["gcc", "msvc"])
# > python3 pp.py -m
# add `#define IS_ONE_INPUT_MULTIPLE_TESTS 1` at the beginning of sub.cpp
# see template/sol.cpp for the usage of this macro
parser.add_argument("-m", "--multiple", action="store_true")
# > python3 pp.py -r
# add `#define NDEBUG` at the beginning of sub.cpp
# used to disable C-style asserts (https://en.cppreference.com/w/cpp/error/assert.html), meanwhile also enable
# `#define IS_IN_DEBUG_MODE 0` from <macro/is_in_debug_mode.hpp>
parser.add_argument("-r", "--release", action="store_true")
argv = parser.parse_args()


sol_cpp_path = Path("sol.cpp")
sub_cpp_path = Path("sub.cpp")

custom_header_include_path = Path("include").resolve()
header_match_pattern = re.compile(r"^#include\s*<(.+)>\s*\n")  # match `#include <xxx>`

headers_to_ignore = ["bits/stdc++.h"]
lines_to_ignore = ["#pragma once", "using namespace std;"]


def expand(cur_file_path: Path):
  with cur_file_path.open() as src_file:
    code = src_file.readlines()

  if len(code) == 0:
    return ""

  for i in range(len(code)):
    if code[i].rstrip() in lines_to_ignore:
      code[i] = ""
      continue

    # avoid duplicate `#include <xxx>`
    header_match = header_match_pattern.match(code[i])
    if header_match:
      header_name = header_match.group(1)
      if header_name in headers_to_ignore:
        code[i] = ""
      else:
        if not header_name.endswith(".hpp"):
          # standard headers
          if argv.target == "gcc":
            # only include <bits/stdc++.h> to reduce code size
            code[i] = ""
          else:
            headers_to_ignore.append(header_name)
        else:
          headers_to_ignore.append(header_name)
          custom_header_path = custom_header_include_path / header_name
          code[i] = expand(custom_header_path)

  return ("".join(code) + ("" if cur_file_path == sol_cpp_path.resolve() else "\n")).lstrip()


chunks_to_ignore = [("assert(", ";")]


def remove_unecessary_chunks(code: str):
  code = bytearray(code, "utf-8")

  for chunk in chunks_to_ignore:
    begin = bytes(chunk[0], "utf-8")
    end = bytes(chunk[1], "utf-8")
    i = code.find(begin, 0)
    while i != -1:
      while code[i] != end:
        code[i] = ord(" ")
        i += 1
      i = code.find(begin, i + 1)

  return code.decode("utf-8")


def remove_unecessary_white_characters(code: list):
  char_set = ";,:?.{}[]()<>=!&|^+-*/%"

  for i in range(len(code)):
    if code[i] == "\n":
      code[i] = ""
    elif code[i] in char_set:
      if i - 1 >= 0 and code[i - 1] == " ":
        code[i - 1] = ""
      if i + 1 < len(code) and code[i + 1] == " ":
        code[i + 1] = ""

  return "".join(code) + "\n\n"


def main():
  expanded_code = expand(sol_cpp_path.resolve())

  if argv.target == "gcc":

    def get_main_fn_end():
      left_brace_cnt = 1
      pos = expanded_code.find("{", expanded_code.find("int main()")) + 1
      while left_brace_cnt != 0:
        if expanded_code[pos] == "{":
          left_brace_cnt += 1
        elif expanded_code[pos] == "}":
          left_brace_cnt -= 1
        pos += 1
      return pos

    main_fn_end_pos = get_main_fn_end()
    upper = remove_unecessary_chunks(expanded_code[:main_fn_end_pos])

    macro_defs = ""
    if argv.multiple:
      macro_defs += "#define IS_ONE_INPUT_MULTIPLE_TESTS 1\n"
    if argv.release:
      macro_defs += "#define NDEBUG\n"

    upper_code_before_pp_path = Path("build/upper_code_before_pp.cpp")
    upper_code_before_pp_path.write_text(macro_defs + upper)
    subprocess.run(["g++", "-E", "-P", "-o", sub_cpp_path, upper_code_before_pp_path])
    subprocess.run(["clang-format", "-style=file:preprocessor/.clang-format-pp", "-i", sub_cpp_path])
    upper = remove_unecessary_white_characters(list(sub_cpp_path.read_text()))

    beginning = "#include <bits/stdc++.h>\n\n" + "using namespace std;\n\n"
    lib_description = "// library from: https://github.com/atyxeut/cp-utils\n"
    expanded_code = beginning + lib_description + upper + expanded_code[main_fn_end_pos:].lstrip()

  sub_cpp_path.write_text(expanded_code)


if __name__ == "__main__":
  main()
