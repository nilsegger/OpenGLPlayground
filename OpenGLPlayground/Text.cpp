#include "Text.hpp"

ShaderProgram * Text::s_shader = nullptr;


Text::Text(char * text, char * fontPath, float size, glm::vec3 position, Camera * camera)
	:m_camera(camera), m_size(size), m_position(position)
{
	m_font = new Font(fontPath);
	m_font->load(true);
	m_font->create();

	setText(text);
}

Text::~Text()
{
}

void Text::setText(std::string text)
{
	clearCharacters();
	for (int i = 0; i < text.size(); i++) {
		std::vector<float> vertices;
		glm::vec4 char_coord = m_font->getTextureCoord(text.at(i));

		vertices.push_back(0.f);
		vertices.push_back(0.f);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x);
		vertices.push_back(char_coord.y);

		vertices.push_back(m_size);
		vertices.push_back(0.f);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x + char_coord.z);
		vertices.push_back(char_coord.y);

		vertices.push_back(0.f);
		vertices.push_back(m_size);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x);
		vertices.push_back(char_coord.y + char_coord.w);


		vertices.push_back(0.f);
		vertices.push_back(m_size);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x);
		vertices.push_back(char_coord.y + char_coord.w);

		vertices.push_back(m_size);
		vertices.push_back(m_size);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x + char_coord.z);
		vertices.push_back(char_coord.y + char_coord.w);

		vertices.push_back(m_size);
		vertices.push_back(0.f);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x + char_coord.z);
		vertices.push_back(char_coord.y);

		Character * new_char = new Character;
		new_char->m_offset = i * m_size;
		new_char->m_drawable = new Drawable(vertices, m_font, nullptr);

		m_characters.push_back(new_char);
	}
}

void Text::setText(char * text)
{
	setText(std::string(text));

	/*clearCharacters();
	char * c = text;
	for (int i = 0; *c; c++, i++) {
		std::vector<float> vertices;
		glm::vec4 char_coord = m_font->getTextureCoord(*c);

		vertices.push_back(0.f);
		vertices.push_back(0.f);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x);
		vertices.push_back(char_coord.y);

		vertices.push_back(m_size);
		vertices.push_back(0.f);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x + char_coord.z);
		vertices.push_back(char_coord.y);

		vertices.push_back(0.f);
		vertices.push_back(m_size);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x);
		vertices.push_back(char_coord.y + char_coord.w);

		vertices.push_back(0.f);
		vertices.push_back(m_size);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x);
		vertices.push_back(char_coord.y + char_coord.w);

		vertices.push_back(m_size);
		vertices.push_back(m_size);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x + char_coord.z);
		vertices.push_back(char_coord.y + char_coord.w);

		vertices.push_back(m_size);
		vertices.push_back(0.f);
		vertices.push_back(0.f);
		vertices.push_back(char_coord.x + char_coord.z);
		vertices.push_back(char_coord.y);

		Character * new_char = new Character;
		new_char->m_offset = i * m_size;
		new_char->m_drawable = new Drawable(vertices, m_font, nullptr);

		m_characters.push_back(new_char);
	}*/
}

void Text::setPosition(glm::vec3 position)
{
}

void Text::draw()
{
	for (unsigned int i = 0; i < unsigned int(m_characters.size()); i++) {
		m_characters[i]->m_drawable->draw(m_position + glm::vec3(m_characters[i]->m_offset, 0.f, 0.f), m_camera);
	}
}

void Text::clearCharacters()
{
	for (int i = 0; i < int(m_characters.size()); i++) {
		delete m_characters[i]->m_drawable;
		delete m_characters[i];
	}
	m_characters.clear();
}

void Text::initDefShader()
{
	s_shader = new ShaderProgram;
	s_shader->attachShader(GL_VERTEX_SHADER, PATH"/textShader.vertex");
	s_shader->attachShader(GL_FRAGMENT_SHADER ,PATH"/textShader.fragment");
	s_shader->create();
}
