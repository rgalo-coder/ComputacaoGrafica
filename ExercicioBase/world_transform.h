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

#ifndef WORLD_TRANSFORM_H
#define WORLD_TRANSFORM_H

#include "ogldev_math_3d.h"

/// <summary>
/// Classe para transformacoes nos objetos
/// </summary>
class WorldTrans {
 public:
    /// <summary>
    /// Construtor
    /// </summary>
    WorldTrans() {}

    /// <summary>
    /// Escalona o objeto
    /// </summary>
    /// <param name="scale">Fator de escalonamento. Padrao 1.0f para 100% do tamanho</param>
    void SetScale(float scale);

    /// <summary>
    /// Define rotacao para o objeto
    /// </summary>
    /// <param name="x">Rotacao no eixo X (em graus)</param>
    /// <param name="y">Rotacao no eixo Y (em graus)</param>
    /// <param name="z">Rotacao no eixo Z (em graus)</param>
    void SetRotation(float x, float y, float z);

    /// <summary>
    /// Translada o objeto
    /// </summary>
    /// <param name="x">Movimento no eixo X</param>
    /// <param name="y">Movimento no eixo Y</param>
    /// <param name="z">Movimento no eixo Z</param>
    void SetPosition(float x, float y, float z);

    void OnMouse(int button, int state, int x, int y);

    void OnMotion(int x, int y);

    /// <summary>
/// Rotaciona objeto alem da rotacao atual
/// </summary>
/// <param name="x">Rotacao no eixo X (em graus)</param>
/// <param name="y">Rotacao no eixo Y (em graus)</param>
/// <param name="z">Rotacao no eixo Z (em graus)</param>
    void Rotate(float x, float y, float z);

    void RotacaoArcBall();

    /// <summary>
    /// Retorna matrix com todas as transformacoes armazenadas na classe
    /// </summary>
    /// <returns>Matrix 4x4 com todas transformacoes </returns>
    Matrix4f GetMatrix();

 private:
    float    m_scale    = 1.0f;
    Vector3f m_rotation = Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f m_pos      = Vector3f(0.0f, 0.0f, 0.0f);
    bool botaoesquerdo;
    float x0, y0, z0 = 0.0f;
};


#endif
