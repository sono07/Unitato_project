#include "../include/Texture.h"

Texture::Texture(const std::string& path, SDL_PixelFormat* format)
{
	SDL_Surface* textureSurface = IMG_Load(path.c_str());

	this->m_TextureSurface = SDL_ConvertSurface(textureSurface, format, 0);

	glGenTextures(1, &this->m_TextureID);
};

Texture::~Texture()
{
	SDL_FreeSurface(this->m_TextureSurface);
	glDeleteTextures(1, &this->m_TextureID);
}

void Texture::Bind() 
{
	glBindTexture(GL_TEXTURE_2D, this->m_TextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_TextureSurface->w, this->m_TextureSurface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, this->m_TextureSurface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

