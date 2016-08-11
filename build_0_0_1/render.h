#pragma once
#ifndef RENDER
#define RENDER
#include"types.h"
#include"matrix.h"
#include"error.h"

TRenum ShadeModel;
#define TR_FLAT
#define TR_SMOOTH


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
TRbool isAssignBuffer=TR_FALSE;
//�������Ƿ��
TRbool isOpenColorBuffer = TR_TRUE;
//������������ɫclearcolor
ColorRGBAf clearcolor = {0,0,0,1};
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
TRvoid trClear(TRenum mode);

/******************
��ͼ����
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
TRenum currentDrawMode=64;
ColorRGBAf currentColor = {1.0f,1.0f,1.0f,1.0f};

TRvoid trBegin(TRenum mode);
TRvoid trEnd();
TRvoid trFinish();
TRvoid trFlush();

TRvoid trDrawPoint(TRdouble * v4);



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




/*********************
����״̬����ʾ״̬��
***********************/
TRenum state;



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
		break;
	}
}
TRvoid trClearDepth(TRfloat n)
{
	cleardepth = n;
}

TRvoid trClear(TRenum mode)
{
	TRuint i, j;
	//��ɫ�����
	if (isOpenColorBuffer == TR_TRUE)
	{
		if ((mode & TR_COLOR_BUFFER_BIT) == TR_COLOR_BUFFER_BIT)
		{
			for (i = 0; i < bufferheight; ++i)
			{
				for (j = 0; j < bufferwidth; ++j)
				{
					currentColorBuffer[i*bufferwidth + j] = clearcolor;
				}
			}
		}
	}
	//��Ȼ����
	if (isOpenDepthBuffer== TR_TRUE)
	{
		if ((mode & TR_DEPTH_BUFFER_BIT) == TR_DEPTH_BUFFER_BIT)
		{
			for (i = 0; i < bufferheight; ++i)
			{
				for (j = 0; j < bufferwidth; ++j)
				{
					depthBuffer[i*bufferwidth + j] = cleardepth;
				}
			}
		}
	}
	//TODO �жϸû����Ƿ�򿪣���ֹ�ڴ�й©
	if ((mode & TR_ACCUM_BUFFER_BIT) == TR_ACCUM_BUFFER_BIT)
	{
		//TODO
		//������ۻ���
	}
	if ((mode & TR_STENCIL_BUFFER_BIT) == TR_STENCIL_BUFFER_BIT)
	{
		//TODO
		//����ģ�建��
	}
}

TRvoid trBegin(TRenum mode)
{
	currentDrawMode = mode;
}

TRvoid trEnd()
{
	return TRvoid();
}

TRvoid trFinish()
{
	return TRvoid();
}

TRvoid trFlush()
{
	return TRvoid();
}

TRvoid trDrawPoint(TRdouble * v4)
{
	//��һ��
	if (v4[3] != 0)
	{
		v4[0] /= v4[3];
		v4[1] /= v4[3];
		v4[2] /= v4[3];
		v4[3] = 1.0;
	}

	//�ü�
	if (v4[0]>=-1.0&&v4[0]<=1.0
		&&v4[1] >= -1.0&&v4[1] <= 1.0)
	{
		if (isOpenColorBuffer == true)
		{
			currentColorBuffer[(TRuint)((v4[1]*(bufferheight-1))*bufferwidth + (v4[0]* (bufferwidth-1)))] = currentColor;
		}
		if (isOpenDepthBuffer==true)
		{
			depthBuffer[(TRuint)((v4[1] * (bufferheight - 1))*bufferwidth + (v4[0] * (bufferwidth - 1)))] = v4[2];
		}

	}
}

TRvoid trVertex2d(TRdouble x, TRdouble y)
{
	return TRvoid();
}

TRvoid trVertex2dv(const TRdouble * v)
{
	return TRvoid();
}

TRvoid trVertex2f(TRfloat x, TRfloat y)
{
	TRdouble point[3];
	point[0] = x;
	point[1] = y;
	point[2] = 0.0;

}

inline TRvoid trVertex2fv(const TRfloat * v)
{
	return TRvoid();
}

inline TRvoid trVertex2i(TRint x, TRint y)
{
	return TRvoid();
}

inline TRvoid trVertex2iv(const TRint * v)
{
	return TRvoid();
}

inline TRvoid trVertex2s(TRshort x, TRshort y)
{
	return TRvoid();
}

