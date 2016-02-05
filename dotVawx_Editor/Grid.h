#pragma once
#include <vector>
#include <SDL.h>
#include "VawxTools.h"
#include "MediaManager.h"
#include "Grid.h"

class Grid
{
public:
	Grid( );
	Grid( float Scale, float ScreenWidth, float ScreenHeight, bool DrawGrid );
	~Grid( );

	/** Setup grid */
	void SetupGrid( MediaManager *Manager );

	/** Get grid element position from click position */
	Vector2 GetGridElement( Vector2 ClickPosition );

	/** Current scale of grid */
	float Scale( ) { return m_GridScale; }

private:

	/** Scale of grid */
	float m_GridScale;

	/** Width of grid */
	float m_Width;

	/** Height of grid */
	float m_Height;

	/** Stores all grid positions */
	std::vector<Vector2> m_Grid;
};