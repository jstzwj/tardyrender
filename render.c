#include"render.h"




/*************************
�ӿ�λ��
**************************/
TRint viewportx, viewporty;
TRint viewportw, viewporth;
/*****************************************************
֡������
*******************************************************/
/****************
ͼ����ɫ������
****************/

//��������С
TRuint bufferheight = 0;
TRuint bufferwidth = 0;
//ǰ������
ColorRGBAf * frontBuffer = NULL;
//�󻺳���
ColorRGBAf * backBuffer = NULL;
//��ǰ������
ColorRGBAf * currentColorBuffer = NULL;
//�������Ƿ����
TRbool isAssignBuffer = TR_FALSE;
//�������Ƿ��
TRbool isOpenColorBuffer = TR_TRUE;
//������������ɫclearcolor
ColorRGBAf clearcolor = { 0,0,0,1 };

/**********************
��Ȼ�����
***********************/

//������
TRdouble * depthBuffer = NULL;
//���������ֵ(0.0-1.0)
TRdouble cleardepth;
//�������Ƿ��
TRbool isOpenDepthBuffer = TR_FALSE;

/************************
ģ�建����
***********************/



/*********************
��ջ�����
********************/


/******************
Opengl 1.0 ��ͼ����
********************/
TRenum currentDrawMode = 64;
ColorRGBAf currentColor = { 1.0f,1.0f,1.0f,1.0f };
//����
TRdouble vec1[4];
ColorRGBAf color1;
TRdouble vec2[4];
ColorRGBAf color2;
TRdouble vec3[4];
ColorRGBAf color3;
TRint vec_num = 0;



/*********************
����״̬����ʾ״̬��
***********************/
TRenum state;

/***********************
��ɫƽ��ģʽ
**************************/

TRenum ShadeModel = TR_SMOOTH;






TRvoid trShadeModel(TRenum model)
{
	ShadeModel = model;
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
	//��ɫ�����

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
	
	//��Ȼ����

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
	
	//OLDTODO �жϸû����Ƿ�򿪣���ֹ�ڴ�й©
	//�ڶ���ע����Ȼ����δ�򿪣���������Ȼ����䣬clear��Ȼ����У�ԭ����Ĳ���
	if ((mode & TR_ACCUM_BUFFER_BIT) == TR_ACCUM_BUFFER_BIT)
	{
		//TODO
		//������ۻ���
	}
	if ((mode & TR_STENCIL_BUFFER_BIT) == TR_STENCIL_BUFFER_BIT)
	{
		//TODO
		//����ģ�建��
	}
}

TRvoid trBegin(TRenum mode)
{
	currentDrawMode = mode;
}

TRvoid trEnd()
{
	currentDrawMode = 0;
	vec_num = 0;
}

TRvoid trFinish()
{
	return;
}

TRvoid trFlush()
{
	return;
}

TRvoid trPutPoint(TRint x, TRint y, TRdouble z, ColorRGBAf color)
{
	//if (x >= 0.0 && x <= 1.0 && 
	//	y >= 0.0 && y <= 1.0 &&
	//	z >= 0.0 && z <= 1.0
	//	)
	//{
	//	if (isOpenColorBuffer == TR_TRUE)
	//	{
	//		currentColorBuffer[(TRuint)((y * (bufferheight - 1))*bufferwidth + (x * (bufferwidth - 1)))] = currentColor;
	//	}
	//	if (isOpenDepthBuffer == TR_TRUE)
	//	{
	//		depthBuffer[(TRuint)((y * (bufferheight - 1))*bufferwidth + (x * (bufferwidth - 1)))] = z;
	//	}
	//}
	//�ü�
	if (x >= 0 && (TRuint)x<bufferwidth&&
		y >= 0 && (TRuint)y<bufferheight&&
		z >= 0.0&&z <= 1.0)
	{
		//TODO ��ģ������Ƿ񸲸�
		//TODO ����Ⱦ����Ƿ񸲸�
		if (isOpenDepthBuffer == TR_TRUE)
		{
			depthBuffer[y*bufferwidth + x] = z;
		}
		if (isOpenColorBuffer == TR_TRUE)
		{
			currentColorBuffer[y*bufferwidth + x] = color;
		}
	}
}

