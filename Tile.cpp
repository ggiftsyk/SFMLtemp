#include "Tile.h"

Tile::Tile(Texture& texture_sheet, IntRect texture_rect, bool damaging)
	: damaging(damaging)
{
	this->sprite.setTexture(texture_sheet);
	this->sprite.setTextureRect(texture_rect);
}

const FloatRect Tile::getGobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Tile::update()
{
}

void Tile::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
