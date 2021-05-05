project (libtreedbs)

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

target_include_directories(libtreedbs
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
    PRIVATE "${LTSMIN_INCLUDE_DIRS}"
)
