/*

        Copyright 2021 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "world_transform.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

void WorldTrans::SetScale(float scale)
{
    m_scale = scale;
}


void WorldTrans::SetRotation(float x, float y, float z)
{
    m_rotation.x = x;
    m_rotation.y = y;
    m_rotation.z = z;
}


void WorldTrans::SetPosition(float x, float y, float z)
{
    m_pos.x = x;
    m_pos.y = y;
    m_pos.z = z;
}

void WorldTrans::OnMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        botaoesquerdo = true;
        x0 = x;
        y0 = y;
        
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        botaoesquerdo = false;
    }
  
}

void WorldTrans::OnMotion(int x, int y)
{
    if (botaoesquerdo == true)
    {
        m_rotation.x = m_rotation.x - (y -y0)/3;
        m_rotation.y = m_rotation.y + (x - x0)/3;
        y0 = y;
        x0 = x;
    }
}


void WorldTrans::Rotate(float x, float y, float z)
{
    m_rotation.x += x;
    m_rotation.y += y;
    m_rotation.z += z;
}

void WorldTrans::RotacaoArcBall()
{
    if (botaoesquerdo == true)
    {
       
    }
}

Matrix4f WorldTrans::GetMatrix()
{
    RotacaoArcBall();

    Matrix4f Scale;
    Scale.InitScaleTransform(m_scale, m_scale, m_scale);

    Matrix4f Rotation;
    Rotation.InitRotateTransform(m_rotation.x, m_rotation.y, m_rotation.z);

    Matrix4f Translation;
    Translation.InitTranslationTransform(m_pos.x, m_pos.y, m_pos.z);

    Matrix4f WorldTransformation = Translation * Rotation * Scale;

    return WorldTransformation;
}
