#pragma once
#include "deps/SFML-2.5.1/include/SFML/Graphics.hpp"
#include <iostream>
#include "random.hpp"
#include "TimeMeter.h"
#include "Fish.h"
#include "ConfigHandler.h"


namespace tv
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

     class Application
     {
     public:
          int Run();
          bool Init_UI_Variables(ConfigHandler& hCfg, UI_State& UIConfig, Fish_State& fCfg);
          bool Init_Player_Variables(ConfigHandler& cfgHandler, Player_State& plCfg);
          bool Init_Fish_Variables(ConfigHandler& hCfg, Fish_State& fishCfg);
          void Fixed_Update(sf::Time& tst, sf::Time tps, Player_State& pCfg, Fish_State& fCfg);
          bool isOnTarget(Player_State& playerConfig, Fish_State& fishConfig);
          void RenderCurrentState(sf::RenderWindow& window, vector<sf::Drawable*> drawables);
          const int MARKER_DROP_RATE = 5;
          const int MARKER_RISE_RATE = -7;
          int MarkerDropRate() { return MARKER_DROP_RATE; }
          int MarkerRiseRate() { return MARKER_RISE_RATE; }
          const int FRAMES_PER_FISH_POS = 300;
          int FRAMES_REMAINING = FRAMES_PER_FISH_POS;
     private:
          void Update() {}
          void FixedUpdate() {}
          void Render() {}

          sf::RenderWindow window;
          float targetPhysicsFPS = 60;
          sf::Time targetPhysicsSPF;
          sf::Time timeSinceTick;


     };

     


}