#include <stdexcept>
#include <iostream>

#include <player.hpp>
#include <normalcard.hpp>

Player::Player(std::string name, std::string color, int age)
: m_Name(name),
  m_Color(color),
  m_Age(age)
{
  if (age < 0) {
    throw std::invalid_argument("age cannot be negative");
  }
}

const std::string& Player::GetName() const {
  return m_Name;
}

int Player::GetAge() const {
  return m_Age;
}

void Player::AddCard(std::unique_ptr<Card>&& card)
{
  m_Cards.push_back(std::move(card));
}

std::unique_ptr<Card> Player::TakeCard(const std::string& name)
{
  for (auto it = m_Cards.begin(); it != m_Cards.end(); ++it) {
    std::unique_ptr<Card>& card = *it;
    if (card->GetName() == name) {
      std::unique_ptr<Card> c = std::move(*it);
      it = m_Cards.erase(it);
      return c;
    }
  }

  return nullptr;
}

void Player::PrintCards(){
  for(const auto& card : m_Cards){
    std::cout << card->GetName() << ' ';
  }
}

void Player::AddDrawnNormalCard(std::unique_ptr<NormalCard>&& card) {
  m_DrawnNormalCards.push_back(std::move(card));
}
