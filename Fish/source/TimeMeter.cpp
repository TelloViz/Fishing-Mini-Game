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

TimeMeter::TimeMeter(sf::Vector2f pos, sf::Vector2f dim, sf::Time dur) : sf::RectangleShape(dim), m_meterMaxDim(dim), m_meterMaxPos( pos )
{
     //this->setPosition(pos);
     
     m_msDuration = dur;
}

void TimeMeter::Update(sf::Time elapsed) // seconds elapsed since last call to this function
{
     m_msElapsed += elapsed;
     if (!m_isPaused)
     {
          //m_elap
         float elapsedRate = m_msElapsed.asSeconds() / m_msDuration.asSeconds();
         //cout << "Elapsed(sec)=" << m_msElapsed.asSeconds() << "/ Duration(sec)=" << m_msDuration.asSeconds() << " Ratio(%)=" << elapsedRate << endl;
         this->setSize(sf::Vector2f(this->getSize().x, m_meterMaxDim.y * elapsedRate));

     }
}

void TimeMeter::Reset()
{
}

void TimeMeter::Restart()
{
     
     //m_msElapsed = 0.0f;
     
}

void TimeMeter::Pause()
{
     m_isPaused = true;
}

float TimeMeter::ElapsedRatio(float elapsed, float maxElapsed)
{
     return elapsed / maxElapsed;
}


