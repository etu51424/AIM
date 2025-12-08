cmake_minimum_required(VERSION 4.0)
project(projet C)

set(CMAKE_C_STANDARD 11)

add_executable(projet main.c)
add_custom_command(TARGET projet POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/table.csv
        $<TARGET_FILE_DIR:projet>
)
