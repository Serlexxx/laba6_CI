#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct Node { //��������� ������������ ������
	char value; //�������� �������
	struct Node* next; // ��������� �� ��������� ����
};

void push(struct Node** head, char data) {	//������� ���������� ������ ����
	struct Node* tmp = (struct Node*)malloc(sizeof(struct Node)); //��������� ������ ��� ����� ����
	tmp->value = data;	//������������ ��������
	tmp->next = (*head);
	(*head) = tmp;
}

char pop(struct Node** head) { //�������� �������� �������� �������� � ������
	struct Node* prev = NULL;
	char val;
	if (head == NULL) {
		return 0;
	}
	prev = (*head);
	val = prev->value;
	(*head) = (*head)->next;
	free(prev);
	return val;
}

struct Node* getNth(struct Node* head, int cnt) { //������� �������� � n-� ���������
	int counter = 0;
	while (counter < cnt && head) {
		head = head->next;
		counter++;
	}
	return head;
}


void insert(struct Node* head, unsigned cnt, char val) { //������� ��� ������� ������ �������� �� n-e �����
	unsigned i = 0;
	struct Node* tmp = NULL;
	while (i < cnt && head->next) {
		head = head->next;
		i++;
	}
	tmp = (struct Node*)malloc(sizeof(struct Node));
	tmp->value = val;
	if (head->next) {
		tmp->next = head->next;
	}
	else {
		tmp->next = NULL;
	}
	head->next = tmp;
}

char deleteNth(struct Node** head, int cnt) { //������� �������� n-�� ���������
	if (cnt == 0) {
		return pop(head);
	}
	else {
		struct Node* prev = getNth(*head, cnt - 1);
		struct Node* elm = prev->next;
		char val = elm->value;

		prev->next = elm->next;
		free(elm);
		return val;
	}
}

void deleteList(struct Node** head) { //�������� ����� ������
	struct Node* prev = NULL;
	while ((*head)->next) {
		prev = (*head);
		(*head) = (*head)->next;
		free(prev);
	}
	free(*head);
}


void printLinkedList(const struct Node* head) { //������� ������ �� ����� ������
	printf("\"");
	while (head) {
		printf("%c", head->value);
		head = head->next;
	}
	printf("\"\n");
} 

int cntLetter(struct Node* head) { //������� ���������� ���-�� ���� � �����
	int cnt = 0;
	while (head->value != '\t' && head->value != ' ' && head->value != '\n') {
		cnt++;
		if (head->next != NULL)
			head = head->next;
		else
			break;
	}
	return cnt;
}

int searchWord(struct Node* head) { //������� ������ ���-�� ����
	int cnt = 0;
	int counter = 0;
	while (head) {
		cnt = cntLetter(head);
		if (cnt % 2 == 1) {
			counter++;
			head = getNth(head, cnt);
		}
		else {
			if (cnt == 0) {
				head = head->next;
			}
			else {
				head = getNth(head, cnt);
			}
		}
	}
	return counter;
}

void searchInd(struct Node* head, int* ind) { //������� ������ ������� ����
	int cnt = 0;
	int index = 0;
	int words = 0;
	while (head) {
		cnt = cntLetter(head);
		if (cnt % 2 == 1) {
			ind[words] = index;
			words++;
			head = getNth(head, cnt);
		}
		else {
			if (cnt == 0) {
				head = head->next;
				index++;
			}
			else {
				head = getNth(head, cnt);
				index += cnt;
			}
		}
	}
}

int getCntfromIndex(struct Node* head, int ind) { //������� ��������� ����� ����� ����� ������
	head = getNth(head, ind);
	int cnt = cntLetter(head);
	return cnt;
}


void formatingTabs(struct Node* head, int size) {
	while(head) {
		if (head->value == '\t') {
			head->value = ' ';
		}
		if (head->next != NULL) {
			head = head->next;
		}
		else
			break;
	}
}

int searchSpaces(struct Node* head) { //������� ������ ���-�� �������� ��������
	int ind = 0;
	while (head) {
		if (head->next != NULL) {
			if (head->value == ' ' && head->next->value == ' ')
				return ind;
			else
				ind++;
		}
		if (head->next != NULL)
			head = head->next;
		else
			break;
	}
	return -1;
}

int getSize(struct Node* head) { //������� ������ ������� ������
	int counter = 0;
	while (head) {
		head = head->next;
		counter++;
	}
	return counter;
}

int main() {
	struct Node* head = NULL;
	printf("Enter your string (Ctrl+Z - end enter)\n");
	char c;
	while ((c = getchar()) != EOF) {
		push(&head, c);
	}

	pop(&head);
	printLinkedList(head); // ����� �������� �����

	int cnt = searchWord(head);
	int* ind;
	ind = (int*)malloc(cnt*sizeof(int));
	searchInd(head, ind);
	for (int i = 0; i < cnt; i++) {
		int counter = getCntfromIndex(head, ind[i]);
		while (counter) {
			deleteNth(&head, ind[i]);
			counter--;
		}
	}
	free(ind);


	int size = getSize(head);

	formatingTabs(head, size);

	printLinkedList(head);

	for (int i = 0; i < size; i++) {
		int index = searchSpaces(head);
		if (index != -1) {
			deleteNth(&head, index);
		}
		else
			break;
		size = getSize(head);
	}
	

	printLinkedList(head);
	
	deleteList(&head); // ������� ������
	return 0;
}