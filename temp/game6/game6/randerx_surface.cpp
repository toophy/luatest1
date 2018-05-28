#include "randerx.h"

using namespace randerx;


Surface::Surface()
{
	m_ID		= 0;
	m_LayerID	= 0;
	m_PosX		= 0;
	m_PosY		= 0;
	m_Width		= 0;
	m_Height	= 0;
	m_Data		= NULL;
	m_Show		= true;
}

Surface::~Surface()
{
	if (m_Data!=NULL) {
		delete []m_Data;
		m_Data = NULL;
	}
	m_ID = 0;
	m_LayerID = 0;
	m_PosX = 0;
	m_PosY = 0;
	m_Width = 0;
	m_Height = 0;
	m_Show = true;
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
bool Surface::IsShow()
{
	return m_Show;
}
void Surface::Show()
{
	m_Show = true;
}
void Surface::Hide()
{
	m_Show = false;
}
bool Surface::Resize(u4 width, u4 height)
{
	if (width<1 || height<1 || width>MaxWidth || height>MaxHeight) {
		return false;
	}
	if (width==m_Width && height==m_Height) {
		return true;
	}

	if (m_Data != NULL) {
		GetScreenBack()->InsertDirtyRect(m_PosX, m_PosY, m_Width, m_Height);

		delete[]m_Data;
		m_Data		= NULL;
		m_Width		= 0;
		m_Height	= 0;
	}
	
	m_Width		= width;
	m_Height	= height;
	m_Data		= new s1[m_Width*m_Height];
	memset(m_Data, 0, m_Width*m_Height);

	GetScreenBack()->InsertDirtyRect(m_PosX, m_PosY, m_Width, m_Height);
}

void Surface::Clear()
{
	if (m_Data!=NULL&&m_Width>0&&m_Height>0) {
		memset(m_Data, 0, m_Width*m_Height);
	}
}

bool Surface::LoadFromImage(u4 imageID)
{
	return true;
}

bool Surface::LoadFromImage(ssr imageAlias)
{
	return true;
}

void Surface::SetID(u4 id)
{
	m_ID = id;
}

void Surface::SetLayerID(u4 id)
{
	m_LayerID = id;
}

void Surface::MoveTo(s4 x, s4 y)
{
	// 移动之后, 两个矩形增加到脏矩形
	if (m_PosX != x || m_PosY != y) {
		GetScreenBack()->InsertDirtyRect(m_PosX, m_PosX, m_Width, m_Height);
		GetScreenBack()->InsertDirtyRect(x, y, m_Width, m_Height);
		m_PosX = x;
		m_PosY = y;
	}
}

