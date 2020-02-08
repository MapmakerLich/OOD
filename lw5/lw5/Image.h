#pragma once

#include "IImage.h"
#include <filesystem>

using namespace std;

class CImage : public IImage
{
public:
	CImage(const string& path, int width, int height)
	{
		Resize(width, height);

		if (!filesystem::exists(path))
		{
			throw runtime_error("This path does not exist");
		}

		string fileExtension = path.substr(path.size() - 4);

		if (fileExtension != ".png" && fileExtension != ".jpg")
		{
			throw runtime_error("Unknown file extension");
		}

		m_path = to_string(m_count) + fileExtension;
		filesystem::remove(m_path);
		filesystem::copy_file(path, m_path);
		m_count++;
	}
	~CImage()
	{
		filesystem::remove(m_path);
	}

	string GetPath() const override
	{
		return m_path;
	}

	int GetWidth() const override
	{
		return m_width;
	}
	int GetHeight() const override
	{
		return m_height;
	}

	void Resize(int width, int height) override 
	{
		if (width < 1 || width > 10000 || height < 1 || height > 10000)
		{
			throw runtime_error("Valid image sizes are from 1 to 10000 pixels");
		}
		m_width = width;
		m_height = height;
	}

private:
	static size_t m_count;

	string m_path;
	int m_width;
	int m_height;
};

size_t CImage::m_count = 1;