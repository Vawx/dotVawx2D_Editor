#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
public:

	Camera( );
	~Camera( );

	/** On each update */
	void Update( );

	/** Set Camera position */
	void SetPosition( const glm::vec2 &NewPosition );

	/** Set Camera scale */
	void SetScale( float NewScale );

	/** Convert screen position to world */
	glm::vec2 ConvertScreenPositionToWorld( glm::vec2 Position );

	/** Get camera scale */
	float GetScale( ) { return m_Scale; }

	/** Get camera position */
	glm::vec2 GetPosition( ) { return m_Position; }

	/** Get camera matrix */
	glm::mat4 GetCameraMatrix( ) { return m_CameraMatrix; }

private:

	/** camera needs matrix update */
	bool m_NeedMatrix;

	/** Screen width */
	int m_ScreenWidth;

	/** Screen height */
	int m_ScreenHeight;

	/** Camera scale */
	float m_Scale;

	/** Camera position */
	glm::vec2 m_Position;

	/** Camera matrix */
	glm::mat4 m_CameraMatrix;

	/** Ortho of camera */
	glm::mat4 m_OrthoMatrix;
};