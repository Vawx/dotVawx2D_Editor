#include <stdio.h>
#include <SDL_image.h>
#include "Media.h"

Media::Media( ){}

Media::Media( char* FilePath, char* Name, int X, int Y, float Width, float Height, SDL_Window* GameWindow, SDL_Renderer* GameRenderer )
{
	m_Name = Name;
	m_FilePath = FilePath;

	if( !IMG_Init( IMG_INIT_PNG ) )
	{
		printf("Failed to initialize PNG Image%s\n", IMG_GetError( ) );
	}

	LoadMedia( m_FilePath, X, Y, Width, Height, GameWindow, GameRenderer );
}

Media::~Media( )
{	
	SDL_DestroyTexture( m_MediaTexture );
	m_MediaTexture = NULL;
	m_FilePath = NULL;
}

bool Media::LoadMedia( char* FilePath, int X, int Y, float Width, float Height, SDL_Window* GameWindow, SDL_Renderer* GameRenderer )
{
	SDL_Surface* mediaSurface = IMG_Load( FilePath );
	if( mediaSurface )
	{
		SDL_SetColorKey( mediaSurface, SDL_TRUE, SDL_MapRGB( mediaSurface->format, 0, 255, 255 ) );
		m_MediaTexture = SDL_CreateTextureFromSurface( GameRenderer, mediaSurface );
		if ( m_MediaTexture )
		{
			m_Width = mediaSurface->w * Width;
			m_Height = mediaSurface->h * Height; 
			m_Y = Y;
			m_X = X;

			SDL_FreeSurface( mediaSurface );
			return true;
		}
	}

	printf( "Unable to load Media %s!\n SDL Error: %s\n", FilePath, SDL_GetError( ) );
	return false;
}

void Media::SetLocation( int X, int Y )
{
	m_X = X;
	m_Y = Y;
}

void Media::SetHidden( bool Hidden )
{
	bHidden = Hidden;
}

void Media::Render( SDL_Renderer* GameRenderer )
{
	if( bHidden )
	{
		return;
	}
	SDL_Rect quad = { m_X, m_Y, m_Width, m_Height };
	SDL_RenderCopy( GameRenderer, m_MediaTexture, NULL, &quad );
}

