set(GAME_SOURCES
        Scenes/MenuScene.cpp Scenes/MenuScene.hpp
        Scenes/ChessScene.cpp Scenes/ChessScene.hpp
        Chess/Logic/Board.cpp Chess/Logic/Board.hpp
        Chess/Logic/Pieces/BasePiece.cpp Chess/Logic/Pieces/BasePiece.hpp
        Chess/Logic/Square.cpp Chess/Logic/Square.hpp
        Chess/Logic/Pieces/Pawn.cpp Chess/Logic/Pieces/Pawn.hpp
        Chess/BoardEntity.cpp Chess/BoardEntity.hpp
        Chess/Logic/Move.cpp Chess/Logic/Move.hpp
        Chess/Logic/Game.cpp Chess/Logic/Game.hpp Chess/Tile.cpp Chess/Tile.hpp Chess/Logic/Pieces/Rook.cpp Chess/Logic/Pieces/Rook.hpp Chess/FloatingPiece.cpp Chess/FloatingPiece.hpp Chess/Logic/Pieces/Knight.cpp Chess/Logic/Pieces/Knight.hpp Chess/Logic/Pieces/Bishop.cpp Chess/Logic/Pieces/Bishop.hpp Chess/Logic/Pieces/Queen.cpp Chess/Logic/Pieces/Queen.hpp Chess/Logic/Pieces/King.cpp Chess/Logic/Pieces/King.hpp)

add_library(Game ${GAME_SOURCES})

# target_link_libraries(Game Engine)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
