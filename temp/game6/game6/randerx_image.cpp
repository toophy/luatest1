#include "randerx.h"
#include <sstream>
#include <iostream>

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
	return m_Name;
}

ssr Image::GetFileName()
{
	return m_FileName;
}

bool Image::IsFromFile()
{
	return !m_FileName.empty();
}

bool Image::LoadFromFile(ssr name, ssr file, bool reload)
{
	return true;
}

bool Image::LoadFromBuffer(ssr name, cs1* data, u4 data_len, bool reload)
{
	s1 buff[128];
	std::istringstream istr(data);
	while (istr.getline(buff, sizeof(buff), '\n')){
		std::cout << buff << std::endl;
	}

	// ¡õ
	// ¡î
	// 
	return true;
}
