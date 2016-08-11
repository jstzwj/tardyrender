#include"error.h"

messagefun mfun;

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