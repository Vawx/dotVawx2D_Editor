#pragma once
#include <SDL.h>
#include <unordered_map>
#include <glm\vec2.hpp>

struct Vector2
{
	int X;
	int Y;
};

class Input
{
public:
	Input( );
	~Input( );

	/** Per update */
	bool Update( );

	/** Is key down */
	bool isKeyPressed( unsigned int ID );

	/** Get mouse position */
	glm::vec2 MousePosition( ) { return m_MousePosition; }

	/** Get literal mouse position */
	Vector2 LiteralMousePosition( ) { return m_LiteralMousePosition; }

private:

	void SetMousePosition( float X, float Y );

	/** Keys being held*/
	std::unordered_map<unsigned int, bool> m_Keys;

	/** Mouse position */
	glm::vec2 m_MousePosition;

	/** Literal mouse position */
	Vector2 m_LiteralMousePosition;
};