#pragma once
#ifndef RENDER
#define RENDER
#include<stdlib.h>

#include"types.h"
#include"matrix.h"
#include"error.h"



#define GL_PERSPECTIVE_CORRECTION_HINT
#define GL_NICEST



//�ɿ��ص�����ģʽ
#define TR_DEPTH_TEST 1

////�����
//struct camera
//{
//	TRdouble position[3] = { 0.0,0.0,0.0 };
//	TRdouble target[3] = { 1.0 ,0.0 ,0.0 };
//};
/*************************
�ӿ�λ��
**************************/
extern TRint viewportx, viewporty;
extern TRint viewportw, viewporth;
/*****************************************************
֡������
*******************************************************/
/****************
ͼ����ɫ������
****************/

//��������С
extern TRuint bufferheight;
extern TRuint bufferwidth;
//ǰ������
extern ColorRGBAf * frontBuffer;
//�󻺳���
extern ColorRGBAf * backBuffer;
//��ǰ������
extern ColorRGBAf * currentColorBuffer;
//�������Ƿ����
extern TRbool isAssignBuffer;
//�������Ƿ��
extern TRbool isOpenColorBuffer;
//������������ɫclearcolor
extern ColorRGBAf clearcolor;
//�ı䴰�ڵı�����ɫ������
TRvoid trClearColor(TRfloat r, TRfloat g, TRfloat b, TRfloat a);
//ѡ�񻺳���
#define TR_FRONT 1
#define TR_BACK 2
TRvoid trDrawBuffer(TRenum mode);

/**********************
��Ȼ�����
***********************/
//��ȱȽϺ���
//��ͨ������������ֵ��ȡ���ο�ֵ��
#define TR_NEVER
//�����������ֵС�ڲο�ֵ����ͨ��
#define TR_LESS
//�����������ֵ���ڲο�ֵ����ͨ��
#define TR_EQUAL
//�����������ֵС�ڻ���ڲο�ֵ����ͨ��
#define TR_LEQUAL
//�����������ֵ���ڲο�ֵ����ͨ��
#define TR_GREATER
//�����������ֵ�����ڲο�ֵ����ͨ��
#define TR_NOTE_QUAL
//�����������ֵ���ڻ���ڲο�ֵ����ͨ��
#define TR_GEQUAL
//����ͨ������������ֵȡ���ο�ֵ��
#define TR_ALWAYS

//������
extern TRdouble * depthBuffer;
//���������ֵ(0.0-1.0)
extern TRdouble cleardepth;
//�������Ƿ��
TRbool isOpenDepthBuffer;
//������Ȼ���
TRvoid trClearDepth(TRfloat n);


/************************
ģ�建����
***********************/



/*********************
��ջ�����
********************/
//��ǰ��д����ɫ����
#define TR_COLOR_BUFFER_BIT 1
//��Ȼ���
#define TR_DEPTH_BUFFER_BIT 2
//�ۻ�����
#define	TR_ACCUM_BUFFER_BIT 4
//ģ�建��
#define TR_STENCIL_BUFFER_BIT 8
TRvoid trClear(TRenum mode);

/******************
Opengl 1.0 ��ͼ����
********************/
/* BeginMode */
#define TR_POINTS 1
#define TR_LINES 2
#define TR_POLYGON 3
#define TR_TRIANGLES 4
#define TR_QUADS 5
#define TR_LINE_STRIP 6
#define TR_LINE_LOOP 7
#define TR_TRIANGLE_STRIP 8
#define TR_TRIANGLE_FAN 9
#define TRQUAD_STRIP 10
extern TRenum currentDrawMode;
extern ColorRGBAf currentColor;
//����
extern TRdouble vec1[4];
extern ColorRGBAf color1;
extern TRdouble vec2[4];
extern ColorRGBAf color2;
extern TRdouble vec3[4];
extern ColorRGBAf color3;
extern TRint vec_num;

TRvoid trBegin(TRenum mode);
TRvoid trEnd();
TRvoid trFinish();
TRvoid trFlush();

TRvoid trPutPoint(TRint x, TRint y, TRdouble z,ColorRGBAf color);
TRvoid trDrawPoint(TRdouble * v4,ColorRGBAf vec_color);
TRvoid trDrawLine(TRdouble * start, ColorRGBAf startcolor, TRdouble * end, ColorRGBAf endcolor);
TRvoid trDrawTriangle(TRdouble *v1, TRdouble *v2, TRdouble *v3);


//�������һ������
TRvoid trVertex(const TRdouble *v);

