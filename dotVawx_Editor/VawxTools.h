#pragma once

struct Vector2
{
	int X;
	int Y;
	Vector2( ) { }
	Vector2( int x, int y ) 
	{
		X = x;
		Y = y;
	}

	bool operator==( const Vector2 &a ) const
	{
		return( X == a.X && Y == a.Y );
	}
};