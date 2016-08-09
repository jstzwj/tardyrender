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


//可开关的所有模式
#define TR_DEPTH_TEST 1

//摄像机
struct camera
{
	TRdouble position[3] = { 0.0,0.0,0.0 };
	TRdouble target[3] = { 1.0 ,0.0 ,0.0 };
};

//图像缓冲区
//缓冲区大小
TRuint height=0;
TRuint width=0;
//前缓冲区
TRubyte * frontBuffer;
//后缓冲区
TRubyte * backBuffer;
//当前缓冲区
TRubyte * currentBuffer;
//缓冲区是否分配
bool isAssignBuffer=false;
//缓冲区背景颜色clearcolor
ColorRGBAi clearcolor = {0,0,0,0};


//深度缓冲区
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



TRvoid trShadeModel(TRenum model);//设置阴影平滑模式
//改变窗口的背景颜色的设置
TRvoid trClearColor(TRfloat r, TRfloat g, TRfloat b, TRfloat a );
//设置深度缓存
TRvoid trClearDepth(TRfloat n);
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
