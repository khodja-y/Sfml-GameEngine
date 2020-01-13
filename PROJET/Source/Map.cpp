#include <Book/Map.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

Map::Map(){

}

Map::~Map(){

}

Map::Map(sf::VertexArray vertices, sf::Texture tileset)
: m_vertices(vertices)
, m_tileset(tileset)
{
    
}

sf::VertexArray Map::getVertices() const
{
    return m_vertices;
}

sf::Texture Map::getTileSet() const
{
    return m_tileset;
}

sf::FloatRect Map::getBoundingRect() const
{
   
    return getWorldTransform().transformRect(m_vertices.getBounds());
}

bool Map::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height){
    // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = height / 2; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    sf::Sprite sp;
    

    // draw the vertex array
    target.draw(m_vertices, states);
    
}

void Map::updateCurrent(sf::Time dt, CommandQueue& commands)
{	
}

void Map::updateCurrent(sf::Time dt)
{
}

void Map::setVertices(sf::VertexArray vertices)
{
    m_vertices = vertices;
}

void Map::setTexture(sf::Texture tileset)
{
    m_tileset = tileset;
}