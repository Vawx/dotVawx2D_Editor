#include "Game.h"
#include <string>

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
	delete m_Menu;
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
					SCREEN_WIDTH + 256, 
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
				else
				{
					m_Menu = new Menu( 256, SCREEN_HEIGHT, 0, 0, "../content/img/gray.png", m_Window, m_Renderer);
					m_Menu->AddMenu( "../content/img/menu_border.png", "border", 0, 0, 256, SCREEN_HEIGHT, 1, m_Window );
					m_Menu->AddMenu( "../content/img/save_button.png", "save", 12, 18, 100, 30, 2, m_Window );
					m_Media = new MediaManager( m_Window, m_Renderer );
					m_Grid = new Grid( 64.f, SCREEN_WIDTH, SCREEN_HEIGHT, false );

					if ( m_Media && m_Grid )
					{
						m_Grid->SetupGrid( m_Media );
					}
				}
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

		Vector2 mouseLoc = m_Input.LiteralMousePosition( );
		Vector2 gridElementPos = m_Grid->GetGridElement( mouseLoc );

		if ( m_Input.isKeyReleased( SDL_BUTTON_LEFT ) )
		{			
			m_Media->AddMedia( "../content/img/gray.png", "grid_block", gridElementPos.X, gridElementPos.Y, 0.5f, 0.5f, 1, false, true );
		}
		if( m_Input.isKeyReleased( SDL_BUTTON_RIGHT ) )
		{
			m_Media->RemoveMedia( gridElementPos );
		}

		if ( m_Input.isKeyReleased( SDLK_t ) )
		{
			m_Media->ToggleBackground( );
		}

		if ( m_Input.isKeyReleased( SDLK_F1 ) )
		{
			std::string media = "";
			for ( int i = 0; i < m_Media->MediaList( ).size( ); i++ )
			{
				for ( int j = 0; j < m_Media->MediaList( )[ i ]->DrawPositions( ).size( ); j++ )
				{
					if( !m_Media->MediaList( )[ i ]->Background( ) )
					{
						Vector2 mediaLoc;
						mediaLoc.X = m_Media->MediaList( )[ i ]->DrawPositions( )[ j ].X;
						mediaLoc.Y = m_Media->MediaList( )[ i ]->DrawPositions( )[ j ].Y;

						std::string mediaX = std::to_string( mediaLoc.X );
						std::string mediaY = std::to_string( mediaLoc.Y );
						media += mediaX + " " + mediaY + "|";
					}
				}
			}

			SaveToFile( media.c_str( ) );
		}

		SDL_RenderClear( m_Renderer );
		m_Media->Update( );
		m_Menu->Update( );
		SDL_RenderPresent( m_Renderer );

		bClose = m_Input.Update( );
		m_FPS = m_Timing.End( m_DeltaTime );

		static int frameCounter = 0;
		frameCounter++;
		if( frameCounter >= 100 ) 
		{ 
			frameCounter = 0;
		}
	}
}