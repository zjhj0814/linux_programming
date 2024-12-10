#include <signal.h>
#include <stdlib.h>

void main(){
	sigset_t set1, set2;

	sigfillset(&set1);
	sigfillset(&set2);
	sigdelset(&set2, SIGINT);
	sigdelset(&set2, SIGQUIT);

	/* executing insignificant code */
	sigprocmask(SIG_SETMASK, &set1, NULL);

	/* executing most critical code */
	sigprocmask(SIG_UNBLOCK, &set2, NULL);

	/* executing less critical code */
	sigprocmask(SIG_UNBLOCK, &set1, NULL);
}
