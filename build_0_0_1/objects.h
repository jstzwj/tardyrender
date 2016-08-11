#pragma once
#ifndef OBJECTS
#define OBJECTS

#include"types.h"

TRuint begin=1;
TRuint end = 1;

#define OBJECT_DELETED_MAX 255
TRuint deleteList[OBJECT_DELETED_MAX] = {0};
TRuint deleteNum=0;


//�ж϶����Ƿ�ɾ��
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
//�½�һ�����
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
//ɾ������
void deleteObject(TRuint n)
{
	deleteList[deleteNum] = n;
	++deleteNum;
}

#endif