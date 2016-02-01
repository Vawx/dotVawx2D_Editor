#include "MediaManager.h"
#include "Media.h"

MediaManager::MediaManager( ){}
MediaManager::MediaManager( SDL_Window* GameWindow, SDL_Renderer* GameRenderer )
{
	m_GameWindow = GameWindow;
	m_GameRenderer = GameRenderer;
}

MediaManager::~MediaManager( )
{
	m_MediaList.clear( );
}

void MediaManager::Update( )
{
	SDL_RenderClear( m_GameRenderer );
	std::vector<Media*>::iterator i;
	for ( i = m_MediaList.begin( ); i != m_MediaList.end( ); ++i )
	{
		(*i)->Render( m_GameRenderer );
	}
	SDL_RenderPresent( m_GameRenderer );
}

Media* MediaManager::AddMedia( char* FilePath, char* Name, int X, int Y, float Width, float Height )
{
	Media* newMedia = new Media( FilePath, Name, X, Y, Width, Height, m_GameWindow, m_GameRenderer );
	if( newMedia )
	{
		m_MediaList.push_back( newMedia );
	}
	return newMedia;
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