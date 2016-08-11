#pragma once
#ifndef MATRIX
#define MATRIX
#include"types.h"
#include"math.h"


//���������ȣ���opengl�෴��transpose������

//OpenGL�е���������������ʾ����(x, y, z)��ʾ��(x',y', z',h)������x=x'/ h; y = y'/h; z=z'/ h
#define H 1

//ģ�;���
#define TR_MODELVIEW 1
extern TRdouble ModelViewMatrix[16];
//ͶӰ����
#define TR_PROJECTION 2
extern TRdouble ProjectionMatrix[16];
//�������
#define TR_TEXTURE  3
extern TRdouble TextureMatrix[16];
//��ɫ����
#define TR_COLOR 4
extern TRdouble ColorMatrix[16];
//��ǰģ��
extern TRdouble* CurrentMatrix;

//��λ����
extern TRdouble IdentityMatrix[16];


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
TRvoid trRotated(TRdouble angle, TRdouble x, TRdouble y, TRdouble z);
TRvoid trRotatef(TRfloat angle, TRfloat x, TRfloat y, TRfloat z);

//���ž���
TRvoid trScalef(TRfloat x, TRfloat y, TRfloat z);
TRvoid trScaled(TRdouble x, TRdouble y, TRdouble z);
//�ҳ�ջ�����󲢷Ż�ջ��
TRvoid trMultMatrixf(TRfloat *m);
TRvoid trMultMatrixd(TRdouble *m);
//���ǽ���ǰ������һ��͸�Ӿ�����ˣ��ѵ�ǰ����ת���͸�Ӿ���
TRvoid trFrustum(TRdouble right, TRdouble bottom, TRdouble top, TRdouble nearVal, TRdouble farVal);

//����ǰ�Ŀ��ӿռ�����Ϊ��ͶӰ�ռ�
TRvoid trOrtho(TRdouble left, TRdouble right, TRdouble bottom, TRdouble top, TRdouble near, TRdouble far);

//matrix stack
#define MATRIX_STACK_MAX 32
extern TRdouble matrix_stack[MATRIX_STACK_MAX][16];
extern TRint stackTop;

//toolkit
//���ƾ���
TRvoid trCopyMatrix(TRdouble * to,TRdouble * from);
//�������
TRvoid trMultiMatrix(TRdouble * lhs, TRdouble * rhs);
//������һ��
TRvoid trNormalizeVector(TRdouble *vec);
//�����ҳ˾���
TRvoid trVectorMultMatrix(TRdouble *v4d,TRdouble *m16d);



#endif // !MATRIX
