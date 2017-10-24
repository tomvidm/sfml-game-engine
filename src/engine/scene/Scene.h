#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "SFML/Graphics.hpp"

#include "../Directories.h"

#include "engine/gameobject/Entity.h"
#include "engine/graphics/Sprite.h"
#include "engine/graphics/Tilemap.h"
#include "engine/lua/LuaHelpers.h"
#include "engine/gui/Widget.h"
#include "engine/graphics/BeamEffect.h"
#include "engine/graphics/ParticleArray.h"

extern "C" 
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include "selene.h"

namespace engine { namespace scene {

    // This class holds all the objects of a scene.

    class Scene 
    {
    public:
        Scene();
        void update();
        void render(sf::RenderWindow* window);

        inline graphics::Sprite& getSprite(int index) { return sprites[index]; }
    private:
        std::vector<gameobject::Entity> entities;
        std::vector<graphics::Sprite> sprites;

        sf::RectangleShape measureRect;
        graphics::Tilemap tmap;
        gui::Widget widget;
        graphics::BeamEffect beam;
        graphics::ParticleArray parr;


    };
}}

#endif