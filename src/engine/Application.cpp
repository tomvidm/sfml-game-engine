#include "Application.h"

#include "AnimatedSprite.h"
#include "SpriteAnimation.h"

namespace engine {
    void Application::enterLoop() {
        loadConfiguration();
        window.create(sf::VideoMode(screenWidth, screenHeight), "myproject");
        maxFramePeriod = 16667;
        varr.addVector(sf::Vector2f(100, 100), sf::Vector2f(400, 100));
        while (window.isOpen())
        {
            loop();
        }
    }

    void Application::loop() {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }

        if (mainClock.getElapsedTime().asMicroseconds() > maxFramePeriod)
        {
            mainClock.restart();
            window.clear();
            drawSprites();
            window.display();
        }
    }

    void Application::drawSprites()
    {
        for (uint i = 0; i < spritePool.getFirstFreeIndex(); i++)
        {
            if (spritePool.getState(i) & ACTIVE == ACTIVE)
            {
                spritePool.get(i).update();
                window.draw(spritePool.get(i));
            }
        }
        window.draw(varr);
    }

    void Application::loadConfiguration()
    {
        luaState.Load("../../src/engine/conf.lua");
        screenWidth = static_cast<int>(luaState["configuration"]["screenWidth"]);
        screenHeight = static_cast<int>(luaState["configuration"]["screenHeight"]);
        return; // Use Lua to load basic configuration such as window size etc
    }

    // Test function. Load texture, assign it to a spriteAnimation.
    // Add frames and hope it works. And of course, push it to the spriteVector.
    void Application::testAnimation()
    {
        //graphics::AnimatedSprite sprite = makeTestSprite();
        spritePool.pushObject(makeTestSprite());
        
    }

    graphics::AnimatedSprite Application::makeTestSprite()
    {
        textureHandler.loadFromFile("../../resources/images/testsprite.png", "testsprite");
        graphics::AnimatedSprite sprite;
        sprite.setTexture(textureHandler.get("testsprite"));
        graphics::SpriteAnimation anim;
        graphics::Frame frame;
        frame.duration = 50*1667;
        frame.texRect = sf::Rect<int>(sf::Vector2i(0, 0), sf::Vector2i(184, 375));
        anim.addFrame(frame);
        frame.texRect = sf::Rect<int>(sf::Vector2i(184, 0), sf::Vector2i(184, 375));
        anim.addFrame(frame);
        frame.texRect = sf::Rect<int>(sf::Vector2i(184*2, 0), sf::Vector2i(184, 375));
        anim.addFrame(frame);
        frame.texRect = sf::Rect<int>(sf::Vector2i(184*3, 0), sf::Vector2i(184, 375));
        anim.addFrame(frame);
        frame.texRect = sf::Rect<int>(sf::Vector2i(184*4, 0), sf::Vector2i(184, 375));
        anim.addFrame(frame);
        frame.texRect = sf::Rect<int>(sf::Vector2i(184*5, 0), sf::Vector2i(184, 375));
        anim.addFrame(frame);
        frame.texRect = sf::Rect<int>(sf::Vector2i(184*6, 0), sf::Vector2i(184, 375));
        anim.addFrame(frame);
        frame.texRect = sf::Rect<int>(sf::Vector2i(184*7, 0), sf::Vector2i(184, 375));
        anim.addFrame(frame);
        sprite.setAnimation(anim);
        return sprite;
    }
}


    