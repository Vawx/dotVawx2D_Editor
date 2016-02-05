#include "Grid.h"

Grid::Grid( ) { }
Grid::Grid( float Scale, float ScreenWidth, float ScreenHeight, bool DrawGrid )
{
	m_GridScale = Scale;
	m_Width = ScreenWidth;
	m_Height = ScreenHeight;
	bDrawGrid = DrawGrid;
}

Grid::~Grid( ) 
{
	
}

void Grid::ToggleGrid( bool bOn ) 
{
	bDrawGrid = bOn;
}

void Grid::SetupGrid( MediaManager *Manager )
{
	float scale_width = (float)m_Width / m_GridScale;
	float scale_height = ( m_Height / m_GridScale ) + 1;
	float start_pos_x = 0;
	float start_pos_y = 0;

	for (int j = 0; j < scale_height; j++)
	{
		for (int i = 0; i < scale_width; i++)
		{
			Manager->AddMedia("../content/img/grid.png", "grid", start_pos_x, start_pos_y, 0.5f, 0.5f, 0, true);
			start_pos_x += m_GridScale;

			Vector2 gridVec;
			gridVec.X = start_pos_x;
			gridVec.Y = start_pos_y;
			m_Grid.push_back( gridVec );
		}
		start_pos_x = 0;
		start_pos_y += m_GridScale;
	}
}