TRvoid trVertex2d(TRdouble x, TRdouble y);
TRvoid trVertex2dv(const TRdouble *v);
TRvoid trVertex2f(TRfloat x, TRfloat y);
TRvoid trVertex2fv(const TRfloat *v);
TRvoid trVertex2i(TRint x, TRint y);
TRvoid trVertex2iv(const TRint *v);
TRvoid trVertex2s(TRshort x, TRshort y);
TRvoid trVertex2sv(const TRshort *v);
TRvoid trVertex3d(TRdouble x, TRdouble y, TRdouble z);
TRvoid trVertex3dv(const TRdouble *v);
TRvoid trVertex3f(TRfloat x, TRfloat y, TRfloat z);
TRvoid trVertex3fv(const TRfloat *v);
TRvoid trVertex3i(TRint x, TRint y, TRint z);
TRvoid trVertex3iv(const TRint *v);
TRvoid trVertex3s(TRshort x, TRshort y, TRshort z);
TRvoid trVertex3sv(const TRshort *v);
TRvoid trVertex4d(TRdouble x, TRdouble y, TRdouble z, TRdouble w);
TRvoid trVertex4dv(const TRdouble *v);
TRvoid trVertex4f(TRfloat x, TRfloat y, TRfloat z, TRfloat w);
TRvoid trVertex4fv(const TRfloat *v);
TRvoid trVertex4i(TRint x, TRint y, TRint z, TRint w);
TRvoid trVertex4iv(const TRint *v);
TRvoid trVertex4s(TRshort x, TRshort y, TRshort z, TRshort w);
TRvoid trVertex4sv(const TRshort *v);
//ָ��һ����ɫ
TRvoid trColor(const TRfloat *v);

TRvoid trColor3b(TRbyte red, TRbyte green, TRbyte blue);
TRvoid trColor3bv(const TRbyte *v);
TRvoid trColor3d(TRdouble red, TRdouble green, TRdouble blue);
TRvoid trColor3dv(const TRdouble *v);
TRvoid trColor3f(TRfloat red, TRfloat green, TRfloat blue);
TRvoid trColor3fv(const TRfloat *v);
TRvoid trColor3i(TRint red, TRint green, TRint blue);
TRvoid trColor3iv(const TRint *v);
TRvoid trColor3s(TRshort red, TRshort green, TRshort blue);
TRvoid trColor3sv(const TRshort *v);
TRvoid trColor3ub(TRubyte red, TRubyte green, TRubyte blue);
TRvoid trColor3ubv(const TRubyte *v);
TRvoid trColor3ui(TRuint red, TRuint green, TRuint blue);
TRvoid trColor3uiv(const TRuint *v);
TRvoid trColor3us(TRushort red, TRushort green, TRushort blue);
TRvoid trColor3usv(const TRushort *v);
TRvoid trColor4b(TRbyte red, TRbyte green, TRbyte blue, TRbyte alpha);
TRvoid trColor4bv(const TRbyte *v);
TRvoid trColor4d(TRdouble red, TRdouble green, TRdouble blue, TRdouble alpha);
TRvoid trColor4dv(const TRdouble *v);
TRvoid trColor4f(TRfloat red, TRfloat green, TRfloat blue, TRfloat alpha);
TRvoid trColor4fv(const TRfloat *v);
TRvoid trColor4i(TRint red, TRint green, TRint blue, TRint alpha);
TRvoid trColor4iv(const TRint *v);
TRvoid trColor4s(TRshort red, TRshort green, TRshort blue, TRshort alpha);
TRvoid trColor4sv(const TRshort *v);
TRvoid trColor4ub(TRubyte red, TRubyte green, TRubyte blue, TRubyte alpha);
TRvoid trColor4ubv(const TRubyte *v);
TRvoid trColor4ui(TRuint red, TRuint green, TRuint blue, TRuint alpha);
TRvoid trColor4uiv(const TRuint *v);
TRvoid trColor4us(TRushort red, TRushort green, TRushort blue, TRushort alpha);
TRvoid trColor4usv(const TRushort *v);



/*********************
����״̬����ʾ״̬��
***********************/
extern TRenum state;

/***********************
��ɫƽ��ģʽ
**************************/
#define TR_FLAT 1
#define TR_SMOOTH 2
extern TRenum ShadeModel;
TRvoid trShadeModel(TRenum model);//������Ӱƽ��ģʽ


TRvoid trEnable(TRenum mode);//������Ȳ���
TRvoid trDepthFunc(TRenum mode);//������Ȳ�������
TRvoid trHint();//����͸��У��


//���õ�ǰ�ӿ�
TRvoid trViewport(TRint x, TRint y, TRsizei width, TRsizei height);

//����͸��ͶӰ����
TRvoid trdPerspective(TRdouble fovy, TRdouble aspect, TRdouble zNear, TRdouble zFar);













#endif // !RENDER
