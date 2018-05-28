#include "randerx.h"

using namespace randerx;

ScreenBack g_ScreenBack;

ScreenBack* GetScreenBack()
{
	return &g_ScreenBack;
}

ScreenBack::ScreenBack()
{
	m_Width		= Default_Width;
	m_Height	= Default_Height;
	m_Data		= new s1[m_Width*m_Height];
	m_Change	= new s1[m_Width*m_Height];
}

ScreenBack::~ScreenBack()
{
	ReleaseAll();
}

u4		ScreenBack::GetWidth()
{
	return m_Width;
}

u4		ScreenBack::GetHeight()
{
	return m_Height;
}

void	ScreenBack::ReleaseAll()
{
	m_Width = 0;
	m_Height = 0;
	if (m_Data != NULL) {
		delete[]m_Data;
		m_Data = NULL;
	}
	if (m_Change != NULL) {
		delete[]m_Change;
		m_Change = NULL;
	}
}

void	ScreenBack::Resize(u4 width, u4 height)
{
	if (width<1 || height<1) {
		return;
	}

	ReleaseAll();

	m_Width		= width;
	m_Height	= height;
	m_Data		= new s1[m_Width*m_Height];
	m_Change	= new s1[m_Width*m_Height];
}

s8	MakeS8(s2 a, s2 b, s2 c, s2 d)
{
	s8 x = 0;
	x = s8(a) << 48 | s8(b) << 32 | s8(c) << 16 | s8(d);
	return x;
}

void	ScreenBack::InsertDirtyRect(Rectx& r)
{
	if (r.Width < 1 || r.Height < 1) {
		return;
	}

	s8 key = MakeS8(s2(r.Width), s2(r.Height), s2(r.X), s2(r.Y));
	DirtyRects::iterator it = m_Rects.find(key);
	if (it==m_Rects.end()) {
		m_Rects.insert(DirtyRects::value_type(key, r));
	}
}

void	ScreenBack::InsertDirtyRect(s4 x, s4 y, s4 w, s4 h)
{
	if (w<1||h<1) {
		return;
	}

	s8 key = MakeS8(w,h,x,y);
	DirtyRects::iterator it = m_Rects.find(key);
	if (it == m_Rects.end()) {
		Rectx x(x, y, w, h);
		m_Rects.insert(DirtyRects::value_type(key, x));
	}
}

