project(game)


if (MSVC)
    # Warning level 4 and all warnings as errors.
    add_compile_options(/W4 /WX)
else ()
    # Lots of warnings and all warnings as errors.
    # TODO: Figure out how to allow all the warnings from raylib on emscripten builds, but fail on them in actual gamecode
    add_compile_options(-Wall)# -Wextra -pedantic -Werror)
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
)

add_executable(game ${game_sources})
target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(game raylib)

#set(game_assets)
#file(GLOB assets ${CMAKE_SOURCE_DIR}/assets/wip/*)
#list(APPEND game_assets ${assets})
#file(COPY ${game_assets} DESTINATION "assets/wip/")

## At the end of the build, copy assets over to runtime directory structure..
## Set asset path according to build type
# Check if building with Emscripten
if (EMSCRIPTEN)
    set(ASSET_PATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")
else()
    set(ASSET_PATH "${CMAKE_BINARY_DIR}/$<$<CONFIG:>:${Configuration}/>${PROJECT_NAME}/assets")
endif()

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_SOURCE_DIR}/assets
        ${ASSET_PATH}
        #
        # \/ the below asset target dir _should_ work on visual studio, or other environments. Not tested though.
        
)


message("--- BUILD COMPLETE ---")
