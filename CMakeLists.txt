project (dmc)
cmake_minimum_required(VERSION 3.2)
include(FetchContent)

FetchContent_Declare(
        dtree
        GIT_REPOSITORY https://github.com/bergfi/dtree.git
        GIT_TAG        4e314dff5b93906ce12739e362991225d5866c68
)
FetchContent_Declare(
        libfrugi
        GIT_REPOSITORY https://github.com/bergfi/libfrugi.git
        GIT_TAG        93deb6ad08818c99d4a2ddf520f12527bb3dd542
)

FetchContent_MakeAvailable(libfrugi dtree)
#if(NOT dtree_POPULATED)
#add_subdirectory(${dtree_SOURCE_DIR} ${dtree_BINARY_DIR})
#endif()
#if(NOT libfrugi_POPULATED)
#add_subdirectory(${libfrugi_SOURCE_DIR} ${libfrugi_BINARY_DIR})
#endif()

##find_package(libfrugi REQUIRED)
#find_package(libfrugi CONFIG)
#if(NOT ${libfrugi_DIR})
#    message("libfrugi not found")
#    message("LOOOOOOOOOOOOOOOOOOOOOOL")
#    FetchContent_MakeAvailable(libfrugi)
#    #    ExternalProject_Add(libfrugiproj
#    #            GIT_REPOSITORY https://github.com/bergfi/libfrugi.git
#    #            GIT_TAG        master
#    #            CONFIGURE_COMMAND ""
#    #            )
#    find_package(libfrugi CONFIG REQUIRED)
#    add_subdirectory()
#    #    set(libfrugi_FOUND true)
#endif()


set(libdmc_VERSION_MAJOR 0)
set(libdmc_VERSION_MINOR 2)
set(libdmc_VERSION_PATCH 0)
set(libdmc_VERSION "${libdmc_VERSION_MAJOR}.${libdmc_VERSION_MINOR}.${libdmc_VERSION_PATCH}")

set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
#set(INSTALL_SYSCONFIG_DIR etc/dmc CACHE PATH "Installation directory for config files")
if(WIN32 AND NOT CYGWIN)
    set(DEF_INSTALL_CMAKE_DIR CMake)
else()
    set(DEF_INSTALL_CMAKE_DIR lib/cmake/libdmc)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

add_subdirectory(treedbs EXCLUDE_FROM_ALL)

add_library(libdmc
        libdmccapi.cpp
        #        pins/pinsWrapper.cpp
        )
set_target_properties(libdmc PROPERTIES OUTPUT_NAME "dmc")
set_property(TARGET libdmc PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET libdmc PROPERTY CXX_STANDARD 17)
set_property(TARGET libdmc PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET libdmc PROPERTY VERSION ${dmc_VERSION})
set_property(TARGET libdmc PROPERTY SOVERSION ${dmc_VERSION_MAJOR})
set_property(TARGET libdmc PROPERTY DEBUG_POSTFIX d)

target_include_directories(libdmc
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/treedbs/include"
        )

target_link_libraries(libdmc
        PUBLIC -fPIC -lpthread -lm libfrugi -ldl -latomic
        PUBLIC libtreedbs dtree
        )

add_dependencies(libdmc libtreedbs)

configure_package_config_file(cmake/libdmcConfig.cmake.in
        "${CMAKE_BINARY_DIR}/cmake/libdmcConfig.cmake"
        INSTALL_DESTINATION ${INSTALL_LIB_DIR}/dmc/cmake
        PATH_VARS INSTALL_INCLUDE_DIR
        )

write_basic_package_version_file(
        "${CMAKE_BINARY_DIR}/cmake/libdmcConfigVersion.cmake"
        VERSION "${libdmc_VERSION}"
        COMPATIBILITY SameMajorVersion
)
install(TARGETS libdmc libtreedbs
        EXPORT libdmcTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}" COMPONENT dev
        )
install(EXPORT libdmcTargets
        FILE libdmcTargets.cmake
        DESTINATION lib/cmake/libdmc
        )
install (DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/include/dmc"
        DESTINATION include
        )
install(FILES
        "${CMAKE_BINARY_DIR}/cmake/libdmcConfig.cmake"
        "${CMAKE_BINARY_DIR}/cmake/libdmcConfigVersion.cmake"
        DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)


add_executable(dmc
        dmc.cpp
        )
set_property(TARGET dmc PROPERTY CXX_STANDARD 17)
set_property(TARGET dmc PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(dmc
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/treedbs/include"
        )
target_link_libraries(dmc
    PUBLIC -Wl,-E -fPIC libfrugi dtree -latomic -ldl
    PRIVATE libtreedbs
)

add_subdirectory(tests)

install (TARGETS dmc DESTINATION bin)
