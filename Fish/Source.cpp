
#include <SFML/Graphics.hpp>
#include <iostream>
#include "random.hpp"
#include "TimeMeter.h"
#include "Fish.h"
#include "ConfigHandler.h"

using namespace std;
//using namespace fishConfig;
using Random = effolkronium::random_static;


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

bool Init_UI_Variables(ConfigHandler& hCfg, UI_State& UIConfig, Fish_State& fCfg);
bool Init_Player_Variables(ConfigHandler& cfgHandler, Player_State& plCfg);
bool Init_Fish_Variables(ConfigHandler& hCfg, Fish_State& fishCfg);

void Fixed_Update(sf::Time& tst, sf::Time tps, Player_State& pCfg, Fish_State& fCfg);

bool isOnTarget(Player_State& playerConfig, Fish_State& fishConfig);

void BatchRender(sf::RenderWindow& window, vector<sf::Drawable*> drawables);

     const int MARKER_DROP_RATE = 5;
     const int MARKER_RISE_RATE = -7;

     int MarkerDropRate() { return MARKER_DROP_RATE; }
     int MarkerRiseRate() { return MARKER_RISE_RATE; }

     

     const int FRAMES_PER_FISH_POS = 300;
     int FRAMES_REMAINING = FRAMES_PER_FISH_POS;

int main()
{     
     TimeMeter* meter;

     ConfigHandler hCfg;
     hCfg.ReadConfigFile(); 
     
     Player_State playerConfig;
     Init_Player_Variables(hCfg, playerConfig);

     Fish_State fishConfig;
     Init_Fish_Variables(hCfg, fishConfig);
     
     UI_State UIConfig;
     Init_UI_Variables(hCfg, UIConfig, fishConfig);

     sf::RenderWindow window(sf::VideoMode(stoi(UIConfig.windowWidth), stoi(UIConfig.windowHeight)), "Fishing!");

     

     vector<sf::Drawable*> drawables;
     drawables.push_back(&UIConfig.frameSprite);


     float targetPhysicsFPS = 60;
     sf::Time targetPhysicsSPF = sf::seconds(1 / targetPhysicsFPS);
     sf::Time timeSinceTick;
     sf::Clock physicsClock;

#pragma region MainLoop
     while (window.isOpen())
     {
//          meter->Update(physicsClock.getElapsedTime().asSeconds());
          timeSinceTick += physicsClock.restart();      
          sf::Event event;
          while (window.pollEvent(event))
          {
               if (event.type == sf::Event::Closed)
                    window.close();
               
          }

                              
          Fixed_Update(timeSinceTick, targetPhysicsSPF, playerConfig, fishConfig);
          
         
          if (isOnTarget(playerConfig, fishConfig))
          {          
               playerConfig.playerMarker.setFillColor(sf::Color(stoi(playerConfig.player_active_R), stoi(playerConfig.player_active_G), stoi(playerConfig.player_active_B), stoi(playerConfig.player_active_A)));
              // meter->IncreaseRemaining(0.05f);
          }
          else playerConfig.playerMarker.setFillColor(sf::Color(stoi(playerConfig.player_R), stoi(playerConfig.player_G), stoi(playerConfig.player_B), stoi(playerConfig.player_A)));


          
          window.clear();
          BatchRender(window, drawables);
          window.display();
     }
#pragma endregion // Main loop

     hCfg.WriteConfigFile();
     return 0;
}

