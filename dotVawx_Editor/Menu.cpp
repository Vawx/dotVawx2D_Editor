#include "Menu.h"

Menu::Menu( ){}
Menu::Menu( int MenuWidth, int MenuHeight, int MenuX, int MenuY, char* Background, SDL_Window *GameWindow, SDL_Renderer *GameRenderer )
{
	m_Width = MenuWidth;
	m_Height = MenuHeight;
	m_X = MenuX;
	m_Y = MenuY;

	m_MenuRenderer = GameRenderer;
	if( m_MenuRenderer )
	{
		if ( SDL_SetRenderDrawColor( m_MenuRenderer, 0,0,0,0 ) != 0 )
		{
			printf( "SDL Failed to set render color%s\n", SDL_GetError( ) );
		}
	}
	else
	{
		printf( "Failed to create Menu Renderer %s\n", SDL_GetError( ) );
	}

	AddMenu( "../content/img/gray.png", "gray", m_X, m_Y, m_Width, m_Height, 0, GameWindow );
}

Menu::~Menu( )
{
	m_MenuMedia.clear( );
}

Media* Menu::AddMenu( char* FilePath, char* Name, int X, int Y, float Width, float Height, Uint8 SortLayer, SDL_Window *GameWindow )
{
	Media* newMedia = new Media(FilePath, Name, X, Y, Width, Height, SortLayer, GameWindow, m_MenuRenderer, false, false);
	if (newMedia)
	{
		m_MenuMedia.push_back(newMedia);
	}

	return newMedia;
}

void Menu::Update( )
{
	SDL_Rect menuViewport;
	menuViewport.x = 1280;
	menuViewport.y = 0;
	menuViewport.w = 256;
	menuViewport.h = 720;

	SDL_RenderSetViewport( m_MenuRenderer, &menuViewport );

	std::vector<Media*>::iterator i;
	for ( i = m_MenuMedia.begin( ); i != m_MenuMedia.end( ); ++i )
	{
		(*i)->Render(m_MenuRenderer);
	}
}