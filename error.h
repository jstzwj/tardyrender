#pragma once
#ifndef TARDY_ERROR
#define TARDY_ERROR



enum MessageType { WARNINGS, ERRORS };
struct message
{
	char * what;
	MessageType type;
};

typedef void(*messagefun)(struct message m);
messagefun mfun;
//注册事件回调函数
void registerMessageFun(messagefun m);





void registerMessageFun(messagefun m)
{
	mfun = m;
}
void callMessageFun(struct message m)
{
	mfun(m);
}
void callWarning(char * str)
{
	struct message tmp;
	tmp.type = WARNINGS;
	tmp.what = str;
	mfun(tmp);
}
void callError(char * str)
{
	struct message tmp;
	tmp.type = ERRORS;
	tmp.what = str;
	mfun(tmp);
}
#endif // !TARDY_ERROR
