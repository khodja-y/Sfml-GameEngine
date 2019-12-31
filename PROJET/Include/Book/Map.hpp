#ifndef MAP_HPP
#define MAP_HPP

#include <Book/SceneNode.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>


class Map : public SceneNode
{
    public:
        explicit    Map();
                    ~Map();
                    Map(sf::VertexArray vertices, sf::Texture tileset);

        void        setVertices(sf::VertexArray vertices);
        void        setTexture(sf::Texture tileset);

        sf::VertexArray     getVertices() const;
        sf::Texture         getTileSet() const;  

        sf::FloatRect       getBoundingRect() const;
        
        bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
        
    private:
         
        

        virtual void        updateCurrent(sf::Time dt, CommandQueue& commands);
        virtual void        updateCurrent(sf::Time dt);

        virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;

};

#endif