TRvoid trDrawPoint(TRdouble * v4, ColorRGBAf vec_color)
{
	//��һ��
	if (v4[3] != 0)
	{
		v4[0] /= v4[3];
		v4[1] /= v4[3];
		v4[2] /= v4[3];
		v4[3] = 1.0;
	}
	//(TRuint)((v4[1]*(bufferheight-1))*bufferwidth + (v4[0]* (bufferwidth-1)))

	trPutPoint((TRint)(v4[0] * (bufferwidth - 1)), (TRint)(v4[1] * (bufferheight - 1)), v4[2], vec_color);
}

TRvoid trDrawLine(TRdouble * start, ColorRGBAf startcolor, TRdouble * end, ColorRGBAf endcolor)
{
	//��ɫ��ʱ����
	ColorRGBAf colortemp;
	//�����ܳ�
	TRdouble XDis;
	TRdouble YDis;
	TRdouble ZDis;
	//��ɫ�ܳ�
	TRdouble RDis;
	TRdouble GDis;
	TRdouble BDis;
	TRdouble ADis;
	// �����Ĳ���  
	long MaxStep;
	//�����ֵ
	TRdouble fXUnitLen = 1.0;  // X����ĵ�λ����  
	TRdouble fYUnitLen = 1.0;  // Y����ĵ�λ���� 
	TRdouble fZUnitLen = 1.0;  // Z����ĵ�λ����
							   //��ɫ��ֵ
	TRdouble rUnitLen = 1.0;// ��ɫ�ĵ�λ����
	TRdouble gUnitLen = 1.0;//��ɫ�ĵ�λ����
	TRdouble bUnitLen = 1.0;// ��ɫ�ĵ�λ����
	TRdouble aUnitLen = 1.0;// ͸���ĵ�λ����


	TRdouble startx = start[0];
	TRdouble starty = start[1];
	TRdouble startz = start[2];
	//��һ��
	if (start[3] != 0)
	{
		start[0] /= start[3];
		start[1] /= start[3];
		start[2] /= start[3];
		start[3] = 1.0;
	}
	if (end[3] != 0)
	{
		end[0] /= end[3];
		end[1] /= end[3];
		end[2] /= end[3];
		end[3] = 1.0;
	}

	//�����ܳ���ֵ
	XDis = end[0] * bufferwidth - start[0] * bufferwidth;
	YDis = end[1] * bufferheight - start[1] * bufferheight;
	ZDis = end[2] - start[2];
	//��ɫ�ܳ���ֵ
	RDis = endcolor.red - startcolor.red;
	GDis = endcolor.green - startcolor.green;
	BDis = endcolor.blue - startcolor.blue;
	ADis = endcolor.alpha - startcolor.alpha;
	//��ѭ����ʼֵ
	startx = start[0] * bufferwidth;
	starty = start[1] * bufferheight;
	startz = start[2];
	colortemp = startcolor;	//TODO ����ֱ���޸�startcolor
							//���㲽����
	MaxStep = (long)tardy_max(tardy_fabs(XDis), tardy_fabs(YDis)); // �����Ĳ���  

	fYUnitLen = (TRdouble)YDis / MaxStep;
	fXUnitLen = (TRdouble)XDis / MaxStep;
	fZUnitLen = (TRdouble)ZDis / MaxStep;

	rUnitLen = (TRdouble)RDis / MaxStep;
	gUnitLen = (TRdouble)GDis / MaxStep;
	bUnitLen = (TRdouble)BDis / MaxStep;
	aUnitLen = (TRdouble)ADis / MaxStep;


	// �������������ɫ  
	trPutPoint((TRint)startx, (TRint)starty, startz, colortemp);
	// ѭ������  
	for (long i = 1; i <= MaxStep; i++)
	{
		startx = startx + fXUnitLen;
		starty = starty + fYUnitLen;
		startz = startz + fZUnitLen;

		colortemp.red += (TRfloat)rUnitLen;
		colortemp.green += (TRfloat)gUnitLen;
		colortemp.blue += (TRfloat)bUnitLen;
		colortemp.alpha += (TRfloat)aUnitLen;
		if (ShadeModel == TR_SMOOTH)
			trPutPoint((TRint)startx, (TRint)starty, startz, colortemp);
		if (ShadeModel == TR_FLAT)
			trPutPoint((TRint)startx, (TRint)starty, startz, endcolor);
	}

}

