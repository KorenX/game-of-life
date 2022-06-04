#include "GameOfLife.h"
#include "CMDScreen.h"
#include <time.h>
#include <random>
#include <stdio.h>

bool random_bool()
{
	return (rand()%2) > 0;
}

int main()
{
	srand(time(0));
	static constexpr size_t MATRIX_DIM = 25;
	static constexpr size_t PIXEL_SIZE = 5;
	static constexpr size_t GENERATIONAL_INTERVAL = 500; // half a second

	bool initial[MATRIX_DIM][MATRIX_DIM];
	bool final_gen = false;

	for (size_t i = 0; i < MATRIX_DIM; i++)
	{
		for (size_t j = 0; j < MATRIX_DIM; j++)
		{
			initial[i][j] = random_bool();
		}
	}

	CMDScreen<PIXEL_SIZE> screen;
	GameOfLife<MATRIX_DIM, MATRIX_DIM> gol(initial, screen);

	gol.ClearScreen();

	while (!final_gen)
	{
		final_gen = gol.ShowGeneration();
		Sleep(GENERATIONAL_INTERVAL);
	}

	printf("finished running!\n");
	getchar();
}

