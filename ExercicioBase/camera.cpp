

#include <GL/freeglut.h>

#include "camera.h"

  

Camera::Camera()
{
    m_pos          = Vector3f(0.0f, 0.0f, 0.0f);
    m_target       = Vector3f(0.0f, 0.0f, 1.0f);
    m_up           = Vector3f(0.0f, 1.0f, 0.0f);
   

}

float Camera::GetzNear()
{
    return zNear;
}

void Camera::SetPosition(float x, float y, float z)
{
    m_pos.x = x;
    m_pos.y = y;
    m_pos.z = z;
}


void Camera::OnKeyboard(unsigned char Key)
{
    switch (Key) {

    case GLUT_KEY_UP:
        m_pos += (m_target * m_speed);
        break;

    case GLUT_KEY_DOWN:
        m_pos -= (m_target * m_speed);
        break;

    case GLUT_KEY_LEFT:
        {
            Vector3f Left = m_target.Cross(m_up);
            Left.Normalize();
            Left *= m_speed;
            m_pos += Left;
        }
        break;

    case GLUT_KEY_RIGHT:
        {
            Vector3f Right = m_up.Cross(m_target);
            Right.Normalize();
            Right *= m_speed;
            m_pos += Right;
        }
        break;

    case 'o':
        m_pos.y += m_speed;
        break;

    case 'l':
        m_pos.y -= m_speed;
        break;

    case '+':
        m_speed += 0.05f;
        printf("Speed changed to %f\n", m_speed);
        break;

    case '-':
        m_speed -= 0.05f;
        if (m_speed < 0.1f) {
            m_speed = 0.1f;
        }
        printf("Speed changed to %f\n", m_speed);
        break;

    case 'q':
        zNear += 0.05f;
        printf("plano de corte alterado para %f\n", zNear);
        break;

    case 'a':
        zNear -= 0.05f;
        printf("plano de corte alterado para %f\n", zNear);
        break;

    case 'z':
        m_isWireframe = !m_isWireframe;

        if (m_isWireframe) {
            glPolygonMode(GL_FRONT, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT, GL_FILL);
        }
        break;

    }
}


Matrix4f Camera::GetMatrix()
{
    Matrix4f CameraTransformation;
    CameraTransformation.InitCameraTransform(m_pos, m_target, m_up);

    return CameraTransformation;
}
