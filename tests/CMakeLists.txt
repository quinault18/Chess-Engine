include_directories(../include)

include(FetchContent)
FetchContent_Declare(
    googletest 
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()



add_executable(tests 
                tests.cpp
                ../src/board.cpp
                ../src/basepiece.cpp
                ../src/square.cpp 
                ../src/move.cpp 
                ../src/queen.cpp 
                ../src/king.cpp
                ../src/rook.cpp
                ../src/pawn.cpp
                ../src/knight.cpp
                ../src/bishop.cpp
                ../src/castlingRights.cpp)

target_link_libraries(tests GTest::gtest_main)
add_test(NAME tests COMMAND tests)