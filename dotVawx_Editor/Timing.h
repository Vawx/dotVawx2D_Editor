#pragma once

class FPSLimiter
{
public:
	FPSLimiter( );
	~FPSLimiter( );

	/** Start Limiter */
	void Begin( );

	/** End Limiter, return FPS out deltatime */
	float End( float &DeltaTime );

	float GetFrameTime( ) { return m_FrameTime; }

private:
	/** Calculate FPS from begin to end */
	void CalculateFPS( );

	/** Target FPS rate */
	float m_TargetFPS;

	/** Current FPS */
	float m_FPS;

	/** Last frame time */
	float m_FrameTime;

	/** Delta time */
	float m_DeltaTime;

	/** End of frame */
	float m_End;

	/** Max FPS */
	float m_MaxFPS;

	/** Start of tick */
	unsigned int m_StartTicks;

};