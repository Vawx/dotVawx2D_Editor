#include <SDL.h>
#include <stdio.h>
#include "Timing.h"

FPSLimiter::FPSLimiter( )
{
	m_MaxFPS = 60.f;
}

FPSLimiter::~FPSLimiter( ){}

void FPSLimiter::Begin( )
{
	m_StartTicks = SDL_GetTicks( );
}

float FPSLimiter::End( float &DeltaTime )
{
	CalculateFPS( );

	float frameTicks = SDL_GetTicks( ) - m_StartTicks;
	if( 1000.f / m_MaxFPS >= frameTicks )
	{
		SDL_Delay( Uint32( 1000.f / m_MaxFPS - frameTicks ) );
	}
	m_End = SDL_GetTicks( );
	DeltaTime = ( m_End - m_StartTicks ) * 0.001f;
	return m_FPS;
}

void FPSLimiter::CalculateFPS( )
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[ NUM_SAMPLES ];
	static int currentFrame = 0;
	static float previousTicks = SDL_GetTicks( );
	float currentTicks = SDL_GetTicks( );

	m_FrameTime = currentTicks - previousTicks;
	frameTimes[ currentFrame % NUM_SAMPLES ] = m_FrameTime;
	previousTicks = currentTicks;

	int count; 
	currentFrame++;
	count = ( currentFrame < NUM_SAMPLES ) ? currentFrame : NUM_SAMPLES;

	float frameTimeAverage = 0;
	for ( int i = 0; i < count; i++ )
	{
		frameTimeAverage += frameTimes[ i ];
	}

	frameTimeAverage /= count;
	m_FPS = ( frameTimeAverage > 0 ) ? 1000.f / frameTimeAverage : 60.f;
}