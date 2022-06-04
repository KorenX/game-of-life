#pragma once

#include <stddef.h>
#include <memory.h>

#include "IScreen.h"


/**
* @param x	the amount of cells in the x axis
* @param y	the amount of cells in the y axis
*/
template <size_t x, size_t y>
class GameOfLife
{
public:

	/**
	* @brief simulates Conway's Game of Life
	* 
	* @param initial_state		the state of the population in the beginning of the simulation
	* @param screen				the screen interface to which the changes in the population will be printed
	*/
	GameOfLife(bool(&initial_state)[x][y], IScreen& screen);

	/**
	* @brief prints the current generation of the simulation, and generates the next one.
	* 
	* @returns true if it is the final generation (the next generation is the same), false otherwise
	*/
	bool ShowGeneration();

	/**
	* @brief sets the screen to black
	*/
	void ClearScreen();
private:

	/**
	* @brief generates the next generation by Conway's algorithm.
	*
	* @returns true if it is the final generation (the next generation is the same), false otherwise
	*/
	bool GenerateNextGeneration();

	/**
	* @brief checks if the cell will be alive or dead in the next generation
	* 
	* @param i		the x axis index
	* @param j		the y axis index
	* 
	* @returns true if alive, false otherwise
	*/
	bool GetNewCellValue(size_t i, size_t j);
	
	/**
	* @brief counts the amount of alive neighbor cells	
	* 
	* @param i		the x axis index
	* @param j		the y axis index
	* 
	* @returns the amount of alive neighbor cells
	*/
	size_t GetNeighboringPositives(size_t i, size_t j);

	bool m_state[x][y];
	IScreen& m_screen;

	static constexpr COLORREF WHITE = RGB(255, 255, 255);
	static constexpr COLORREF BLACK = RGB(0, 0, 0);

	static constexpr size_t UNDER_POPULATION_THRESHOLD = 2;
	static constexpr size_t OVER_POPULATION_THRESHOLD = 3;
	static constexpr size_t REPRODUCTION_THRESHOLD = 3;

};

template <size_t x, size_t y>
GameOfLife<x, y>::GameOfLife(bool(&initial_state)[x][y], IScreen& screen) : m_screen(screen)
{
	memcpy(m_state, initial_state, sizeof(m_state));
}

template <size_t x, size_t y>
bool GameOfLife<x, y>::ShowGeneration()
{
	for (size_t i = 0; i < x; i++)
	{
		for (size_t j = 0; j < y; j++)
		{
			m_screen.SetPixel(i, j, m_state[i][j] ? WHITE : BLACK);
		}
	}

	m_screen.Refresh();
	return GenerateNextGeneration();
}

template <size_t x, size_t y>
bool GameOfLife<x, y>::GenerateNextGeneration()
{
	bool new_state[x][y] = {};

	for (size_t i = 0; i < x; i++)
	{
		for (size_t j = 0; j < y; j++)
		{
			new_state[i][j] = GetNewCellValue(i, j);
		}
	}

	if (memcmp(m_state, new_state, sizeof(m_state)) == 0)
	{
		return true;
	}

	memcpy(m_state, new_state, sizeof(m_state));
	return false;
}

template <size_t x, size_t y>
bool GameOfLife<x, y>::GetNewCellValue(size_t i, size_t j)
{
	size_t neighbors = GetNeighboringPositives(i, j);

	// over or under population
	if (neighbors < UNDER_POPULATION_THRESHOLD || neighbors > OVER_POPULATION_THRESHOLD)
	{
		return false;
	}

	// if there are not enough neighbors, dead stays dead
	if (!m_state[i][j] && neighbors != REPRODUCTION_THRESHOLD)
	{
		return false;
	}

	return true;
}

template <size_t x, size_t y>
size_t GameOfLife<x, y>::GetNeighboringPositives(size_t i, size_t j)
{
	size_t positives_counter = 0;

	for (size_t leftmost = i + x - 1; leftmost <= i + x + 1; leftmost++)
	{
		for (size_t upmost = j + y - 1; upmost <= j + y + 1; upmost++)
		{
			size_t actual_x = leftmost % x;
			size_t actual_y = upmost % y;

			if (!(i == actual_x && j == actual_y))
			{
				positives_counter += m_state[actual_x][actual_y] ? 1 : 0;
			}
		}
	}

	return positives_counter;
}

template <size_t x, size_t y>
void GameOfLife<x, y>::ClearScreen()
{
	for (size_t i = 0; i < x; i++)
	{
		for (size_t j = 0; j < y; j++)
		{
			m_screen.SetPixel(i, j, BLACK);
		}
	}
}
