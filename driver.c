#include <stdio.h>
#include <string.h>
#include "user.h"


int main(void) {
	struct User * head=NULL;
	printf("creating head\n");
	head = add(head, "rob");
	printUser(head);
	printf("printing digest of rob head\n");
	struct Digest digest;
	generateDigest(&(digest), head);
	printDigest(digest);

	struct User* newuser;
	head = add(head, "newuser");
	printUser(head);
	struct Digest newdigest;
	generateDigest(&(newdigest), head);
	printf("printing digest of newuser head\n");
	printDigest(newdigest);

	printf("comparing digest of rob and newuser\n");
	if (digest_equal(digest, newdigest)) {
		printf("digests are equal\n");
	}
	else {
		printf("digests are not equal\n");
	}
	




	


	//head = add(head, "hanif");
	//head = add(head, "gahyun");
	//head = add(head, "matt");
	//head = add(head, "sumita");
	//head = add(head, "james");
	//printf("verifying log\n");
	//verify(head);
	//printf("printing log\n");
	//printLog(head);
	//printUser(head);
	return 0;
}