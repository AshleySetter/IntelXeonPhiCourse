#include <utmpx.h>
int sched_getcpu();

int findmycpu_ (){ return sched_getcpu(); }
