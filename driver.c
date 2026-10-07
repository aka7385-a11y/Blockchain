#include <stdio.h>
#include <string.h>
#include "user.h"


int main(void) {
	struct User * head=NULL;
	printf("creating head\n");
	head = add(head, "rob");
	head = add(head, "hanif");
	head = add(head, "gahyun");
	head = add(head, "matt"); 
	head = add(head, "sumita");
	printf("verifying log\n");
	verify(head);
	printf("printing log\n");
	
	return 0;
}