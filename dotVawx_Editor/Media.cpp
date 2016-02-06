#include <stdio.h>
#include <SDL_image.h>
#include "Media.h"

Media::Media( ){}

Media::Media( char* FilePath, 
			char* Name, 
			int X, 
			int Y, 
			float Width, 
			float Height, 
			Uint8 SortLayer, 
			SDL_Window* GameWindow, 
			SDL_Renderer* GameRenderer, 
			bool Background, 
			bool Scaled )
{
	m_Name = Name;
	m_FilePath = FilePath;
	m_SortLayer = SortLayer;
	bBackground = Background;

	if( !IMG_Init( IMG_INIT_PNG ) )
	{
		printf("Failed to initialize PNG Image%s\n", IMG_GetError( ) );
	}

	if (Scaled)
	{
		LoadMediaScaled(m_FilePath, X, Y, Width, Height, GameWindow, GameRenderer);
	}
	else
	{
		LoadMediaPixel(m_FilePath, X, Y, Width, Height, GameWindow, GameRenderer);
	}
}

Media::~Media( )
{	
	SDL_DestroyTexture( m_MediaTexture );
	m_MediaTexture = NULL;
	m_FilePath = NULL;
}

bool Media::LoadMediaScaled( char* FilePath, int X, int Y, float Width, float Height, SDL_Window* GameWindow, SDL_Renderer* GameRenderer )
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
			
			Vector2 firstDrawLoc;
			firstDrawLoc.X = X;
			firstDrawLoc.Y = Y;
			m_DrawPositions.push_back( firstDrawLoc );

			SDL_FreeSurface( mediaSurface );
			return true;
		}
		else
		{
			printf( "Error loading texture %s\n", SDL_GetError( ) );
		}
	}

	printf( "Unable to load Media %s!\n SDL Error: %s\n", FilePath, SDL_GetError( ) );
	return false;
}

bool Media::LoadMediaPixel( char* FilePath, int X, int Y, float Width, float Height, SDL_Window* GameWindow, SDL_Renderer* GameRenderer )
{
	SDL_Surface* mediaSurface = IMG_Load( FilePath );
	if( mediaSurface )
	{
		SDL_SetColorKey( mediaSurface, SDL_TRUE, SDL_MapRGB( mediaSurface->format, 0, 255, 255 ) );
		m_MediaTexture = SDL_CreateTextureFromSurface( GameRenderer, mediaSurface );
		if ( m_MediaTexture )
		{
			m_Width = Width;
			m_Height = Height; 

			Vector2 firstDrawLoc;
			firstDrawLoc.X = X;
			firstDrawLoc.Y = Y;
			m_DrawPositions.push_back( firstDrawLoc );

			SDL_FreeSurface( mediaSurface );
			return true;
		}
		else
		{
			printf( "Error loading texture %s\n", SDL_GetError( ) );
		}
	}

	printf( "Unable to load Media %s!\n SDL Error: %s\n", FilePath, SDL_GetError( ) );
	return false;
}

void Media::AddDrawPosition( Vector2 DrawTo )
{
	bool included = false;
	for ( int i = 0; i < m_DrawPositions.size( ); i++ )
	{
		if ( m_DrawPositions[ i ] == DrawTo )
		{
			included = true;
		}
	}

	if ( !included )
	{
		m_DrawPositions.push_back( DrawTo );
	}
}

bool Media::RemoveDrawPosition( Vector2 RemoveFrom )
{
	for ( int i = 0; i < m_DrawPositions.size( ); i++ )
	{
		if( m_DrawPositions[ i ] == RemoveFrom && !bBackground )
		{
			m_DrawPositions.erase( m_DrawPositions.begin( ) + i );
			return true;
		}
	}
	return false;
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

	for ( int i = 0; i < m_DrawPositions.size( ); i++ )
	{
		SDL_Rect quad = { m_DrawPositions[ i ].X, m_DrawPositions[ i ].Y, m_Width, m_Height };
		SDL_RenderCopy( GameRenderer, m_MediaTexture, NULL, &quad );
	}
}
