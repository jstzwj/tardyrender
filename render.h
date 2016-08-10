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
TRbool isAssignBuffer=TR_FALSE;
//缓冲区是否打开
TRbool isOpenColorBuffer = TR_TRUE;
//缓冲区背景颜色clearcolor
ColorRGBAf clearcolor = {0,0,0,1};
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
TRvoid trClear(TRenum mode);

/******************
绘图函数
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
隐藏状态，表示状态机
***********************/
TRenum state;



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
	//颜色缓冲打开
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
	//深度缓冲打开
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
	//TODO 判断该缓冲是否打开，防止内存泄漏
	if ((mode & TR_ACCUM_BUFFER_BIT) == TR_ACCUM_BUFFER_BIT)
	{
		//TODO
		//清理积累缓存
	}
	if ((mode & TR_STENCIL_BUFFER_BIT) == TR_STENCIL_BUFFER_BIT)
	{
		//TODO
		//清理模板缓存
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
	//归一化
	if (v4[3] != 0)
	{
		v4[0] /= v4[3];
		v4[1] /= v4[3];
		v4[2] /= v4[3];
		v4[3] = 1.0;
	}

	//裁剪
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
	//向量
	TRdouble vec[4];
	//复制
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = w;
	trVertex4dv(vec);
}
//vertex系列函数都会调用这个
TRvoid trVertex4dv(const TRdouble * v)
{
	TRint i;
	//设备矩阵
	TRdouble transformMatrix[16] = { 1.0,0.0,0.0,0.0,
									0.0,1.0,0.0,0.0,
									0.0,0.0,1.0,0.0,
									0.0,0.0,0.0,1.0 };
	//向量
	TRdouble vec[4];
	//复制向量
	vec[0] = v[0];
	vec[1] = v[1];
	vec[2] = v[2];
	vec[3] = v[3];
	//世界、模型矩阵
	trMultiMatrix(transformMatrix, ModelViewMatrix);
	//投影矩阵
	trMultiMatrix(transformMatrix,ProjectionMatrix);
	switch (currentDrawMode)
	{
	case TR_POINTS:
		//转换到设备向量
		trVectorMultMatrix(vec,transformMatrix);
		//画点到当前缓冲区
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
//视口的左上角和视口的高与宽
TRvoid trViewport(TRint x, TRint y, TRsizei width, TRsizei height)
{
	//长宽不为0
	if (width<=0||height<=0)
	{
		return;
	}
	//第一次调用分配缓冲区空间
	if (isAssignBuffer == TR_FALSE)
	{
		isAssignBuffer = TR_TRUE;
		bufferheight = height;
		bufferwidth = width;
		//颜色缓冲打开
		if (isOpenColorBuffer== TR_TRUE)
		{
			frontBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
			backBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
			currentColorBuffer = frontBuffer;
		}
		//深度缓冲打开
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
			//颜色缓冲打开
			if (isOpenColorBuffer == TR_TRUE)
			{
				free(frontBuffer);
				free(backBuffer);
				frontBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
				backBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
				currentColorBuffer = frontBuffer;
			}
			//深度缓冲打开
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
