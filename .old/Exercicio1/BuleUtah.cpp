/*

        Copyright 2010 Etay Meiri

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

    Tutorial 11 - Perspective Projection - part 1
*/

#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_math_3d.h"


#include <memory>
#include "BuleUtah.h"


#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600

GLuint VBO;
GLuint IBO;
GLuint gWorldLocation;
//
float ContadorCor = 0.3f;



static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    static float Scale = -2.1f;

#ifdef _WIN64
    //   Scale += 0.01f ;
#else
    Scale += 0.02f;
#endif

    Matrix4f Rotation(cosf(Scale), 0.0f, -sinf(Scale), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sinf(Scale), 0.0f, cosf(Scale), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    Matrix4f RotationX(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cosf(Scale), -sinf(Scale), 0.0f,
        0.0f, sinf(Scale), cosf(Scale), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    Matrix4f Translation(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 2.5f,
        0.0f, 0.0f, 0.0f, 1.0f);

    float FOV = 90.0f;
    float tanHalfFOV = tanf(ToRadian(FOV / 2.0f));
    float f = 1 / tanHalfFOV;

    Matrix4f Projection(f, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f);

    Matrix4f FinalMatrix = Projection * Translation * RotationX;
    //Matrix4f FinalMatrix = Translation * Rotation;

  //   Matrix4f FinalMatrix = Projection * Translation ;

    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &FinalMatrix.m[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
   //glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_TRIANGLES, 96 * 10, GL_UNSIGNED_INT, 0);
    

    glDrawArrays(GL_POINTS, 0, 300);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);



    glutPostRedisplay();

    glutSwapBuffers();
}


struct Vertex {
    Vector3f pos;
    Vector3f color;

    Vertex()
    {

    }

    Vertex(float x, float y, float z)
    {
        pos = Vector3f(x, y, z);

        //float red = (float)rand() / (float)RAND_MAX;
        //float green = (float)rand() / (float)RAND_MAX;
        //float blue = (float)rand() / (float)RAND_MAX;
        //color = Vector3f(red, green, blue);


        color = Vector3f(ContadorCor, ContadorCor, 0.0f);


    }
};


static void CreateVertexBuffer()
{
    Vertex Vertices[307];

    Vertices[0] = Vertex(0.0f, 0.0f, 0.0f);
    Vertices[1] = Vertex(1.4f, 0.0f, 2.4f);
    Vertices[2] = Vertex(1.4f, -0.784f, 2.4f);
    Vertices[3] = Vertex(0.78f, -1.4f, 2.4f);
    Vertices[4] = Vertex(0.0f, -1.4f, 2.4f);
    Vertices[5] = Vertex(1.3375f, 0.0f, 2.53125f);
    Vertices[6] = Vertex(1.3375f, -0.749f, 2.53125f);
    Vertices[7] = Vertex(0.749f, -1.3375f, 2.53125f);
    Vertices[8] = Vertex(0.0f, -1.3375f, 2.53125f);
    Vertices[9] = Vertex(1.4375f, 0.0f, 2.53125f);
    Vertices[10] = Vertex(1.4375f, -0.805f, 2.53125f);
    Vertices[11] = Vertex(0.805f, -1.4375f, 2.53125f);
    Vertices[12] = Vertex(0.0f, -1.4375f, 2.53125f);
    Vertices[13] = Vertex(1.5f, 0.0f, 2.4f);
    Vertices[14] = Vertex(1.5f, -0.84f, 2.4f);
    Vertices[15] = Vertex(0.84f, -1.5f, 2.4f);
    Vertices[16] = Vertex(0.0f, -1.5f, 2.4f);
    Vertices[17] = Vertex(-0.784f, -1.4f, 2.4f);
    Vertices[18] = Vertex(-1.4f, -0.784f, 2.4f);
    Vertices[19] = Vertex(-1.4f, 0.0f, 2.4f);
    Vertices[20] = Vertex(-0.749f, -1.3375f, 2.53125f);
    Vertices[21] = Vertex(-1.3375f, -0.749f, 2.53125f);
    Vertices[22] = Vertex(-1.3375f, 0.0f, 2.53125f);
    Vertices[23] = Vertex(-0.805f, -1.4375f, 2.53125f);
    Vertices[24] = Vertex(-1.4375f, -0.805f, 2.53125f);
    Vertices[25] = Vertex(-1.4375f, 0.0f, 2.53125f);
    Vertices[26] = Vertex(-0.84f, -1.5f, 2.4f);
    Vertices[27] = Vertex(-1.5f, -0.84f, 2.4f);
    Vertices[28] = Vertex(-1.5f, 0.0f, 2.4f);
    Vertices[29] = Vertex(-1.4f, 0.784f, 2.4f);
    Vertices[30] = Vertex(-0.784f, 1.4f, 2.4f);
    Vertices[31] = Vertex(0.0f, 1.4f, 2.4f);
    Vertices[32] = Vertex(-1.3375f, 0.749f, 2.53125f);
    Vertices[33] = Vertex(-0.749f, 1.3375f, 2.53125f);
    Vertices[34] = Vertex(0.0f, 1.3375f, 2.53125f);
    Vertices[35] = Vertex(-1.4375f, 0.805f, 2.53125f);
    Vertices[36] = Vertex(-0.805f, 1.4375f, 2.53125f);
    Vertices[37] = Vertex(0.0f, 1.4375f, 2.53125f);
    Vertices[38] = Vertex(-1.5f, 0.84f, 2.4f);
    Vertices[39] = Vertex(-0.84f, 1.5f, 2.4f);
    Vertices[40] = Vertex(0.0f, 1.5f, 2.4f);
    Vertices[41] = Vertex(0.784f, 1.4f, 2.4f);
    Vertices[42] = Vertex(1.4f, 0.784f, 2.4f);
    Vertices[43] = Vertex(0.749f, 1.3375f, 2.53125f);
    Vertices[44] = Vertex(1.3375f, 0.749f, 2.53125f);
    Vertices[45] = Vertex(0.805f, 1.4375f, 2.53125f);
    Vertices[46] = Vertex(1.4375f, 0.805f, 2.53125f);
    Vertices[47] = Vertex(0.84f, 1.5f, 2.4f);
    Vertices[48] = Vertex(1.5f, 0.84f, 2.4f);
    Vertices[49] = Vertex(1.75f, 0.0f, 1.875f);
    Vertices[50] = Vertex(1.75f, -0.98f, 1.875f);
    Vertices[51] = Vertex(0.98f, -1.75f, 1.875f);
    Vertices[52] = Vertex(0.0f, -1.75f, 1.875f);
    Vertices[53] = Vertex(2.0f, 0.0f, 1.35f);
    Vertices[54] = Vertex(2.0f, -1.12f, 1.35f);
    Vertices[55] = Vertex(1.12f, -2.0f, 1.35f);
    Vertices[56] = Vertex(0.0f, -2.0f, 1.35f);
    Vertices[57] = Vertex(2.0f, 0.0f, 0.9f);
    Vertices[58] = Vertex(2.0f, -1.12f, 0.9f);
    Vertices[59] = Vertex(1.12f, -2.0f, 0.9f);
    Vertices[60] = Vertex(0.0f, -2.0f, 0.9f);
    Vertices[61] = Vertex(-0.98f, -1.75f, 1.875f);
    Vertices[62] = Vertex(-1.75f, -0.98f, 1.875f);
    Vertices[63] = Vertex(-1.75f, 0.0f, 1.875f);
    Vertices[64] = Vertex(-1.12f, -2.0f, 1.35f);
    Vertices[65] = Vertex(-2.0f, -1.12f, 1.35f);
    Vertices[66] = Vertex(-2.0f, 0.0f, 1.35f);
    Vertices[67] = Vertex(-1.12f, -2.0f, 0.9f);
    Vertices[68] = Vertex(-2.0f, -1.12f, 0.9f);
    Vertices[69] = Vertex(-2.0f, 0.0f, 0.9f);
    Vertices[70] = Vertex(-1.75f, 0.98f, 1.875f);
    Vertices[71] = Vertex(-0.98f, 1.75f, 1.875f);
    Vertices[72] = Vertex(0.0f, 1.75f, 1.875f);
    Vertices[73] = Vertex(-2.0f, 1.12f, 1.35f);
    Vertices[74] = Vertex(-1.12f, 2.0f, 1.35f);
    Vertices[75] = Vertex(0.0f, 2.0f, 1.35f);
    Vertices[76] = Vertex(-2.0f, 1.12f, 0.9f);
    Vertices[77] = Vertex(-1.12f, 2.0f, 0.9f);
    Vertices[78] = Vertex(0.0f, 2.0f, 0.9f);
    Vertices[79] = Vertex(0.98f, 1.75f, 1.875f);
    Vertices[80] = Vertex(1.75f, 0.98f, 1.875f);
    Vertices[81] = Vertex(1.12f, 2.0f, 1.35f);
    Vertices[82] = Vertex(2.0f, 1.12f, 1.35f);
    Vertices[83] = Vertex(1.12f, 2.0f, 0.9f);
    Vertices[84] = Vertex(2.0f, 1.12f, 0.9f);
    Vertices[85] = Vertex(2.0f, 0.0f, 0.45f);
    Vertices[86] = Vertex(2.0f, -1.12f, 0.45f);
    Vertices[87] = Vertex(1.12f, -2.0f, 0.45f);
    Vertices[88] = Vertex(0.0f, -2.0f, 0.45f);
    Vertices[89] = Vertex(1.5f, 0.0f, 0.225f);
    Vertices[90] = Vertex(1.5f, -0.84f, 0.225f);
    Vertices[91] = Vertex(0.84f, -1.5f, 0.225f);
    Vertices[92] = Vertex(0.0f, -1.5f, 0.225f);
    Vertices[93] = Vertex(1.5f, 0.0f, 0.15f);
    Vertices[94] = Vertex(1.5f, -0.84f, 0.15f);
    Vertices[95] = Vertex(0.84f, -1.5f, 0.15f);
    Vertices[96] = Vertex(0.0f, -1.5f, 0.15f);
    Vertices[97] = Vertex(-1.12f, -2.0f, 0.45f);
    Vertices[98] = Vertex(-2.0f, -1.12f, 0.45f);
    Vertices[99] = Vertex(-2.0f, 0.0f, 0.45f);
    Vertices[100] = Vertex(-0.84f, -1.5f, 0.225f);
    Vertices[101] = Vertex(-1.5f, -0.84f, 0.225f);
    Vertices[102] = Vertex(-1.5f, 0.0f, 0.225f);
    Vertices[103] = Vertex(-0.84f, -1.5f, 0.15f);
    Vertices[104] = Vertex(-1.5f, -0.84f, 0.15f);
    Vertices[105] = Vertex(-1.5f, 0.0f, 0.15f);
    Vertices[106] = Vertex(-2.0f, 1.12f, 0.45f);
    Vertices[107] = Vertex(-1.12f, 2.0f, 0.45f);
    Vertices[108] = Vertex(0.0f, 2.0f, 0.45f);
    Vertices[109] = Vertex(-1.5f, 0.84f, 0.225f);
    Vertices[110] = Vertex(-0.84f, 1.5f, 0.225f);
    Vertices[111] = Vertex(0.0f, 1.5f, 0.225f);
    Vertices[112] = Vertex(-1.5f, 0.84f, 0.15f);
    Vertices[113] = Vertex(-0.84f, 1.5f, 0.15f);
    Vertices[114] = Vertex(0.0f, 1.5f, 0.15f);
    Vertices[115] = Vertex(1.12f, 2.0f, 0.45f);
    Vertices[116] = Vertex(2.0f, 1.12f, 0.45f);
    Vertices[117] = Vertex(0.84f, 1.5f, 0.225f);
    Vertices[118] = Vertex(1.5f, 0.84f, 0.225f);
    Vertices[119] = Vertex(0.84f, 1.5f, 0.15f);
    Vertices[120] = Vertex(1.5f, 0.84f, 0.15f);
    Vertices[121] = Vertex(-1.6f, 0.0f, 2.025f);
    Vertices[122] = Vertex(-1.6f, -0.3f, 2.025f);
    Vertices[123] = Vertex(-1.5f, -0.3f, 2.25f);
    Vertices[124] = Vertex(-1.5f, 0.0f, 2.25f);
    Vertices[125] = Vertex(-2.3f, 0.0f, 2.025f);
    Vertices[126] = Vertex(-2.3f, -0.3f, 2.025f);
    Vertices[127] = Vertex(-2.5f, -0.3f, 2.25f);
    Vertices[128] = Vertex(-2.5f, 0.0f, 2.25f);
    Vertices[129] = Vertex(-2.7f, 0.0f, 2.025f);
    Vertices[130] = Vertex(-2.7f, -0.3f, 2.025f);
    Vertices[131] = Vertex(-3.0f, -0.3f, 2.25f);
    Vertices[132] = Vertex(-3.0f, 0.0f, 2.25f);
    Vertices[133] = Vertex(-2.7f, 0.0f, 1.8f);
    Vertices[134] = Vertex(-2.7f, -0.3f, 1.8f);
    Vertices[135] = Vertex(-3.0f, -0.3f, 1.8f);
    Vertices[136] = Vertex(-3.0f, 0.0f, 1.8f);
    Vertices[137] = Vertex(-1.5f, 0.3f, 2.25f);
    Vertices[138] = Vertex(-1.6f, 0.3f, 2.025f);
    Vertices[139] = Vertex(-2.5f, 0.3f, 2.25f);
    Vertices[140] = Vertex(-2.3f, 0.3f, 2.025f);
    Vertices[141] = Vertex(-3.0f, 0.3f, 2.25f);
    Vertices[142] = Vertex(-2.7f, 0.3f, 2.025f);
    Vertices[143] = Vertex(-3.0f, 0.3f, 1.8f);
    Vertices[144] = Vertex(-2.7f, 0.3f, 1.8f);
    Vertices[145] = Vertex(-2.7f, 0.0f, 1.575f);
    Vertices[146] = Vertex(-2.7f, -0.3f, 1.575f);
    Vertices[147] = Vertex(-3.0f, -0.3f, 1.35f);
    Vertices[148] = Vertex(-3.0f, 0.0f, 1.35f);
    Vertices[149] = Vertex(-2.5f, 0.0f, 1.125f);
    Vertices[150] = Vertex(-2.5f, -0.3f, 1.125f);
    Vertices[151] = Vertex(-2.65f, -0.3f, 0.9375f);
    Vertices[152] = Vertex(-2.65f, 0.0f, 0.9375f);
    Vertices[153] = Vertex(-2.0f, -0.3f, 0.9f);
    Vertices[154] = Vertex(-1.9f, -0.3f, 0.6f);
    Vertices[155] = Vertex(-1.9f, 0.0f, 0.6f);
    Vertices[156] = Vertex(-3.0f, 0.3f, 1.35f);
    Vertices[157] = Vertex(-2.7f, 0.3f, 1.575f);
    Vertices[158] = Vertex(-2.65f, 0.3f, 0.9375f);
    Vertices[159] = Vertex(-2.5f, 0.3f, 1.125f);
    Vertices[160] = Vertex(-1.9f, 0.3f, 0.6f);
    Vertices[161] = Vertex(-2.0f, 0.3f, 0.9f);
    Vertices[162] = Vertex(1.7f, 0.0f, 1.425f);
    Vertices[163] = Vertex(1.7f, -0.66f, 1.425f);
    Vertices[164] = Vertex(1.7f, -0.66f, 0.6f);
    Vertices[165] = Vertex(1.7f, 0.0f, 0.6f);
    Vertices[166] = Vertex(2.6f, 0.0f, 1.425f);
    Vertices[167] = Vertex(2.6f, -0.66f, 1.425f);
    Vertices[168] = Vertex(3.1f, -0.66f, 0.825f);
    Vertices[169] = Vertex(3.1f, 0.0f, 0.825f);
    Vertices[170] = Vertex(2.3f, 0.0f, 2.1f);
    Vertices[171] = Vertex(2.3f, -0.25f, 2.1f);
    Vertices[172] = Vertex(2.4f, -0.25f, 2.025f);
    Vertices[173] = Vertex(2.4f, 0.0f, 2.025f);
    Vertices[174] = Vertex(2.7f, 0.0f, 2.4f);
    Vertices[175] = Vertex(2.7f, -0.25f, 2.4f);
    Vertices[176] = Vertex(3.3f, -0.25f, 2.4f);
    Vertices[177] = Vertex(3.3f, 0.0f, 2.4f);
    Vertices[178] = Vertex(1.7f, 0.66f, 0.6f);
    Vertices[179] = Vertex(1.7f, 0.66f, 1.425f);
    Vertices[180] = Vertex(3.1f, 0.66f, 0.825f);
    Vertices[181] = Vertex(2.6f, 0.66f, 1.425f);
    Vertices[182] = Vertex(2.4f, 0.25f, 2.025f);
    Vertices[183] = Vertex(2.3f, 0.25f, 2.1f);
    Vertices[184] = Vertex(3.3f, 0.25f, 2.4f);
    Vertices[185] = Vertex(2.7f, 0.25f, 2.4f);
    Vertices[186] = Vertex(2.8f, 0.0f, 2.475f);
    Vertices[187] = Vertex(2.8f, -0.25f, 2.475f);
    Vertices[188] = Vertex(3.525f, -0.25f, 2.49375f);
    Vertices[189] = Vertex(3.525f, 0.0f, 2.49375f);
    Vertices[190] = Vertex(2.9f, 0.0f, 2.475f);
    Vertices[191] = Vertex(2.9f, -0.15f, 2.475f);
    Vertices[192] = Vertex(3.45f, -0.15f, 2.5125f);
    Vertices[193] = Vertex(3.45f, 0.0f, 2.5125f);
    Vertices[194] = Vertex(2.8f, 0.0f, 2.4f);
    Vertices[195] = Vertex(2.8f, -0.15f, 2.4f);
    Vertices[196] = Vertex(3.2f, -0.15f, 2.4f);
    Vertices[197] = Vertex(3.2f, 0.0f, 2.4f);
    Vertices[198] = Vertex(3.525f, 0.25f, 2.49375f);
    Vertices[199] = Vertex(2.8f, 0.25f, 2.475f);
    Vertices[200] = Vertex(3.45f, 0.15f, 2.5125f);
    Vertices[201] = Vertex(2.9f, 0.15f, 2.475f);
    Vertices[202] = Vertex(3.2f, 0.15f, 2.4f);
    Vertices[203] = Vertex(2.8f, 0.15f, 2.4f);
    Vertices[204] = Vertex(0.0f, 0.0f, 3.15f);
    Vertices[205] = Vertex(0.0f, -0.002f, 3.15f);
    Vertices[206] = Vertex(0.002f, 0.0f, 3.15f);
    Vertices[207] = Vertex(0.8f, 0.0f, 3.15f);
    Vertices[208] = Vertex(0.8f, -0.45f, 3.15f);
    Vertices[209] = Vertex(0.45f, -0.8f, 3.15f);
    Vertices[210] = Vertex(0.0f, -0.8f, 3.15f);
    Vertices[211] = Vertex(0.0f, 0.0f, 2.85f);
    Vertices[212] = Vertex(0.2f, 0.0f, 2.7f);
    Vertices[213] = Vertex(0.2f, -0.112f, 2.7f);
    Vertices[214] = Vertex(0.112f, -0.2f, 2.7f);
    Vertices[215] = Vertex(0.0f, -0.2f, 2.7f);
    Vertices[216] = Vertex(-0.002f, 0.0f, 3.15f);
    Vertices[217] = Vertex(-0.45f, -0.8f, 3.15f);
    Vertices[218] = Vertex(-0.8f, -0.45f, 3.15f);
    Vertices[219] = Vertex(-0.8f, 0.0f, 3.15f);
    Vertices[220] = Vertex(-0.112f, -0.2f, 2.7f);
    Vertices[221] = Vertex(-0.2f, -0.112f, 2.7f);
    Vertices[222] = Vertex(-0.2f, 0.0f, 2.7f);
    Vertices[223] = Vertex(0.0f, 0.002f, 3.15f);
    Vertices[224] = Vertex(-0.8f, 0.45f, 3.15f);
    Vertices[225] = Vertex(-0.45f, 0.8f, 3.15f);
    Vertices[226] = Vertex(0.0f, 0.8f, 3.15f);
    Vertices[227] = Vertex(-0.2f, 0.112f, 2.7f);
    Vertices[228] = Vertex(-0.112f, 0.2f, 2.7f);
    Vertices[229] = Vertex(0.0f, 0.2f, 2.7f);
    Vertices[230] = Vertex(0.45f, 0.8f, 3.15f);
    Vertices[231] = Vertex(0.8f, 0.45f, 3.15f);
    Vertices[232] = Vertex(0.112f, 0.2f, 2.7f);
    Vertices[233] = Vertex(0.2f, 0.112f, 2.7f);
    Vertices[234] = Vertex(0.4f, 0.0f, 2.55f);
    Vertices[235] = Vertex(0.4f, -0.224f, 2.55f);
    Vertices[236] = Vertex(0.224f, -0.4f, 2.55f);
    Vertices[237] = Vertex(0.0f, -0.4f, 2.55f);
    Vertices[238] = Vertex(1.3f, 0.0f, 2.55f);
    Vertices[239] = Vertex(1.3f, -0.728f, 2.55f);
    Vertices[240] = Vertex(0.728f, -1.3f, 2.55f);
    Vertices[241] = Vertex(0.0f, -1.3f, 2.55f);
    Vertices[242] = Vertex(1.3f, 0.0f, 2.4f);
    Vertices[243] = Vertex(1.3f, -0.728f, 2.4f);
    Vertices[244] = Vertex(0.728f, -1.3f, 2.4f);
    Vertices[245] = Vertex(0.0f, -1.3f, 2.4f);
    Vertices[246] = Vertex(-0.224f, -0.4f, 2.55f);
    Vertices[247] = Vertex(-0.4f, -0.224f, 2.55f);
    Vertices[248] = Vertex(-0.4f, 0.0f, 2.55f);
    Vertices[249] = Vertex(-0.728f, -1.3f, 2.55f);
    Vertices[250] = Vertex(-1.3f, -0.728f, 2.55f);
    Vertices[251] = Vertex(-1.3f, 0.0f, 2.55f);
    Vertices[252] = Vertex(-0.728f, -1.3f, 2.4f);
    Vertices[253] = Vertex(-1.3f, -0.728f, 2.4f);
    Vertices[254] = Vertex(-1.3f, 0.0f, 2.4f);
    Vertices[255] = Vertex(-0.4f, 0.224f, 2.55f);
    Vertices[256] = Vertex(-0.224f, 0.4f, 2.55f);
    Vertices[257] = Vertex(0.0f, 0.4f, 2.55f);
    Vertices[258] = Vertex(-1.3f, 0.728f, 2.55f);
    Vertices[259] = Vertex(-0.728f, 1.3f, 2.55f);
    Vertices[260] = Vertex(0.0f, 1.3f, 2.55f);
    Vertices[261] = Vertex(-1.3f, 0.728f, 2.4f);
    Vertices[262] = Vertex(-0.728f, 1.3f, 2.4f);
    Vertices[263] = Vertex(0.0f, 1.3f, 2.4f);
    Vertices[264] = Vertex(0.224f, 0.4f, 2.55f);
    Vertices[265] = Vertex(0.4f, 0.224f, 2.55f);
    Vertices[266] = Vertex(0.728f, 1.3f, 2.55f);
    Vertices[267] = Vertex(1.3f, 0.728f, 2.55f);
    Vertices[268] = Vertex(0.728f, 1.3f, 2.4f);
    Vertices[269] = Vertex(1.3f, 0.728f, 2.4f);
    Vertices[270] = Vertex(0.0f, 0.0f, 0.0f);
    Vertices[271] = Vertex(1.5f, 0.0f, 0.15f);
    Vertices[272] = Vertex(1.5f, 0.84f, 0.15f);
    Vertices[273] = Vertex(0.84f, 1.5f, 0.15f);
    Vertices[274] = Vertex(0.0f, 1.5f, 0.15f);
    Vertices[275] = Vertex(1.5f, 0.0f, 0.075f);
    Vertices[276] = Vertex(1.5f, 0.84f, 0.075f);
    Vertices[277] = Vertex(0.84f, 1.5f, 0.075f);
    Vertices[278] = Vertex(0.0f, 1.5f, 0.075f);
    Vertices[279] = Vertex(1.425f, 0.0f, 0.0f);
    Vertices[280] = Vertex(1.425f, 0.798f, 0.0f);
    Vertices[281] = Vertex(0.798f, 1.425f, 0.0f);
    Vertices[282] = Vertex(0.0f, 1.425f, 0.0f);
    Vertices[283] = Vertex(-0.84f, 1.5f, 0.15f);
    Vertices[284] = Vertex(-1.5f, 0.84f, 0.15f);
    Vertices[285] = Vertex(-1.5f, 0.0f, 0.15f);
    Vertices[286] = Vertex(-0.84f, 1.5f, 0.075f);
    Vertices[287] = Vertex(-1.5f, 0.84f, 0.075f);
    Vertices[288] = Vertex(-1.5f, 0.0f, 0.075f);
    Vertices[289] = Vertex(-0.798f, 1.425f, 0.0f);
    Vertices[290] = Vertex(-1.425f, 0.798f, 0.0f);
    Vertices[291] = Vertex(-1.425f, 0.0f, 0.0f);
    Vertices[292] = Vertex(-1.5f, -0.84f, 0.15f);
    Vertices[293] = Vertex(-0.84f, -1.5f, 0.15f);
    Vertices[294] = Vertex(0.0f, -1.5f, 0.15f);
    Vertices[295] = Vertex(-1.5f, -0.84f, 0.075f);
    Vertices[296] = Vertex(-0.84f, -1.5f, 0.075f);
    Vertices[297] = Vertex(0.0f, -1.5f, 0.075f);
    Vertices[298] = Vertex(-1.425f, -0.798f, 0.0f);
    Vertices[299] = Vertex(-0.798f, -1.425f, 0.0f);
    Vertices[300] = Vertex(0.0f, -1.425f, 0.0f);
    Vertices[301] = Vertex(0.84f, -1.5f, 0.15f);
    Vertices[302] = Vertex(1.5f, -0.84f, 0.15f);
    Vertices[303] = Vertex(0.84f, -1.5f, 0.075f);
    Vertices[304] = Vertex(1.5f, -0.84f, 0.075f);
    Vertices[305] = Vertex(0.798f, -1.425f, 0.0f);
    Vertices[306] = Vertex(1.425f, -0.798f, 0.0f);

 


    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}



static void EnviarBuffer(Vertex* Vertices, int tamanhoVertices, unsigned int* Indices, int tamanhoIndices)
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, tamanhoVertices, Vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tamanhoIndices, Indices, GL_STATIC_DRAW);

}


