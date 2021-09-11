#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>

#include <string>

class Texture 
{
private:
	SDL_Surface* m_TextureSurface = nullptr;
	unsigned int m_TextureID;
public:
	/// <summary>
	/// Instantiates a Texture object
	/// </summary>
	/// <param name="path">| Relative or absolute path to the .PNG texture file</param>
	/// <param name="format">| Format of the screen obtained from an SDL_Surface object through the format member</param>
	Texture(const std::string& path, SDL_PixelFormat* format);

	/// <summary>
	/// Destroys a Texture object by freeing its container and deleting its ID
	/// </summary>
	~Texture();

	/// <summary>
	/// Calls OpenGL specifing functions to bind texture to the drawing API, all draw calls following Bind will use the texture in its calls
	/// </summary>
	void Bind();
};