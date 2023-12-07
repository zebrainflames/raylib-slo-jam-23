cmake_minimum_required(VERSION 3.24)

project(raylib-slo-jam)

set(CMAKE_C_STANDARD 23)

# Config options.
option(NO_MSAA "Disable MSAA" OFF)

include(FetchContent)

# Search for a raylib-config.cmake. Fetch it and build it if we can't find one.
find_package(raylib 5.0 QUIET)
if (NOT raylib_FOUND)

    # Option 1 - get raylib from the latest master build.
    #

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
            #            If master is broken for some reason then uncomment this.
            #            GIT_REPOSITORY ${CMAKE_SOURCE_DIR}/../3rdparty/raylib
            #            GIT_TAG rod2
    )

    # Option 2 - clone raylib into a parallel directory.
    #
    # Do the following (manual) step before running CMake.
    #
    #       git clone --depth=1 https://github.com/raysan5/raylib
    #
    #    FetchContent_Declare(
    #            raylib
    #            GIT_REPOSITORY ${CMAKE_SOURCE_DIR}/..//raylib
    #            GIT_TAG master
    #    )

    FetchContent_GetProperties(raylib)

    # Download and build raylib.
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        # Don't build the raylib examples.
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

        # Build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif ()
endif ()

set(raylib_VERBOSE 1)

if (NO_MSAA)
    add_compile_definitions(NO_MSAA)
endif ()

add_subdirectory(game)
