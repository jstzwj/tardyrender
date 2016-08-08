#pragma once
#ifndef VERTEX_ARRAY
#define VERTEX_ARRAY
#include"types.h"

void trGenVertexArrays(TRsizei n,TRuint *arrys);

void trBindVertexArray(TRuint arry);

void trDeleteVertexArrays(TRsizei n, const TRuint *arrys);

void trVertexAttribIPointer(TRuint index, TRint size, TRenum type, TRsizei stride, const TRvoid * pointer);

void trEnableVertexAttribArray(TRuint index);

void trDisableVertexAttribArray(TRuint index);

void trGenVertexArrays(TRsizei n, TRuint * arrys)
{


}

void trBindVertexArray(TRuint arry)
{


}

void trDeleteVertexArrays(TRsizei n, const TRuint * arrys)
{
}

void trVertexAttribIPointer(TRuint index, TRint size, TRenum type, TRsizei stride, const TRvoid * pointer)
{
}

void trEnableVertexAttribArray(TRuint index)
{
}

void trDisableVertexAttribArray(TRuint index)
{
}




#endif // !VERTEX_ARRAY
