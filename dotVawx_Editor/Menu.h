#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Media.h"

class Menu
{
public:
	Menu( );
	Menu( int MenuWidth, int MenuHeight, int MenuX, int MenuY, char* Background, SDL_Window *GameWindow, SDL_Renderer *GameRenderer );
	~Menu( );

	/** Add media to menu */
	Media* AddMenu( char* FilePath, char* Name, int X, int Y, float Width, float Height, Uint8 SortLayer, SDL_Window *GameWindow );

	/** Per frame */
	void Update( );

private:

	/** Menu width */
	int m_Width;

	/** Menu Height */
	int m_Height;

	/** Menu X */
	int m_X;

	/** Menu Y */
	int m_Y;

	/** Menu media to draw */
	std::vector<Media*> m_MenuMedia;

	/** Menu renderer */
	SDL_Renderer *m_MenuRenderer;
};