//�п��������ٻ�
TRvoid trDrawTriangle(TRdouble * v1,ColorRGBAf c1, TRdouble * v2, ColorRGBAf c2, TRdouble * v3,ColorRGBAf c3 )
{
	TRdouble *x_max, *x_min,*x_other;
	TRdouble *y_max, *y_min,*y_other;

	TRdouble other[4];
	TRint line;
	TRint linepoint;
	TRint allMax;	//�ܲ���
	ColorRGBAf co;	//��ɫ
	TRdouble start[4], end[4];

	//��һ��
	if (v1[3] != 0)
	{
		v1[0] /= v1[3];
		v1[1] /= v1[3];
		v1[2] /= v1[3];
		v1[3] = 1.0;
	}
	if (v2[3] != 0)
	{
		v2[0] /= v2[3];
		v2[1] /= v2[3];
		v2[2] /= v2[3];
		v2[3] = 1.0;
	}
	if (v3[3] != 0)
	{
		v3[0] /= v3[3];
		v3[1] /= v3[3];
		v3[2] /= v3[3];
		v3[3] = 1.0;
	}
	//�����ι�դ����ʼ��
	//��x�᷽��������
	if (v1[0]>v2[0])
	{
		if (v2[0]>v3[0])
		{
			x_max = v1;
			x_min = v3;
			x_other = v2;
		}
		else
		{
			if (v1[0]>v3[0])
			{
				x_max = v1;
				x_min = v2;
				x_other = v3;
			}
			else
			{
				x_max = v3;
				x_min = v2;
				x_other = v1;
			}
		}
	}
	else
	{
		if (v1[0]>v3[0])
		{
			x_max = v2;
			x_min = v3;
			x_other = v1;
		}
		else
		{
			if (v2[0]>v3[0])
			{
				x_max = v2;
				x_min = v1;
				x_other = v3;
			}
			else
			{
				x_max = v3;
				x_min = v1;
				x_other = v2;
			}
		}
	}
	//��y�᷽��������
	if (v1[1]>v2[1])
	{
		if (v2[1]>v3[1])
		{
			y_max = v1;
			y_min = v3;
			y_other = v2;
		}
		else
		{
			if (v1[1]>v3[1])
			{
				y_max = v1;
				y_min = v2;
				y_other = v3;
			}
			else
			{
				y_max = v3;
				y_min = v2;
				y_other = v1;
			}
		}
	}
	else
	{
		if (v1[1]>v3[1])
		{
			y_max = v2;
			y_min = v3;
			y_other = v1;
		}
		else
		{
			if (v2[1]>v3[1])
			{
				y_max = v2;
				y_min = v1;
				y_other = v3;
			}
			else
			{
				y_max = v3;
				y_min = v1;
				y_other = v2;
			}
		}
	}
	//ʹ��ɨ���߹�դ��������
	//if (y_max[1]-y_min[1]>x_max[0]-x_min[0])
	//{
	//}
	//else
	//{	
	//}
	allMax = y_other[1] * bufferheight - y_min[1] * bufferheight;
	for (line = y_min[1] * bufferheight; line < y_other[1] * bufferheight; ++line)
	{
		start[0] = ((TRdouble)line/ bufferheight-y_min[1])*(y_min[0]-y_other[0])/(y_min[1]-y_other[1])+y_min[0];
		start[1] = line;
		start[2] = y_min[2]+(y_other[2]-y_min[2])*line/allMax;
		start[3] = 1.0;
		end[0] = ((TRdouble)line / bufferheight - y_min[1])*(y_min[0] - y_max[0]) / (y_min[1] - y_max[1]) + y_min[0];
		end[1] = line;
		end[2] = y_min[2] + (y_other[2] - y_min[2])*line / allMax;
		end[3] = 1.0;
		if (start[0] < end[0])
		{
			for (linepoint = start[0] * bufferwidth; linepoint < end[0] * bufferwidth; ++linepoint)
			{
				trPutPoint(linepoint, line, 0.0, currentColor);
			}
		}
		else
		{
			for (linepoint = end[0] * bufferwidth; linepoint < start[0] * bufferwidth; ++linepoint)
			{
				trPutPoint(linepoint, line, 0.0, currentColor);
			}
		}
		
	}
	for (line = y_other[1] * bufferheight; line < y_max[1] * bufferheight; ++line)
	{
		start[0] = ((TRdouble)line / bufferheight - y_max[1])*(y_max[0] - y_other[0]) / (y_max[1] - y_other[1]) + y_max[0];
		start[1] = line;
		start[2] = y_max[2] + (y_other[2] - y_max[2])*line / allMax;
		start[3] = 1.0;
		end[0] = ((TRdouble)line / bufferheight - y_min[1])*(y_min[0] - y_max[0]) / (y_min[1] - y_max[1]) + y_min[0];
		end[1] = line;
		end[2] = y_min[2] + (y_max[2] - y_min[2])*line / allMax;
		end[3] = 1.0;
		if (start[0] < end[0])
		{
			for (linepoint = start[0] * bufferwidth; linepoint < end[0] * bufferwidth; ++linepoint)
			{
				trPutPoint(linepoint, line, 0.0, currentColor);
			}
		}
		else
		{
			for (linepoint = end[0] * bufferwidth; linepoint < start[0] * bufferwidth; ++linepoint)
			{
				trPutPoint(linepoint, line, 0.0, currentColor);
			}
		}
		
	}
}
//vertexϵ�к�������������
TRvoid trVertex(const TRdouble * v)
{
	//�豸����
	TRdouble transformMatrix[16] = { 1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,0.0,1.0 };
	TRdouble vec[4];
	//��������
	vec[0] = v[0];
	vec[1] = v[1];
	vec[2] = v[2];
	vec[3] = v[3];
	//���硢ģ�;���
	trMultiMatrix(transformMatrix, ModelViewMatrix);
	//ͶӰ����
	trMultiMatrix(transformMatrix, ProjectionMatrix);
	//ת�����豸����
	trVectorMultMatrix(vec, transformMatrix);

	switch (currentDrawMode)
	{
	case TR_POINTS:
		//���㵽��ǰ������
		trDrawPoint(vec, currentColor);
		break;
	case TR_LINES:
		++vec_num;
		if (vec_num == 1)
		{
			//��������
			vec1[0] = vec[0];
			vec1[1] = vec[1];
			vec1[2] = vec[2];
			vec1[3] = vec[3];
			//������ɫ
			color1 = currentColor;
		}
		else if (vec_num == 2)
		{
			//��������
			vec2[0] = vec[0];
			vec2[1] = vec[1];
			vec2[2] = vec[2];
			vec2[3] = vec[3];
			//������ɫ
			color2 = currentColor;
		}
		if (vec_num >= 2)
		{
			trDrawLine(vec1, color1, vec2, color2);
			vec_num = 0;
		}
		break;
	case TR_POLYGON:
		++vec_num;
		if (vec_num == 1)
		{
			//��������
			//���
			vec1[0] = vec[0];
			vec1[1] = vec[1];
			vec1[2] = vec[2];
			vec1[3] = vec[3];
			//�����ɫ��ֵ
			color1 = currentColor;
		}
		else if (vec_num == 2)
		{
			//��������
			//��һ����
			vec2[0] = vec[0];
			vec2[1] = vec[1];
			vec2[2] = vec[2];
			vec2[3] = vec[3];
			//��ɫ��ֵ
			color2 = currentColor;
		}
		else
		{
			trDrawTriangle(vec1,color1, vec2,color2, vec,currentColor);
			//��������
			//��һ����
			vec2[0] = vec[0];
			vec2[1] = vec[1];
			vec2[2] = vec[2];
			vec2[3] = vec[3];
			//��ɫ��ֵ
			color2 = currentColor;
		}
		break;
	case TR_TRIANGLES:
		++vec_num;
		if (vec_num == 1)
		{
			//��������
			//���
			vec1[0] = vec[0];
			vec1[1] = vec[1];
			vec1[2] = vec[2];
			vec1[3] = vec[3];
			//�����ɫ��ֵ
			color1 = currentColor;
		}
		else if (vec_num == 2)
		{
			//��������
			//��һ����
			vec2[0] = vec[0];
			vec2[1] = vec[1];
			vec2[2] = vec[2];
			vec2[3] = vec[3];
			//��ɫ��ֵ
			color2 = currentColor;
		}
		else
		{
			trDrawTriangle(vec1, color1, vec2, color2, vec, currentColor);
			vec_num = 0;
		}
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

TRvoid trVertex2d(TRdouble x, TRdouble y)
{
	TRdouble point[4];
	point[0] = x;
	point[1] = y;
	point[2] = 0.0;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex2dv(const TRdouble * v)
{
	TRdouble point[4];
	point[0] = v[0];
	point[1] = v[1];
	point[2] = 0.0;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex2f(TRfloat x, TRfloat y)
{
	TRdouble point[4];
	point[0] = x;
	point[1] = y;
	point[2] = 0.0;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex2fv(const TRfloat * v)
{
	TRdouble point[4];
	point[0] = v[0];
	point[1] = v[1];
	point[2] = 0.0;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex2i(TRint x, TRint y)
{
	TRdouble point[4];
	point[0] = x;
	point[1] = y;
	point[2] = 0.0;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex2iv(const TRint * v)
{
	TRdouble point[4];
	point[0] = v[0];
	point[1] = v[1];
	point[2] = 0.0;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex2s(TRshort x, TRshort y)
{
	TRdouble point[4];
	point[0] = x;
	point[1] = y;
	point[2] = 0.0;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex2sv(const TRshort * v)
{
	TRdouble point[4];
	point[0] = v[0];
	point[1] = v[1];
	point[2] = 0.0;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex3d(TRdouble x, TRdouble y, TRdouble z)
{
	TRdouble point[4];
	point[0] = x;
	point[1] = y;
	point[2] = z;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex3dv(const TRdouble * v)
{
	TRdouble point[4];
	point[0] = v[0];
	point[1] = v[1];
	point[2] = v[2];
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex3f(TRfloat x, TRfloat y, TRfloat z)
{
	TRdouble point[4];
	point[0] = x;
	point[1] = y;
	point[2] = z;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex3fv(const TRfloat * v)
{
	TRdouble point[4];
	point[0] = v[0];
	point[1] = v[1];
	point[2] = v[2];
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex3i(TRint x, TRint y, TRint z)
{
	TRdouble point[4];
	point[0] = x;
	point[1] = y;
	point[2] = z;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex3iv(const TRint * v)
{
	TRdouble point[4];
	point[0] = v[0];
	point[1] = v[1];
	point[2] = v[2];
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex3s(TRshort x, TRshort y, TRshort z)
{
	TRdouble point[4];
	point[0] = x;
	point[1] = y;
	point[2] = z;
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex3sv(const TRshort * v)
{
	TRdouble point[4];
	point[0] = v[0];
	point[1] = v[1];
	point[2] = v[2];
	point[3] = 1.0;
	trVertex(point);
}

TRvoid trVertex4d(TRdouble x, TRdouble y, TRdouble z, TRdouble w)
{
	//����
	TRdouble vec[4];
	//����
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = w;
	trVertex(vec);
}
//vertexϵ�к�������������
TRvoid trVertex4dv(const TRdouble * v)
{
	trVertex(v);
}

TRvoid trVertex4f(TRfloat x, TRfloat y, TRfloat z, TRfloat w)
{
	TRdouble point[4];
	point[0] = x;
	point[1] = y;
	point[2] = z;
	point[3] = w;
	trVertex(point);
}

TRvoid trVertex4fv(const TRfloat * v)
{
	TRdouble point[4];
	point[0] = v[0];
	point[1] = v[1];
	point[2] = v[2];
	point[3] = v[3];
	trVertex(point);
}

TRvoid trVertex4i(TRint x, TRint y, TRint z, TRint w)
{
	TRdouble point[4];
	point[0] = x;
	point[1] = y;
	point[2] = z;
	point[3] = w;
	trVertex(point);
}

TRvoid trVertex4iv(const TRint * v)
{
	TRdouble point[4];
	point[0] = v[0];
	point[1] = v[1];
	point[2] = v[2];
	point[3] = v[3];
	trVertex(point);
}

TRvoid trVertex4s(TRshort x, TRshort y, TRshort z, TRshort w)
{
	TRdouble point[4];
	point[0] = x;
	point[1] = y;
	point[2] = z;
	point[3] = w;
	trVertex(point);
}

TRvoid trVertex4sv(const TRshort * v)
{
	TRdouble point[4];
	point[0] = v[0];
	point[1] = v[1];
	point[2] = v[2];
	point[3] = v[3];
	trVertex(point);
}
//colorϵ�к�������������,vectorһ��4��Ԫ��
TRvoid trColor(const TRfloat * v)
{
	int i;
	//����
	currentColor.red = v[0];
	currentColor.green = v[1];
	currentColor.blue = v[2];
	currentColor.alpha = v[3];
	//�����ɫ�Ƿ����
	//openglһ����һ����ɫ����0.0-1.0 ����Ϊ0������Ҳ������
	if (currentColor.red<0.0f||currentColor.red>1.0f)
	{
		currentColor.red = 0.0f;
	}
	if (currentColor.green<0.0f || currentColor.green>1.0f)
	{
		currentColor.green = 0.0f;
	}
	if (currentColor.blue<0.0f || currentColor.blue>1.0f)
	{
		currentColor.blue = 0.0f;
	}
	if (currentColor.alpha<0.0f || currentColor.alpha>1.0f)
	{
		currentColor.alpha = 0.0f;
	}
}

TRvoid trColor3b(TRbyte red, TRbyte green, TRbyte blue)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / BYTE_MAX;
	colorvec[1] = (TRfloat)green / BYTE_MAX;
	colorvec[2] = (TRfloat)blue / BYTE_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3bv(const TRbyte * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / BYTE_MAX;
	colorvec[1] = (TRfloat)v[1] / BYTE_MAX;
	colorvec[2] = (TRfloat)v[2] / BYTE_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3d(TRdouble red, TRdouble green, TRdouble blue)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red;
	colorvec[1] = (TRfloat)green;
	colorvec[2] = (TRfloat)blue;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3dv(const TRdouble * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0];
	colorvec[1] = (TRfloat)v[1];
	colorvec[2] = (TRfloat)v[2];
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3f(TRfloat red, TRfloat green, TRfloat blue)
{
	TRfloat colorvec[4];
	colorvec[0] = red;
	colorvec[1] = green;
	colorvec[2] = blue;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3fv(const TRfloat * v)
{
	TRfloat colorvec[4];
	colorvec[0] = v[0];
	colorvec[1] = v[1];
	colorvec[2] = v[2];
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3i(TRint red, TRint green, TRint blue)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / INT_MAX;
	colorvec[1] = (TRfloat)green / INT_MAX;
	colorvec[2] = (TRfloat)blue / INT_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3iv(const TRint * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / INT_MAX;
	colorvec[1] = (TRfloat)v[1] / INT_MAX;
	colorvec[2] = (TRfloat)v[2] / INT_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3s(TRshort red, TRshort green, TRshort blue)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / SHRT_MAX;
	colorvec[1] = (TRfloat)green / SHRT_MAX;
	colorvec[2] = (TRfloat)blue / SHRT_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3sv(const TRshort * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / SHRT_MAX;
	colorvec[1] = (TRfloat)v[1] / SHRT_MAX;
	colorvec[2] = (TRfloat)v[2] / SHRT_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3ub(TRubyte red, TRubyte green, TRubyte blue)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / UBYTE_MAX;
	colorvec[1] = (TRfloat)green / UBYTE_MAX;
	colorvec[2] = (TRfloat)blue / UBYTE_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3ubv(const TRubyte * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / UBYTE_MAX;
	colorvec[1] = (TRfloat)v[1] / UBYTE_MAX;
	colorvec[2] = (TRfloat)v[2] / UBYTE_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3ui(TRuint red, TRuint green, TRuint blue)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / UINT_MAX;
	colorvec[1] = (TRfloat)green / UINT_MAX;
	colorvec[2] = (TRfloat)blue / UINT_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3uiv(const TRuint * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / UINT_MAX;
	colorvec[1] = (TRfloat)v[1] / UINT_MAX;
	colorvec[2] = (TRfloat)v[2] / UINT_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3us(TRushort red, TRushort green, TRushort blue)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / USHRT_MAX;
	colorvec[1] = (TRfloat)green / USHRT_MAX;
	colorvec[2] = (TRfloat)blue / USHRT_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor3usv(const TRushort * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / USHRT_MAX;
	colorvec[1] = (TRfloat)v[1] / USHRT_MAX;
	colorvec[2] = (TRfloat)v[2] / USHRT_MAX;
	colorvec[3] = 1.0;
	trColor(colorvec);
}

TRvoid trColor4b(TRbyte red, TRbyte green, TRbyte blue, TRbyte alpha)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / BYTE_MAX;
	colorvec[1] = (TRfloat)green / BYTE_MAX;
	colorvec[2] = (TRfloat)blue / BYTE_MAX;
	colorvec[3] = (TRfloat)alpha / BYTE_MAX;
	trColor(colorvec);
}

TRvoid trColor4bv(const TRbyte * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / BYTE_MAX;
	colorvec[1] = (TRfloat)v[1] / BYTE_MAX;
	colorvec[2] = (TRfloat)v[2] / BYTE_MAX;
	colorvec[3] = (TRfloat)v[3] / BYTE_MAX;;
	trColor(colorvec);
}

TRvoid trColor4d(TRdouble red, TRdouble green, TRdouble blue, TRdouble alpha)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red;
	colorvec[1] = (TRfloat)green;
	colorvec[2] = (TRfloat)blue;
	colorvec[3] = (TRfloat)alpha;
	trColor(colorvec);
}

TRvoid trColor4dv(const TRdouble * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0];
	colorvec[1] = (TRfloat)v[1];
	colorvec[2] = (TRfloat)v[2];
	colorvec[3] = (TRfloat)v[3];
	trColor(colorvec);
}

TRvoid trColor4f(TRfloat red, TRfloat green, TRfloat blue, TRfloat alpha)
{
	TRfloat colorvec[4];
	colorvec[0] = red;
	colorvec[1] = green;
	colorvec[2] = blue;
	colorvec[3] = alpha;
	trColor(colorvec);
}

TRvoid trColor4fv(const TRfloat * v)
{
	TRfloat colorvec[4];
	colorvec[0] = v[0];
	colorvec[1] = v[1];
	colorvec[2] = v[2];
	colorvec[3] = v[3];
	trColor(colorvec);
}

TRvoid trColor4i(TRint red, TRint green, TRint blue, TRint alpha)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / INT_MAX;
	colorvec[1] = (TRfloat)green / INT_MAX;
	colorvec[2] = (TRfloat)blue / INT_MAX;
	colorvec[3] = (TRfloat)alpha / INT_MAX;
	trColor(colorvec);
}

TRvoid trColor4iv(const TRint * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / INT_MAX;
	colorvec[1] = (TRfloat)v[1] / INT_MAX;
	colorvec[2] = (TRfloat)v[2] / INT_MAX;
	colorvec[3] = (TRfloat)v[3] / INT_MAX;
	trColor(colorvec);
}

TRvoid trColor4s(TRshort red, TRshort green, TRshort blue, TRshort alpha)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / SHRT_MAX;
	colorvec[1] = (TRfloat)green / SHRT_MAX;
	colorvec[2] = (TRfloat)blue / SHRT_MAX;
	colorvec[3] = (TRfloat)alpha / SHRT_MAX;
	trColor(colorvec);
}

TRvoid trColor4sv(const TRshort * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / SHRT_MAX;
	colorvec[1] = (TRfloat)v[1] / SHRT_MAX;
	colorvec[2] = (TRfloat)v[2] / SHRT_MAX;
	colorvec[3] = (TRfloat)v[3] / SHRT_MAX;
	trColor(colorvec);
}

TRvoid trColor4ub(TRubyte red, TRubyte green, TRubyte blue, TRubyte alpha)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / USHRT_MAX;
	colorvec[1] = (TRfloat)green / USHRT_MAX;
	colorvec[2] = (TRfloat)blue / USHRT_MAX;
	colorvec[3] = (TRfloat)alpha / USHRT_MAX;
	trColor(colorvec);
}

TRvoid trColor4ubv(const TRubyte * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / USHRT_MAX;
	colorvec[1] = (TRfloat)v[1] / USHRT_MAX;
	colorvec[2] = (TRfloat)v[2] / USHRT_MAX;
	colorvec[3] = (TRfloat)v[3] / USHRT_MAX;
	trColor(colorvec);
}

TRvoid trColor4ui(TRuint red, TRuint green, TRuint blue, TRuint alpha)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / UINT_MAX;
	colorvec[1] = (TRfloat)green / UINT_MAX;
	colorvec[2] = (TRfloat)blue / UINT_MAX;
	colorvec[3] = (TRfloat)alpha / UINT_MAX;
	trColor(colorvec);
}

TRvoid trColor4uiv(const TRuint * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / UINT_MAX;
	colorvec[1] = (TRfloat)v[1] / UINT_MAX;
	colorvec[2] = (TRfloat)v[2] / UINT_MAX;
	colorvec[3] = (TRfloat)v[3] / UINT_MAX;
	trColor(colorvec);
}

TRvoid trColor4us(TRushort red, TRushort green, TRushort blue, TRushort alpha)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)red / USHRT_MAX;
	colorvec[1] = (TRfloat)green / USHRT_MAX;
	colorvec[2] = (TRfloat)blue / USHRT_MAX;
	colorvec[3] = (TRfloat)alpha / USHRT_MAX;
	trColor(colorvec);
}

TRvoid trColor4usv(const TRushort * v)
{
	TRfloat colorvec[4];
	colorvec[0] = (TRfloat)v[0] / USHRT_MAX;
	colorvec[1] = (TRfloat)v[1] / USHRT_MAX;
	colorvec[2] = (TRfloat)v[2] / USHRT_MAX;
	colorvec[3] = (TRfloat)v[3] / USHRT_MAX;
	trColor(colorvec);
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
	return;
}
TRvoid trHint()
{
	return;
}
//�ӿڵ����ϽǺ��ӿڵĸ����
TRvoid trViewport(TRint x, TRint y, TRsizei width, TRsizei height)
{
	//����Ϊ0
	if (width <= 0 || height <= 0)
	{
		return;
	}

	//��һ�ε��÷��仺�����ռ�
	//ע��������⣬opengl�ڴ�����Ƕ�̬�ģ��洰�ڴ�С�ı�ģ��Ҳ���viewport�У�����viewport�й�
	//ע��֮ǰ����ˣ��ر�ĳ���ԣ�����Ӱ�컺�����ڴ����
	if (isAssignBuffer == TR_FALSE)
	{
		bufferheight = height;
		bufferwidth = width;
		//��ɫ�������
		frontBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
		if (frontBuffer == NULL)
		{
			return;
		}
		backBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
		if (backBuffer == NULL)
		{
			return;
		}
		currentColorBuffer = frontBuffer;

		//��Ȼ������
		depthBuffer = (TRdouble *)malloc(sizeof(TRdouble)*bufferheight*bufferwidth);
		if (depthBuffer == NULL)
		{
			return;
		}
		//�ŵ���󣬷�ֹmallocʧ��
		isAssignBuffer = TR_TRUE;
	}
	else
	{
		if (width > (TRint)bufferwidth || height > (TRint)bufferheight)
		{
			bufferheight = height;
			bufferwidth = width;
			//��ɫ�������·���
			free(frontBuffer);
			free(backBuffer);
			frontBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
			if (frontBuffer == NULL)
			{
				return;
			}
			backBuffer = (ColorRGBAf *)malloc(sizeof(ColorRGBAf)*bufferheight*bufferwidth);
			if (backBuffer == NULL)
			{
				return;
			}
			currentColorBuffer = frontBuffer;

			//��Ȼ������·���
			free(depthBuffer);
			depthBuffer = (TRdouble *)malloc(sizeof(TRdouble)*bufferheight*bufferwidth);
			if (depthBuffer == NULL)
			{
				return;
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
	return;
}