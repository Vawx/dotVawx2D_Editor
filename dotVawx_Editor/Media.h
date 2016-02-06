#pragma once
#include <SDL.h>
#include <vector>
#include "VawxTools.h"

class Media
{
public:
	Media( );
	Media( char* FilePath, 
		   char* Name, 
		   int X, 
		   int Y, 
		   float Width, 
		   float Height,
		   Uint8 SortLayer,
		   SDL_Window* GameWindow, 
		   SDL_Renderer* GameRenderer, 
		   bool Background, 
		   bool Scaled );
	~Media( );

	/** Loads Media as PNG */
	bool LoadMediaScaled( char* FilePath, int X, int Y, float Width, float Height, SDL_Window* GameWindow, SDL_Renderer* GameRenderer );

	/** Load media as PNG */
	bool LoadMediaPixel( char* FilePath, int X, int Y, float Width, float Height, SDL_Window* GameWindow, SDL_Renderer* GameRenderer );

	/** Renders the texture to the window */
	void Render( SDL_Renderer* GameRenderer );

	/** Add draw position */
	void AddDrawPosition( Vector2 DrawTo );

	/** Remove draw position */
	bool RemoveDrawPosition( Vector2 RemoveFrom );

	/** Get Media Name */
	char* Name( ) { return m_Name; }

	/** Get media texture */
	SDL_Texture* Texture( ) { return m_MediaTexture; }

	/** Set hidden */
	void SetHidden( bool Hidden );

	/** Get width */
	float Width( ) { return m_Width; }

	/** Get height */
	float Height( ) { return m_Height; }

	/** Get sort layer */
	Uint8 SortLayer( ) { return m_SortLayer; }

	/** Is background */
	bool Background( ) { return bBackground; }

	/** Get file path */
	char* FilePath( ) { return m_FilePath; }

	/** Get draw positions */
	std::vector<Vector2> DrawPositions( ) { return m_DrawPositions; }

private:

	/** Texture */
	SDL_Texture* m_MediaTexture;

	/** Width */
	float m_Width;

	/** Height */
	float m_Height;

	/** Stored file path for this media */
	char* m_FilePath;

	/** Name of media */
	char* m_Name;

	/** Hidden */
	bool bHidden;
	
	/** Sort layer */
	Uint8 m_SortLayer;
	
	/** If part of background */
	bool bBackground;

	/** Vector locations to draw this media to */
	std::vector<Vector2> m_DrawPositions;
};