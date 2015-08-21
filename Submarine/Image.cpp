#include "Image.h"


sub::Image::Image()
{
}


bool sub::Image::load(const std::string &texture)
{
	if (!m_texture.loadFromFile(texture))
		return false;

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(4);

	sf::Vector2u texSize = m_texture.getSize();

	m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(texSize.x, 0);
	m_vertices[2].position = sf::Vector2f(texSize.x, texSize.y);
	m_vertices[3].position = sf::Vector2f(0, texSize.y);

	m_vertices[0].texCoords = sf::Vector2f(0, 0);
	m_vertices[1].texCoords = sf::Vector2f(texSize.x, 0);
	m_vertices[2].texCoords = sf::Vector2f(texSize.x, texSize.y);
	m_vertices[3].texCoords = sf::Vector2f(0, texSize.y);

	//if (!sf::Shader::isAvailable()) {
	//	std::cout << "Shader not available\n";
	//	return false;
	//}

	//if (!m_shader.loadFromFile("grayscale.frag", sf::Shader::Fragment)) {
	//	std::cout << "Could not load shader\n";
	//	return false;
	//}
	//else {
	//	hasShader = true;
	//	m_shader.setParameter("color_r", 0.299);
	//	m_shader.setParameter("color_g", 0.587);
	//	m_shader.setParameter("color_b", 0.114);
	//}

	return true;
}

void sub::Image::update(float delta)
{
}

sub::Image::~Image()
{
}
