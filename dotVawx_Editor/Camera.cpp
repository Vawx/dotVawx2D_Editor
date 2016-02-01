#include "Camera.h"

Camera::Camera( ) : m_Position ( 0, 0 ),
					m_CameraMatrix( 1.f ),
					m_OrthoMatrix( 1.f ),
					m_Scale( 1.f ),
					m_NeedMatrix( true ),
					m_ScreenHeight( 720 ),
					m_ScreenWidth( 1280 )
{
	m_OrthoMatrix = glm::ortho( 0.f, (float)m_ScreenWidth, 0.f, (float)m_ScreenHeight );
}

Camera::~Camera( ) { }

void Camera::Update( )
{
	if( m_NeedMatrix )
	{
		glm::vec3 translate( -m_Position.x + m_ScreenWidth / 2, -m_Position.y + m_ScreenHeight / 2, 0.f );
		m_CameraMatrix = glm::translate( m_OrthoMatrix, translate );
		
		glm::vec3 scale( m_Scale, m_Scale, 0.f );
		m_CameraMatrix = glm::scale( glm::mat4( 1.f ), scale ) * m_CameraMatrix;

		m_NeedMatrix = false;
	}
}

void Camera::SetPosition( const glm::vec2 &NewPosition )
{
	m_Position = NewPosition;
	m_NeedMatrix = true;
}

void Camera::SetScale( float NewScale )
{
	m_Scale = NewScale;
	if( m_Scale <= 0.f ) { m_Scale = 0.f; }
	m_NeedMatrix = true;
}

glm::vec2 Camera::ConvertScreenPositionToWorld( glm::vec2 Position )
{
	Position.y = m_ScreenHeight - Position.y;
	Position -= glm::vec2( m_ScreenWidth / 2, m_ScreenHeight / 2 );
	Position /= m_Scale;
	Position += m_Position;
	return Position;
}