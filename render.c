#include"render.h"




/*************************
视口位置
**************************/
TRint viewportx, viewporty;
TRint viewportw, viewporth;
/*****************************************************
帧缓冲区
*******************************************************/
/****************
图像颜色缓冲区
****************/

//缓冲区大小
TRuint bufferheight = 0;
TRuint bufferwidth = 0;
//前缓冲区
ColorRGBAf * frontBuffer = NULL;
//后缓冲区
ColorRGBAf * backBuffer = NULL;
//当前缓冲区
ColorRGBAf * currentColorBuffer = NULL;
//缓冲区是否分配
TRbool isAssignBuffer = TR_FALSE;
//缓冲区是否打开
TRbool isOpenColorBuffer = TR_TRUE;
//缓冲区背景颜色clearcolor
ColorRGBAf clearcolor = { 0,0,0,1 };

/**********************
深度缓冲区
***********************/

//缓冲区
TRdouble * depthBuffer = NULL;
//缓冲区清除值(0.0-1.0)
TRdouble cleardepth;
//缓冲区是否打开
TRbool isOpenDepthBuffer = TR_FALSE;

/************************
模板缓冲区
***********************/



/*********************
清空缓冲区
********************/


/******************
Opengl 1.0 绘图函数
********************/
TRenum currentDrawMode = 64;
ColorRGBAf currentColor = { 1.0f,1.0f,1.0f,1.0f };
//向量
TRdouble vec1[4];
ColorRGBAf color1;
TRdouble vec2[4];
ColorRGBAf color2;
TRdouble vec3[4];
ColorRGBAf color3;
TRint vec_num = 0;



/*********************
隐藏状态，表示状态机
***********************/
TRenum state;

