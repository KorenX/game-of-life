#pragma once

#include <windows.h>

#include "IScreen.h"

template <size_t pixel_size>
class CMDScreen : public IScreen
{
public:
	/**
	* @brief A screen that allows printing into the CMD
	*/
	CMDScreen();

	/**
	* see 'IScreen.h' for doc
	*/
	void SetPixel(size_t i, size_t j, COLORREF color) override;
	
	/**
	* see 'IScreen.h' for doc
	*/
	void Refresh() override;

private:
	HDC m_hdc;

	static constexpr size_t X_OFFSET = 50;
	static constexpr size_t Y_OFFSET = 50;
};

template <size_t pixel_size>
CMDScreen<pixel_size>::CMDScreen()
{
	m_hdc = GetDC(GetConsoleWindow());
}

template <size_t pixel_size>
void CMDScreen<pixel_size>::SetPixel(size_t i, size_t j, COLORREF color)
{
	for (size_t x = i * pixel_size; x < (i + 1) * pixel_size; x++)
	{
		for (size_t y = j * pixel_size; y < (j + 1) * pixel_size; y++)
		{
			::SetPixel(m_hdc, X_OFFSET + x, Y_OFFSET + y, color);
		}
	}
}

template <size_t pixel_size>
void CMDScreen<pixel_size>::Refresh()
{
	return;
}