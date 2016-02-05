#include <functional>
#include "MediaManager.h"
#include "Media.h"

MediaManager::MediaManager( ){}
MediaManager::MediaManager( SDL_Window* GameWindow, SDL_Renderer* GameRenderer )
{
	m_GameWindow = GameWindow;
	m_GameRenderer = GameRenderer;
	bToggleBackground = true;
}

MediaManager::~MediaManager( )
{
	m_MediaList.clear( );
	m_BackgroundMediaList.clear( );
}

void MediaManager::ToggleBackground( )
{
	bToggleBackground = !bToggleBackground;
}


void MediaManager::Update( )
{
	SDL_Rect gameViewport;
	gameViewport.x = 0;
	gameViewport.y = 0;
	gameViewport.w = 1280;
	gameViewport.h = 720;
	SDL_RenderSetViewport( m_GameRenderer, &gameViewport );

	std::vector<Media*>::iterator i;
	for ( i = m_MediaList.begin( ); i != m_MediaList.end( ); ++i )
	{
		if( (*i)->Background( ) && !bToggleBackground )
		{
			continue;
		}

		(*i)->Render(m_GameRenderer);
	}
}

Media* MediaManager::AddMedia( char* FilePath, char* Name, int X, int Y, float Width, float Height, Uint8 SortLayer, bool Background, bool Scaled )
{
	if (X >= 0 && Y >= 0)
	{
		Media* newMedia = new Media(FilePath, Name, X, Y, Width, Height, SortLayer, m_GameWindow, m_GameRenderer, Background, Scaled);
		if (newMedia)
		{
			m_MediaList.push_back(newMedia);
		}
		std::sort(m_MediaList.begin(), m_MediaList.end(), SortLayerCompare());
		return newMedia;
	}
}

void MediaManager::RemoveMedia( char* Name )
{
	std::vector<Media*>::iterator i = m_MediaList.begin( );
	while( i != m_MediaList.end( ) )
	{
		if ( (*i)->Name( ) == Name )
		{
			Media* to_delete = (*i);
			delete (*i);

			i = m_MediaList.erase( i );
		}
		else
		{
			++i;
		}
	}
}

void MediaManager::RemoveMedia( Vector2 Position )
{
	std::vector<Media*>::iterator i = m_MediaList.begin( );
	while( i != m_MediaList.end( ) )
	{
		if ( (*i)->X( ) == Position.X && (*i)->Y( ) == Position.Y && !(*i)->Background( ) )
		{
			Media* to_delete = (*i);
			delete (*i);

			i = m_MediaList.erase( i );
		}
		else
		{
			++i;
		}
	}
}