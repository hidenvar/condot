#include <cstddef>
#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <event.hpp>
#include <player.hpp>
#include <card.hpp>
#include <mercenary.hpp>
#include <button.hpp>


Player::Player(
  State* state,
  Event* rotateTurnEvent,
  const std::string& name,
  Color color,
  int age,
  Position position
)
: m_State(state),
  m_RotateTurnEvent(rotateTurnEvent),
  m_Name(name),
  m_Color(color),
  m_Age(age),
  m_Position(position),
  m_IsPassed(false),
  m_PassButton ("SURRENDER",Rectangle(GetScreenWidth() - float(1600), GetScreenHeight() - float(200), 170 , 100))
{
}

void Player::Update()
{
  if (m_State->Get() != State::PLAYING_CARD){
    return;
  }
    m_PassButton.Update();  
    if (PlayCard())
    {
      m_RotateTurnEvent->Raise(this, nullptr);
    }
}

void Player::AddCard(Card card)
{
  m_Cards.push_back(card);
}

void Player::Render(const AssetManager& assets) const
{
  if (m_State->Get() == State::MAIN_MENU || m_State->Get() == State::CUSTOMIZATION_MENU)
  {
    return;
  }

  float width = GetScreenWidth();
  float height = GetScreenHeight();

  int length = 3 * height / 4;
  int thickness = 200;
  
  Vector2 BOTTOM{(width - float(570)) / 2  , height - float(200)};
  Vector2 TOP   {(width + float(570)) / 2  , 200};
  Vector2 LEFT  { 200                      , (height - float(570)) / 2 };
  Vector2 RIGHT {(width - float(200))      , (height + float(570)) / 2 };
  
  switch (m_Position)
  {
  case Position::TOP:
    DrawRectangle((width - length) / 2, 0, length, thickness, RED);
    RenderRows ( assets , Vector2{TOP.x + 50, TOP.y + 200} , 180);
    RenderCards( assets , TOP ,180);
    break;
  case Position::RIGHT:
    DrawRectangle(width - thickness, (height - length) / 2, thickness, length, GREEN);
    RenderRows (assets,Vector2{ RIGHT.x - 200, RIGHT.y + 50}, 270);
    RenderCards(assets, RIGHT , 270);
    break;
  case Position::BOTTOM:
    DrawRectangle((width - length) / 2, height - thickness, length, thickness, BLUE);
    RenderRows (assets,Vector2{ BOTTOM.x - 50, BOTTOM.y - 200}, 0);
    m_PassButton.Render(assets);
    RenderCards(assets, BOTTOM, 0);
    break;
  case Position::LEFT:
    DrawRectangle(0, (height - length) / 2, thickness, length, GRAY);
    RenderRows (assets,Vector2{ LEFT.x + 200, LEFT.y - 50}, 90);
    RenderCards(assets, LEFT, 90);
    break;
  }
}

void Player::RenderRows(const AssetManager& assets, Vector2 cordinate, float rotation) const
{
  float ratio = 0.75;
  if (m_Position == Position::TOP)
  {
    for (auto c = m_Row.rbegin(); c != m_Row.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= 50;
    }
  }

  if (m_Position == Position::BOTTOM)
  {
    for (const auto& c : m_Row)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += 50;
    }
    
  }
  if (m_Position == Position::LEFT)
  {
    for (const auto& c : m_Row)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y += 50;
    }
  }

  if (m_Position == Position::RIGHT)
  {
    for(auto c = m_Row.rbegin(); c != m_Row.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y -= 50;
      
    }  
  }
}

void Player::RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation) const
{
  Card card = Card::BACKSIDE;
  
  float ratio = 0.75;
  if (m_Position == Position::TOP)
  {
    for (size_t c{} ; c < m_Cards.size() ; ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= 50;
    }
  }

  if (m_Position == Position::BOTTOM)
  {
    for (const auto& c : m_Cards)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += 50;
    }
    
  }
  
  if (m_Position == Position::LEFT)
  {
    for (size_t c{} ; c < m_Cards.size(); ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y += 50;
    }
  }
  
  if (m_Position == Position::RIGHT)
  {
    for(size_t c{} ; c < m_Cards.size() ; ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y -= 50;
      
    }  
  }
}

