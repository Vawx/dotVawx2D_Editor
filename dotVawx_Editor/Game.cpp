#include "Game.h"


Game::Game( )
{
	CreateWindowAndSurface( );
}

Game::~Game( )
{
	SDL_DestroyRenderer( m_Renderer );
	SDL_DestroyWindow( m_Window );
	m_Renderer = NULL;
	m_Window = NULL;
	IMG_Quit( );
	SDL_Quit( );

	delete m_Media;
	delete m_Grid;
}

// Create game window and game window surface
void Game::CreateWindowAndSurface( )
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL Failed to init%s\n", SDL_GetError( ) );
		bClose = true;
	}
	else
	{
		m_Window =  SDL_CreateWindow( "dotVawx Editor", 
					SDL_WINDOWPOS_UNDEFINED, 
					SDL_WINDOWPOS_UNDEFINED, 
					SCREEN_WIDTH, 
					SCREEN_HEIGHT, 
					SDL_WINDOW_SHOWN );

		if ( m_Window )
		{
			m_Renderer = SDL_CreateRenderer( m_Window, -1, SDL_RENDERER_ACCELERATED );
			if( m_Renderer )
			{
				if ( SDL_SetRenderDrawColor( m_Renderer, 0,0,0,0 ) != 0 )
				{
					printf( "SDL Failed to set render color%s\n", SDL_GetError( ) );
					bClose = true;
				}
			}

			m_Media = new MediaManager( m_Window, m_Renderer );
			m_Grid = new Grid( 64.f, SCREEN_WIDTH, SCREEN_HEIGHT, false );

			if ( m_Media && m_Grid )
			{
				m_Grid->SetupGrid( m_Media );
			}
		}
		else
		{
			printf( "SDL Failed to create window!\n" );
			bClose = true;
		}
		Run( );
	}
}

// Main game loop
void Game::Run( )
{
	while( !bClose )
	{
		m_Timing.Begin( );

		m_Media->Update( m_Input.isKeyPressed( SDLK_t ) );

		bClose = m_Input.Update( );
		m_FPS = m_Timing.End( m_DeltaTime );

		static int frameCounter = 0;
		frameCounter++;
		if( frameCounter >= 100 ) 
		{ 
			printf( "FPS: %f\n", m_FPS );
			frameCounter = 0;
		}
	}
}