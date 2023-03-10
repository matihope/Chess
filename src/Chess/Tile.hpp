#pragma once
//#include "Chess/Logic/BasePiece.hpp"
//#include "Chess/Logic/Position.hpp"
//#include <Clickable/Clickable.hpp>
//#include <CollisionShape/CollisionShape.hpp>
//#include <GUI/Label.hpp>
//#include <SFML/Graphics.hpp>
//#include <WorldEntity/WorldEntity.hpp>
//
//class ChessScene;
//
//namespace Chess {
//class Tile : public WorldEntity, public Clickable {
//  sf::RectangleShape m_shape;
//  BasePiece m_piece;
//  RectCollision m_collision_shape;
//  Position m_square;
//
//  // labels
//  bool m_flipped;
//  GUI::Label m_file_label;
//  GUI::Label m_rank_label;
//  void setLabel();
//
//  // clicking
//  void onRelease() override;
//  bool m_show_move_indicator;
//  sf::CircleShape m_move_indicator;
//
// public:
//  Tile();
//  explicit Tile(Position square);
//  void update(float dt) override;
//  void setColor(sf::Color color);
//  void setSize(float size);
//  float getSize();
//  void setSquare(Position square);
//  Position getSquare();
//  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
//  void setPiece(PieceType type);
//  void clearPiece();
//  void setFlipped(bool flipped);
//  void setMoveIndicator(bool show);
//};
//}  // namespace Chess
