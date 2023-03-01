set(GAME_SOURCES
    Scene/MenuScene.cpp
    Scene/ChessScene.cpp
    Chess/Tile.cpp
    Chess/Piece.cpp
    Chess/GameOfChess.cpp
    Chess/TileManager.cpp
)

add_library(Game ${GAME_SOURCES})

# target_link_libraries(Game Engine)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
