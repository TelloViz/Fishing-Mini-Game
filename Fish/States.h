#pragma once
#include <string>
#include <SFML/Graphics.hpp>
using std::string;

namespace tv
{
     namespace st
     {
          struct UI_State
          {
               string
                    canvasWidth{},
                    canvasHeight{},
                    canvas_X{},
                    canvas_Y{},
                    windowWidth,
                    windowHeight,
                    frame;

               sf::Texture frameTexture;
               sf::RectangleShape canvasShape;
               sf::Sprite frameSprite;

               string timer_X, timer_Y,
                    timerWidth, timerMinHeight, timerMaxHeight,
                    timer_R, timer_G, timer_B, timer_A;

          };

          struct Player_State
          {
               string
                    player_W,
                    player_H,
                    player_X,
                    player_Y,
                    player_R,
                    player_G,
                    player_B,
                    player_A,
                    player_active_R,
                    player_active_G,
                    player_active_B,
                    player_active_A,
                    markerTopLimit,
                    markerBottomLimit;
               sf::RectangleShape playerMarker;
          };

          struct Fish_State
          {
               Fish fish;
               sf::Texture fishTexture;
               string fishIconPath;
          };
     }
}