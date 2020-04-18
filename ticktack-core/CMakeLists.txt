project(ticktack)

cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)
# define our library
add_library(ticktack_lib STATIC src/TickTackStore.cpp src/TickTackStore.h src/Counter.cpp src/Counter.h)


# SETUP GOOGLE TEST FRAMEWORK

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

if(result)
    message(ERROR "CMake step for googletest failed: ${result}")
else()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
        message(ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
            ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
            EXCLUDE_FROM_ALL)

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
        include_directories("${gtest_SOURCE_DIR}/include")
    endif()

    # Now simply link against gtest or gtest_main as needed. Eg
    add_executable(unittesting tests/TickTackStore_unittest.cpp tests/Counter_unittest.cpp)
    target_link_libraries(unittesting gtest_main ticktack_lib)
    add_test(NAME unittesting COMMAND unittesting)
endif()

