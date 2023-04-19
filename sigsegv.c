#define NSIGMAX 5

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

void set_default() {

	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
//sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGSEGV, &sa, NULL);
}

void int_handler(int sig)
{

	static int nsig = 0;

//	if (nsig++ < NSIGMAX) printf(" C-c won’t kill me\n");

	printf(" unless you insist...\n"); set_default();
}

void	*thread_function(void *)
{
	printf("Hey\n");
	return (NULL);
}
int main () {

	// struct sigaction sa;
	// sa.sa_handler = int_handler; sigemptyset(&sa.sa_mask); sa.sa_flags = 0;
	// sigaction(SIGSEGV, &sa, NULL);
	char *s = NULL;
	pthread_t		thread_id;

	int	i;

	i = -1;
	int	pid;

	pid = fork();
	if (!pid)
	{
			printf("Hey\n");
			sleep(100000000);
			printf("Hello\n");
			// exit(21);
	}
	usleep(100);
	// printf("%s\n", s[0]);
	fprintf(stderr, "Bye\n");

	return 0;
}
