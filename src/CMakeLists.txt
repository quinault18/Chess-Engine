include_directories(${PROJECT_SOURCE_DIR}/include/)
add_executable(main main.cpp square.cpp board.cpp basepiece.cpp castlingRights.cpp)

enable_testing()

target_link_libraries(main)
