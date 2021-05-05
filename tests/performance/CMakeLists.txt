add_definitions(-fPIC)

add_executable(model_msq
        model_msq.cpp
        )
set_property(TARGET model_msq PROPERTY CXX_STANDARD 17)
set_property(TARGET model_msq PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(model_msq -fPIC
        -lpthread -lm libfrugi
        libtreedbs
        -latomic
        libdmc
        dtree
        )
add_dependencies(model_msq libdmc)

add_executable(model_philo
        model_philo.cpp
        )
set_property(TARGET model_philo PROPERTY CXX_STANDARD 17)
set_property(TARGET model_philo PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(model_philo -fPIC
        -lpthread -lm libfrugi
        libtreedbs
        -latomic
        libdmc
        dtree
        )

add_executable(model_bakery
        model_bakery.cpp
        )

set_property(TARGET model_bakery PROPERTY CXX_STANDARD 17)
set_property(TARGET model_bakery PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(model_bakery -fPIC
        -lpthread -lm libfrugi
        libtreedbs
        -latomic
        libdmc
        dtree
        )

add_executable(model_bakery_fixed
        model_bakery_fixed.cpp
        )

set_property(TARGET model_bakery_fixed PROPERTY CXX_STANDARD 17)
set_property(TARGET model_bakery_fixed PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(model_bakery_fixed -fPIC
        -lpthread -lm libfrugi
        libtreedbs
        -latomic
        libdmc
        dtree
        )

add_executable(model_promela
        model_promela.cpp
        )

set_property(TARGET model_promela PROPERTY CXX_STANDARD 17)
set_property(TARGET model_promela PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(model_promela -fPIC
        -lpthread -lm libfrugi
        libtreedbs
        -latomic
        libdmc
        dtree
        )

set_property(TARGET dmc PROPERTY CXX_STANDARD 17)
set_property(TARGET dmc PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(model_hashmap
        model_hashmap.cpp
        )

set_property(TARGET model_hashmap PROPERTY CXX_STANDARD 17)
set_property(TARGET model_hashmap PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(model_hashmap -fPIC
        -lpthread -lm libfrugi -ldl
        libtreedbs
        -latomic
        libdmc
        dtree
        )

add_executable(model_sortedlist
        model_sortedlist.cpp
        )

set_property(TARGET model_sortedlist PROPERTY CXX_STANDARD 17)
set_property(TARGET model_sortedlist PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(model_sortedlist -fPIC
        -lpthread -lm libfrugi -ldl
        libtreedbs
        -latomic
        libdmc
        dtree
        )

