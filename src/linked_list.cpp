#include <cstddef>
#include <iostream>

class Node
{
public:
	int data;
	
	Node *next;
};

void display(Node *n)
{
    while (n != NULL)
    {
		std::cout << n->data;
        
        n = n->next;
        
        if (n != NULL)
        {
			 std::cout << " => ";
		}
    }
    
    std::cout << std::endl;
} 

// add to end of list
void append(Node **head_ref, int new_data)
{
    Node *new_node = new Node();
    Node *last = *head_ref;
    
    new_node->data = new_data;
    new_node->next = NULL;
    
    while (last->next != NULL)
    {
        last = last->next;
	}
	
    last->next = new_node;
}

// add to the beginning of list (becomes new head)
void push(Node **head_ref, int new_data)
{
    Node *new_node = new Node();
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
} 

// insert after a specific node
void insert(Node *prev_node, int new_data)
{
    if (prev_node == NULL)
    {
        std::cout << "the given previous node cannot be NULL" << std::endl;
        
        return;
    }
    
    Node *new_node = new Node();
    
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

int main()
{
    auto head = new Node();
    auto second = new Node();
    auto third = new Node();

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

	std::cout << "original:" << std::endl;
    display(head);
    
    std::cout << "push:" << std::endl;
    push(&head, 11);
    display(head);
    
    std::cout << "append:" << std::endl;
    append(&head, 12);
    display(head);
    
    std::cout << "insert:" << std::endl;
    insert(second, 13);
    display(head);
}
