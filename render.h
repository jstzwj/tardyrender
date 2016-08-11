#pragma once
#ifndef RENDER
#define RENDER
#include<stdlib.h>

#include"types.h"
#include"matrix.h"
#include"error.h"



#define GL_PERSPECTIVE_CORRECTION_HINT
#define GL_NICEST



//可开关的所有模式
#define TR_DEPTH_TEST 1

////摄像机
//struct camera
//{
//	TRdouble position[3] = { 0.0,0.0,0.0 };
//	TRdouble target[3] = { 1.0 ,0.0 ,0.0 };
//};
/*************************
视口位置
**************************/
extern TRint viewportx, viewporty;
extern TRint viewportw, viewporth;
/*****************************************************
帧缓冲区
*******************************************************/
/****************
图像颜色缓冲区
****************/

//缓冲区大小
extern TRuint bufferheight;
extern TRuint bufferwidth;
//前缓冲区
extern ColorRGBAf * frontBuffer;
//后缓冲区
extern ColorRGBAf * backBuffer;
//当前缓冲区
extern ColorRGBAf * currentColorBuffer;
//缓冲区是否分配
extern TRbool isAssignBuffer;
//缓冲区是否打开
extern TRbool isOpenColorBuffer;
//缓冲区背景颜色clearcolor
extern ColorRGBAf clearcolor;
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
extern TRdouble * depthBuffer;
//缓冲区清除值(0.0-1.0)
extern TRdouble cleardepth;
//缓冲区是否打开
TRbool isOpenDepthBuffer;
//设置深度缓存
TRvoid trClearDepth(TRfloat n);


/************************
模板缓冲区
***********************/



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
Opengl 1.0 绘图函数
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
//向量
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


//用来标出一个顶点
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
//指定一个颜色
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
隐藏状态，表示状态机
***********************/
extern TRenum state;

/***********************
颜色平滑模式
**************************/
#define TR_FLAT 1
#define TR_SMOOTH 2
extern TRenum ShadeModel;
TRvoid trShadeModel(TRenum model);//设置阴影平滑模式


TRvoid trEnable(TRenum mode);//允许深度测试
TRvoid trDepthFunc(TRenum mode);//设置深度测试类型
TRvoid trHint();//进行透视校正


//重置当前视口
TRvoid trViewport(TRint x, TRint y, TRsizei width, TRsizei height);

//建立透视投影矩阵
TRvoid trdPerspective(TRdouble fovy, TRdouble aspect, TRdouble zNear, TRdouble zFar);













#endif // !RENDER
