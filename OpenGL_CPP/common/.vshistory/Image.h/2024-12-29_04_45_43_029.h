﻿#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <string>

class Image
{
private:
	int m_width;
	int m_height;
	int m_channels;

	uint8_t* m_pixels;
public:
	Image(const std::string& filename)
	{
		
	}
	
};

#endif