#pragma once
#ifndef MATRIX
#define MATRIX
#include"types.h"

//���������ȣ���opengl�෴��transpose������

//OpenGL�е���������������ʾ����(x, y, z)��ʾ��(x',y', z',h)������x=x'/ h; y = y'/h; z=z'/ h
#define H 1

//ģ�;���
#define TR_MODELVIEW 1
TRdouble ModelViewMatrix[16]= { 
	1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0 };
//ͶӰ����
#define TR_PROJECTION 2
TRdouble ProjectionMatrix[16] = {
	1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0 };
//�������
#define TR_TEXTURE  3
TRdouble TextureMatrix[16] = { 
	1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0 };
//��ɫ����
#define TR_COLOR 4
TRdouble ColorMatrix[16] = { 
	1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0 };
//��ǰģ��
TRdouble* CurrentMatrix=ModelViewMatrix;

//��λ����
TRdouble IdentityMatrix[16] = { 1.0,0.0,0.0,0.0,
								0.0,1.0,0.0,0.0,
								0.0,0.0,1.0,0.0,
								0.0,0.0,0.0,1.0 };


//ѡ��ͶӰ����
TRvoid trMatrixMode(TRenum mode);
//���ؾ���
TRvoid trLoadMatrixf(TRfloat* m);
//���ؾ���
TRvoid trLoadMatrixd(TRdouble* m);
//����ת�þ���
TRvoid trLoadTransposeMatrixf(TRfloat *m);
//����ת�þ���
TRvoid trLoadTransposeMatrixd(TRdouble *m);

//ѹ������ջ
TRvoid trPushMatrix(TRdouble *m);
//���������ջ
TRvoid trPopMatrix(TRdouble *m);

//���ص�λ����
TRvoid trLoadIdentity();
//ƽ�ƾ���
TRvoid trTranslatef(TRfloat x, TRfloat y, TRfloat z);
TRvoid trTranslated(TRdouble x, TRdouble y, TRdouble z);
//��ת����
TRvoid trRotatef();
TRvoid trScalef();
//�ҳ�ջ�����󲢷Ż�ջ��
TRvoid trMultMatrixf(TRfloat *m);
TRvoid trMultMatrixd(TRdouble *m);
//���ǽ���ǰ������һ��͸�Ӿ�����ˣ��ѵ�ǰ����ת���͸�Ӿ���
TRvoid trFrustum(TRdouble right, TRdouble bottom, TRdouble top, TRdouble nearVal, TRdouble farVal);

//����ǰ�Ŀ��ӿռ�����Ϊ��ͶӰ�ռ�
TRvoid trOrtho(TRdouble left, TRdouble right, TRdouble bottom, TRdouble top, TRdouble near, TRdouble far);

//matrix stack
#define MATRIX_STACK_MAX 32
TRdouble matrix_stack[MATRIX_STACK_MAX][16];
TRint stackTop=0;

//toolkit
//���ƾ���
TRvoid trCopyMatrix(TRdouble * to,TRdouble * from);
//�������
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
//���ص�λ����
TRvoid trLoadIdentity()
{
	trCopyMatrix(matrix_stack[stackTop],IdentityMatrix);
}
//ƽ�ƾ���
TRvoid trTranslatef(TRfloat x, TRfloat y, TRfloat z)
{

	return TRvoid();
}
//ƽ�ƾ���
TRvoid trTranslated(TRdouble x, TRdouble y, TRdouble z)
{
	return TRvoid();
}
//���ؾ���
TRvoid trLoadMatrixf(TRfloat * m)
{
	trCopyMatrix(CurrentMatrix, (TRdouble *)m);
}
//���ؾ���
TRvoid trLoadMatrixd(TRdouble * m)
{
	trCopyMatrix(CurrentMatrix, m);
}
//����ת�þ���
TRvoid trLoadTransposeMatrixf(TRfloat * m)
{
	return TRvoid();
}
//����ת�þ���
TRvoid trLoadTransposeMatrixd(TRdouble * m)
{
	return TRvoid();
}
//ѹ�����
inline TRvoid trPushMatrix(TRdouble * m)
{
	return TRvoid();
}
//��������
inline TRvoid trPopMatrix(TRdouble * m)
{
	return TRvoid();
}
//���ƾ���
TRvoid trCopyMatrix(TRdouble * to, TRdouble * from)
{
	TRint i;
	for (i = 0; i < 16;++i)
	{
		to[i] = from[i];
	}
}
//�ҳ˾���
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
