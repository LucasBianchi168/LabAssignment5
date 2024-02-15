#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	if (head == NULL) {
		// if the list is empty, then return 0
		return 0;
	}
	else {
		node* temp = head; // use temp to scroll through the linked list
		int count = 0; // use count to count the characters in the linked list
		while (temp != NULL) {
			++count; // increment count
			temp = temp->next; // move to the next node
		}
		return count; // return the count;
	}
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	if (head == NULL) {
		// cannot print the string if the linked list is empty
		printf("ERROR: Head is NULL. Please try again!");
		return '\0';
	}
	else {
		int strlen = length(head); // get the length of the stringwe have in the linked list
		node* temp = head; // use temp to scroll through the linked list
		char* string = (char*)malloc(10000 * sizeof(char)); // this is the string pointer that will be returned
		for (int i = 0; (i < strlen); ++i) {
			//
			string[i] = temp->letter; // add the letter to the string pointer
			temp = temp->next; // scroll to the next node
		}
		string[strlen] = '\0'; // add a null character at the end of the string to ensure there are no glitched characters
		return string; // return the string pointer
	}
}

// inserts character to the linkedlist
// if the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	node* temp = *pHead; // use temp to scroll through the linked list
	if (*pHead == NULL) {
		// if the linked list is empty, create its first node
		*pHead = (node*)malloc(sizeof(node));
		(*pHead)->letter = c;
		(*pHead)->next = NULL;
	}
	else {
		while(temp->next != NULL) {
			// scroll through the linked list until you reach the end
			temp = temp->next;
		}
		node* newNode = (node*)malloc(sizeof(node)); // create a new node and give its data
		newNode->letter = c;
		newNode->next = NULL;
		temp->next = newNode;
	}
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	if (*pHead == NULL) {
		// cannot delete a list if it doesn't exist
		printf("ERROR: Head is NULL. Either the list doesn't exist or was already deleted.");
	}
	else {
		node* temp = *pHead; // use temp to scroll through the linked list
		node* toDel = *pHead; // this variable will be used to free each node of the linked list
		while (temp != NULL) {
			toDel = temp; // assign toDel to temp
			temp = temp->next; // scroll to the next node of the linked list
			free(toDel); // free the node that is assigned to toDel
		}
		*pHead = NULL; // free doesn't affect *pHead's value, so assign NULL to *pHead so that it doesn't point to the now deleted linked list
	}
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}