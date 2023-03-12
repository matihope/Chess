set(GAME_SOURCES
        Scene/MenuScene.cpp Scene/MenuScene.hpp
        Scene/ChessScene.cpp Scene/ChessScene.hpp
        Chess/Logic/Board.cpp Chess/Logic/Board.hpp
        Chess/Logic/BasePiece.cpp Chess/Logic/BasePiece.hpp
        Chess/Logic/Square.cpp Chess/Logic/Square.hpp
        Chess/Logic/Pawn.cpp Chess/Logic/Pawn.hpp
        Chess/BoardEntity.cpp Chess/BoardEntity.hpp
        Chess/Logic/Move.cpp Chess/Logic/Move.hpp
        Chess/Logic/Game.cpp Chess/Logic/Game.hpp Chess/Logic/PieceView.cpp Chess/Logic/PieceView.hpp Chess/Tile.cpp Chess/Tile.hpp)

add_library(Game ${GAME_SOURCES})

# target_link_libraries(Game Engine)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
