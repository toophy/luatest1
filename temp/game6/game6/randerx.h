#pragma once

#include <vector>
#include <map>
#include "safetype.h"

namespace randerx
{
	#define max(a,b) (((a) > (b)) ? (a) : (b))
	#define min(a,b) (((a) < (b)) ? (a) : (b))

	// 点
 	class Point
	{
	public:
		Point();
		Point(Point &point);
		Point(s4 x, s4 y);
		Point operator+(Point& point);
		Point operator-(Point& point);
		bool Equals(Point& point);
	public:
		s4 X;
		s4 Y;
	};

	// 矩形
	class Rect
	{
	public:
		Rect();
		Rect(s4 x, s4 y, s4 width, s4 height);
		Rect* Clone();
		void GetLocation(Point* point);
		void GetBounds(Rect* rect);
		s4 GetLeft();
		s4 GetTop();
		s4 GetRight();
		s4 GetBottom();
		bool IsEmptyArea();
		bool Equals(Rect & rect);
		bool Contains(s4 x, s4 y);
		bool Contains(Point& pt);
		bool Contains(Rect& rect);
		void Inflate(s4 dx, s4 dy);
		void Inflate(Point& point);
		bool Intersect(Rect& rect);
		static bool Intersect(Rect& c, Rect& a, Rect& b);
		bool IntersectsWith(Rect& rect);
		static bool Union(Rect& c, Rect& a, Rect& b);
		void Offset(const Point& point);
		void Offset(s4 dx, s4 dy);
	public:
		s4 X;
		s4 Y;
		s4 Width;
		s4 Height;
	};

	// 静态图片资源
	class Image
	{
	public:
		Image(u4 id);
		~Image();

		u4 GetID();
		u4 GetWidth();
		u4 GetHeight();

		ssr GetName();
		ssr GetFileName();

		bool IsFromFile();

		bool LoadFromFile(ssr alias, ssr file, bool reload);
		bool LoadFromBuffer(ssr alias, s1* data, bool reload);

	protected:
		u4		m_ID;
		u4		m_Width;
		u4		m_Height;
		vs1		m_Data;
		ssr		m_Name;
		ssr		m_FileName;
	};

	// 图片资源管理
	class ImageMgr
	{
		typedef std::map<u4, Image*>	ImageIDs;
		typedef std::map<ssr, Image*>	ImageNames;
	public:
		ImageMgr();
		~ImageMgr();

		u4 GetImage(ssr alias);

		u4 LoadFromFile(ssr alias, ssr file, bool reload);
		u4 LoadFromBuffer(ssr alias, vs1& data, bool reload);

	private:
		u4			m_LastID;
		ImageIDs	m_ImageIDs;
		ImageNames	m_ImageNames;
	};

	class Layer;

	// 面板(动态图片面板)
	class Surface
	{
		friend class Layer;
	public:
		Surface();
		~Surface();

		u4	GetID();
		u4	GetLayerID();

		ssr	GetName();

		s4	GetPosX();
		s4	GetPosY();
		u4	GetWidth();
		u4	GetHeight();

		void Resize(u4 width, u4 height);
		bool LoadFromImage(u4 imageID);
		bool LoadFromImage(ssr imageAlias);

	private:
		void SetID(u4 id);
		void SetLayerID(u4 id);
		void MoveTo(u4 x, u4 y);

	protected:
		u4		m_ID;
		u4		m_LayerID;
		s4		m_PosX;
		s4		m_PosY;
		u4		m_Width;
		u4		m_Height;
		vs1		m_Data;
		ssr		m_Name;
	};

	// 动态图片分层管理
	class Layer
	{
		typedef	std::map<u4, Surface*>	SurfaceIDs;
		typedef std::map<ssr, Surface*>	SurfaceNames;
	public:
		Layer(u4 id, ssr name);
		~Layer();

		u4		GetID();
		ssr		GetName();

		u4		InsertSurface(ssr name,Surface* data);
		bool	RemoveSurface(u4 id);
		bool	RemoveSurface(ssr name);

		bool	MoveTo(u4 id,u4 x, u4 y);
		bool	MoveTo(ssr name, u4 x, u4 y);

		bool	ChangeZIndex(u4 id);
		bool	ChangeZIndex(ssr name);

	protected:

	private:
		u4				m_ID;
		ssr				m_Name;
		SurfaceIDs		m_SurfaceIDs;
		SurfaceNames	m_SurfaceNames;
	};

	// 屏幕备份, 脏矩形产地
	class ScreenBack
	{
		typedef std::map<u8, Rect>	DirtyRects;
	public:
		ScreenBack();

		~ScreenBack();

		void	InsertDirtyRect(Rect& r);
		void	InsertDirtyRect(s4 x, s4 y, u4 w, u4 h);

	private:
		DirtyRects			m_Rects;
	};
}
