#!/usr/bin/env python3

import argparse
import os
import pathlib

script_path = pathlib.Path(__file__).parent.resolve()
script_path = str(script_path)


class FileWriter:

   def __init__(self, fileName):

      self._fileName = fileName
      self._file = None
      self._indent = 0

   def __enter__(self):

      if os.path.exists(self._fileName):
         print(f' !! File {self._fileName} already exists')
      else:
         self._file = open(self._fileName, 'w')
      return self

   def __exit__(self, *args):

      if not self._file:
         return

      print(f' * Created file {self._fileName}')
      self._file.close()

   def __call__(self, content=None):

      if not self._file:
         return

      if content:
         self._file.write(' ' * 3 * self._indent + content + '\n')
      else:
         self._file.write('\n')

   def indent(self, value=0):

      self._indent += value


def createComponent(name, useQt=True):

   path = script_path + '/' + name
   os.makedirs(path + '/src', exist_ok=True)

   os.chdir(path)
   print(f'Creating component {name} in {path}')

   macroName = name.upper()
   with FileWriter(f'{name}ExportDef.h') as line:

      line(f'#ifndef {name}ExportDefH')
      line(f'#define {name}ExportDefH')
      line()
      line('/*!')
      line(f'@defgroup {name} {name} component')
      line(f'@includedoc{{doc}} {name}/{name}.md')
      line('*/')
      line()
      line('// clang-format off')
      line('#if defined(__unix) || defined(__APPLE__) || defined(DOXYGEN)')
      line(f'   #define {macroName}_DECLSPEC')
      line('#else')
      line(f'   #ifdef EXTENSION_{macroName}')
      line(f'      #define {macroName}_DECLSPEC __declspec(dllexport)')
      line('   #else')
      line(f'      #define {macroName}_DECLSPEC __declspec(dllimport)')
      line('   #endif')
      line('#endif')
      line('// clang-format on')
      line()
      line(f'#endif // NOT {name}ExportDefH')
      line()

   with FileWriter(f'{name}Config.cmake') as line:

      line('include_directories(${CMAKE_CURRENT_LIST_DIR})')
      line('include(${CMAKE_CURRENT_LIST_DIR}/../CommonUse.cmake)')
      line()
      if useQt:
         line('find_package(Qt6 REQUIRED COMPONENTS Core)')
         line(f'link_libraries(Qt6::Core {name})')
      else:
         line(f'link_libraries({name})')
      line()

   with FileWriter(f'CMakeLists.txt') as line:

      line('cmake_minimum_required(VERSION 3.20)')
      line(f'project({name} LANGUAGES CXX)')
      line()
      line('include(../CommonBuild.cmake)')
      line()

      if useQt:
         line('find_package(Qt6 REQUIRED COMPONENTS Core)')
         line('set(CMAKE_AUTOMOC ON)')
         line()

      line('include_directories(${CMAKE_CURRENT_SOURCE_DIR})')
      line()
      line('file(GLOB HEADER_FILES')
      line('   ${CMAKE_CURRENT_SOURCE_DIR}/*.h')
      line('   ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp')
      line(')')
      line()
      line('file(GLOB SOURCE_FILES')
      line('   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h')
      line('   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp')
      line('   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp')
      line(')')
      line()

      if useQt:
         line('qt_add_library(${PROJECT_NAME} ${XX_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES})')
      else:
         line('add_library(${PROJECT_NAME} ${XX_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES})')
      line(f'add_compile_definitions(EXTENSION_{macroName})')

      if useQt:
         line()
         line('target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)')
      line()

   with FileWriter(f'{name}.md') as line:

      line(f'@brief {name} ')
      line()


def main():

   parser = argparse.ArgumentParser(description='create new cmake components.')
   parser.add_argument('names', metavar='NAMES', type=str, nargs='+', help='list of components to create')

   args = parser.parse_args()  # will quit here if help is called

   for name in args.names:
      name = name[0].upper() + name[1:]
      if not name.startswith('XX'):
          name = 'XX' + name
      createComponent(name)


if __name__ == "__main__":
   main()
