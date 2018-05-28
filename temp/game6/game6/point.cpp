#include "randerx.h"

using namespace randerx;

Pointx::Pointx()
{
	X = Y = 0;
}

Pointx::Pointx(Pointx &point)
{
	X = point.X;
	Y = point.Y;
}

Pointx::Pointx(s4 x, s4 y)
{
	X = x;
	Y = y;
}

Pointx Pointx::operator+(Pointx& point)
{
	return Pointx(X + point.X, Y + point.Y);
}

Pointx Pointx::operator-(Pointx& point)
{
	return Pointx(X - point.X, Y - point.Y);
}

bool Pointx::Equals(Pointx& point)
{
	return (X == point.X) && (Y == point.Y);
}

Rectx::Rectx()
{
	X = Y = Width = Height = 0;
}

Rectx::Rectx(s4 x, s4 y, s4 width, s4 height)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
}

Rectx* Rectx::Clone()
{
	return new Rectx(X, Y, Width, Height);
}

void Rectx::GetLocation(Pointx* point)
{
	point->X = X;
	point->Y = Y;
}

void Rectx::GetBounds(Rectx* rect)
{
	rect->X = X;
	rect->Y = Y;
	rect->Width = Width;
	rect->Height = Height;
}

s4 Rectx::GetLeft()
{
	return X;
}

s4 Rectx::GetTop()
{
	return Y;
}

s4 Rectx::GetRight()
{
	return X + Width;
}

s4 Rectx::GetBottom()
{
	return Y + Height;
}

bool Rectx::IsEmptyArea()
{
	return (Width <= 0) || (Height <= 0);
}

bool Rectx::Equals(Rectx & rect)
{
	return X == rect.X &&
		Y == rect.Y &&
		Width == rect.Width &&
		Height == rect.Height;
}

bool Rectx::Contains(s4 x, s4 y)
{
	return x >= X && x < X + Width &&
		y >= Y && y < Y + Height;
}

bool Rectx::Contains(Pointx& pt)
{
	return Contains(pt.X, pt.Y);
}

bool Rectx::Contains(Rectx& rect)
{
	return (X <= rect.X) && (rect.GetRight() <= GetRight()) &&
		(Y <= rect.Y) && (rect.GetBottom() <= GetBottom());
}

void Rectx::Inflate(s4 dx, s4 dy)
{
	X -= dx;
	Y -= dy;
	Width += 2 * dx;
	Height += 2 * dy;
}

void Rectx::Inflate(Pointx& point)
{
	Inflate(point.X, point.Y);
}

bool Rectx::Intersect(Rectx& rect)
{
	return Intersect(*this, *this, rect);
}

bool Rectx::Intersect(Rectx& c, Rectx& a, Rectx& b)
{
	s4 right = min(a.GetRight(), b.GetRight());
	s4 bottom = min(a.GetBottom(), b.GetBottom());
	s4 left = max(a.GetLeft(), b.GetLeft());
	s4 top = max(a.GetTop(), b.GetTop());

	c.X = left;
	c.Y = top;
	c.Width = right - left;
	c.Height = bottom - top;
	return !c.IsEmptyArea();
}

bool Rectx::IntersectsWith(Rectx& rect)
{
	return (GetLeft() < rect.GetRight() &&
		GetTop() < rect.GetBottom() &&
		GetRight() > rect.GetLeft() &&
		GetBottom() > rect.GetTop());
}

bool Rectx::Union(Rectx& c, Rectx& a, Rectx& b)
{
	s4 right = max(a.GetRight(), b.GetRight());
	s4 bottom = max(a.GetBottom(), b.GetBottom());
	s4 left = min(a.GetLeft(), b.GetLeft());
	s4 top = min(a.GetTop(), b.GetTop());

	c.X = left;
	c.Y = top;
	c.Width = right - left;
	c.Height = bottom - top;
	return !c.IsEmptyArea();
}

void Rectx::Offset(const Pointx& point)
{
	Offset(point.X, point.Y);
}

void Rectx::Offset(s4 dx, s4 dy)
{
	X += dx;
	Y += dy;
}
