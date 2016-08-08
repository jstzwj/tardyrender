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

//�����
struct camera
{
	TRdouble position[3] = { 0.0,0.0,0.0 };
	TRdouble target[3] = { 1.0 ,0.0 ,0.0 };
};




TRvoid trShadeModel(TRenum model);//������Ӱƽ��ģʽ
TRvoid trClearColor(TRfloat r, TRfloat g, TRfloat b, TRfloat a );//�ı䴰�ڵı�����ɫ������������ò�����ú�û��ʲôЧ��
TRvoid trClearDepth(TRfloat n);//������Ȼ���
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
