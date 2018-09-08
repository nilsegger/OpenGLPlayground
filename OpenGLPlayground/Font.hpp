#pragma once
#include "Texture.hpp"
#include <map>
#include <glm.hpp>

//This class only support bitmap fonts

class Font :
	public Texture
{
public:
	Font() = delete;
	Font(char * path, short cellSizeX = 32, short cellSizeY = 32);
	~Font();

	//getSizeOf(Char);

	glm::vec4 getTextureCoord(char c);

	bool load(bool flipFont = false) override;

	short getCellSizeX() const;
	short getCellSizeY() const;
private:
	short m_cellSizeX;
	short m_cellSizeY;
	
	std::map<char, glm::vec4> m_character_coord;
};

