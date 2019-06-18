#ifndef SIZES_H
#define SIZES_H

#define YES 0
#define NO 1
#define MAYBE 2

#define SIZE 1

#if (SIZE == 0) //tiny
	#define BUFFER 10
	#define HASH 10
	#define BUCKET 5
	#define NEIGHBORS 10
	#define INDEX 10
	#define QUEUE 5
	#define STACK 2
	#define POINTS 10
	#define BOTTOM 0.2
	#define COMPNODES 1
	#define COMPONENTS 3
	#define GRAILINDEX 10
	#define GRAIL 1
	#define THREADS 4
	#define VERSIONS 2
	#define RESSIZE 10
#elif (SIZE == 1) // small-medium-large
	#define BUFFER 1000
	#define HASH 1000
	#define BUCKET 1000
	#define NEIGHBORS 15
	#define INDEX 1000
	#define QUEUE 100
	#define STACK 1000
	#define POINTS 100
	#define BOTTOM 0.2
	#define COMPNODES 500
	#define COMPONENTS 1000
	#define GRAILINDEX 1000
	#define GRAIL 3
	#define THREADS 6
	#define VERSIONS 1000
	#define RESSIZE	5000
	#define JQUEUE 5000
#else	 // large alternative
	#define BUFFER 3000
	#define HASH 3000
	#define BUCKET 6000
	#define NEIGHBORS 60
	#define INDEX 3000
	#define QUEUE 300
	#define STACK 3000
	#define POINTS 300
	#define BOTTOM 0.2
	#define COMPNODES 3000
	#define COMPONENTS 3000
	#define GRAILINDEX 3000
	#define GRAIL 5
	#define THREADS 6
	#define VERSIONS 100
	#define RESSIZE	200
#endif	

#endif // SIZES_H
