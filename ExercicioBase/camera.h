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

#ifndef CAMERA_H
#define CAMERA_H

#include "ogldev_math_3d.h"

/// <summary>
/// Classe para controle da camera
/// </summary>
class Camera
{
public:
    /// <summary>
    /// Construtor da classe Camera
    /// </summary>
    Camera();
    float GetzNear();
    /// <summary>
    /// Define posicao da camera
    /// </summary>
    /// <param name="x">Coordenada X</param>
    /// <param name="y">Coordenada Y</param>
    /// <param name="z">Coordenada Z</param>
    void SetPosition(float x, float y, float z);

    /// <summary>
    /// Funcao chamada quando uma tecla e pressionada
    /// </summary>
    /// <param name="key">Tecla pressionada<param>
    void OnKeyboard(unsigned char key);

    /// <summary>
    /// Retorna matrix 4x4 com a posicao da camera
    /// </summary>
    /// <returns>Matrix 4x4 com posicao da camera</returns>
    Matrix4f GetMatrix();
    float zNear = 1.0f;

private:

    Vector3f m_pos;
    Vector3f m_target;
    Vector3f m_up;
    float m_speed = 0.2f;
    bool m_isWireframe = false;

};

#endif  /* CAMERA_H */
