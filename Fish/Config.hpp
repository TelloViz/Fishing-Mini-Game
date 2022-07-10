#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace fishConfig
{
     // RENDER WINDOW
     const int DEFAULT_WINDOW_WIDTH = 400;
     const int DEFAULT_WINDOW_HEIGHT = 600;

     const int DEFAULT_CANVAS_WIDTH = 101;
     const int DEFAULT_CANVAS_HEIGHT = 445;

     const float CANVAS_X_POS = DEFAULT_WINDOW_WIDTH / 2.0f - DEFAULT_CANVAS_WIDTH / 2.0f;
     const float CANVAS_Y_POS = DEFAULT_WINDOW_HEIGHT / 2.0f - DEFAULT_CANVAS_HEIGHT / 2.0f;

     // TIMER DURATION (SECONDS)
     sf::Time TimerDuration = sf::seconds(60.0f);

     // CENTER AXIS
     const int AXIS_WIDTH = 15;
     const int AXIS_HEIGHT = 500;

     const float AXIS_X_POS = CANVAS_X_POS + (DEFAULT_CANVAS_WIDTH / 2.0f) - (AXIS_WIDTH / 2.0f);
     const float AXIS_Y_POS = CANVAS_Y_POS + DEFAULT_CANVAS_HEIGHT / 2.0f - AXIS_HEIGHT / 2.0f;
     const sf::Color DEFAULT_AXIS_COLOR(100, 50, 50, 255);


     const int PLAYER_INDICATOR_WIDTH = 26;
     const int PLAYER_INDICATOR_HEIGHT = 75;

     const float PLAYER_X_POS = CANVAS_X_POS + 29;
     const float PLAYER_Y_POS = CANVAS_Y_POS + 25;

     const sf::Color DEFUALT_PLAYER_INDICATOR_COLOR = sf::Color(115,140,13, 255);
     const sf::Color POSITIVE_INDICATOR_COLOR{ 155,188,15, 255 };

     const int DEFAULT_FISH_WIDTH = 40;
     const int DEFAULT_FISH_HEIGHT = 15;

     const float DEFAULT_FISH_X_POS = PLAYER_X_POS+7;
     const float DEFAULT_FISH_Y_POS = 100; // TODO should be random

     const sf::Color DEFAULT_FISH_COLOR = sf::Color(0,125,125,255);


     const int MARKER_DROP_RATE = 5;
     const int MARKER_RISE_RATE = -7;

     int MarkerDropRate() { return MARKER_DROP_RATE; }
     int MarkerRiseRate() { return MARKER_RISE_RATE; }

     

     const int FRAMES_PER_FISH_POS = 300;
     int FRAMES_REMAINING = FRAMES_PER_FISH_POS;

     const int DEFAULT_TIMER_WIDTH = 5;
     const int MAX_TIMER_HEIGHT = 437;
     const int MIN_TIMER_HEIGHT = 1;

     const sf::Vector2f TIMER_MAX_POS{ 238, 84 };

     const sf::Color DEFAULT_TIMER_COLOR(155, 188, 15, 255);
}
