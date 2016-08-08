#pragma once
#ifndef SHAPE
#define SHAPE

#include"types.h"

#define GL_ALIASED_LINE_WIDTH_RANGE
#define GL_SMOOTH_LINE_WIDTH_RANGE
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY
#define GL_LINE_STIPPLE


//设置被渲染点的宽度，以像素为单位，默认为1  
TRvoid trPointSize(TRfloat size);

TRvoid trLineWidth(TRfloat width);
//设置直线的宽度，默认为1  
TRvoid trGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE);//查询带锯齿直线宽度的范围  
TRvoid trGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE);//查询带平滑直线宽度的范围  
TRvoid trGetFloatv(GL_SMOOTH_LINE_WIDTH_GRANULARITY);//查询平滑直线粒度的范围  

TRvoid trEnable(GL_LINE_STIPPLE);//打开直线的点画模式  
TRvoid trLineStipple(1, 0x0101);//设置直线的当前点画模式，1为倍数，0x0101为线型  



glPolygonMode(GLenum face, GLenum mode);
//控制多边形正面和反面的绘图形式，默认情况下face为GL_FRONT_AND_BACK，mode为GL_FILL，即正面和背面都采取填充形式绘制  
glFrontFace(GLenum mode);
//控制多边形的正面是如何确定的，默认mode为GL_CCW(顶点为逆时针的表面为正面，GL_CW(顺时针为正面))  
glEnable(GL_CULL_FACE);//使剔除生效  
glCullFace();//表示参数所设置的多边形在转换到屏幕坐标之前应该被丢弃  



glEnable(GL_POLYGON_STIPPLE);
glPolygonStipple(fly);//fly为一个指向32*32位图的指针 


#endif // !SHAPE
