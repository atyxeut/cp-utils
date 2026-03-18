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
import shutil
import subprocess
from pathlib import Path

# > python3 init.py
#   create necessary folders and files for future use, if those folders and files already exist, then nothing happens
parser = argparse.ArgumentParser(add_help=False)
# > python3 init.py -t count
#                        ↑ can be empty, defaults to 0, setting a value < 0 is equivalent to setting 0
#                          can be floating-point numbers, e.g. 1e2
#   if count is 0, reset test/data folder to its initial state
#   if count > 0, create new xxx.in/xxx.out pairs to test/data folder
parser.add_argument("-t", "--test", metavar="count", nargs="?", const=0, type=float)
argv = parser.parse_args()


def remove(path: Path):
  if not path.exists():
    return

  if path.is_dir():
    shutil.rmtree(path)
  else:
    path.unlink()


sol_cpp_path = Path("sol.cpp")
sub_cpp_path = Path("sub.cpp")
std_cpp_path = Path("std.cpp")
gen_cpp_path = Path("gen.cpp")


def generate_cpp_files():
  if not sol_cpp_path.exists():
    sol_cpp_path.touch()
  if not sub_cpp_path.exists():
    sub_cpp_path.touch()
  if not std_cpp_path.exists():
    std_cpp_path.touch()
  if not gen_cpp_path.exists():
    gen_cpp_path.touch()


test_dir_path = Path("test")
test_data_dir_path = Path("test/data")


def generate_test_folder(cnt: int = 0):
  test_dir_path.mkdir(exist_ok=True)

  if cnt <= 0:
    remove(test_data_dir_path)
    remove(test_dir_path / "log.txt")

  test_data_dir_path.mkdir(exist_ok=True)
  (test_dir_path / "log.txt").touch(exist_ok=True)

  (test_data_dir_path / "debug.in").touch()
  (test_data_dir_path / "debug.out").touch()
  (test_data_dir_path / "debug.err").touch()

  (test_data_dir_path / "0.in").touch()
  (test_data_dir_path / "0.out").touch()
  (test_data_dir_path / "0.err").touch()

  def get_new_test_data_stem():
    number_stems = [int(path.stem) for path in test_data_dir_path.glob("*.in") if path.stem.isdigit()]
    if number_stems:
      absent = set(range(1, max(number_stems) + 2)) - set(number_stems)
      return str(min(absent))
    return "1"

  for _ in range(cnt):
    stem = get_new_test_data_stem()
    (test_data_dir_path / (stem + ".in")).touch()
    (test_data_dir_path / (stem + ".out")).touch()
    (test_data_dir_path / (stem + ".err")).touch()


def generate_build_folder():
  remove(Path(".cache"))
  remove(Path(".xmake"))
  remove(Path("build"))
  subprocess.run(["xmake", "f"])
  subprocess.run(["xmake", "project", "-k", "compile_commands", "--outputdir=build"], text=True, stdout=subprocess.PIPE)

  build_test_target_name = "build-test"
  build_info = subprocess.run(["xmake", "--rebuild", "-v", build_test_target_name], text=True, stdout=subprocess.PIPE).stdout.split("\n")

  for i in range(len(build_info)):
    if build_info[i].find("linking.") != -1:
      # see https://xmake.io/guide/basic-commands/build-targets.html#find-detailed-compilation-commands for the format of the log
      linking_command = build_info[i + 1].split(" ")
      for part in linking_command:
        pos = part.find(build_test_target_name)
        if pos != -1:
          target_exe_path_str = part[:pos]
          break
      break
  remove(Path(target_exe_path_str))

  last_slash_idx = target_exe_path_str.rfind("/")
  Path("build/exe_dir.txt").write_text(target_exe_path_str[: last_slash_idx if last_slash_idx != -1 else target_exe_path_str.rfind("\\")])


def main():
  if argv.test or argv.test == 0:
    generate_test_folder(int(argv.test))
  else:
    generate_cpp_files()
    if not test_data_dir_path.exists():
      generate_test_folder()

  generate_build_folder()


if __name__ == "__main__":
  main()
