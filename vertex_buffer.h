#pragma once
#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include"types.h"

#define GL_ARRAY_BUFFER 
#define GL_STATIC_DRAW


void trGenBuffers(TRsizei n, TRuint *arrys);
TRbool trIsBuffer(TRuint buffer);
TRvoid *trMapBuffer(TRenum target, TRenum access);
//�ṩ�Ի���������������������ݼ��ϵĸ���
//access:GL_READ_ONLY,GL_WRITE_ONLY,GL_READ_WRITE

TRbool *trUnMapBuffer(TRenum target);
//��ʾ��ǰ�󶨻���������ĸ����Ѿ���ɣ���glMapBuffer()���ʹ��
TRvoid trCopyBufferSubData(TRenum readbuffer, TRenum writebuffer,TRintptr readoffset, TRintptr writeoffset, TRsizeiptr size);
//�����ݴ�readbuffer������Ļ����������Ƶ�writebuffer�Ļ���������
//��readoffset��ʼ�ƶ�size�����ݵ�������wirteoffset��
TRvoid trBufferData(TRenum target, TRsizei size, const TRvoid *data, TRenum usage);
TRvoid trBindBuffer(TRenum target, TRuint buffer);
void trBufferData(TRenum target, TRsizeiptr size, const TRvoid *data, TRenum usage);

TRvoid trDeleteBuffers(TRsizei n, TRuint *buffers);






void trGenBuffers(TRsizei n, TRuint * arrys)
{
}

inline TRbool trIsBuffer(TRuint buffer)
{
	return TRbool();
}

inline TRvoid * trMapBuffer(TRenum target, TRenum access)
{
	return NULL;
}

inline TRbool * trUnMapBuffer(TRenum target)
{
	return NULL;
}

inline TRvoid trCopyBufferSubData(TRenum readbuffer, TRenum writebuffer, TRintptr readoffset, TRintptr writeoffset, TRsizeiptr size)
{
	return TRvoid();
}

inline TRvoid trBufferData(TRenum target, TRsizei size, const TRvoid * data, TRenum usage)
{
	return TRvoid();
}

inline TRvoid trBindBuffer(TRenum target, TRuint buffer)
{
	return TRvoid();
}

inline void trBufferData(TRenum target, TRsizeiptr size, const TRvoid * data, TRenum usage)
{
}

inline TRvoid trDeleteBuffers(TRsizei n, TRuint * buffers)
{
	return TRvoid();
}




#endif // !VERTEX_BUFFER
