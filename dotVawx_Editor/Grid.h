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

	/** Get if draw grid */
	bool DrawGrid( ) { return bDrawGrid; }

	/** Change grid showing */
	void ToggleGrid( bool bOn );

	/** Setupg grid */
	void SetupGrid( MediaManager *Manager );

private:

	/** to draw grid */
	bool bDrawGrid;

	/** Scale of grid */
	float m_GridScale;

	/** Width of grid */
	float m_Width;

	/** Height of grid */
	float m_Height;

	/** Stores all grid positions */
	std::vector<Vector2> m_Grid;
};