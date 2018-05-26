#include "randerx.h"

using namespace randerx;

// µã
class Point
{
public:
	Point()
	{
		X = Y = 0;
	}

	Point(Point &point)
	{
		X = point.X;
		Y = point.Y;
	}

	Point(s4 x, s4 y)
	{
		X = x;
		Y = y;
	}

	Point operator+(Point& point)
	{
		return Point(X + point.X, Y + point.Y);
	}

	Point operator-(Point& point)
	{
		return Point(X - point.X, Y - point.Y);
	}

	bool Equals(Point& point)
	{
		return (X == point.X) && (Y == point.Y);
	}

public:

	s4 X;
	s4 Y;
};

// ¾ØÐÎ
class Rect
{
public:

	Rect()
	{
		X = Y = Width = Height = 0;
	}

	Rect(s4 x, s4 y, s4 width, s4 height)
	{
		X = x;
		Y = y;
		Width = width;
		Height = height;
	}

	Rect* Clone()
	{
		return new Rect(X, Y, Width, Height);
	}

	void GetLocation(Point* point)
	{
		point->X = X;
		point->Y = Y;
	}

	void GetBounds(Rect* rect)
	{
		rect->X = X;
		rect->Y = Y;
		rect->Width = Width;
		rect->Height = Height;
	}

	s4 GetLeft()
	{
		return X;
	}

	s4 GetTop()
	{
		return Y;
	}

	s4 GetRight()
	{
		return X + Width;
	}

	s4 GetBottom()
	{
		return Y + Height;
	}

	bool IsEmptyArea()
	{
		return (Width <= 0) || (Height <= 0);
	}

	bool Equals(Rect & rect)
	{
		return X == rect.X &&
			Y == rect.Y &&
			Width == rect.Width &&
			Height == rect.Height;
	}

	bool Contains(s4 x, s4 y)
	{
		return x >= X && x < X + Width &&
			y >= Y && y < Y + Height;
	}

	bool Contains(Point& pt)
	{
		return Contains(pt.X, pt.Y);
	}

	bool Contains(Rect& rect)
	{
		return (X <= rect.X) && (rect.GetRight() <= GetRight()) &&
			(Y <= rect.Y) && (rect.GetBottom() <= GetBottom());
	}

	void Inflate(s4 dx, s4 dy)
	{
		X -= dx;
		Y -= dy;
		Width += 2 * dx;
		Height += 2 * dy;
	}

	void Inflate(Point& point)
	{
		Inflate(point.X, point.Y);
	}

	bool Intersect(Rect& rect)
	{
		return Intersect(*this, *this, rect);
	}

	static bool Intersect(Rect& c, Rect& a, Rect& b)
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

	bool IntersectsWith(Rect& rect)
	{
		return (GetLeft() < rect.GetRight() &&
			GetTop() < rect.GetBottom() &&
			GetRight() > rect.GetLeft() &&
			GetBottom() > rect.GetTop());
	}

	static bool Union(Rect& c, Rect& a, Rect& b)
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

	void Offset(const Point& point)
	{
		Offset(point.X, point.Y);
	}

	void Offset(s4 dx, s4 dy)
	{
		X += dx;
		Y += dy;
	}

public:
	s4 X;
	s4 Y;
	s4 Width;
	s4 Height;
};
