project(game)


if (MSVC)
    # Warning level 4 and all warnings as errors.
    add_compile_options(/W4 /WX)
else ()
    # ignore a bunch of warnings on emscripten builds as dependency builds cause them
    if (EMSCRIPTEN)
        add_compile_options(-Wall)
    else()
        add_compile_options(-Wall -Wextra -pedantic -Werror)
    endif()
endif ()

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s USE_WEBGL2=1")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --shell-file ${CMAKE_SOURCE_DIR}/shell.html")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    if (IS_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/assets)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ${CMAKE_CURRENT_BINARY_DIR}/assets@assets/")
    endif ()
endif ()

# listing sources here is a bit laboursome -- maybe these should just be GLOBbed??
set(game_sources ${game_sources}
    "main.c" 
    "game.c" 
    "rendering/textures.c"
    "scenes/scene.c"
    "entities/entity.c"
    "entities/player.c"
)

add_executable(game ${game_sources})
target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(game raylib)


## At the end of the build, copy assets over to runtime directory structure..
## Set asset path according to build type
# Check if building with Emscripten
if (EMSCRIPTEN)
    set(ASSET_PATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")
else()
    set(ASSET_PATH "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/assets")
endif()

message("ASSET_PATH: ${ASSET_PATH}")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
            ${CMAKE_SOURCE_DIR}/assets
            ${ASSET_PATH}
        COMMENT "Copying assets to ${ASSET_PATH}"
)


message("--- BUILD COMPLETE ---")
