include_directories(${PROJECT_SOURCE_DIR}/include/)
add_executable(main 
                main.cpp 
                square.cpp 
                board.cpp 
                basepiece.cpp
                castlingRights.cpp 
                king.cpp 
                queen.cpp 
                rook.cpp 
                bishop.cpp 
                knight.cpp 
                pawn.cpp 
                castlingRights.cpp 
                move.cpp)

enable_testing()

target_link_libraries(main)
