#pragma once

#include <memory>
#include <string>

#include <vector>
#include <memory.h>
#include <cards.hpp>

class Player {
public:
  Player();
  Player(std::string name, std::string color, int age);

  std::string                         name;
  int                                 age;
  std::string                         color;
  const std::string& GetName() const;
  int GetAge() const;

private:
  std::string m_Name;
  std::string m_Color;
  int m_Age;
};