bool Init_UI_Variables(ConfigHandler& hCfg, UI_State& UIConfig, Fish_State& fCfg)
{
     hCfg.FindConfig("DEFAULT_WINDOW_WIDTH", UIConfig.windowWidth);
     hCfg.FindConfig("DEFAULT_WINDOW_HEIGHT", UIConfig.windowHeight);
     hCfg.FindConfig("BG_IMAGE_PATH", UIConfig.frame);
     if (!UIConfig.frameTexture.loadFromFile(UIConfig.frame))
     {
          // error ...
     }

     hCfg.FindConfig("DEFAULT_CANVAS_WIDTH", UIConfig.canvasWidth);
     hCfg.FindConfig("DEFAULT_CANVAS_HEIGHT", UIConfig.canvasHeight);
     hCfg.FindConfig("CANVAS_X_POS", UIConfig.canvas_X);
     hCfg.FindConfig("CANVAS_Y_POS", UIConfig.canvas_Y);

    
     UIConfig.canvasShape.setSize( sf::Vector2f(stoi(UIConfig.canvasWidth), stoi(UIConfig.canvasHeight)) );
     UIConfig.canvasShape.setFillColor(sf::Color::Transparent);
     UIConfig.canvasShape.setOutlineThickness(1.0f);
     UIConfig.canvasShape.setOutlineColor(sf::Color(255, 255, 255, 255));
     UIConfig.canvasShape.setPosition(stoi(UIConfig.canvas_X), stoi(UIConfig.canvas_Y));

     UIConfig.frameSprite.setTexture(UIConfig.frameTexture);
     UIConfig.frameSprite.setPosition(stoi(UIConfig.canvas_X), stoi(UIConfig.canvas_Y));

     hCfg.FindConfig("TIMER_X", UIConfig.timer_X);
     hCfg.FindConfig("TIMER_Y", UIConfig.timer_Y);
     hCfg.FindConfig("DEFAULT_TIMER_WIDTH", UIConfig.timerWidth);
     hCfg.FindConfig("MIN_TIMER_HEIGHT", UIConfig.timerMinHeight);
     hCfg.FindConfig("MAX_TIMER_HEIGHT", UIConfig.timerMaxHeight);
     hCfg.FindConfig("DEFAULT_TIMER_COLOR_R", UIConfig.timer_R);
     hCfg.FindConfig("DEFAULT_TIMER_COLOR_G", UIConfig.timer_G);
     hCfg.FindConfig("DEFAULT_TIMER_COLOR_B", UIConfig.timer_B);
     hCfg.FindConfig("DEFAULT_TIMER_COLOR_A", UIConfig.timer_A);

     return true;
}

bool Init_Player_Variables(ConfigHandler& hCfg, Player_State& playerConfig)
{
     hCfg.FindConfig("PLAYER_INDICATOR_WIDTH", playerConfig.player_W);
     hCfg.FindConfig("PLAYER_INDICATOR_HEIGHT", playerConfig.player_H);
     hCfg.FindConfig("PLAYER_X_POS", playerConfig.player_X);
     hCfg.FindConfig("PLAYER_Y_POS", playerConfig.player_Y);
     hCfg.FindConfig("DEFUALT_PLAYER_INDICATOR_COLOR_R", playerConfig.player_R);
     hCfg.FindConfig("DEFUALT_PLAYER_INDICATOR_COLOR_G", playerConfig.player_G);
     hCfg.FindConfig("DEFUALT_PLAYER_INDICATOR_COLOR_B", playerConfig.player_B);
     hCfg.FindConfig("DEFUALT_PLAYER_INDICATOR_COLOR_A", playerConfig.player_A);
     hCfg.FindConfig("DEFUALT_PLAYER_INDICATOR_COLOR_R", playerConfig.player_active_R);
     hCfg.FindConfig("DEFUALT_PLAYER_INDICATOR_COLOR_G", playerConfig.player_active_G);
     hCfg.FindConfig("DEFUALT_PLAYER_INDICATOR_COLOR_B", playerConfig.player_active_B);
     hCfg.FindConfig("DEFUALT_PLAYER_INDICATOR_COLOR_A", playerConfig.player_active_A);

     playerConfig.playerMarker.setSize(sf::Vector2f(stoi(playerConfig.player_W), stoi(playerConfig.player_H)));
     playerConfig.playerMarker.setPosition(stoi(playerConfig.player_X), stoi(playerConfig.player_Y));
     playerConfig.playerMarker.setFillColor(sf::Color(stoi(playerConfig.player_R), stoi(playerConfig.player_G), stoi(playerConfig.player_B), stoi(playerConfig.player_A)));

     
     hCfg.FindConfig("MARKER_TOP_LIMIT", playerConfig.markerTopLimit);
     hCfg.FindConfig("MARKER_BOTTOM_LIMIT", playerConfig.markerBottomLimit);


     return true;
}

