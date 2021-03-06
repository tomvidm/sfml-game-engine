#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "SFML/Graphics.hpp"

#include "../animation/AnimationController.h"
#include "engine/graphics/TextureManager.h"

namespace engine { namespace graphics {
    typedef unsigned int uint;

    // The Sprite class is an extension of sf::Sprite with the added
    // fuctionality implemented by AnimationController.
    // The purpose of this class is to give a simple interface for
    // creating animated sprites and switching between stored animations.
    // See AnimationController, AnimationHandler and FrameData.

    class Sprite : public sf::Sprite
    {
        public:
            Sprite();
            void update();
            void updateRect();

            void setSpriteAnimation(std::string animationName);
            void setSpriteTexture(std::string texturename);
        private:
            std::string spritename;
            animation::AnimationController animationController;

    };
}}

#endif