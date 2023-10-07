cmake_minimum_required(VERSION 3.26)

project( prizewheel )

find_package(libzip CONFIG REQUIRED)
add_executable(prizewheel prizewheel.c)

target_link_libraries(prizewheel PRIVATE libzip::zip)
