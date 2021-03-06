#ifndef MOUSE_H
#define MOUSE_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

namespace engine { namespace input {
    enum MouseEvent : int
    {
        NONE, LEFT_CLICKED, LEFT_RELEASED,
        RIGHT_CLICKED, RIGHT_RELEASED
    };

    // This is a wrapper for mouse input. The purpose of this
    // is for simplifying the detection of single/double click or hold,
    // and getting relative mouse position by requiring the user
    // to set a window context.

    class Mouse 
    {
    public:
        static void setWindowContext(sf::RenderWindow& window);

        static inline sf::Vector2i getMousePos() 
        { 
            return sf::Mouse::getPosition(*windowContext); 
        }

        static inline sf::Vector2f getMouseFloatPos(bool worldCoords = false) 
        { 
            sf::Vector2i mpos = sf::Mouse::getPosition(*windowContext);
            if (worldCoords)
            {
                return sf::Vector2f(static_cast<float>(mpos.x), static_cast<float>(mpos.y));
            }
            else
            {
                return windowContext->mapPixelToCoords(mpos);
            }
        }

        static inline sf::Vector2f getPositionOnLeftPress()
        {
            return leftPressPosition;
        }

        static bool isLeftHold();
        static bool isRightHold();
        static bool isLeftClick(sf::Event& event);
        static bool isRightClick(sf::Event& event);

        static void registerButtonPressEvent(sf::Event& event);
        static MouseEvent returnMouseEventOnRelease(sf::Event& event);
    private:
        static sf::RenderWindow* windowContext;

        static sf::Vector2f leftPressPosition;
        static sf::Vector2f rightPressPosition;

        static bool leftIsPressed;
        static bool rightIsPressed;

        static sf::Clock leftHoldTimer;
        static sf::Clock rightHoldTimer;

        static sf::Time leftClickTimeThreshold;
        static sf::Time rightClickTimeThreshold;
        
        //static bool leftHold();
        //static bool rightHold();
    };
}}

#endif