bool Init_Fish_Variables(ConfigHandler& hCfg, Fish_State& fishCfg)
{
     hCfg.FindConfig("FISH_ICON_PATH", fishCfg.fishIconPath);
     string fish_X, fish_Y, fishDif;

     hCfg.FindConfig("DEFAULT_FISH_X_POS", fish_X);
     hCfg.FindConfig("DEFAULT_FISH_Y_POS", fish_Y);
     hCfg.FindConfig("FISH_DIFFICULTY", fishDif);

     switch (stoi(fishDif))
     {
     case 1:
          fishCfg.fish.setDifficulty(Fish::DifficultyTier::EASY);
          break;
     case 2:
          fishCfg.fish.setDifficulty(Fish::DifficultyTier::MEDIUM);
          break;
     case 3:
          fishCfg.fish.setDifficulty(Fish::DifficultyTier::HARD);
          break;
     default:
          break;
     }

     if (!fishCfg.fishTexture.loadFromFile(fishCfg.fishIconPath))
     {
          // error...
          return false;
     }

     
     fishCfg.fish.setTexture(fishCfg.fishTexture);
     fishCfg.fish.setPosition(stoi(fish_X), stoi(fish_Y));
     


     
     return true;
}

void Fixed_Update(sf::Time& tst, sf::Time tps, Player_State& pCfg, Fish_State& fCfg)
{
     while (tst >= tps)
     {
          --FRAMES_REMAINING;

          if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
          {
               pCfg.playerMarker.move(sf::Vector2f(0, MarkerRiseRate()));
               if (pCfg.playerMarker.getPosition().y <= stoi(pCfg.markerBottomLimit))
               {
                    pCfg.playerMarker.setPosition(pCfg.playerMarker.getPosition().x, stoi(pCfg.markerBottomLimit));

               }
          }
          else
          {
               pCfg.playerMarker.move(sf::Vector2f(0, MarkerDropRate()));
               if (pCfg.playerMarker.getPosition().y + pCfg.playerMarker.getSize().y > stoi(pCfg.markerTopLimit))
               {
                    pCfg.playerMarker.setPosition(pCfg.playerMarker.getPosition().x, stoi(pCfg.markerTopLimit) - pCfg.playerMarker.getSize().y);

               }
          }

          if (FRAMES_REMAINING <= 0)
          {
               FRAMES_REMAINING = FRAMES_PER_FISH_POS;
               //fCfg.fish.setPosition(fCfg.fish.getPosition().x, Random::get(fCfg., 435.0f));
          }

          tst -= tps;
     }
}

bool isOnTarget(Player_State& playerConfig, Fish_State& fishConfig)
{
     float mTop = playerConfig.playerMarker.getPosition().y;
     float mBot = playerConfig.playerMarker.getPosition().y + playerConfig.playerMarker.getSize().y;
     float fTop = fishConfig.fish.getPosition().y;
     float fBot = fishConfig.fish.getPosition().y + fishConfig.fish.getTexture()->getSize().y; // TODO this will fail as soon as the texture isn't just so

     if ((mTop >= fTop && mTop <= fBot) || (mBot >= fTop && mBot <= fBot) || (mTop < fTop && mBot > fBot))
     {
          return true;
     }
     return false;
}

void BatchRender(sf::RenderWindow& window, vector<sf::Drawable*> drawables)
{
     for (auto i : drawables)
     {
          window.draw(*i);
     }
}
