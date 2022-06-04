#pragma once

#include <stddef.h>
#include <wtypes.h>

class IScreen
{
public:

	/**
	* @brief print a pixel to the screen buffer
	* 
	* @param i		the x axis index
	* @param j		the y axis index
	* @param color	the color to set to the pixel
	*/
	virtual void SetPixel(size_t i, size_t j, COLORREF color) = 0;

	/**
	* @brief flushes the screen buffer to the actual screen, if relevant
	*/
	virtual void Refresh() = 0;
};

