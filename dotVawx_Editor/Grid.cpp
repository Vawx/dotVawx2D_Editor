#include "Grid.h"

Grid::Grid( ) { }
Grid::Grid( float Scale, float ScreenWidth, float ScreenHeight, bool DrawGrid )
{
	m_GridScale = Scale;
	m_Width = ScreenWidth;
	m_Height = ScreenHeight;
}

Grid::~Grid( ) 
{
	
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
			Manager->AddMedia("../content/img/grid.png", "grid", start_pos_x, start_pos_y, 0.5f, 0.5f, 0, true, true);

			Vector2 gridVec;
			gridVec.X = start_pos_x;
			gridVec.Y = start_pos_y;
			m_Grid.push_back( gridVec );

			start_pos_x += m_GridScale;
		}
		start_pos_x = 0;
		start_pos_y += m_GridScale;
	}
}

Vector2 Grid::GetGridElement( Vector2 ClickPosition )
{
	for ( int i = 0; i < m_Grid.size( ); ++i )
	{
		if ( ClickPosition.Y > m_Grid[ i ].Y && 
			 ClickPosition.Y < m_Grid[ i ].Y + m_GridScale &&
			 ClickPosition.X > m_Grid[ i ].X &&
			 ClickPosition.X < m_Grid[ i ].X + m_GridScale )
		{
			return m_Grid[ i ];
		}
	}
	return Vector2( -1, -1 );
}