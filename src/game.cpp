#include <raylib.h>

#include <game.hpp>

Game::Game()
{
  InitWindow(1600, 900, "Condottiere");
  SetTargetFPS(60);
  ToggleFullscreen();
}

Game::~Game()
{
  CloseWindow();
}

void Game::Start()
{
  while (!WindowShouldClose())
  {
    Update();

    BeginDrawing();
    Render();

    EndDrawing();
  }
}

void Game::Update()
{
}

void Game::Render() const
{
  ClearBackground(RAYWHITE);
  DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
}
