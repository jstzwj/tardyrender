#pragma once
#ifndef RENDER
#define RENDER
#include"types.h"
#include"matrix.h"
#include"error.h"

TRenum ShadeModel;
#define TR_FLAT
#define TR_SMOOTH

#define GL_LEQUAL

#define GL_PERSPECTIVE_CORRECTION_HINT
#define GL_NICEST

#define GL_PROJECTION
#define GL_MODELVIEW


//�ɿ��ص�����ģʽ
#define TR_DEPTH_TEST 1

//�����
struct camera
{
	TRdouble position[3] = { 0.0,0.0,0.0 };
	TRdouble target[3] = { 1.0 ,0.0 ,0.0 };
};

//ͼ�񻺳���
//��������С
TRuint height=0;
TRuint width=0;
//ǰ������
TRubyte * frontBuffer;
//�󻺳���
TRubyte * backBuffer;
//��ǰ������
TRubyte * currentBuffer;
//�������Ƿ����
bool isAssignBuffer=false;
//������������ɫclearcolor
ColorRGBAi clearcolor = {0,0,0,0};


//��Ȼ�����
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
TRdouble * depthBuffer;
//���������ֵ(0.0-1.0)
TRdouble cleardepth;



TRvoid trShadeModel(TRenum model);//������Ӱƽ��ģʽ
//�ı䴰�ڵı�����ɫ������
TRvoid trClearColor(TRfloat r, TRfloat g, TRfloat b, TRfloat a );
//������Ȼ���
TRvoid trClearDepth(TRfloat n);
TRvoid trEnable(TRenum mode);//������Ȳ���
TRvoid trDepthFunc(TRenum mode);//������Ȳ�������
TRvoid trHint();//����͸��У��


//���õ�ǰ�ӿ�
TRvoid trViewport(TRint x, TRint y, TRsizei width, TRsizei height);

//����͸��ͶӰ����
TRvoid trdPerspective(TRdouble fovy, TRdouble aspect, TRdouble zNear, TRdouble zFar);



TRvoid trShadeModel(TRenum model)
{
	return TRvoid();
}
TRvoid trClearColor(TRfloat r, TRfloat g, TRfloat b, TRfloat a)
{
	clearcolor.red = r * 255;
	clearcolor.green = g * 255;
	clearcolor.blue = b * 255;
	clearcolor.alpha = a * 255;
}
TRvoid trClearDepth(TRfloat n)
{
	cleardepth = n;
}

TRvoid trEnable(TRenum mode)
{
	switch (mode)
	{
	case TR_DEPTH_TEST:
		break;

	default:
		callWarning("unknown mode");
		break;
	}
}
TRvoid trDepthFunc(TRenum mode)
{
	return TRvoid();
}
TRvoid trHint()
{
	return TRvoid();
}
inline TRvoid trViewport(TRint x, TRint y, TRsizei width, TRsizei height)
{
	return TRvoid();
}


inline TRvoid trdPerspective(TRdouble fovy, TRdouble aspect, TRdouble zNear, TRdouble zFar)
{
	return TRvoid();
}
#endif // !RENDER
