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
TRdouble matrix_stack[MATRIX_STACK_MAX][16];
TRint stackTop=0;

//toolkit
//复制矩阵
TRvoid trCopyMatrix(TRdouble * to,TRdouble * from);
//矩阵相乘
TRvoid trMultiMatrix(TRdouble * lhs, TRdouble * rhs);
//向量归一化
TRvoid trNormalizeVector(TRdouble *vec)
{
	double h = tardy_sqrt(vec[0]* vec[0]+ vec[1]* vec[1]+ vec[2]* vec[2]+ vec[3]* vec[3]);
	if (h>1e-6)
	{
		vec[0] = vec[0] / h;
		vec[1] = vec[1] / h;
		vec[2] = vec[2] / h;
		vec[3] = vec[3] / h;
	}
}
//向量右乘矩阵
TRvoid trVectorMultMatrix(TRdouble *v4d,TRdouble *m16d);




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
	trCopyMatrix(CurrentMatrix,IdentityMatrix);
}
//平移矩阵
TRvoid trTranslatef(TRfloat x, TRfloat y, TRfloat z)
{
	TRdouble temp[16];
	trCopyMatrix(temp,IdentityMatrix);
	temp[3 * 4 + 0] = x;
	temp[3 * 4 + 1] = y;
	temp[3 * 4 + 2] = z;
	//相乘
	trMultiMatrix(CurrentMatrix,temp);
}
//平移矩阵
TRvoid trTranslated(TRdouble x, TRdouble y, TRdouble z)
{
	TRdouble temp[16];
	trCopyMatrix(temp, IdentityMatrix);
	temp[3 * 4 + 0] = x;
	temp[3 * 4 + 1] = y;
	temp[3 * 4 + 2] = z;
	//相乘
	trMultiMatrix(CurrentMatrix, temp);
}
TRvoid trRotated(TRdouble angle, TRdouble x, TRdouble y, TRdouble z)
{
	TRdouble temp[16];
	TRdouble h;
	TRdouble sinangle;
	TRdouble cosangle;
	sinangle = tardy_sin(angle);
	cosangle = tardy_cos(angle);
	h = tardy_sqrt(x*x + y*y + z*z);
	if (h != 1)
	{
		x = x / h;
		y = y / h;
		z = z / h;
	}
	temp[0 * 4 + 0] = x*x+(1-x*x)*cosangle;
	temp[0 * 4 + 1] = x*y*(1-cosangle)+z*sinangle;
	temp[0 * 4 + 2] = x*z*(1-cosangle)-y*sinangle;
	temp[0 * 4 + 3] = 0;
	temp[1 * 4 + 0] = x*y*(1-cosangle)-z*sinangle;
	temp[1 * 4 + 1] = y*y+(1-y*y)*cosangle;
	temp[1 * 4 + 2] = y*z*(1-cosangle)+x*sinangle;
	temp[1 * 4 + 3] = 0;
	temp[2 * 4 + 0] = x*z*(1-cosangle)+y*sinangle;
	temp[2 * 4 + 1] = y*z*(1-cosangle)-x*sinangle;
	temp[2 * 4 + 2] = z*z+(1-z*z)*cosangle;
	temp[2 * 4 + 3] = 0;
	temp[3 * 4 + 0] = 0;
	temp[3 * 4 + 1] = 0;
	temp[3 * 4 + 2] = 0;
	temp[3 * 4 + 3] = 1;
	//相乘
	trMultiMatrix(CurrentMatrix, temp);
}
TRvoid trRotatef(TRfloat angle, TRfloat x, TRfloat y, TRfloat z)
{
	TRdouble temp[16];
	TRfloat h;
	TRdouble sinangle;
	TRdouble cosangle;
	sinangle = tardy_sin(angle);
	cosangle = tardy_cos(angle);
	h = (TRfloat)tardy_sqrt(x*x + y*y + z*z);
	if (h != 1&&h>1e-6)
	{
		x = x / h;
		y = y / h;
		z = z / h;
	}
	temp[0 * 4 + 0] = x*x + (1 - x*x)*cosangle;
	temp[0 * 4 + 1] = x*y*(1 - cosangle) + z*sinangle;
	temp[0 * 4 + 2] = x*z*(1 - cosangle) - y*sinangle;
	temp[0 * 4 + 3] = 0;
	temp[1 * 4 + 0] = x*y*(1 - cosangle) - z*sinangle;
	temp[1 * 4 + 1] = y*y + (1 - y*y)*cosangle;
	temp[1 * 4 + 2] = y*z*(1 - cosangle) + x*sinangle;
	temp[1 * 4 + 3] = 0;
	temp[2 * 4 + 0] = x*z*(1 - cosangle) + y*sinangle;
	temp[2 * 4 + 1] = y*z*(1 - cosangle) - x*sinangle;
	temp[2 * 4 + 2] = z*z + (1 - z*z)*cosangle;
	temp[2 * 4 + 3] = 0;
	temp[3 * 4 + 0] = 0;
	temp[3 * 4 + 1] = 0;
	temp[3 * 4 + 2] = 0;
	temp[3 * 4 + 3] = 1;
	//相乘
	trMultiMatrix(CurrentMatrix, temp);
}
//缩放矩阵
TRvoid trScalef(TRfloat x, TRfloat y, TRfloat z)
{
	TRdouble temp[16];
	trCopyMatrix(temp, IdentityMatrix);
	temp[0 * 4 + 0] = x;
	temp[1 * 4 + 1] = y;
	temp[2 * 4 + 2] = z;
	//相乘
	trMultiMatrix(CurrentMatrix, temp);
}
//缩放矩阵
TRvoid trScaled(TRdouble x, TRdouble y, TRdouble z)
{
	TRdouble temp[16];
	trCopyMatrix(temp, IdentityMatrix);
	temp[0 * 4 + 0] = x;
	temp[1 * 4 + 1] = y;
	temp[2 * 4 + 2] = z;
	//相乘
	trMultiMatrix(CurrentMatrix, temp);
}
TRvoid trMultMatrixf(TRfloat * m)
{
	TRint i;
	TRdouble tmp[16];
	for (i = 0; i < 16;++i)
	{
		tmp[i] = m[i];
	}
	trMultiMatrix(matrix_stack[stackTop],tmp);
}
TRvoid trMultMatrixd(TRdouble * m)
{
	trMultiMatrix(matrix_stack[stackTop], m);
}
//加载矩阵
TRvoid trLoadMatrixf(TRfloat * m)
{
	TRint i;
	TRdouble tmp[16];
	for (i = 0; i < 16; ++i)
	{
		tmp[i] = m[i];
	}
	trCopyMatrix(CurrentMatrix, tmp);
}
//加载矩阵
TRvoid trLoadMatrixd(TRdouble * m)
{
	trCopyMatrix(CurrentMatrix, m);
}
//加载转置矩阵
TRvoid trLoadTransposeMatrixf(TRfloat * m)
{
	TRint i, j;
	for (i = 0; i < 4;++i)
	{
		for (j = 0; j < 4;++j)
		{
			CurrentMatrix[j*4+i] = m[i*4+j];
		}
	}
}
//加载转置矩阵
TRvoid trLoadTransposeMatrixd(TRdouble * m)
{
	TRint i, j;
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			CurrentMatrix[j * 4 + i] = m[i * 4 + j];
		}
	}
}
//压入矩阵
TRvoid trPushMatrix(TRdouble * m)
{
	trCopyMatrix(matrix_stack[stackTop],CurrentMatrix);
	++stackTop;
}
//弹出矩阵
inline TRvoid trPopMatrix(TRdouble * m)
{
	trCopyMatrix(CurrentMatrix, matrix_stack[stackTop]);
	--stackTop;
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

TRvoid trVectorMultMatrix(TRdouble * v4d, TRdouble * m16d)
{
	int i,j;
	TRdouble result[4];
	for (i = 0; i < 4;++i)
	{
		result[i] = v4d[0] * m16d[0 * 4 + i] + v4d[1] * m16d[1 * 4 + i] + v4d[2] * m16d[2 * 4 + i] + v4d[3] * m16d[3 * 4 + i];
	}
	v4d[0] = result[0];
	v4d[1] = result[1];
	v4d[2] = result[2];
	v4d[3] = result[3];
}



#endif // !MATRIX
