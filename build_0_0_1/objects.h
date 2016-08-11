#pragma once
#ifndef OBJECTS
#define OBJECTS

#include"types.h"

TRuint begin=1;
TRuint end = 1;

#define OBJECT_DELETED_MAX 255
TRuint deleteList[OBJECT_DELETED_MAX] = {0};
TRuint deleteNum=0;


//判断对象是否删除
bool isDeleted(TRuint n)
{
	TRuint i;
	if (n>=end||n<begin)
	{
		return true;
	}
	else
	{
		for (i = 0; i < deleteNum;++i)
		{
			if (deleteList[i]==n)
			{
				return true;
			}
		}
		if (i==deleteNum)
		{
			return false;
		}
	}
}
//新建一组对象
void newObject(TRsizei n,TRuint * arry)
{
	TRuint i;
	if (deleteNum==0)
	{
		for (i = 0; i < n;++i)
		{
			arry[i] = end + i;
		}
		end = end + n;
	}
	else
	{
		if (n<=deleteNum)
		{
			for (i = n-1; i >=0; --i)
			{
				arry[n - 1 - i] = deleteList[i];
			}
			deleteNum -= n;
		}
		else
		{
			for (i = deleteNum - 1; i >= 0; --i)
			{
				arry[deleteNum - 1 - i] = deleteList[i];
			}
			for (i = deleteNum; i < n;++i)
			{
				arry[i] = end + i;
			}
			end = end + n - deleteNum;
			deleteNum = 0;
		}
	}
}
//删除对象
void deleteObject(TRuint n)
{
	deleteList[deleteNum] = n;
	++deleteNum;
}

#endif