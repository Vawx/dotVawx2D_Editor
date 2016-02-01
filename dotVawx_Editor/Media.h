#pragma once
#include <SDL.h>

class Media
{
public:
	Media( );
	Media( char* FilePath, char* Name, int X, int Y, float Width, float Height, SDL_Window* GameWindow, SDL_Renderer* GameRenderer );
	~Media( );

	/** Loads Media as BMP 
	 * @param: FilePath - Path to image file. */
	bool LoadMedia( char* FilePath, int X, int Y, float Width, float Height, SDL_Window* GameWindow, SDL_Renderer* GameRenderer );

	/** Renders the texture to the window */
	void Render( SDL_Renderer* GameRenderer );

	/** Get Media Name */
	char* Name( ) { return m_Name; }

	/** Get media texture */
	SDL_Texture* Texture( ) { return m_MediaTexture; }

	/** Set screen position */
	void SetLocation( int X, int Y );

	/** Set hidden */
	void SetHidden( bool Hidden );

	/** Get width */
	float Width( ) { return m_Width; }

	/** Get height */
	float Height( ) { return m_Height; }

	/** Get X */
	int X( ) { return m_X; }

	/** Get Y */
	int Y( ) { return m_Y; }

private:

	/** Texture */
	SDL_Texture* m_MediaTexture;

	/** Width */
	float m_Width;

	/** Height */
	float m_Height;

	/** Screen Loc x */
	int m_X;

	/** Screen Loc y */
	int m_Y;

	/** Stored file path for this media */
	char* m_FilePath;

	/** Name of media */
	char* m_Name;

	/** Hidden */
	bool bHidden;
};