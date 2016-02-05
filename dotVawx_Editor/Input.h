#pragma once
#include <SDL.h>
#include <unordered_map>
#include "VawxTools.h"

class Input
{
public:
	Input( );
	~Input( );

	/** Per update */
	bool Update( );

	/** Is key down */
	bool isKeyPressed( unsigned int ID );


	/** Get literal mouse position */
	Vector2 LiteralMousePosition( ) { return m_LiteralMousePosition; }

private:

	void SetMousePosition( float X, float Y );

	/** Keys being held*/
	std::unordered_map<unsigned int, bool> m_Keys;

	/** Literal mouse position */
	Vector2 m_LiteralMousePosition;
};