#pragma once
#ifndef IMG
#define IMG


void resize(unsigned int *from ,
	unsigned int fromw, 
	unsigned int fromh,
	unsigned int *to, 
	unsigned int tow,
	unsigned int toh)
{
	double fw = (double)(fromw) / tow;
	double fh = (double)(fromh) / toh;

	int x,y;

	for (y = 0; y<toh; y++)
	{
		for (x = 0; x<tow; x++)
		{
			to[y*tow + x] = from[(int)(y*fh)*fromw + (int)(x*fw)];
		}
	}
}





#endif // !IMG
