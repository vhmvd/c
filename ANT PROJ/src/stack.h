#if !defined(STACK_H)
#define STACK_H

#define MAX_SIZE 100

typedef struct{
	int x, y;
}coordinates;

int         isEmpty();
int         isFull ();
coordinates peek   (); 
coordinates pop    ();
void        push   (coordinates);
void        clear  ();

#endif // STACK_H
