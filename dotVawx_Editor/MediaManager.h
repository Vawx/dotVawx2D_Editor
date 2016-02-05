#pragma once
#include "Media.h"
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

struct SortLayerCompare {
	bool operator()( Media *m1, Media *m2 )
	{
		return m1->SortLayer( ) < m2->SortLayer( );
	}
};


class MediaManager
{
public:
	MediaManager( );
	MediaManager( SDL_Window* GameWindow, SDL_Renderer* GameRenderer );
	~MediaManager( );

	/** Add media to screen */
	Media* AddMedia( char* FilePath, char* Name, int X, int Y, float Width, float Height, Uint8 SortLayer, bool Background );
	
	/** Remove media from screen */
	void RemoveMedia( char* Name );

	/** Per cycle */
	void Update( bool Background );

	/** List of background game media */
	std::vector<Media*> m_BackgroundMediaList;

private:

	/** Game window */
	SDL_Window* m_GameWindow;

	/** Game renderer */
	SDL_Renderer* m_GameRenderer;

	/** List of active game media */
	std::vector<Media*> m_MediaList;
};