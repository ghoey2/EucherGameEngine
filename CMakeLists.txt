cmake_minimum_required(VERSION 3.17)
project(final_project_ghoey2)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Warning flags
if (MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /MTd)
else ()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror)
endif ()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if (${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif ()

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.11.1
)

# Adds Catch2 testing library
FetchContent_GetProperties(catch2)
if (NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif ()



get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")


list(APPEND SOURCE_FILES ${CORE_SOURCE_FILES}
        src/core/card.cc
        src/players/computer_random_strategy.cc
        src/visualizer/eucher_app.cc
        src/core/game.cc
        src/players/player.cc
        src/core/deck.cc
        src/core/round.cc
        src/core/trick.cc
        src/core/euchre_exception.cc
        src/players/human_player.cc
        )

list(APPEND TEST_FILES
        test/deck_tests.cc
        test/card_tests.cc
        test/game_tests.cc
        test/trick_tests.cc)

ci_make_app(
        APP_NAME        euchre-app
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         apps/cinder_app_main.cc ${SOURCE_FILES}
        INCLUDES        include
)


ci_make_app(
        APP_NAME euchre-test
        CINDER_PATH ${CINDER_PATH}
        SOURCES test/test_main.cc ${SOURCE_FILES} ${TEST_FILES}
        INCLUDES include
        LIBRARIES catch2
)

if(MSVC)
    set_property(TARGET euchre-test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif()
