#pragma once

#include <vector>
#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <entity.hpp>
#include <button.hpp>
#include <input.hpp>

class CustomizationMenu : public Entity
{
public:
  CustomizationMenu(State* state);

  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
  struct PlayerRow {
    Input Name;
    Input Age;
  };

private:
  State* m_State;

  Rectangle m_Dimensions;

  Button m_IncreasePlayersButton;
  Button m_DecreasePlayersButton;
  std::vector<PlayerRow> m_PlayerRows;
};
