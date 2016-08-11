#pragma once
#ifndef TARDY_ERROR
#define TARDY_ERROR



enum MessageType { WARNINGS, ERRORS };
struct message
{
	char * what;
	enum MessageType type;
};

typedef void(*messagefun)(struct message m);
extern messagefun mfun;
//注册事件回调函数
void registerMessageFun(messagefun m);

void callMessageFun(struct message m);

void callWarning(char * str);

void callError(char * str);

#endif // !TARDY_ERROR
