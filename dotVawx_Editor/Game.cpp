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
}

// Create game window and game window surface
void Game::CreateWindowAndSurface( )
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL Failed to init%s\n", SDL_GetError( ) );
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
				}
			}

			m_Media = new MediaManager( m_Window, m_Renderer );
			Run( );
		}
		else
		{
			printf( "SDL Failed to create window!\n" );
			bClose = true;
		}
	}
}

// Main game loop
void Game::Run( )
{
	while( !bClose )
	{
		m_Timing.Begin( );

		if( m_Input.isKeyPressed( SDLK_1 ) )
		{
			if( !test_media )
			{
				test_media = m_Media->AddMedia( "../content/img/test_block.png", "test", 40, 120, 0.5f, 0.5f );
			}
		}
		else if ( m_Input.isKeyPressed( SDLK_2 ) )
		{
			if ( test_media )
			{
				m_Media->RemoveMedia( test_media->Name( ) );
				test_media = NULL;
			}
		}

		if ( test_media )
		{
			if ( m_Input.isKeyPressed( SDL_BUTTON_LEFT ) )
			{
				test_media->SetHidden( false );
				Vector2 mouseLoc = m_Input.LiteralMousePosition( );
				mouseLoc.X -= test_media->Width( ) * 0.5f;
				mouseLoc.Y -= test_media->Height( ) * 0.5f;
				test_media->SetLocation( mouseLoc.X, mouseLoc.Y );
			}
			else
			{
				test_media->SetHidden( true );
			}
		}

		m_Camera.Update( );
		m_Media->Update( );
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