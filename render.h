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



//可开关的所有模式
#define TR_DEPTH_TEST 1

//摄像机
struct camera
{
	TRdouble position[3] = { 0.0,0.0,0.0 };
	TRdouble target[3] = { 1.0 ,0.0 ,0.0 };
};
/*************************
视口位置
**************************/
TRint viewportx, viewporty;
TRint viewportw, viewporth;
/****************
图像颜色缓冲区
****************/

//缓冲区大小
TRuint bufferheight=0;
TRuint bufferwidth=0;
//前缓冲区
ColorRGBAf * frontBuffer;
//后缓冲区
ColorRGBAf * backBuffer;
//当前缓冲区
ColorRGBAf * currentColorBuffer=frontBuffer;
//缓冲区是否分配
bool isAssignBuffer=false;
//缓冲区是否打开
bool isOpenColorBuffer = true;
//缓冲区背景颜色clearcolor
ColorRGBAi clearcolor = {0,0,0,0};
//改变窗口的背景颜色的设置
TRvoid trClearColor(TRfloat r, TRfloat g, TRfloat b, TRfloat a);
//选择缓冲区
#define TR_FRONT 1
#define TR_BACK 2
TRvoid trDrawBuffer(TRenum mode);

/**********************
深度缓冲区
***********************/
//深度比较函数
//不通过（输入的深度值不取代参考值）
#define TR_NEVER
//如果输入的深度值小于参考值，则通过
#define TR_LESS
//如果输入的深度值等于参考值，则通过
#define TR_EQUAL
//如果输入的深度值小于或等于参考值，则通过
#define TR_LEQUAL
//如果输入的深度值大于参考值，则通过
#define TR_GREATER
//如果输入的深度值不等于参考值，则通过
#define TR_NOTE_QUAL
//如果输入的深度值大于或等于参考值，则通过
#define TR_GEQUAL
//总是通过（输入的深度值取代参考值）
#define TR_ALWAYS

//缓冲区
TRdouble * depthBuffer;
//缓冲区清除值(0.0-1.0)
TRdouble cleardepth;
//设置深度缓存
TRvoid trClearDepth(TRfloat n);
//缓冲区是否打开
bool isOpenDepthBuffer = false;

/*********************
清空缓冲区
********************/
//当前可写的颜色缓冲
#define TR_COLOR_BUFFER_BIT 1
//深度缓冲
#define TR_DEPTH_BUFFER_BIT 2
//累积缓冲
#define	TR_ACCUM_BUFFER_BIT 4
//模板缓冲
#define TR_STENCIL_BUFFER_BIT 8
TRvoid trclear(TRenum mode);

/******************

********************/





TRvoid trShadeModel(TRenum model);//设置阴影平滑模式


TRvoid trEnable(TRenum mode);//允许深度测试
TRvoid trDepthFunc(TRenum mode);//设置深度测试类型
TRvoid trHint();//进行透视校正


//重置当前视口
TRvoid trViewport(TRint x, TRint y, TRsizei width, TRsizei height);

//建立透视投影矩阵
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
		//清理积累缓存
	}
	if (mode & TR_STENCIL_BUFFER_BIT == TR_STENCIL_BUFFER_BIT)
	{
		//TODO
		//清理模板缓存
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
//视口的左上角和视口的高与宽
TRvoid trViewport(TRint x, TRint y, TRsizei width, TRsizei height)
{
	//第一次调用分配缓冲区空间
	if (isAssignBuffer == false)
	{
		bufferheight = height;
		bufferwidth = width;
		//颜色缓冲打开
		if (isOpenColorBuffer==true)
		{
			frontBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
			backBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
		}
		//深度缓冲打开
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