bool Player::PlayCard(){
  if (m_Position == Position::BOTTOM)
  {
    size_t index = 0;
    for(auto it = m_Cards.rbegin(); it != m_Cards.rend(); ++it)
    {
      Rectangle LowerLayer = {((GetScreenWidth() - float(570)) / 2) + (float) 50 * index , GetScreenHeight() - float(200) , 50  , 190};
      Rectangle UpperLayer = {((GetScreenWidth() - float(570)) / 2) + (float) 50 * index , GetScreenHeight() - float(200) , 120 , 190};
        
      if((CheckCollisionPointRec(GetMousePosition(), LowerLayer) ||
         (CheckCollisionPointRec(GetMousePosition(), UpperLayer) &&
         m_Cards.size() - 1 == index )) && 
          IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
          PickCard(index);
          return true;
        }
      else if (m_PassButton.Pressed()){
        //m_IsPassed = true;  
        return true;
      }
      index++;
    }
  }
    return false;
}
int Player::GetAge() const {
  return m_Age;
}

void Player::PickCard(const size_t& index){
          auto card = m_Cards[index].GetType();
          if (card == Card::MERCENARY_1) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(1);
          }
          
          else if (card == Card::MERCENARY_2) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(2);
          }
          
          else if (card == Card::MERCENARY_3) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(3);
          }
          
          else if (card == Card::MERCENARY_4) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(4);
          }
          
          else if (card == Card::MERCENARY_5) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(5);
          }
          
          else if (card == Card::MERCENARY_6) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(6);
          }
          
          else if (card == Card::MERCENARY_10) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(10);
          }
          
          // TODO : does something with gameflow
          else if (card == Card::BISHOP) {
            m_Cards.erase(m_Cards.begin() + index);
            // TODO: use event
          }
          
          else if (card == Card::DRUMMER) {
            m_Cards.erase(m_Cards.begin() + index);
            if (!m_s.count("DRUMMER")) m_s.insert({"DRUMMER" , 1});
          }
          
          else if (card == Card::HEROINE) {
            m_Cards.erase(m_Cards.begin() + index);
            // TODO int Heroine++;
          }
          
          else if (card == Card::SCARECROW) {
            m_Cards.erase((m_Cards.begin() + index));
            //TODO : SCARECROW();
          }
          else if (card == Card::SPRING) {
            m_Cards.erase(m_Cards.begin() + index);
            //TODO : Set(Season::SPRING);
          }
          
          else if (card == Card::SPY) {
            m_Cards.erase(m_Cards.begin() + index);
            //TODO : int Spy++;
            
          }
          
          else if (card == Card::TURNCOAT) {
            m_Cards.erase(m_Cards.begin() + index);
            // TODO : EndGame();
          }
          
          else if (card == Card::WINTER) {
            m_Cards.erase(m_Cards.begin() + index);
            // TODO : Set(Season::WINTER);
          }
          
}

void Player::SetPosition(const Position& position){
  m_Position = position;
}

void Player::Pass(){
  m_IsPassed = true;
}

bool Player::IsPassed(){
  return m_IsPassed;
}

const Position& Player::GetPosition() const{
  return m_Position;
}

std::vector<Card>&  Player::GetCards(){
  return m_Cards;
}

void Player::Add(const size_t& index){
  size_t power = m_Row[index].GetPower();
  if (power == 1) {
    m_Cards.push_back(Card::MERCENARY_1);
  }

  else if (power == 2) {
    m_Cards.push_back(Card::MERCENARY_2);
  }

  else if (power == 3) {
    m_Cards.push_back(Card::MERCENARY_3);
  }
   
  else if (power == 4) {
    m_Cards.push_back(Card::MERCENARY_4);
  }
  
  else if (power == 5) {
    m_Cards.push_back(Card::MERCENARY_5);
  }
  
  else if (power == 6) {
    m_Cards.push_back(Card::MERCENARY_6);
  }
  
  else if (power == 10) {
    m_Cards.push_back(Card::MERCENARY_10);
 }
}
      
