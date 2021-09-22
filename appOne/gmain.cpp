#define _COORDINATE_DIRECTX

#ifdef _COORDINATE_DIRECTX
#include"libOne.h"
void gmain() {
    window(1000, 1000);
    VECTOR p[3];
    p[0].set(-1, 1, 0);
    p[1].set(-1, -1, 0);
    p[2].set(1, -1, 0);
    while (notQuit) {
        clear();
        triangle3D(p[0], p[1], p[2]);
    }
}
#endif
#ifdef _COORDINATE_MATH1
#include"libOne.h"
void gmain() {
    window(1000, 1000);
    const int numVertices = 3;
    VECTOR op[numVertices];
    op[0].set(0, 1, 0);
    op[1].set(-1, -1, 0);
    op[2].set(1, -1, 0);
    VECTOR p[numVertices];
    float angle = 0;
    while (notQuit) {
        clear(60);
        float c = cos(angle);
        angle += 0.017f;
        for (int i = 0; i < numVertices; i++) {
            //world座標変換
            p[i].x = op[i].x;
            p[i].y = op[i].y;
            p[i].z = op[i].z - 2 + c;
            //projection座標変換
            p[i].z *= -1;
            p[i].x /= p[i].z;
            p[i].y /= p[i].z;
            p[i].z /= 5;
        }
        triangle3D(p[0], p[1], p[2]);
    }
}
#endif
#ifdef _COORDINATE_MATH2
#include"libOne.h"
void gmain() {
    window(1000, 1000);
    const int numVertices = 4;
    VECTOR op[numVertices];
    op[0].set(-0.5f,0.5f,0);
    op[1].set(-0.5f,-0.5f,0);
    op[2].set(0.5f,0.5f,0);
    op[3].set(0.5f,-0.5f,0);
    VECTOR p[numVertices];
    float angle = 0;
    int sw = 0;
    while (notQuit) {
        clear(60);
        if (isTrigger(KEY_SPACE))++sw %= 5;
        float s = sin(angle);
        float c = cos(angle);
        angle += 0.04f;
        for (int i = 0; i < numVertices; i++) {
            //ワールド座標変換
            if (sw == 0) {
                p[i].x = op[i].x * c + op[i].y * -s;
                p[i].y = op[i].x * s + op[i].y * c;
                p[i].z = op[i].z;
            }
            else if (sw == 1) {
                p[i].x = op[i].x * c + op[i].z * s;
                p[i].y = op[i].y;
                p[i].z = op[i].x * -s + op[i].z * c;
            }
            else if (sw == 2) {
                p[i].x = op[i].x;
                p[i].y = op[i].y * c + op[i].z * -s;
                p[i].z = op[i].y * s + op[i].z * c;
            }
            else if (sw == 3) {
                p[i].x = op[i].x * (c + 1.5f);
                p[i].y = op[i].y;
                p[i].z = op[i].z;
            }
            else if (sw == 4) {
                p[i].x = op[i].x;
                p[i].y = op[i].y;
                p[i].z = op[i].z + (c - 1);
            }
            p[i].z += -2;
            //プロジェクション座標変換
            p[i].z *= -1;
            p[i].x /= p[i].z;
            p[i].y /= p[i].z;
            p[i].z /= 20;
        }
        triangle3D(p[0], p[1], p[2]);
        triangle3D(p[2], p[1], p[3]);
    }
}
#endif
#ifdef _WORLD_MATRIX
#include"libOne.h"
void gmain() {
    window(1000, 1000);
    const int numVertices = 4;
    VECTOR op[numVertices];
    op[0].set(-0.5f, 0.5f, 0);
    op[1].set(-0.5f, -0.5f, 0);
    op[2].set(0.5f, 0.5f, 0);
    op[3].set(0.5f, -0.5f, 0);
    VECTOR p[numVertices];
    MATRIX world;
    float angle = 0;
    while (notQuit) {
        clear(60);

        //行列をつくる
        world.identity();
        world.mulTranslate(0, 0, -4);
        world.mulRotateY(angle);
        world.mulTranslate(2, 0, 0);
        world.mulRotateY(angle*8);
        angle += 0.017f;

        for (int i = 0; i < numVertices; i++) {
            //ワールド座標変換
            p[i] = world * op[i];
            //プロジェクション座標変換
            p[i].z *= -1;
            p[i].x /= p[i].z;
            p[i].y /= p[i].z;
            p[i].z /= 20;
        }

        triangle3D(p[0], p[1], p[2]);
        triangle3D(p[2], p[1], p[3]);
    }
}
#endif
