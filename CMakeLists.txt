cmake_minimum_required(VERSION 3.10)
project(coverage_playground)
enable_testing()

find_package(Boost)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "GCC detected")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 14.0)
        include(cmake/CodeCoverage_gcc14.cmake)
    else()
        include(cmake/CodeCoverage_gcc13.cmake)
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Clang detected")
    include(cmake/CodeCoverage_clang.cmake)
    set(ENV{LLVM_PROFILE_FILE} "%p.profraw")
endif()

add_executable(app1 app1.cpp)
append_coverage_compiler_flags_to_target(app1)
add_test(app1 app1)
set_property(TEST app1 PROPERTY ENVIRONMENT "LLVM_PROFILE_FILE=app1.profraw")
add_executable(app2 app2.cpp)
append_coverage_compiler_flags_to_target(app2)
add_test(app2 app2)
set_property(TEST app2 PROPERTY ENVIRONMENT "LLVM_PROFILE_FILE=app2.profraw")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    setup_target_for_coverage_gcovr_html(
        NAME coverage
        EXECUTABLE ctest
        DEPENDENCIES app1 app2
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    setup_target_for_coverage_clang_html(
        NAME coverage
        EXECUTABLE ctest
        DEPENDENCIES app1 app2
    )
endif()
