

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>


struct Vec3f
{
    float x;
    float y;
    float z;

    Vec3f() {}

    Vec3f(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Vec3f(const float* pFloat)
    {
        x = pFloat[0];
        y = pFloat[1];
        z = pFloat[2];
    }

    Vec3f(float f)
    {
        x = y = z = f;
    }

    Vec3f& operator+=(const Vec3f& r)
    {
        x += r.x;
        y += r.y;
        z += r.z;

        return *this;
    }

    Vec3f& operator-=(const Vec3f& r)
    {
        x -= r.x;
        y -= r.y;
        z -= r.z;

        return *this;
    }

    Vec3f& operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;

        return *this;
    }

    operator const float* () const
    {
        return &(x);
    }


    Vec3f Cross(const Vec3f& v) const;

    Vec3f& Normalize();

    void Rotate(float Angle, const Vec3f& Axis);

    void Print() const
    {
        printf("(%.02f, %.02f, %.02f)", x, y, z);
    }
};


class Matrix4f
{
public:
    float m[4][4];

    Matrix4f() {}

    Matrix4f(float a00, float a01, float a02, float a03,
        float a10, float a11, float a12, float a13,
        float a20, float a21, float a22, float a23,
        float a30, float a31, float a32, float a33)
    {
        m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
        m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
        m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
        m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
    }

    // constructor from Assimp matrix
    Matrix4f(const aiMatrix4x4& AssimpMatrix)
    {
        m[0][0] = AssimpMatrix.a1; m[0][1] = AssimpMatrix.a2; m[0][2] = AssimpMatrix.a3; m[0][3] = AssimpMatrix.a4;
        m[1][0] = AssimpMatrix.b1; m[1][1] = AssimpMatrix.b2; m[1][2] = AssimpMatrix.b3; m[1][3] = AssimpMatrix.b4;
        m[2][0] = AssimpMatrix.c1; m[2][1] = AssimpMatrix.c2; m[2][2] = AssimpMatrix.c3; m[2][3] = AssimpMatrix.c4;
        m[3][0] = AssimpMatrix.d1; m[3][1] = AssimpMatrix.d2; m[3][2] = AssimpMatrix.d3; m[3][3] = AssimpMatrix.d4;
    }

    Matrix4f(const aiMatrix3x3& AssimpMatrix)
    {
        m[0][0] = AssimpMatrix.a1; m[0][1] = AssimpMatrix.a2; m[0][2] = AssimpMatrix.a3; m[0][3] = 0.0f;
        m[1][0] = AssimpMatrix.b1; m[1][1] = AssimpMatrix.b2; m[1][2] = AssimpMatrix.b3; m[1][3] = 0.0f;
        m[2][0] = AssimpMatrix.c1; m[2][1] = AssimpMatrix.c2; m[2][2] = AssimpMatrix.c3; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

    void SetZero()
    {
        ZERO_MEM(m);
    }

    Matrix4f Transpose() const
    {
        Matrix4f n;

        for (unsigned int i = 0; i < 4; i++) {
            for (unsigned int j = 0; j < 4; j++) {
                n.m[i][j] = m[j][i];
            }
        }

        return n;
    }


    inline void InitIdentity()
    {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

    inline Matrix4f operator*(const Matrix4f& Right) const
    {
        Matrix4f Ret;

        for (unsigned int i = 0; i < 4; i++) {
            for (unsigned int j = 0; j < 4; j++) {
                Ret.m[i][j] = m[i][0] * Right.m[0][j] +
                    m[i][1] * Right.m[1][j] +
                    m[i][2] * Right.m[2][j] +
                    m[i][3] * Right.m[3][j];
            }
        }

        return Ret;
    }

    Vector4f operator*(const Vector4f& v) const
    {
        Vector4f r;

        r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
        r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
        r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
        r.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

        return r;
    }

    operator const float* () const
    {
        return &(m[0][0]);
    }

    void Print() const
    {
        for (int i = 0; i < 4; i++) {
            printf("%f %f %f %f\n", m[i][0], m[i][1], m[i][2], m[i][3]);
        }
    }

    float Determinant() const;

    Matrix4f& Inverse();

    void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);

    void InitRotateTransform(float RotateX, float RotateY, float RotateZ);

    void InitRotateTransform(const Quaternion& quat);

    void InitTranslationTransform(float x, float y, float z);

    void InitCameraTransform(const Vector3f& Target, const Vector3f& Up);

    void InitCameraTransform(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up);

    void InitPersProjTransform(const PersProjInfo& p);

    void InitOrthoProjTransform(const OrthoProjInfo& p);
};


float evaluateBezierSurface(float P[16], float u, float v)
{
    float Pu[4];
    // compute 4 control points along u direction
    for (int i = 0; i < 4; ++i) {
        float curveP[4];
        curveP[0] = P[i * 4];
        curveP[1] = P[i * 4 + 1];
        curveP[2] = P[i * 4 + 2];
        curveP[2] = P[i * 4 + 3];
        Pu[i] = evalBezierCurve(curveP, u);
    }
    // compute final position on the surface using v
    return evalBezierCurve(Pu, v);
}


Vec3f evalBezierCurve(const Vec3f* P, const float& t)
{
    float b0 = (1 - t) * (1 - t) * (1 - t);
    float b1 = 3 * t * (1 - t) * (1 - t);
    float b2 = 3 * t * t * (1 - t);
    float b3 = t * t * t;
    return P[0] * b0 + P[1] * b1 + P[2] * b2 + P[3] * b3;
}

Vec3f evalBezierPatch(const Vec3f* controlPoints, const float& u, const float& v)
{
    Vec3f uCurve[4];
    for (int i = 0; i < 4; ++i) uCurve[i] = evalBezierCurve(controlPoints + 4 * i, u);
    return evalBezierCurve(uCurve, v);
}

void generatePolyTeapot(const Matrix4f& o2w, std::vector<Object*>& objects)
{
    uint32_t divs = 16;
    Vec3f* P = new Vec3f[(divs + 1) * (divs + 1)];
    uint32_t* nvertices = new uint32_t[divs * divs];
    uint32_t* vertices = new uint32_t[divs * divs * 4];
    Vec3f controlPoints[16];
    for (int np = 0; np < kTeapotNumPatches; ++np) {
        // set the control points for the current patch                                                                                                                                                    
        for (uint32_t i = 0; i < 16; ++i)
            controlPoints[i][0] = teapotVertices[teapotPatches[np][i] - 1][0],
            controlPoints[i][1] = teapotVertices[teapotPatches[np][i] - 1][1],
            controlPoints[i][2] = teapotVertices[teapotPatches[np][i] - 1][2];
        // generate grid                                                                                                                                                                                   
        for (uint16_t j = 0, k = 0; j <= divs; ++j) {
            for (uint16_t i = 0; i <= divs; ++i, ++k) {
                P[k] = evalBezierPatch(controlPoints, i / (float)divs, j / (float)divs);
            }
        }
        // face connectivity
        for (uint16_t j = 0, k = 0; j < divs; ++j) {
            for (uint16_t i = 0; i < divs; ++i, ++k) {
                nvertices[k] = 4;
                vertices[k * 4] = (divs + 1) * j + i;
                vertices[k * 4 + 1] = (divs + 1) * (j + 1) + i;
                vertices[k * 4 + 2] = (divs + 1) * (j + 1) + i + 1;
                vertices[k * 4 + 3] = (divs + 1) * j + i + 1;
            }
        }

        objects.push_back(new PolygonMesh(o2w, divs * divs, nvertices, vertices, P));
    }

    delete[] P;
    delete[] nvertices;
    delete[] vertices;
}