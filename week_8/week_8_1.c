#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
typedef struct Node {
	char elem;
	struct Node* next;
	struct Node* prev;
}Node;
Node* header;
Node* trailer;
Node* getNode() {
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}
void init() {
	header = getNode();
	trailer = getNode();

	header->next = trailer;
	trailer->prev = header;
}
void add(int r, char e) {
	Node* p = getNode();
	p->elem = e;
	Node* q =header;
	while (r--) {
		q = q->next;
	}
	p->prev = q->prev;
	p->next = q;
	q->prev->next = p;
	q->prev = p;

}
void delete( int r) {
	Node* q = header;
	while (r--) {
		q = q->next;
	}
	Node* p = q;
	q->prev->next = q->next;
	q->next->prev = q->prev;

	free(p);
}
char get(int r) {
	Node* q = header;
	while (r--) {
		q = q->next;
	}
	return q->elem;
}
void print() {
	Node* q = header->next;
	while (q !=trailer) {
		printf("%c", q->elem);
		q = q->next;
	}
}
int main(void) {
	int n,cnt=0;
	init();
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		char ch, e;
		int r;
		getchar();
		scanf("%c", &ch);
		if (ch == 'A') {
			scanf("%d %c", &r, &e);
			
			if (r > cnt+1) {
				printf("invalid position\n");
			}
			else { 
				add(r, e);
				cnt++;
			}
		}
		else if (ch == 'D') {
			scanf("%d", &r);
			if (r > cnt) {
				printf("invalid position\n");

			}
			else { 
				delete(r); 
				cnt--;
			}
		}
		else if (ch == 'G') {
			scanf("%d", &r);
			if (r > cnt) {
				printf("invalid position\n");
			}
			else { 
				printf("%c",get(r));
			}
		}
		else if (ch == 'P') {
			print();
			printf("\n");
		}

	}
	return 0;
}