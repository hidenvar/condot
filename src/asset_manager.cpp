#include <raylib.h>

#include <asset_manager.hpp>

AssetManager::AssetManager()
{
  Map = LoadTexture("assets/map.png");
  Bishop = LoadTexture("assets/special/bishop.png");
  Drummer = LoadTexture("assets/special/drummer.png");
  Heroine = LoadTexture("assets/special/heroine.png");
  Scarecrow = LoadTexture("assets/special/scarecrow.png");
  Spring = LoadTexture("assets/special/spring.png");
  Spy = LoadTexture("assets/special/spy.png");
  Turncoat = LoadTexture("assets/special/turncoat.png");
  Winter = LoadTexture("assets/special/winter.png");
}

AssetManager::~AssetManager()
{
  // NOTE: reverse ordering recommended

  UnloadTexture(Winter);
  UnloadTexture(Turncoat);
  UnloadTexture(Spy);
  UnloadTexture(Spring);
  UnloadTexture(Scarecrow);
  UnloadTexture(Heroine);
  UnloadTexture(Drummer);
  UnloadTexture(Bishop);
  UnloadTexture(Map);
}
