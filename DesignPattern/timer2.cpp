#include <sys/time.h>
#include <sys/select.h>
#include <cstdio>

void timer(int seconds, int mseconds)
{
	struct timeval temp;
	temp.tv_sec = seconds;
	temp.tv_usec = mseconds;

	select(0, NULL, NULL, NULL, &temp);
	printf("timer\n");
}

int main()
{
	printf("waiting\n");
	timer(1,30);

	getchar();
	return 0;
}
