# BMSTU homeworks

## Description
This repository contains homework assignments completed in the C++ programming language 
using Google Test for testing. Each homework assignment is presented in a separate directory containing files with source code and tests.

## Directory Structure
This repository has the following structure for example:
```bash
bmstu-cpp-works/
├── dummy_vector/
│   ├── array_bundle.h       # Header file for simulating arrays
│   ├── vector_template.h    # Header file for simulating vectors
│   ├── vector_test.cpp      # File with tests for simulating vectors
│   └── CMakeLists.txt       # CMake file for building the project in the dummy_vector directory
├── dummy_string/
│   ├── string_bundle.h      # Header file for simulating strings
│   ├── string_template.h    # Header file for working with string templates
│   ├── string_test.cpp      # File with tests for simulating strings
│   └── CMakeLists.txt       # CMake file for building the project in the dummy_string directory
├── dummy_list/
│   ├── basic_list.h         # Header file for simulating linked lists
│   ├── list_testing.cpp     # File with tests for simulating linked lists
│   └── CMakeLists.txt       # CMake file for building the project in the dummy_list directory
├── ...                      # Other directories with homeworks
├── README.md                # Documentation and instructions for usage
└── CMakeLists.txt           # Main CMake file for setting up the project and building
...
```
## Build Project
- **Building the Project:** Use CMake to build the project. Ensure that CMake is installed on your system. If not, download and install it from https://cmake.org/download/ or if you use Linux, download package using terminal (Example for Fedora:``` 
sudo dnf install cmake```).
- **Installing Google Test Framework:** Install using ```git clone https://github.com/google/googletest.git``` and etc.
- **Testing the Code:** Run the tests to ensure the correctness of the implemented code. Use the following commands:
    ```bash
    mkdir build && cd build
    cmake ..
    cmake --build .
    ctest or ./name_of_project
    ```


## License
This project is licensed under the [MIT License](https://github.com/git/git-scm.com/blob/main/MIT-LICENSE.txt)
. 
