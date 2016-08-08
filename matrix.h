#pragma once
#ifndef MATRIX
#define MATRIX
#include"types.h"

//矩阵行优先，与opengl相反，transpose列主序

//OpenGL中的坐标用齐次坐标表示，即(x, y, z)表示成(x',y', z',h)，其中x=x'/ h; y = y'/h; z=z'/ h
#define H 1

//模型矩阵
#define TR_MODELVIEW 1
TRdouble ModelViewMatrix[16]= { 
	1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0 };
//投影矩阵
#define TR_PROJECTION 2
TRdouble ProjectionMatrix[16] = {
	1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0 };
//纹理矩阵
#define TR_TEXTURE  3
TRdouble TextureMatrix[16] = { 
	1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0 };
//颜色矩阵
#define TR_COLOR 4
TRdouble ColorMatrix[16] = { 
	1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0 };
//当前模型
TRdouble* CurrentMatrix=ModelViewMatrix;

//单位矩阵
TRdouble IdentityMatrix[16] = { 1.0,0.0,0.0,0.0,
								0.0,1.0,0.0,0.0,
								0.0,0.0,1.0,0.0,
								0.0,0.0,0.0,1.0 };


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
TRvoid trRotatef();
TRvoid trScalef();
//右乘栈顶矩阵并放回栈顶
TRvoid trMultMatrixf(TRfloat *m);
TRvoid trMultMatrixd(TRdouble *m);
//它是将当前矩阵与一个透视矩阵相乘，把当前矩阵转变成透视矩阵
TRvoid trFrustum(TRdouble right, TRdouble bottom, TRdouble top, TRdouble nearVal, TRdouble farVal);

//将当前的可视空间设置为正投影空间
TRvoid trOrtho(TRdouble left, TRdouble right, TRdouble bottom, TRdouble top, TRdouble near, TRdouble far);

//matrix stack
#define MATRIX_STACK_MAX 32
TRdouble matrix_stack[MATRIX_STACK_MAX][16];
TRint stackTop=0;

//toolkit
//复制矩阵
TRvoid trCopyMatrix(TRdouble * to,TRdouble * from);
//矩阵相乘
TRvoid trMultiMatrix(TRdouble * lhs, TRdouble * rhs);

TRvoid trMatrixMode(TRenum mode)
{
	switch (mode)
	{
	case TR_MODELVIEW:
		CurrentMatrix = ModelViewMatrix;
		break;
	case TR_PROJECTION:
		CurrentMatrix = ProjectionMatrix;
		break;
	case TR_TEXTURE:
		CurrentMatrix = TextureMatrix;
		break;
	case TR_COLOR:
		CurrentMatrix = ColorMatrix;
		break;
	default:
		//TODO error
		CurrentMatrix = NULL;
		return;
		break;
	}
}
//加载单位矩阵
TRvoid trLoadIdentity()
{
	trCopyMatrix(matrix_stack[stackTop],IdentityMatrix);
}
//平移矩阵
TRvoid trTranslatef(TRfloat x, TRfloat y, TRfloat z)
{

	return TRvoid();
}
//平移矩阵
TRvoid trTranslated(TRdouble x, TRdouble y, TRdouble z)
{
	return TRvoid();
}
//加载矩阵
TRvoid trLoadMatrixf(TRfloat * m)
{
	trCopyMatrix(CurrentMatrix, (TRdouble *)m);
}
//加载矩阵
TRvoid trLoadMatrixd(TRdouble * m)
{
	trCopyMatrix(CurrentMatrix, m);
}
//加载转置矩阵
TRvoid trLoadTransposeMatrixf(TRfloat * m)
{
	return TRvoid();
}
//加载转置矩阵
TRvoid trLoadTransposeMatrixd(TRdouble * m)
{
	return TRvoid();
}
//压入矩阵
inline TRvoid trPushMatrix(TRdouble * m)
{
	return TRvoid();
}
//弹出矩阵
inline TRvoid trPopMatrix(TRdouble * m)
{
	return TRvoid();
}
//复制矩阵
TRvoid trCopyMatrix(TRdouble * to, TRdouble * from)
{
	TRint i;
	for (i = 0; i < 16;++i)
	{
		to[i] = from[i];
	}
}
//右乘矩阵
TRvoid trMultiMatrix(TRdouble * lhs, TRdouble * rhs)
{
	TRint i;
	TRint j;
	TRint k;
	TRdouble temp[16];
	for (i = 0; i < 4;++i)
	{
		for (j = 0; j < 4;++j)
		{
			temp[i*4+j] = lhs[i * 4 + 0] * rhs[j * 4 + 0] + 
					lhs[i * 4 + 1] * rhs[j * 4 + 1]+
					lhs[i * 4 + 2] * rhs[j * 4 + 2]+
					lhs[i * 4 + 3] * rhs[j * 4 + 3];
		}
	}
	trCopyMatrix(lhs,temp);
}



#endif // !MATRIX
