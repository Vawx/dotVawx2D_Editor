#pragma once
#include "Media.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class MediaManager
{
public:
	MediaManager( );
	MediaManager( SDL_Window* GameWindow, SDL_Renderer* GameRenderer );
	~MediaManager( );

	/** Add media to screen */
	Media* AddMedia( char* FilePath, char* Name, int X, int Y, float Width, float Height );
	
	/** Remove media from screen */
	void RemoveMedia( char* Name );

	/** Per cycle */
	void Update( );

private:

	/** Game window */
	SDL_Window* m_GameWindow;

	/** Game renderer */
	SDL_Renderer* m_GameRenderer;

	/** List of active game media */
	std::vector<Media*> m_MediaList;
};