inline TRvoid trVertex2sv(const TRshort * v)
{
	return TRvoid();
}

inline TRvoid trVertex3d(TRdouble x, TRdouble y, TRdouble z)
{
	return TRvoid();
}

inline TRvoid trVertex3dv(const TRdouble * v)
{
	return TRvoid();
}

inline TRvoid trVertex3f(TRfloat x, TRfloat y, TRfloat z)
{
	return TRvoid();
}

inline TRvoid trVertex3fv(const TRfloat * v)
{
	return TRvoid();
}

inline TRvoid trVertex3i(TRint x, TRint y, TRint z)
{
	return TRvoid();
}

inline TRvoid trVertex3iv(const TRint * v)
{
	return TRvoid();
}

inline TRvoid trVertex3s(TRshort x, TRshort y, TRshort z)
{
	return TRvoid();
}

inline TRvoid trVertex3sv(const TRshort * v)
{
	return TRvoid();
}

TRvoid trVertex4d(TRdouble x, TRdouble y, TRdouble z, TRdouble w)
{
	//����
	TRdouble vec[4];
	//����
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = w;
	trVertex4dv(vec);
}
//vertexϵ�к�������������
TRvoid trVertex4dv(const TRdouble * v)
{
	TRint i;
	//�豸����
	TRdouble transformMatrix[16] = { 1.0,0.0,0.0,0.0,
									0.0,1.0,0.0,0.0,
									0.0,0.0,1.0,0.0,
									0.0,0.0,0.0,1.0 };
	//����
	TRdouble vec[4];
	//��������
	vec[0] = v[0];
	vec[1] = v[1];
	vec[2] = v[2];
	vec[3] = v[3];
	//���硢ģ�;���
	trMultiMatrix(transformMatrix, ModelViewMatrix);
	//ͶӰ����
	trMultiMatrix(transformMatrix,ProjectionMatrix);
	switch (currentDrawMode)
	{
	case TR_POINTS:
		//ת�����豸����
		trVectorMultMatrix(vec,transformMatrix);
		//���㵽��ǰ������
		trDrawPoint(vec);
		break;
	case TR_LINES:
		break;
	case TR_POLYGON:
		break;
	case TR_TRIANGLES:
		break;
	case TR_QUADS:
		break;
	case TR_LINE_STRIP:
		break;
	case TR_LINE_LOOP:
		break;
	case TR_TRIANGLE_STRIP:
		break;
	case TR_TRIANGLE_FAN:
		break;
	case TRQUAD_STRIP:
		break;
	}
}

inline TRvoid trVertex4f(TRfloat x, TRfloat y, TRfloat z, TRfloat w)
{
	return TRvoid();
}

inline TRvoid trVertex4fv(const TRfloat * v)
{
	return TRvoid();
}

inline TRvoid trVertex4i(TRint x, TRint y, TRint z, TRint w)
{
	return TRvoid();
}

inline TRvoid trVertex4iv(const TRint * v)
{
	return TRvoid();
}

inline TRvoid trVertex4s(TRshort x, TRshort y, TRshort z, TRshort w)
{
	return TRvoid();
}

inline TRvoid trVertex4sv(const TRshort * v)
{
	return TRvoid();
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
	//����Ϊ0
	if (width<=0||height<=0)
	{
		return;
	}
	//��һ�ε��÷��仺�����ռ�
	if (isAssignBuffer == TR_FALSE)
	{
		isAssignBuffer = TR_TRUE;
		bufferheight = height;
		bufferwidth = width;
		//��ɫ�����
		if (isOpenColorBuffer== TR_TRUE)
		{
			frontBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
			backBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
			currentColorBuffer = frontBuffer;
		}
		//��Ȼ����
		if (isOpenDepthBuffer == TR_TRUE)
		{
			depthBuffer = (TRdouble *)malloc(sizeof(TRdouble)*bufferheight*bufferwidth);
		}
	}
	else
	{
		if (width>bufferwidth||height>bufferheight)
		{
			bufferheight = height;
			bufferwidth = width;
			//��ɫ�����
			if (isOpenColorBuffer == TR_TRUE)
			{
				free(frontBuffer);
				free(backBuffer);
				frontBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
				backBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
				currentColorBuffer = frontBuffer;
			}
			//��Ȼ����
			if (isOpenDepthBuffer == TR_TRUE)
			{
				free(depthBuffer);
				depthBuffer = (TRdouble *)malloc(sizeof(TRdouble)*bufferheight*bufferwidth);
			}
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
