#pragma once
#ifndef SHAPE
#define SHAPE

#include"types.h"

#define GL_ALIASED_LINE_WIDTH_RANGE				//��ѯ�����ֱ�߿�ȵķ�Χ 
#define GL_SMOOTH_LINE_WIDTH_RANGE				//��ѯ��ƽ��ֱ�߿�ȵķ�Χ  
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY		//��ѯƽ��ֱ�����ȵķ�Χ  
#define GL_LINE_STIPPLE


//���ñ���Ⱦ��Ŀ�ȣ�������Ϊ��λ��Ĭ��Ϊ1 
TRdouble pointsize=1.0;
TRvoid trPointSize(TRdouble size);
//����ֱ�ߵĿ�ȣ�Ĭ��Ϊ1  
TRdouble linewidth = 1.0;
TRvoid trLineWidth(TRdouble width);
//����ֱ�ߵĵ�ǰ�㻭ģʽ��1Ϊ������0x0101Ϊ���� 
TRvoid trLineStipple(TRint n, TRenum mode); 



TRvoid trGetFloatv(TRenum mode); 

 



//���ƶ��������ͷ���Ļ�ͼ��ʽ��Ĭ�������faceΪTR_FRONT_AND_BACK��modeΪTR_FILL��������ͱ��涼��ȡ�����ʽ����  
TRvoid trPolygonMode(TRenum face, TRenum mode);
//���ƶ���ε����������ȷ���ģ�Ĭ��modeΪGL_CCW(����Ϊ��ʱ��ı���Ϊ���棬GL_CW(˳ʱ��Ϊ����)) 
TRvoid trFrontFace(TRenum mode);
//��ʾ���������õĶ������ת������Ļ����֮ǰӦ�ñ����� 
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
