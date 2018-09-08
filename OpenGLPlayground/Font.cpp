#include "Font.hpp"

Font::Font(char * path, short cellSizeX, short cellSizeY)
	:Texture(path), m_cellSizeX(cellSizeX), m_cellSizeY(cellSizeY)
{

}

Font::~Font()
{
}

glm::vec4 Font::getTextureCoord(char c)
{

	if ((c >= 32 && c <= 95) == false) return getTextureCoord('?');
	return m_character_coord.find(c)->second;
}

bool Font::load(bool flipFont)
{
	if (!Texture::load(flipFont)) return false;
	float w, h;
	w = 1.f / width * m_cellSizeX;
	h = 1.f / height * m_cellSizeY;
	short x = 0, y = 0;
	for (char c = 32; c <= 95; c++) {

		if(!flipFont) m_character_coord.insert(std::make_pair(c, glm::vec4(float(1.f / width * x), float(1.f / height * y), w, h)));
		else m_character_coord.insert(std::make_pair(c, glm::vec4(float(1.f / width * x), float(height - (1.f / height * y) - h), w, h)));

		x += m_cellSizeX;
		if (x >= width) {
			x = 0;
			y += m_cellSizeY;
		}
	}

	return true;
}


short Font::getCellSizeX() const
{
	return m_cellSizeX;
}

short Font::getCellSizeY() const
{
	return m_cellSizeY;
}
