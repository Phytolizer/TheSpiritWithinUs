cmake_minimum_required(VERSION 3.16...3.23)

project(
    "The Spirit Within Us"
    LANGUAGES C
    VERSION "0.1.0"
    DESCRIPTION "A text-based adventure"
    HOMEPAGE_URL "https://github.com/Phytolizer/TheSpiritWithinUs"
)

set(SRC
    attack.c
    clear.c
    damage.c
    end.c
    expand.c
    fire.c
    flashback.c
    fox.c
    health.c
    inventory.c
    inventory2.c
    location.c
    main.c
    manual.c
    match.c
    misc.c
    move.c
    noun.c
    onoff.c
    openclose.c
    parsexec.c
    reach.c
    toggle.c
    turn.c
)
list(TRANSFORM SRC PREPEND "src/")

find_program(AWK awk mawk gawk REQUIRED)
find_program(DOT dot REQUIRED)

add_custom_command(
    OUTPUT "${PROJECT_BINARY_DIR}/object.c"
    COMMAND
        "${AWK}" -f "${PROJECT_SOURCE_DIR}/src/object.awk" -v pass=c1
        "${PROJECT_SOURCE_DIR}/src/object.txt" >
        "${PROJECT_BINARY_DIR}/object.c"
    COMMAND
        "${AWK}" -f "${PROJECT_SOURCE_DIR}/src/object.awk" -v pass=c2
        "${PROJECT_SOURCE_DIR}/src/object.txt" >>
        "${PROJECT_BINARY_DIR}/object.c"
)
add_custom_command(
    OUTPUT "${PROJECT_BINARY_DIR}/include/object.h"
    COMMAND "${CMAKE_COMMAND}" -E make_directory "include"
    COMMAND
        "${AWK}" -f "${PROJECT_SOURCE_DIR}/src/object.awk" -v pass=h
        "${PROJECT_SOURCE_DIR}/src/object.txt" >
        "${PROJECT_BINARY_DIR}/include/object.h"
)
add_custom_command(
    OUTPUT "${PROJECT_BINARY_DIR}/map.gv"
    COMMAND
        "${AWK}" -f "${PROJECT_SOURCE_DIR}/src/map.awk"
        "${PROJECT_SOURCE_DIR}/src/object.txt" > "${PROJECT_BINARY_DIR}/map.gv"
)
add_custom_target(
    map_png ALL
    DEPENDS "${PROJECT_BINARY_DIR}/map.gv"
    COMMAND "${DOT}" -Tpng -o "${PROJECT_BINARY_DIR}/map.png"
            "${PROJECT_BINARY_DIR}/map.gv"
)
set(GEN_SRC "${PROJECT_BINARY_DIR}/object.c"
            "${PROJECT_BINARY_DIR}/include/object.h"
)
add_executable(spirit ${SRC} ${GEN_SRC})
target_include_directories(
    spirit PRIVATE "${PROJECT_SOURCE_DIR}/src" "${PROJECT_BINARY_DIR}/include"
)
