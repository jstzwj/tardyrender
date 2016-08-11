#pragma once
#ifndef MATRIX
#define MATRIX
#include"types.h"
#include"math.h"


//矩阵行优先，与opengl相反，transpose列主序

//OpenGL中的坐标用齐次坐标表示，即(x, y, z)表示成(x',y', z',h)，其中x=x'/ h; y = y'/h; z=z'/ h
#define H 1

//模型矩阵
#define TR_MODELVIEW 1
extern TRdouble ModelViewMatrix[16];
//投影矩阵
#define TR_PROJECTION 2
extern TRdouble ProjectionMatrix[16];
//纹理矩阵
#define TR_TEXTURE  3
extern TRdouble TextureMatrix[16];
//颜色矩阵
#define TR_COLOR 4
extern TRdouble ColorMatrix[16];
//当前模型
extern TRdouble* CurrentMatrix;

//单位矩阵
extern TRdouble IdentityMatrix[16];


//选择投影矩阵
TRvoid trMatrixMode(TRenum mode);
//加载矩阵
TRvoid trLoadMatrixf(TRfloat* m);
//加载矩阵
TRvoid trLoadMatrixd(TRdouble* m);
//加载转置矩阵
TRvoid trLoadTransposeMatrixf(TRfloat *m);
//加载转置矩阵
TRvoid trLoadTransposeMatrixd(TRdouble *m);

//压入矩阵堆栈
TRvoid trPushMatrix(TRdouble *m);
//弹出矩阵堆栈
TRvoid trPopMatrix(TRdouble *m);

//加载单位矩阵
TRvoid trLoadIdentity();
//平移矩阵
TRvoid trTranslatef(TRfloat x, TRfloat y, TRfloat z);
TRvoid trTranslated(TRdouble x, TRdouble y, TRdouble z);
//旋转矩阵
TRvoid trRotated(TRdouble angle, TRdouble x, TRdouble y, TRdouble z);
TRvoid trRotatef(TRfloat angle, TRfloat x, TRfloat y, TRfloat z);

//缩放矩阵
TRvoid trScalef(TRfloat x, TRfloat y, TRfloat z);
TRvoid trScaled(TRdouble x, TRdouble y, TRdouble z);
//右乘栈顶矩阵并放回栈顶
TRvoid trMultMatrixf(TRfloat *m);
TRvoid trMultMatrixd(TRdouble *m);
//它是将当前矩阵与一个透视矩阵相乘，把当前矩阵转变成透视矩阵
TRvoid trFrustum(TRdouble right, TRdouble bottom, TRdouble top, TRdouble nearVal, TRdouble farVal);

//将当前的可视空间设置为正投影空间
TRvoid trOrtho(TRdouble left, TRdouble right, TRdouble bottom, TRdouble top, TRdouble near, TRdouble far);

//matrix stack
#define MATRIX_STACK_MAX 32
extern TRdouble matrix_stack[MATRIX_STACK_MAX][16];
extern TRint stackTop;

//toolkit
//复制矩阵
TRvoid trCopyMatrix(TRdouble * to,TRdouble * from);
//矩阵相乘
TRvoid trMultiMatrix(TRdouble * lhs, TRdouble * rhs);
//向量归一化
TRvoid trNormalizeVector(TRdouble *vec);
//向量右乘矩阵
TRvoid trVectorMultMatrix(TRdouble *v4d,TRdouble *m16d);



#endif // !MATRIX
