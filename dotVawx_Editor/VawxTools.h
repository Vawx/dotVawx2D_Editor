#pragma once
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

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

static bool SaveToFile( const char* media )
{
	std::ofstream myFile;
	myFile.open	( "../save/save_00.txt" );
	myFile << media;
	myFile.close( );

	return true;
}

static void OpenFromFile( )
{

}