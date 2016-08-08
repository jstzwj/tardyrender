#pragma once
#ifndef RENDER
#define RENDER
#include"types.h"
#include"matrix.h"


TRenum ShadeModel;
#define TR_FLAT


#define GL_LEQUAL

#define GL_PERSPECTIVE_CORRECTION_HINT
#define GL_NICEST

#define GL_PROJECTION
#define GL_MODELVIEW

//摄像机
struct camera
{
	TRdouble position[3] = { 0.0,0.0,0.0 };
	TRdouble target[3] = { 1.0 ,0.0 ,0.0 };
};




TRvoid trShadeModel(TRenum model);//设置阴影平滑模式
TRvoid trClearColor(TRfloat r, TRfloat g, TRfloat b, TRfloat a );//改变窗口的背景颜色，不过我这里貌似设置后并没有什么效果
TRvoid trClearDepth(TRfloat n);//设置深度缓存
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
	return TRvoid();
}
TRvoid trClearDepth(TRfloat n)
{
	return TRvoid();
}

TRvoid trEnable(TRenum mode)
{
	return TRvoid();
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
