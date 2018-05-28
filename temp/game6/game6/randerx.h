#pragma once

#include <vector>
#include <map>
#include "safetype.h"

namespace randerx
{
	#define max(a,b) (((a) > (b)) ? (a) : (b))
	#define min(a,b) (((a) < (b)) ? (a) : (b))

	// 点
 	class Pointx
	{
	public:
		Pointx();
		Pointx(Pointx &point);
		Pointx(s4 x, s4 y);
		Pointx operator+(Pointx& point);
		Pointx operator-(Pointx& point);
		bool Equals(Pointx& point);
	public:
		s4 X;
		s4 Y;
	};

	// 矩形
	class Rectx
	{
	public:
		Rectx();
		Rectx(s4 x, s4 y, s4 width, s4 height);
		Rectx* Clone();
		void GetLocation(Pointx* point);
		void GetBounds(Rectx* rect);
		s4 GetLeft();
		s4 GetTop();
		s4 GetRight();
		s4 GetBottom();
		bool IsEmptyArea();
		bool Equals(Rectx & rect);
		bool Contains(s4 x, s4 y);
		bool Contains(Pointx& pt);
		bool Contains(Rectx& rect);
		void Inflate(s4 dx, s4 dy);
		void Inflate(Pointx& point);
		bool Intersect(Rectx& rect);
		static bool Intersect(Rectx& c, Rectx& a, Rectx& b);
		bool IntersectsWith(Rectx& rect);
		static bool Union(Rectx& c, Rectx& a, Rectx& b);
		void Offset(const Pointx& point);
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

		bool LoadFromFile(ssr name, ssr file, bool reload);
		bool LoadFromBuffer(ssr name, cs1* data, u4 data_len, bool reload);

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

		Image* GetImageFromID(u4 id);
		Image* GetImageFromName(ssr name);
		u4 GetImage(ssr name);

		u4 LoadFromFile(ssr name, ssr file, bool reload);
		u4 LoadFromBuffer(ssr name, cs1* data, u4 data_len, bool reload);

	private:
		u4			m_LastID;
		ImageIDs	m_ImageIDs;
		ImageNames	m_ImageNames;
	};

	ImageMgr* GetImageMgr();

	class Layer;

	// 面板(动态图片面板)
	class Surface
	{
		friend class Layer;
	public:
		enum {
			MaxWidth = 1000
		};
		enum {
			MaxHeight = 1000
		};
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

		bool IsShow();
		void Show();
		void Hide();

		bool Resize(u4 width, u4 height);
		void Clear();
		bool LoadFromImage(u4 imageID);
		bool LoadFromImage(ssr imageAlias);

	private:
		void SetID(u4 id);
		void SetLayerID(u4 id);
		void MoveTo(s4 x, s4 y);

	protected:
		u4		m_ID;
		u4		m_LayerID;
		s4		m_PosX;
		s4		m_PosY;
		u4		m_Width;
		u4		m_Height;
		s1		*m_Data;
		ssr		m_Name;
		bool	m_Show;
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
		void	RemoveSurface(u4 id);
		void	RemoveSurface(ssr name);

		bool	MoveTo(u4 id,s4 x, s4 y);
		bool	MoveTo(ssr name, s4 x, s4 y);

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
	public:
		typedef std::map<u8, Rectx>	DirtyRects;
		enum {
			Default_Width = 82,
			Default_Height = 32,
		};
	public:
		ScreenBack();
		~ScreenBack();

		u4		GetWidth();
		u4		GetHeight();

		void	Resize(u4 width, u4 height);

		void	InsertDirtyRect(Rectx& r);
		void	InsertDirtyRect(s4 x, s4 y, s4 w, s4 h);

	private:
		void	ReleaseAll();

	private:
		u4					m_Width;
		u4					m_Height;
		s1*					m_Data;
		s1*					m_Change;
		DirtyRects			m_Rects;
	};

	// 公共屏幕备份
	ScreenBack* GetScreenBack();
};

