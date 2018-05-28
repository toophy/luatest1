#include "randerx.h"

using namespace randerx;

Layer::Layer(u4 id, ssr name)
{
	m_ID = 0;
}

Layer::~Layer()
{
}

u4		Layer::GetID()
{
	return m_ID;
}

ssr		Layer::GetName()
{
	return m_Name;
}

u4		Layer::InsertSurface(ssr name, Surface* data)
{
	return false;
}

void	Layer::RemoveSurface(u4 id)
{
	SurfaceIDs::iterator it = m_SurfaceIDs.find(id);
	if (it!=m_SurfaceIDs.end()) {
	}
}

void	Layer::RemoveSurface(ssr name)
{
	SurfaceNames::iterator it = m_SurfaceNames.find(name);
	if (it!=m_SurfaceNames.end()) {
	}
}

bool	Layer::MoveTo(u4 id, s4 x, s4 y)
{
	return true;
}
	
bool	Layer::MoveTo(ssr name, s4 x, s4 y)
{
	return true;
}

bool	Layer::ChangeZIndex(u4 id)
{
	return true;
}

bool	Layer::ChangeZIndex(ssr name)
{
	return true;
}
