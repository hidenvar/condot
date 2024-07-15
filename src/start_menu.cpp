#include "asset_manager.hpp"
#include <raylib.h>

#include <state.hpp>
#include <menu.hpp>

static const int BUTTON_WIDTH = 800;
static const int BUTTON_HEIGHT = 100;

StartMenu::StartMenu(State* state)
: m_State(state),
  m_ButtonStart("Start", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f - 60,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
  m_ButtonExit("Exit", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f + 60,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  })
{
}

void StartMenu::Update()
{
  if (m_State->Get() == State::START_MENU)
  {
    m_ButtonStart.Update();
    m_ButtonExit.Update();

    if (m_ButtonStart.Pressed())
    {
      m_State->Set(State::PLAYER_PICK_MENU);
    }
    if (m_ButtonExit.Pressed())
    {
      // TODO: signal game to exit
    }
  }
}

void StartMenu::Render(const AssetManager& assets) const
{
  if (m_State->Get() == State::START_MENU)
  {
    m_ButtonStart.Render(assets);
    m_ButtonExit.Render(assets);
  }
}
