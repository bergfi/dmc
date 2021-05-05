FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        6a7ed316a5cdc07b6d26362c90770787513822d4
)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(storage_test
    storage_test.cpp
)
set_property(TARGET storage_test PROPERTY CXX_STANDARD 17)
set_property(TARGET storage_test PROPERTY CXX_STANDARD_REQUIRED ON)

add_definitions(-fPIC)

gtest_discover_tests(storage_test)
target_link_libraries(storage_test PUBLIC
    -fPIC
    gtest gtest_main
    -lpthread -lm
    libtreedbs
    -latomic
    libdmc
    libtreedbs
    dtree
    )
add_test(storage_test storage_test)

add_executable(model_test
        model_test.cpp
        )
set_property(TARGET model_test PROPERTY CXX_STANDARD 17)
set_property(TARGET model_test PROPERTY CXX_STANDARD_REQUIRED ON)

add_definitions(-fPIC)

gtest_discover_tests(model_test)
target_link_libraries(model_test PUBLIC
    -fPIC
    gtest gtest_main
    -lpthread -lm libfrugi
    libtreedbs
    -latomic
    libdmc
    libtreedbs
    dtree
    )
add_test(model_test model_test)
