#pragma once
#include <SFML/Graphics.hpp>

class TimeMeter : public sf::RectangleShape
{
public:
     explicit TimeMeter(sf::Vector2f size = sf::Vector2f(0.0f, 0.0f));
     TimeMeter(sf::Vector2f pos, sf::Vector2f dim);
     TimeMeter(sf::Vector2f pos, sf::Vector2f dim, float dur,sf::Color fillColor);
     virtual ~TimeMeter() {}

     void IncreaseRemaining(float secIncrease) { m_secElapsed = m_secElapsed - secIncrease / m_secDuration; }
     void SetRemaining(float newSec) { m_secElapsed = m_secDuration - newSec; }
     void Update(float secElapsed);
     void Reset();
     void Restart();
     void Pause();
       
private:

     // returns a ratio indicating how much time is left on the timer.
     float ElapsedRatio(float elapsed, float maxElapsed);

     float               m_secDuration{ 60 };
     float               m_secElapsed{0};
     sf::Vector2f        m_meterMaxDim;
     sf::Vector2f        m_meterMaxPos;
     bool                m_isPaused{ false };
};

