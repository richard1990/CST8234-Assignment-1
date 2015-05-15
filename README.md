# CST8234 Assignment #1 - Particle System
This was my assignment I created in my "C Language and Network Programming" course at Algonquin College. Written in C using Vim, the particle system I created allows the particles to "bounce" off the boundaries by multiplying their position incremently by -1 if they reached the window boundaries. This results in the particles going backwards until they hit the other end, in which case they will again bounce off the wall and repeat. Upon opening the program, 100 particles are generated. I compiled the files with a makefile, while most of the code in the "particles_OpenGL.c" file was written by my professor.

Making use of rand() (which makes use of a definition in "particle.h" provided by my professor), I randomized values to determine the particle colours (which are all opaque), direction (a random number between 1 and 10 subtracted by 5 to generate negative numbers so that the particles shoot all over the place), and speed (same method as with direction, only choosing between 1 and 2 for speed value). All particles have a lifespan of 100 and a size of 3. All particles also originate at the centre of the window (position 0,0). The particles disappear once their lifspan reaches 0, and the program exits if there are no more particles.

I only change the x and y values to make the particles bounce off the walls. The formulas to do this are as follows:

p -> pos.x += (p -> spd.x * p -> dir.x);
p -> pos.y += (p -> spd.y * p -> dir.y);

I check the boundaries with the following code:

if (p -> pos.x > 100 || p -> pos.x < -100)
    p -> dir.x *= -1;
if (p -> pos.y > 100 || p -> pos.y < -100)
    p -> dir.y *= -1;

This program expanded my knowledge of C and got me to really think about creating and freeing memory.
