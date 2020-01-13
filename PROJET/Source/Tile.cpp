#include <Book/Tile.hpp>

//Tile Constructor
Tile::Tile(sf::Texture *tex, sf::Vector2f pos) {
	mTexture = tex;
	mVertices = sf::VertexArray(sf::Quads, 4);
	mVertices[0].texCoords = { 0 , 0 };
	mVertices[1].texCoords = { 32 , 0 };
	mVertices[2].texCoords = { 32 , 32 };
	mVertices[3].texCoords = { 0 , 32 };
	
	mVertices[0].position = { getPosition().x , getPosition().y };
	mVertices[1].position = { getPosition().x + 32 , getPosition().y };
	mVertices[2].position = { getPosition().x + 32 , getPosition().y + 32 };
	mVertices[3].position = { getPosition().x , getPosition().y + 32 };
	setPosition(pos);
}

//Draw method
void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform = getTransform();
	states.texture = mTexture;
	target.draw(mVertices, states);
}