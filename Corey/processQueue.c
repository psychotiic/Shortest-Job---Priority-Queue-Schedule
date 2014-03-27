//About:
// The algorithiums were found on stack overflow both priority and 
// shortest job first process schedules. 
   #include <stdio.h>
    #include <stdlib.h>     
    //QUEUE
    struct process {
    int pid; //pid
    int burst; // burst
    int priority; //priority
    struct process *next;
    };
     
    struct process *init_process (int pid, int burst, int priority); 
    struct process *plist, *ptmp;
    void listRunningProcesses (struct process *proc);
    void priority (struct process *proc);
    void shortestJobFirst (struct process *proc);
    double newRandomDouble(double min, double max);   
    void processQueueMethods();

    int main (void) {
    /* Initialize process list */
   
	printf("Process List Created\n");
    plist = init_process(1, 50, 3);
    plist->next = init_process(2, 1, 1); ptmp = plist->next; // pid, burst time, priotrity
	for (int i = 3; i < 47; i++){
ptmp->next = init_process(i,i%6 , newRandomDouble(1, 17)); ptmp = ptmp->next;
	}
    ptmp->next = init_process(48, 5, 2); // ends the data
	printf("Process List has Been Loaded with Processes\n");
	processQueueMethods();
    while (plist != NULL) {
    ptmp = plist;
    plist = plist->next;
    free(ptmp);
    };
	printf("Shutting Down Schedule Queue Simulation Program\n");
    return(0);
    };
  ///////////////////////////////////////////////////////  
	void processQueueMethods(){
		listRunningProcesses(plist);
		priority(plist);
		shortestJobFirst(plist);
	}
double newRandomDouble(double min, double max)
{
    return (double)rand()/(double)RAND_MAX * (max - min) + min;
}
     
    // Process list entry initialization routine
    struct process *init_process (int pid, int burst, int priority) {
    struct process *proc;
    proc = malloc(sizeof(struct process));
    if (proc == NULL) {
    printf("Fatal erroror: memory allocation failure.\n");
    exit(1);
    };
    proc->pid = pid;
    proc->burst = burst;
    proc->priority = priority;
    proc->next = NULL;
    return(proc);
    };
 
    // Process listing 
    void listRunningProcesses (struct process *proc) {
    struct process *tmp = proc;
     
    printf("Starting Up:\tProcess List Report\n");
     
    while (tmp != NULL) {
    printf("Process: %d\tPriority: %d\tBurst Time Limit: %d\n", tmp->pid, tmp->priority, tmp->burst);
    tmp = tmp->next;
    };
     
    printf("Shutting Down:\tProcess Listing\n");
    };
    void priority (struct process *proc) {
    int time, start, end, highest;
    struct process *copy, *tmpsrc, *tmp, *beforehighest;
     
    printf("Starting Up:\tPriority Schedule\n");
     
    /* Duplicate process list */
    tmpsrc = proc;
    copy = tmp = NULL;
    while (tmpsrc != NULL) {
    if (copy == NULL) {
    copy = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
    tmp = copy;
    } else {
    tmp->next = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
    tmp = tmp->next;
    };
    tmpsrc = tmpsrc->next;
    };
     

    time = 0;
    while (copy != NULL) {
    beforehighest = NULL;
    highest = copy->priority;
    tmp = copy->next;
    tmpsrc = copy;
    while (tmp != NULL) {
    if (tmp->priority < highest) {
    highest = tmp->priority;
    beforehighest = tmpsrc;
    };
    tmpsrc = tmp;
    tmp = tmp->next;
    };
    if (beforehighest == NULL) {
    start = time;
    time += copy->burst;
    end = time;
    printf("Process: %d\t\nStopping Time: %d\t\nTime Spent Waiting: %d\t\n\n", copy->pid, time, start);
    tmpsrc = copy->next;
    free(copy);
    copy = tmpsrc;
    } else {
    tmp = beforehighest->next;
    start = time;
    time += tmp->burst;
    end = time;
    printf("Process: %d\t\nStopping Time: %d\t\nTime Spent Waiting: %d\t\n\n", tmp->pid, time, start);
    beforehighest->next = tmp->next;
    free(tmp);
    };
    };
     
    printf("Shutting Down:\tPriority scheduling simulation\n");
    };
     // Shortest Job First scheduling simulation 
    void shortestJobFirst (struct process *proc) {
    int time, start, end, shortest;
    struct process *copy, *tmpsrc, *tmp, *beforeshortest;
     
    printf("Starting Up:\tShortest Job First\n");
     
    /* Duplicate process list */
    tmpsrc = proc;
    copy = tmp = NULL;
    while (tmpsrc != NULL) {
    if (copy == NULL) {
    copy = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
    tmp = copy;
    } else {
    tmp->next = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
    tmp = tmp->next;
    };
    tmpsrc = tmpsrc->next;
    };
     
    /* Main routine */
    time = 0;
    while (copy != NULL) {
    /* Find the next job */
    beforeshortest = NULL;
    shortest = copy->burst;
    tmp = copy->next;
    tmpsrc = copy;
    while (tmp != NULL) {
    if (tmp->burst < shortest) {
    shortest = tmp->burst;
    beforeshortest = tmpsrc;
    };
    tmpsrc = tmp;
    tmp = tmp->next;
    };
     
    /* Process job and remove from copy of process list */
    if (beforeshortest == NULL) {
    /* Handle first job is shortest case */
    start = time;
    time += copy->burst;
    end = time;
    printf("Process: %d\t\nStopping Time: %d\t\nTime Spent Waiting: %d\t\n\n", copy->pid, time, start);
    tmpsrc = copy;
    copy = copy->next;
    free(tmpsrc);
    } else {
    /* Handle first job is not shortest case */
    tmp = beforeshortest->next;
    start = time;
    time += tmp->burst;
    end = time;
    printf("Process: %d\t\nStopping Time: %d\t\nTime Spent Waiting: %d\t\n\n", tmp->pid, time, start);
    beforeshortest->next = tmp->next;
    free(tmp);
    };
    };
     
    printf("Shutting Down:\tShortest Job First \n\n");
    };

