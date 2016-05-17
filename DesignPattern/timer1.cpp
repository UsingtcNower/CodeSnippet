#include <unistd.h>
#include <cstdio>
#include <signal.h>

int timeout = 3;
bool every = false;
void timer(int sig)
{
	if(sig == SIGALRM) {
		printf("timer\n");
		if(every)
			alarm(timeout);
	}
}

int main()
{
	signal(SIGALRM, timer);
	printf("waiting...\n");
	alarm(timeout);

	getchar();
	return 0;
}
