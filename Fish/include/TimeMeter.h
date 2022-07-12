#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class TimeMeter : public sf::RectangleShape
{
public:
     explicit TimeMeter(sf::Vector2f size = sf::Vector2f(0.0f, 0.0f));
     TimeMeter(sf::Vector2f pos, sf::Vector2f dim);
     TimeMeter(sf::Vector2f pos, sf::Vector2f dim, sf::Time dur);
     virtual ~TimeMeter() {}

     void IncreaseRemaining(sf::Time secIncrease) { m_msElapsed = sf::milliseconds(m_msElapsed.asMilliseconds() - (secIncrease.asMilliseconds() / m_msDuration.asMilliseconds())); }
     void SetRemaining(sf::Time newSec) { m_msElapsed = m_msDuration - newSec; }
     void Update(sf::Time secElapsed);
     void Reset();
     void Restart();
     void Pause();
       
private:

     // returns a ratio indicating how much time is left on the timer.
     float ElapsedRatio(float elapsed, float maxElapsed);

     sf::Time           m_msDuration{};
     sf::Time           m_msElapsed;
     sf::Vector2f        m_meterMaxDim;
     sf::Vector2f        m_meterMaxPos;
     bool                m_isPaused{ false };
};

