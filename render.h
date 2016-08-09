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



//�ɿ��ص�����ģʽ
#define TR_DEPTH_TEST 1

//�����
struct camera
{
	TRdouble position[3] = { 0.0,0.0,0.0 };
	TRdouble target[3] = { 1.0 ,0.0 ,0.0 };
};
/*************************
�ӿ�λ��
**************************/
TRint viewportx, viewporty;
TRint viewportw, viewporth;
/****************
ͼ����ɫ������
****************/

//��������С
TRuint bufferheight=0;
TRuint bufferwidth=0;
//ǰ������
ColorRGBAf * frontBuffer;
//�󻺳���
ColorRGBAf * backBuffer;
//��ǰ������
ColorRGBAf * currentColorBuffer=frontBuffer;
//�������Ƿ����
bool isAssignBuffer=false;
//�������Ƿ��
bool isOpenColorBuffer = true;
//������������ɫclearcolor
ColorRGBAi clearcolor = {0,0,0,0};
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
TRdouble * depthBuffer;
//���������ֵ(0.0-1.0)
TRdouble cleardepth;
//������Ȼ���
TRvoid trClearDepth(TRfloat n);
//�������Ƿ��
bool isOpenDepthBuffer = false;

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
TRvoid trclear(TRenum mode);

/******************

********************/





TRvoid trShadeModel(TRenum model);//������Ӱƽ��ģʽ


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
	clearcolor.red = r;
	clearcolor.green = g;
	clearcolor.blue = b;
	clearcolor.alpha = a;
}
TRvoid trDrawBuffer(TRenum mode)
{
	switch (mode)
	{
	case TR_FRONT:
		currentColorBuffer = frontBuffer;
		break;
	case TR_BACK:
		currentColorBuffer = backBuffer;
		break;
	default:
		//TODO ERROR
	}
}
TRvoid trClearDepth(TRfloat n)
{
	cleardepth = n;
}

TRvoid trclear(TRenum mode)
{
	TRint i, j;
	if (mode & TR_COLOR_BUFFER_BIT == TR_COLOR_BUFFER_BIT)
	{
		for (i = 0; i < bufferheight;++i)
		{
			for (j = 0; j < bufferwidth;++j)
			{
				currentColorBuffer[i*bufferheight + j] = clearcolor;
			}
		}
	}
	if (mode & TR_DEPTH_BUFFER_BIT == TR_DEPTH_BUFFER_BIT)
	{
		for (i = 0; i < bufferheight; ++i)
		{
			for (j = 0; j < bufferwidth; ++j)
			{
				depthBuffer[i*bufferheight + j] = cleardepth;
			}
		}
	}
	if (mode & TR_ACCUM_BUFFER_BIT == TR_ACCUM_BUFFER_BIT)
	{
		//TODO
		//������ۻ���
	}
	if (mode & TR_STENCIL_BUFFER_BIT == TR_STENCIL_BUFFER_BIT)
	{
		//TODO
		//����ģ�建��
	}
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
//�ӿڵ����ϽǺ��ӿڵĸ����
TRvoid trViewport(TRint x, TRint y, TRsizei width, TRsizei height)
{
	//��һ�ε��÷��仺�����ռ�
	if (isAssignBuffer == false)
	{
		bufferheight = height;
		bufferwidth = width;
		//��ɫ�����
		if (isOpenColorBuffer==true)
		{
			frontBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
			backBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
		}
		//��Ȼ����
		if (isOpenDepthBuffer == true)
		{
			depthBuffer = (TRdouble *)malloc(sizeof(TRdouble)*bufferheight*bufferwidth);
		}
	}
	viewportx = x;
	viewporty = y;
	viewportw = width;
	viewporth = height;
}


TRvoid trdPerspective(TRdouble fovy, TRdouble aspect, TRdouble zNear, TRdouble zFar)
{
	return TRvoid();
}
#endif // !RENDER
