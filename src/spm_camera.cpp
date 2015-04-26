/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_camera.h"

Camera Camera::GameCam;

Camera::Camera()
{
    m_Rect.x = 0;
    m_Rect.y = 0;
    m_Rect.w = SCR_WIDTH;
    m_Rect.h = SCR_HEIGHT;
}

void Camera::Update(const Vector2f& pos)
{
    m_Rect.x = pos.x - SCR_WIDTH / 2;
    m_Rect.y = pos.y - SCR_HEIGHT / 2;

    if( m_Rect.x < 0 ) {
        m_Rect.x = 0;
    }
    if( m_Rect.y < 0 ) {
        m_Rect.y = 0;
    }
    if( m_Rect.x > LVL_WIDTH - SCR_WIDTH ) {
        m_Rect.x = LVL_WIDTH - SCR_WIDTH;
    }
    if( m_Rect.y > LVL_HEIGHT - SCR_HEIGHT ) {
        m_Rect.y = LVL_HEIGHT - SCR_HEIGHT;
    }
}
