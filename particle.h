/* PROGRAM:	particle.h
   AUTHOR:	Richard Barney
   DATE:	November 2013
   TOPIC:	Assignment 1
   NOTES:	header for Assignment 1
 */

/**************************************************************************
 includes 
**************************************************************************/
#include <stdlib.h>

/**************************************************************************
 definitions 
**************************************************************************/
#define	DFLT_INIT_NUM_PARTICLES 100
#define RANDOM_NUMBER(min, max) (min + (int)((double)max * rand() / (RAND_MAX + 1.0)))

/***************************************************************************
 struct declarations 
****************************************************************************/
struct vector {
	float x;
	float y;
	float z;
};
typedef struct vector Point3D;
typedef struct vector Vector3D;

struct color {
	float r;
	float g;
	float b;
	float a;
};
typedef struct color Color4;

struct particle {
	Color4 col;
	Point3D	pos;
	Vector3D dir;
	Vector3D spd;
	int lifespan;
	int size;
	struct particle* next;
};

/**************************************************************************
 function declarations 
**************************************************************************/
int particle_init(struct particle* p);  
int particle_add(struct particle** head);
int particle_remove(struct particle* p);
int particle_destroy(struct particle** head);
int particle_update(struct particle** head);