static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(1);
    }

    const GLchar* p[1];
    p[0] = pShaderText;

    GLint Lengths[1];
    Lengths[0] = (GLint)strlen(pShaderText);

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    std::string vs, fs;

    if (!ReadFile(pVSFileName, vs)) {
        exit(1);
    };

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

    if (!ReadFile(pFSFileName, fs)) {
        exit(1);
    };

    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
    if (gWorldLocation == -1) {
        printf("Error getting uniform location of 'gWorld'\n");
        exit(1);
    }

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);
}

void GerarVerticesBule()
{

}



int BuleUtah(int argc, char** argv)
{
#ifdef _WIN64
    srand(GetCurrentProcessId());
#else
    srandom(getpid());
#endif

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);
    int win = glutCreateWindow("Bule de Utah");
    printf("window id: %d\n", win);

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    Vertex base1, base2, base3, base4, base5;
    base1 = Vertex(0.5, 0.5, 0);


  //  EnviarBuffer(TodosVertices, Totalvertices * sizeof(perna1.Vertices[0]), TodosIndices, TotalIndices * sizeof(perna1.Indices[0]));

    CreateVertexBuffer();
    //CreateIndexBuffer();

    int textureunits = 0;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureunits);
    printf("Number of texture units %d\n", textureunits);

    CompileShaders();

    glutDisplayFunc(RenderSceneCB);

    glutMainLoop();

    return 0;
}
