#pragma once

#include <string>
#include <raylib.h>

#include <player.hpp>

class Region
{
public:
  explicit Region(const std::string& name, Rectangle collision);

  Rectangle GetCollision() const;
  bool CollidesWith(Vector2 v) const;

private:
  std::string m_Name;
  Rectangle m_Collision;
  Player* m_Ruler;
};
