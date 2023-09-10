cmake_minimum_required(VERSION 3.26)
project(socket_implementation_c)

set(CMAKE_C_STANDARD 17)

if (UNIX)
    add_compile_options(
        -O2
        -Wall
        -Wextra
        -Wpedantic
        -fstack-protector
        -D_FORTIFY_SOURCE=2
        -fPIE
        -fPIC
        -Wformat-security
        )
    add_link_options(
        -pie
        -Wl,-z,relro,-z,now
        )
elseif(WIN32)
    add_compile_options(/GS)
endif ()

add_executable(client c_implementation/client.c)
add_executable(server c_implementation/server.c)

if (WIN32)
    target_link_libraries(client PRIVATE ws2_32)
    target_link_libraries(server PRIVATE ws2_32)
endif ()
