#pragma once
#ifndef SHAPE
#define SHAPE

#include"types.h"

#define GL_ALIASED_LINE_WIDTH_RANGE				//查询带锯齿直线宽度的范围 
#define GL_SMOOTH_LINE_WIDTH_RANGE				//查询带平滑直线宽度的范围  
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY		//查询平滑直线粒度的范围  
#define GL_LINE_STIPPLE


//设置被渲染点的宽度，以像素为单位，默认为1 
TRdouble pointsize=1.0;
TRvoid trPointSize(TRdouble size);
//设置直线的宽度，默认为1  
TRdouble linewidth = 1.0;
TRvoid trLineWidth(TRdouble width);
//设置直线的当前点画模式，1为倍数，0x0101为线型 
TRvoid trLineStipple(TRint n, TRenum mode); 



TRvoid trGetFloatv(TRenum mode); 

 



//控制多边形正面和反面的绘图形式，默认情况下face为TR_FRONT_AND_BACK，mode为TR_FILL，即正面和背面都采取填充形式绘制  
TRvoid trPolygonMode(TRenum face, TRenum mode);
//控制多边形的正面是如何确定的，默认mode为GL_CCW(顶点为逆时针的表面为正面，GL_CW(顺时针为正面)) 
TRvoid trFrontFace(TRenum mode);
//表示参数所设置的多边形在转换到屏幕坐标之前应该被丢弃 
TRvoid trCullFace(); 


TRvoid trPointSize(TRdouble size)
{
	pointsize = size;
}
TRvoid trLineWidth(TRdouble width)
{
	linewidth = width;
}
TRvoid trGetFloatv(TRenum mode)
{
	return TRvoid();
}
TRvoid trLineStipple(TRint n, TRenum mode)
{
	return TRvoid();
}
TRvoid trPolygonMode(TRenum face, TRenum mode)
{
	return TRvoid();
}
TRvoid trFrontFace(TRenum mode)
{
	return TRvoid();
}
TRvoid trCullFace()
{
	return TRvoid();
}
#endif // !SHAPE
