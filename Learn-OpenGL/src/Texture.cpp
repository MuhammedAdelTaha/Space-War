#include "Texture.h"
#include "Debugger.h"
#include "stb_image/stb_image.h"

Texture::Texture(const string& filePath) : m_FilePath(filePath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glCall(glGenTextures(1, &m_RendererId));
	glCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));

	// always done
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	glCall(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

void Texture::bind(unsigned int slot) const
{
	glCall(glActiveTexture(GL_TEXTURE0 + slot));
	glCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

void Texture::unbind() const
{
	glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::deleteTexture() const
{
	glCall(glDeleteTextures(1, &m_RendererId));
}
