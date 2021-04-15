project (libtreedbs)

## Find pins.h
#if(WITH_LTSMIN)
#    if(EXISTS "${WITH_LTSMIN}/include/ltsmin/pins.h")
#        set(CMAKE_REQUIRED_INCLUDES "${WITH_LTSMIN}/include")
#        set(LTSMIN_INCLUDE_DIRS "${WITH_LTSMIN}/include")
#    else()
#        message(SEND_ERROR "${WITH_LTSMIN} does not contain ltsmin/pins.h")
#    endif()
#else()
#    find_path(LTSMIN_INCLUDE_DIRS ltsmin/pins.h)
#endif()
#if(NOT HAVE_PINS_H)
#    check_include_file("ltsmin/pins.h" HAVE_PINS_H)
#endif()
#set(CMAKE_REQUIRED_INCLUDES)
#if(NOT HAVE_PINS_H)
#    message(SEND_ERROR "Looking for ltsmin/pins.h - not found")
#endif()

add_definitions(-fPIC)

add_library(libtreedbs STATIC
    src/treedbs-ll.c
    src/clt_table.c
    src/dbs-ll.c
    src/common.cpp
)

target_link_libraries(libtreedbs
    PUBLIC -lpthread -lm
)

message("msg ${LTSMIN_INCLUDE_DIRS}")

target_include_directories(libtreedbs
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
    PRIVATE "${LTSMIN_INCLUDE_DIRS}"
)
