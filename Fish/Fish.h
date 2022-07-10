#pragma once
#include <SFML/Graphics.hpp>
class Fish : public sf::Sprite
{
public:
     enum class DifficultyTier {EASY, MEDIUM, HARD};

     float difFactor(DifficultyTier level)
     {
          
          switch (level)
          {
          case Fish::DifficultyTier::EASY:
               return easyFactor;
               break;
          case Fish::DifficultyTier::MEDIUM:
               return medFactor;
               break;
          case Fish::DifficultyTier::HARD:
               return hardFactor;
               break;
          }
     }
private:
     DifficultyTier m_diffTier;
     float easyFactor{ 1.0f };
     float medFactor{ 0.5f };
     float hardFactor{ 0.25f };

     
};