/***********************
颜色平滑模式
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
	//颜色缓冲打开

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
	
	//深度缓冲打开

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
	
	//OLDTODO 判断该缓冲是否打开，防止内存泄漏
	//第二次注：虽然测试未打开，缓冲区依然会分配，clear依然会进行，原来想的不对
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
	//裁剪
	if (x >= 0 && (TRuint)x<bufferwidth&&
		y >= 0 && (TRuint)y<bufferheight&&
		z >= 0.0&&z <= 1.0)
	{
		//TODO 用模板决定是否覆盖
		//TODO 用深度决定是否覆盖
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
	//归一化
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
	//颜色临时对象
	ColorRGBAf colortemp;
	//距离总长
	TRdouble XDis;
	TRdouble YDis;
	TRdouble ZDis;
	//颜色总长
	TRdouble RDis;
	TRdouble GDis;
	TRdouble BDis;
	TRdouble ADis;
	// 步进的步数  
	long MaxStep;
	//距离插值
	TRdouble fXUnitLen = 1.0;  // X方向的单位步进  
	TRdouble fYUnitLen = 1.0;  // Y方向的单位步进 
	TRdouble fZUnitLen = 1.0;  // Z方向的单位步进
							   //颜色插值
	TRdouble rUnitLen = 1.0;// 红色的单位步进
	TRdouble gUnitLen = 1.0;//绿色的单位步进
	TRdouble bUnitLen = 1.0;// 蓝色的单位步进
	TRdouble aUnitLen = 1.0;// 透明的单位步进


	TRdouble startx = start[0];
	TRdouble starty = start[1];
	TRdouble startz = start[2];
	//归一化
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

	//距离总长赋值
	XDis = end[0] * bufferwidth - start[0] * bufferwidth;
	YDis = end[1] * bufferheight - start[1] * bufferheight;
	ZDis = end[2] - start[2];
	//颜色总长赋值
	RDis = endcolor.red - startcolor.red;
	GDis = endcolor.green - startcolor.green;
	BDis = endcolor.blue - startcolor.blue;
	ADis = endcolor.alpha - startcolor.alpha;
	//赋循环初始值
	startx = start[0] * bufferwidth;
	starty = start[1] * bufferheight;
	startz = start[2];
	colortemp = startcolor;	//TODO 可以直接修改startcolor
							//计算步进数
	MaxStep = (long)tardy_max(tardy_fabs(XDis), tardy_fabs(YDis)); // 步进的步数  

	fYUnitLen = (TRdouble)YDis / MaxStep;
	fXUnitLen = (TRdouble)XDis / MaxStep;
	fZUnitLen = (TRdouble)ZDis / MaxStep;

	rUnitLen = (TRdouble)RDis / MaxStep;
	gUnitLen = (TRdouble)GDis / MaxStep;
	bUnitLen = (TRdouble)BDis / MaxStep;
	aUnitLen = (TRdouble)ADis / MaxStep;


	// 设置起点像素颜色  
	trPutPoint((TRint)startx, (TRint)starty, startz, colortemp);
	// 循环步进  
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

//切开三角形再画
TRvoid trDrawTriangle(TRdouble * v1,ColorRGBAf c1, TRdouble * v2, ColorRGBAf c2, TRdouble * v3,ColorRGBAf c3 )
{
	TRdouble *x_max, *x_min,*x_other;
	TRdouble *y_max, *y_min,*y_other;

	TRdouble other[4];
	TRint line;
	TRint linepoint;
	TRint allMax;	//总步长
	ColorRGBAf co;	//颜色
	TRdouble start[4], end[4];

	//归一化
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
	//三角形光栅化开始了
	//求x轴方向最大距离
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
	//求y轴方向最大距离
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
	//使用扫描线光栅化三角形
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
//vertex系列函数都会调用这个
TRvoid trVertex(const TRdouble * v)
{
	//设备矩阵
	TRdouble transformMatrix[16] = { 1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,0.0,1.0 };
	TRdouble vec[4];
	//复制向量
	vec[0] = v[0];
	vec[1] = v[1];
	vec[2] = v[2];
	vec[3] = v[3];
	//世界、模型矩阵
	trMultiMatrix(transformMatrix, ModelViewMatrix);
	//投影矩阵
	trMultiMatrix(transformMatrix, ProjectionMatrix);
	//转换到设备向量
	trVectorMultMatrix(vec, transformMatrix);

	switch (currentDrawMode)
	{
	case TR_POINTS:
		//画点到当前缓冲区
		trDrawPoint(vec, currentColor);
		break;
	case TR_LINES:
		++vec_num;
		if (vec_num == 1)
		{
			//复制向量
			vec1[0] = vec[0];
			vec1[1] = vec[1];
			vec1[2] = vec[2];
			vec1[3] = vec[3];
			//复制颜色
			color1 = currentColor;
		}
		else if (vec_num == 2)
		{
			//复制向量
			vec2[0] = vec[0];
			vec2[1] = vec[1];
			vec2[2] = vec[2];
			vec2[3] = vec[3];
			//复制颜色
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
			//复制向量
			//起点
			vec1[0] = vec[0];
			vec1[1] = vec[1];
			vec1[2] = vec[2];
			vec1[3] = vec[3];
			//起点颜色赋值
			color1 = currentColor;
		}
		else if (vec_num == 2)
		{
			//复制向量
			//上一个点
			vec2[0] = vec[0];
			vec2[1] = vec[1];
			vec2[2] = vec[2];
			vec2[3] = vec[3];
			//颜色赋值
			color2 = currentColor;
		}
		else
		{
			trDrawTriangle(vec1,color1, vec2,color2, vec,currentColor);
			//复制向量
			//上一个点
			vec2[0] = vec[0];
			vec2[1] = vec[1];
			vec2[2] = vec[2];
			vec2[3] = vec[3];
			//颜色赋值
			color2 = currentColor;
		}
		break;
	case TR_TRIANGLES:
		++vec_num;
		if (vec_num == 1)
		{
			//复制向量
			//起点
			vec1[0] = vec[0];
			vec1[1] = vec[1];
			vec1[2] = vec[2];
			vec1[3] = vec[3];
			//起点颜色赋值
			color1 = currentColor;
		}
		else if (vec_num == 2)
		{
			//复制向量
			//上一个点
			vec2[0] = vec[0];
			vec2[1] = vec[1];
			vec2[2] = vec[2];
			vec2[3] = vec[3];
			//颜色赋值
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
	//向量
	TRdouble vec[4];
	//复制
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = w;
	trVertex(vec);
}
//vertex系列函数都会调用这个
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
//color系列函数都会调用这个,vector一共4个元素
TRvoid trColor(const TRfloat * v)
{
	int i;
	//复制
	currentColor.red = v[0];
	currentColor.green = v[1];
	currentColor.blue = v[2];
	currentColor.alpha = v[3];
	//检测颜色是否合理
	//opengl一旦有一个颜色超出0.0-1.0 就设为0，这里也是这样
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
//视口的左上角和视口的高与宽
TRvoid trViewport(TRint x, TRint y, TRsizei width, TRsizei height)
{
	//长宽不为0
	if (width <= 0 || height <= 0)
	{
		return;
	}

	//第一次调用分配缓冲区空间
	//注：经过检测，opengl内存分配是动态的，随窗口大小改变的，且不在viewport中，但与viewport有关
	//注：之前想错了，关闭某测试，不会影响缓冲区内存分配
	if (isAssignBuffer == TR_FALSE)
	{
		bufferheight = height;
		bufferwidth = width;
		//颜色缓冲分配
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

		//深度缓冲分配
		depthBuffer = (TRdouble *)malloc(sizeof(TRdouble)*bufferheight*bufferwidth);
		if (depthBuffer == NULL)
		{
			return;
		}
		//放到最后，防止malloc失败
		isAssignBuffer = TR_TRUE;
	}
	else
	{
		if (width > (TRint)bufferwidth || height > (TRint)bufferheight)
		{
			bufferheight = height;
			bufferwidth = width;
			//颜色缓冲重新分配
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

			//深度缓冲重新分配
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