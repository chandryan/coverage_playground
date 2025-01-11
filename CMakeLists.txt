cmake_minimum_required(VERSION 3.10)
project(CppPlayground)

find_package(Boost)

if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 14.0)
    include(cmake/CodeCoverage_gcc14.cmake)
else()
    include(cmake/CodeCoverage_gcc13.cmake)
endif()

add_executable(CppPlayground main.cpp)
setup_target_for_coverage_gcovr_html(
    NAME coverage
    EXECUTABLE CppPlayground
    DEPENDENCIES CppPlayground
)
append_coverage_compiler_flags_to_target(CppPlayground)