#pragma once
#ifndef SHAPE
#define SHAPE

#include"types.h"

#define GL_ALIASED_LINE_WIDTH_RANGE
#define GL_SMOOTH_LINE_WIDTH_RANGE
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY
#define GL_LINE_STIPPLE


//���ñ���Ⱦ��Ŀ�ȣ�������Ϊ��λ��Ĭ��Ϊ1  
TRvoid trPointSize(TRfloat size);

TRvoid trLineWidth(TRfloat width);
//����ֱ�ߵĿ�ȣ�Ĭ��Ϊ1  
TRvoid trGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE);//��ѯ�����ֱ�߿�ȵķ�Χ  
TRvoid trGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE);//��ѯ��ƽ��ֱ�߿�ȵķ�Χ  
TRvoid trGetFloatv(GL_SMOOTH_LINE_WIDTH_GRANULARITY);//��ѯƽ��ֱ�����ȵķ�Χ  

TRvoid trEnable(GL_LINE_STIPPLE);//��ֱ�ߵĵ㻭ģʽ  
TRvoid trLineStipple(1, 0x0101);//����ֱ�ߵĵ�ǰ�㻭ģʽ��1Ϊ������0x0101Ϊ����  



glPolygonMode(GLenum face, GLenum mode);
//���ƶ��������ͷ���Ļ�ͼ��ʽ��Ĭ�������faceΪGL_FRONT_AND_BACK��modeΪGL_FILL��������ͱ��涼��ȡ�����ʽ����  
glFrontFace(GLenum mode);
//���ƶ���ε����������ȷ���ģ�Ĭ��modeΪGL_CCW(����Ϊ��ʱ��ı���Ϊ���棬GL_CW(˳ʱ��Ϊ����))  
glEnable(GL_CULL_FACE);//ʹ�޳���Ч  
glCullFace();//��ʾ���������õĶ������ת������Ļ����֮ǰӦ�ñ�����  



glEnable(GL_POLYGON_STIPPLE);
glPolygonStipple(fly);//flyΪһ��ָ��32*32λͼ��ָ�� 


#endif // !SHAPE
