#include "randerx.h"

using namespace randerx;

Image::Image(u4 id) :
	m_ID(id)
{
}

Image::~Image()
{
}

u4 Image::GetID()
{
	return m_ID;
}
u4 Image::GetWidth()
{
	return m_Width;
}
u4 Image::GetHeight()
{
	return m_Height;
}

ssr Image::GetName()
{
	return m_Alias;
}

ssr Image::GetFileName()
{
	return m_FileName;
}

bool Image::IsFromFile()
{
	return !m_FileName.empty();
}

bool Image::LoadFromFile(ssr alias, ssr file, bool reload)
{
	return true;
}

bool Image::LoadFromBuffer(ssr alias, s1* data, bool reload)
{
	return true;
}
