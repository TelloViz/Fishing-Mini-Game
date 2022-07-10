#include "TimeMeter.h"
#include <iostream>
using namespace std;

TimeMeter::TimeMeter(sf::Vector2f dim) : sf::RectangleShape{ dim }, m_meterMaxDim{ dim }
{
}

TimeMeter::TimeMeter(sf::Vector2f pos, sf::Vector2f dim) : sf::RectangleShape{ dim }, m_meterMaxDim{ dim }, m_meterMaxPos{ pos }
{
     this->setPosition(pos);
}

TimeMeter::TimeMeter(sf::Vector2f pos, sf::Vector2f dim, float dur) : sf::RectangleShape{dim}, m_meterMaxDim{dim}, m_meterMaxPos{ pos }
{
     this->setFillColor(sf::Color(255,255,255,255));
     this->setPosition(pos);
     
     m_secDuration = dur;
}

void TimeMeter::Update(float secElapsed) // seconds elapsed since last call to this function
{
     if (!m_isPaused)
     {
          m_secElapsed += secElapsed; // keep our running total synced up     
          auto newHeight = m_meterMaxDim.y * ElapsedRatio(m_secElapsed, m_secDuration);;
          this->setSize(sf::Vector2f(this->getSize().x, newHeight));
     }
}

void TimeMeter::Reset()
{
}

void TimeMeter::Restart()
{
     
     m_secElapsed = 0.0f;
     
}

void TimeMeter::Pause()
{
     m_isPaused = true;
}

float TimeMeter::ElapsedRatio(float elapsed, float maxElapsed)
{
     return elapsed / maxElapsed;
}


