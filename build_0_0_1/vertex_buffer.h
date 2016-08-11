#pragma once
#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include"types.h"

#define GL_ARRAY_BUFFER 
#define GL_STATIC_DRAW


void trGenBuffers(TRsizei n, TRuint *arrys);
TRbool trIsBuffer(TRuint buffer);
TRvoid *trMapBuffer(TRenum target, TRenum access);
//提供对缓冲区对象包含的整个数据集合的更新
//access:GL_READ_ONLY,GL_WRITE_ONLY,GL_READ_WRITE

TRbool *trUnMapBuffer(TRenum target);
//表示当前绑定缓冲区对象的更新已经完成，与glMapBuffer()结合使用
TRvoid trCopyBufferSubData(TRenum readbuffer, TRenum writebuffer,TRintptr readoffset, TRintptr writeoffset, TRsizeiptr size);
//把数据从readbuffer相关联的缓冲区对象复制到writebuffer的缓冲区对象
//从readoffset开始移动size个数据的数量到wirteoffset中
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
