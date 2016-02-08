#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
	myFile.open( "../save/save_00.txt" );
	myFile << media;
	myFile.close( );

	return true;
}

static std::vector<Vector2> OpenFromFile( )
{
	std::ifstream file( "../save/save_00.txt" );
	std::stringstream buffer;
	buffer << file.rdbuf( );
	std::string outString;
	std::vector<Vector2> outList;

	Vector2 toList;
	std::string fromList;

	for ( int i = 0; i < buffer.str( ).length( ); i++ )
	{
		// 32 = " "
		if ( buffer.str( )[ i ] == char( 32 ) )
		{
			toList.X = std::stoi( fromList );
			fromList = "";
		}
		// 124 = "|"
		else if ( buffer.str( )[ i ] == char( 124 ) )
		{
			toList.Y = std::stoi( fromList );
			fromList = "";

			outList.push_back( toList );
			toList.X = -1;
			toList.Y = -1;

		}
		else
		{
			fromList += buffer.str( )[ i ];
		}
	}
	return outList;
}