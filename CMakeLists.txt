cmake_minimum_required(VERSION 2.8.12)
project(cmake_example)

include_directories(src)
include_directories(/usr/include/python3.8)
include_directories(C/Program_Files/Git/mnt/c/Users/davidflanderka/.local/lib/python3.8/site-packages/pybind11/include)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fvisibility=hidden")


add_library(bih_tree SHARED src/bih.cc)
#add_library(python_test SHARED src/python_field_base.cc)


# targets for test executables
add_executable(test_bih_tree test/test_bih_tree.cc)
target_link_libraries(test_bih_tree bih_tree)

# targets for test executables
#add_executable(test_field_python test/test_field_python.cc)
#target_link_libraries(test_field_python 
#  /usr/lib/x86_64-linux-gnu/libpython3.8.so.1.0)

# targets for test executables
add_executable(example test/example.cpp)
target_link_libraries(example 
  /usr/lib/x86_64-linux-gnu/libpython3.8.so.1.0)
  