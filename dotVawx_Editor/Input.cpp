#include "Input.h"

Input::Input( )
{

}

Input::~Input( )
{

}

bool Input::Update( )
{
	SDL_Event e;
	m_ReleasedKeys.clear( );
	while( SDL_PollEvent( &e ) != 0 )
	{
		if ( e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE ){	return true; }		
		switch( e.type )
		{
		case SDL_KEYDOWN:
			m_Keys[ e.key.keysym.sym ] = true;
			break;
		case SDL_KEYUP:
			m_Keys[ e.key.keysym.sym ] = false;
			m_ReleasedKeys[ e.key.keysym.sym ] = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_Keys[ e.button.button ] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			m_Keys[ e.button.button ] = false;
			m_ReleasedKeys[ e.button.button ] = true;
			break;
		case SDL_MOUSEMOTION:
			SetMousePosition( e.motion.x, e.motion.y );
			break;
		}
	}

	return false;
}

bool Input::isKeyPressed( unsigned int ID )
{
	auto input = m_Keys.find( ID );
	return( input != m_Keys.end( ) ) ? input->second : false;
}

bool Input::isKeyReleased( unsigned int ID )
{
	auto input = m_ReleasedKeys.find( ID );
	return( input != m_ReleasedKeys.end( ) ) ? input->second : false;
}

void Input::SetMousePosition( float X, float Y )
{
	m_LiteralMousePosition.X = X;
	m_LiteralMousePosition.Y = Y;
}

