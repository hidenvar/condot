#pragma once

#include <string>
#include <raylib.h>
#include <unordered_map>
#include <vector>

#include <asset_manager.hpp>
#include <state.hpp>
#include <event.hpp>
#include <entity.hpp>
#include <card.hpp>
#include <mercenary.hpp>
#include <button.hpp>

enum class Position {
  TOP_LEFT,
  TOP_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_RIGHT,
  LEFT,
  RIGHT,
};

class Player : public Entity
{
public:
  Player(const std::string& name, int age, Color color, Position position);

  void Update() override;
  void Render(const AssetManager& assets) const override;

  void SetContext(State* state, Event* rotateTurnEvent);
  const std::string& GetName() const;
  int GetAge() const;
  void AddCard(Card card);
  bool IsPassed();
  void SetPosition(const Position& position);
  Position GetPosition() const;
  void PickCard(const size_t& index);

private:
  bool PlayCard();
  void RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation, float ratio) const;
  void RenderRows(const AssetManager& assets, Vector2 cordinate, float rotation, float ratio) const;
  void Pass();
  void Add(size_t index);
  Color GetColor() const;

private:
  State* m_State;
  Event* m_RotateTurnEvent;
  std::string m_Name;
  Color m_Color;
  int m_Age;
  Position m_Position;
  std::vector<Card> m_Cards;
  std::vector<Mercenary> m_Row;
  bool m_IsPassed;
  //Button m_PassButton;
  std::unordered_map<std::string , int> m_s;
};
