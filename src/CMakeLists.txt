set(GAME_SOURCES
    Scene/MenuScene.cpp Scene/MenuScene.hpp
    Scene/ChessScene.cpp Scene/ChessScene.hpp
    Chess/Chess.hpp
    Chess/Tile.cpp Chess/Tile.hpp
    Chess/Piece.cpp Chess/Piece.hpp
    Chess/Manager.cpp Chess/Manager.hpp
)

add_library(Game ${GAME_SOURCES})

# target_link_libraries(Game Engine)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
