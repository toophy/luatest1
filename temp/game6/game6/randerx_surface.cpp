#include "randerx.h"

using namespace randerx;


Surface::Surface(u4 id) :
	m_ID(id)
{
}

Surface::~Surface()
{
}

u4 Surface::GetID()
{
	return m_ID;
}
u4 Surface::GetWidth()
{
	return m_Width;
}
u4 Surface::GetHeight()
{
	return m_Height;
}

void Surface::Resize(u4 width, u4 height)
{
}

bool Surface::LoadFromImage(u4 nImageID)
{
	return true;
}
