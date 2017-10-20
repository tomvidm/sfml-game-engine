#pragma once

#include <cmath>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "../Utility.h"
#include "engine/input/Mouse.h"

namespace engine {
namespace graphics {

    class Tilemap : public sf::Drawable, public sf::Transformable
    {
    public:
        Tilemap();
        void setSize(int u, int v);
        void setTileSize(sf::Vector2f& size);
        void allocateVertices();
        void allocateVerticesOrdered();
        void setTilePlacement(int u, int v, sf::Vertex* quad);
        sf::CircleShape c;
        void update(sf::Window* window);
        //void setTexture(sf::Texture& tex);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        inline void setGridVisibility(const bool& showOrNot) { showGrid = showOrNot; }
        inline bool gridIsVisible() const { return showGrid; }

        sf::Vector2i getMouseOverVector(sf::Window* window) const;
    private:
        bool showGrid;
        int usize;
        int vsize;
        const sf::Vector2f uVector = 32.f*sf::Vector2f(1.f, 0.5f);
        const sf::Vector2f vVector = 32.f*sf::Vector2f(-1.f, 0.5f);

        sf::Vector2f tileSize;

        sf::Texture* texturePtr;
        sf::VertexArray varr;
        sf::VertexArray grid;
    };

}
}