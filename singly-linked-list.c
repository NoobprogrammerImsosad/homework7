/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	printf("[----- [TaeYoungKim] [2021041005] -----]\n");
	char command;
	int key;
	headNode* headnode= NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//새로운 node 만들기
	node->key = key;
	node->link =NULL;
	if(h == NULL){//만약 headNode가 NULL이라면 initialize를 하지 않았다는 뜻
		printf("\nHeadNode is NULL. Please initialize first\n");
		return 0;
	}
	if(h->first == NULL){//만약 headNode의 first가 가리키는게 NULL 이라면 빈 리스트이므로 맨 앞에 만든 노드 추가
		node->link = NULL;
		h->first = node;
		return 0;
	}
	else{
	node->link = h->first;
	h->first = node;
	}

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	if(h == NULL){//만약 headNode가 NULL이라면 initialize를 하지 않았다는 뜻
		printf("\nHeadNode is NULL. Please initialize first\n");
		return 0;
	}
	listNode* p=h->first;//Node 를 검색할때 쓸 pointer p 맨 앞의 header로 초기화 
	listNode* prev = p;//p의 이전 node를 가리키는 pointer prev
	listNode* node = (listNode*)malloc(sizeof(listNode));//Key 값을 data로 하는 새로운 node 만들기
		node -> key = key;
		node -> link = NULL;
	if(p == NULL){//만약 headNode의 first가 가리키는게 NULL 이라면 빈 리스트이므로 맨 앞에 만든 노드 추가
		h->first = node;//headNode의 first에 만들었던 node의 주소를 넣어줌
		return 0;
	}
	while(1){
		if(p->key >= key){//p가 가리키는 node의 key값이 key값보다 크거나 같다면
			if(prev == p){//prev와 p가 같다면 p가 가리키는 node가 맨 앞의 node라는 뜻
				node->link = p;//만들어진 node의 link에 p를 넣어줌
				h->first = node;//headNode의 first에 만들어진 node를 넣어줌
				break;
			}
			else{//prev와 p가 같지 않다면 key값보다 큰 node를 찾았다는 뜻
				prev->link = node;//prev가 가리키는 node의 link에 만들어진 node를 넣어줌
				node->link = p;//만들어진 node의 link에 p를 넣어줌
				break;
			}
		}
		if(p->link == NULL){//p가 가리키는 node의 link가 NULL이라면 key값보다 큰 node가 없다는 뜻
			p->link = node;//마지막 node의 link에 만들어진 node를 넣어줌
			break;
		}
		prev = p;//p가 가리키는 node의 key값이 key값보다 작다면 prev에 p를 넣어주고
		p = p->link;//p를 다음 node로 이동
	}
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	if(h == NULL){//만약 h가 NULL이라면 initialize가 안되어있다는 뜻
		printf("\nHeadNode is NULL. Please initialize first\n");
		return 0;
	}
	listNode* node = (listNode*)malloc(sizeof(listNode));//key값을 data로 하는 새로운 node 만들기
	node -> key = key;
	node -> link = NULL;
	listNode* p = h->first;//Node 를 검색할때 쓸 pointer p 맨 앞의 header로 초기화
	if(p == NULL){//만약 headNode의 first가 가리키는게 NULL 이라면 빈 리스트이므로 맨 앞에 만든 노드 추가
		h->first = node;//headNode의 first에 만들었던 node의 주소를 넣어줌
		return 0;
	}
	while(1){
		if(p->link == NULL){//p가 가리키는 node가 NULL 이라면 마지막 node 이므로 마지막 node 뒤에 붙임
			p->link = node;//마지막 node의 link에 만들었던 node를 연결
			break;
		}
		p = p->link;//p가 가리키는 node의 link가 NULL이 아니라면 다음 node로 이동
	}
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* p = h->first;//맨 앞의 node를 가리키는 pointer p
	if(p == NULL){//만약 headNode의 first가 가리키는게 NULL 이라면 빈 리스트이므로 삭제할게 없음
		printf("\nThe list is empty.\n");
		return 0;
	}
	h->first = p->link;//h가 가리키는 headNode의 first에 p가 가리키는 node의 link를 넣어줌
	free(p);//p가 가리키는 node를 free
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* p = h->first;//맨 앞의 node를 가리키는 pointer p
	listNode* prev = NULL;//p의 이전 node를 가리키는 pointer prev
	if(p == NULL){//만약 headNode의 first가 가리키는게 NULL 이라면 빈 리스트이므로 삭제할게 없음
		printf("\nThe list is empty.\n");
		return 0;
	}
	while(1){
		if(p->key == key){//p가 가리키는 node의 key값이 key값과 같다면
			if(prev == NULL){//prev가 NULL이라면 p가 가리키는 node가 맨 앞의 node라는 뜻
				h->first = p->link;//h가 가리키는 headNode의 first에 p가 가리키는 node의 link를 넣어줌
				free(p);//p가 가리키는 node를 free
				break;
			}
			else{//prev가 NULL이 아니라면 key값을 가진 node를 list에서 찾았다는 뜻
				prev->link = p->link;//prev가 가리키는 node의 link에 p가 가리키는 node의 link를 넣어줌
				free(p);//p가 가리키는 node를 free
				break;
			}
		}
		if(p->link == NULL){//p가 가리키는 node의 link가 NULL이라면 key값을 가진 node가 없다는 뜻
			printf("\nThere is no node with key value.\n");
			break;
		}
		prev = p;//p가 가리키는 node의 key값이 key값과 같지 않다면 prev에 p를 넣어주고
		p = p->link;//p를 다음 node로 이동
	}
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* p = h->first;//맨 앞의 node를 가리키는 pointer p
	if(p == NULL){//만약 headNode의 first가 가리키는게 NULL 이라면 빈 리스트이므로 삭제할게 없음
		printf("\nThe list is empty.\n");
		return 0;
	}
	listNode* prev = NULL;//p의 이전 node를 가리키는 pointer prev
	while(1){
		if(p->link == NULL){//p가 가리키는 node의 link가 NULL이라면 마지막 node이므로
			if(prev == NULL){//prev가 NULL이라면 node가 하나밖에 없다는 뜻
				h->first = NULL;//headNode의 first에 NULL을 넣어줌
				free(p);//p가 가리키는 node를 free
				break;
			}
			else{//prev가 NULL이 아니라면 마지막 node를 찾았다는 뜻
				prev->link = NULL;//prev가 가리키는 node의 link에 NULL을 넣어줌
				free(p);//p가 가리키는 node를 free
				break;
			}
		}
		prev = p;//p가 가리키는 node의 link가 NULL이 아니라면 prev에 p를 넣어주고
		p = p->link;//p를 다음 node로 이동
	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* lead = h->first;//맨 앞의 node를 가리키는 pointer p
	if(lead == NULL){//만약 headNode의 first가 가리키는게 NULL 이라면 빈 리스트이므로 역순으로 바꿀게 없음
		printf("\nThe list is empty.\n");
		return 0;
	}
	listNode* trail = NULL;//p의 이전 node를 가리키는 pointer prev
	listNode* middle = NULL;//p의 다음 node를 가리키는 pointer next
	if(lead->link == NULL){//만약 headNode의 first가 가리키는 node의 link가 NULL이라면 node가 하나밖에 없다는 뜻
		return 0;
	}
	while(lead != NULL){//lead가 NULL이라면 마지막 node 까지 온거임
		middle = lead;//middle에 lead를 넣고
		lead = lead->link;//lead를 다음 node로 이동
		middle -> link = trail;//middle의 link에 trail을 넣어줌
		trail = middle;//trail에 middle을 넣어줌
	}
	h->first = middle;//headNode의 first에 middle을 넣어줌
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

