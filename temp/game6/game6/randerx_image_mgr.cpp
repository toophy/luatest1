#include "randerx.h"

using namespace randerx;

ImageMgr g_ImageMgr;

ImageMgr* randerx::GetImageMgr()
{
	return &g_ImageMgr;
}

ImageMgr::ImageMgr()
{
}

ImageMgr::~ImageMgr()
{
}

Image* ImageMgr::GetImageFromID(u4 id)
{
	ImageIDs::iterator it = m_ImageIDs.find(id);
	if (it!=m_ImageIDs.end()) {
		return it->second;
	}
	return NULL;
}

Image* ImageMgr::GetImageFromName(ssr name)
{
	ImageNames::iterator it = m_ImageNames.find(name);
	if (it!=m_ImageNames.end()) {
		return it->second;
	}
	return NULL;
}

u4 ImageMgr::GetImage(ssr name)
{
	ImageNames::iterator it = m_ImageNames.find(name);
	if (it != m_ImageNames.end()) {
		return it->second->GetID();
	}
	return 0;
}

u4 ImageMgr::LoadFromFile(ssr name, ssr file, bool reload)
{
	u4 id = GetImage(name);
	if (id == 0){
		++m_LastID;
		Image* newImage = new(std::nothrow) Image(m_LastID);
		if (newImage == nullptr) {
			--m_LastID;
			return id;
		}
		if (!newImage->LoadFromFile(name, file, reload)){
			delete newImage;
			--m_LastID;
			return id;
		}
		id = newImage->GetID();
		m_ImageIDs.insert(ImageIDs::value_type(newImage->GetID(), newImage));
		m_ImageNames.insert(ImageNames::value_type(newImage->GetName(), newImage));
	}

	return id;
}

u4 ImageMgr::LoadFromBuffer(ssr name, cs1* data, u4 data_len, bool reload)
{
	u4 id = GetImage(name);
	if (id == 0){
		++m_LastID;
		Image* newImage = new(std::nothrow) Image(m_LastID);
		if (newImage==nullptr) {
			--m_LastID;
			return id;
		}
		if (!newImage->LoadFromBuffer(name, data, data_len, reload)){
			delete newImage;
			--m_LastID;
			return id;
		}
		id = newImage->GetID();
		m_ImageIDs.insert(ImageIDs::value_type(newImage->GetID(), newImage));
		m_ImageNames.insert(ImageNames::value_type(newImage->GetName(), newImage));
	}

	return id;
}

