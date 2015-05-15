/* PROGRAM:	particle.c
   AUTHOR:	Richard Barney
   DATE:	November 2013
   TOPIC:	Assignment 1
   NOTES:	This file sets how the particles float around the screen.
		They will start in the middle and move in a random 
		direction, bouncing off the edges of the screen and last
		only a few seconds.	
 */

/**************************************************************************
 include private library headers
 **************************************************************************/
#include "particle.h"

/**************************************************************************
 FUNCTION : particle_init
 PURPOSE  : initialize the properties of a single particle
 INPUT    : pointer to the particle structure to be initialized
 OUTPUT   : returns -1 on error, 0 on success
 NOTES    : the core program of Assignment1. makes used of particle.h, particles_OpenGL.c, and random.c. 
 **************************************************************************/
int particle_init(struct particle* p) {
	/* create array to help pick a random number between 0.0 and 1.0 */
	float floatarray[] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
	/* colors */	
	p -> col.r = floatarray[RANDOM_NUMBER(0, 10)];
	p -> col.g = floatarray[RANDOM_NUMBER(0, 10)];
	p -> col.b = floatarray[RANDOM_NUMBER(0, 10)];
	p -> col.a = floatarray[RANDOM_NUMBER(0, 10)];
	/* position */
	p -> pos.x = 0;
	p -> pos.y = 0;
	p -> pos.z = 0;
	/* direction, subtract 5 to get some negative values so that the particles go in all directions */
	p -> dir.x = RANDOM_NUMBER(1, 10) - 5;
	/* if particle is directly on x-axis, loop until its not */
	while (p -> dir.x == 0)
		p -> dir.x = RANDOM_NUMBER(1, 10) - 5;
	p -> dir.y = RANDOM_NUMBER(1, 10) - 5;
	/* if particle is directly on y-axis, loop until its not */
	while (p -> dir.y == 0)
		p -> dir.y = RANDOM_NUMBER(1, 10) - 5;
	p -> dir.z = 0;
	/* speed */
	p -> spd.x = RANDOM_NUMBER(1, 2);
	p -> spd.y = RANDOM_NUMBER(1, 2);
	p -> spd.z = 0;
	/* lifespan */
	p -> lifespan = 100;
	/* size */
	p -> size = 3;
	return 0;
}
/**************************************************************************
 FUNCTION : particle_add
 PURPOSE  : add a particle to the dynamic particle linked list
 INPUT    : struct particle* head. Head of the particle list
 OUTPUT   : returns -1 on error, 0 on success
 NOTES    : calls particle_init();
 **************************************************************************/
int particle_add(struct particle** head) {
	struct particle* new;
	/* allocate memory for new node */
	new = (struct particle*) malloc(sizeof(struct particle));
	new -> next = *head;
	*head = new;
	particle_init(new);
	return 0;
} 

/**************************************************************************
 FUNCTION : particle_remove
 PURPOSE  : remove a specific particle from the dynamic particle linked list
 INPUT    : pointer to the particle to remove
 OUTPUT   : returns -1 on error, 0 on success
 NOTES    : particle can be situated in any part of the list. Usually deleted because the lifespan ran out
 **************************************************************************/
int particle_remove(struct particle* p) {	
	struct particle* old = p;
	/* create temporary pointer because head is not known */
	struct particle* tmp = NULL;
	/* if the value of the next particle is NULL, return -1, else continue on */
	if (old -> next == NULL)
		return -1;
	else {
		/* copy the value of the next node to the current node and delete the next node. */
		tmp = old -> next;
		old -> next = tmp -> next;
		return 0;
	}
}

/**************************************************************************
 FUNCTION : particle_destroy
 PURPOSE  : free memory used by the dynamic particle linked list
 INPUT    : struct particle** head. Head of the particle linked list
 OUTPUT   : returns -1 on error, the number of particles destroyed on success
 NOTES    : removes all particles from the list. Calls particle_remove();
 **************************************************************************/
int particle_destroy(struct particle** head) {	
	struct particle* old;	
	int count = 0;
	/* if the head is already null, return -1, else continue on */	
	if (*head == NULL)
		return -1;
	else {
		while (*head != NULL) {
			old = *head;
			*head = old -> next;
			particle_remove(old);
			count++;		
		}
		return count;
	}
} 

/**************************************************************************
 FUNCTION : particle_update
 PURPOSE  : update the particles properties to be rendered in the next frame
 INPUT    : struct particle** head. Head of the particle linked list
 OUTPUT   : returns -1 on error, 0 on sucesss
 NOTES    : creativity and more creativity
 **************************************************************************/
int particle_update(struct particle** head) {
	struct particle* p = NULL;
	p = *head;
	if (p == NULL)
		return -1;
	/* exit if all particles are gone */
	else if (p -> next == NULL) {
		particle_destroy(&p);
		exit(EXIT_SUCCESS);
	}
	else {
		while (p != NULL) {
			/* change x position */
			p -> pos.x += (p -> spd.x * p -> dir.x);
			/* x boundaries so that particle does not exceed window. just multiply value by -1 to make it bounce off window */
			if (p -> pos.x > 100 || p -> pos.x < -100)
				p -> dir.x *= -1;
			/* change y position */		
			p -> pos.y += (p -> spd.y * p -> dir.y);
			/* y boundaries so that particle does not exceed window. just multiply value by -1 to make it bounce off window */		
			if (p -> pos.y > 100 || p -> pos.y < -100)
				p -> dir.y *= -1;
			/* decrement lifespan by 1 */		
			p -> lifespan -= 1;
			/* if lifespan equals or falls below 0, delete the particle */		
			if (p -> lifespan <= 0)
				particle_remove(p);
			p = p -> next;
		}
		return 0;
	}
}
