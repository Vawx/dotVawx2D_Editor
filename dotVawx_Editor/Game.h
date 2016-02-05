#pragma once
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "MediaManager.h"
#include "Input.h"
#include "Timing.h"
#include "Grid.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class Game
{
public:
	Game( );
	~Game( );

private:
	/** Creates game window and surface */
	void CreateWindowAndSurface( );

	/** Run the game */
	void Run( );

	/** Input */
	Input m_Input;

	/** Media Manager */
	MediaManager* m_Media;

	/** Game window */
	SDL_Window* m_Window;

	/** Game renderer */
	SDL_Renderer *m_Renderer;

	/** Grid */
	Grid *m_Grid;

	/** Timing */
	FPSLimiter m_Timing;

	/** Time of last frame as DeltaTime */
	float m_DeltaTime;

	/** If game is closing */
	bool bClose;

	/** Game FPS */
	float m_FPS;

	Media *test_media = NULL;

	Media *test_media_2 = NULL;

};
