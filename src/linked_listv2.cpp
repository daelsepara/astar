#include <cstddef>
#include <iostream>
#include <memory>

class Node
{
public:
    int data;

    std::shared_ptr<Node> next = nullptr;
};

void display(std::shared_ptr<Node> n)
{
    while (n != nullptr)
    {
        std::cout << n->data;

        n = n->next;

        if (n != nullptr)
        {
            std::cout << " => ";
        }
    }

    std::cout << std::endl;
}

// add to end of list
void append(std::shared_ptr<Node> &head_ref, int new_data)
{
    auto new_node = std::make_shared<Node>();
    auto last = head_ref;

    new_node->data = new_data;
    new_node->next = nullptr;

    while (last->next != nullptr)
    {
        last = last->next;
    }

    last->next = new_node;
}

// add to the beginning of list (becomes new head)
void push(std::shared_ptr<Node> &head_ref, int new_data)
{
    auto new_node = std::make_shared<Node>();
    new_node->data = new_data;
    new_node->next = head_ref;
    head_ref = new_node;
}

// insert after a specific node
void insert(std::shared_ptr<Node> &prev_node, int new_data)
{
    if (prev_node == nullptr)
    {
        std::cout << "the given previous node cannot be nullptr" << std::endl;

        return;
    }

    auto new_node = std::make_shared<Node>();

    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

int main()
{
    auto head = std::make_shared<Node>();
    auto second = std::make_shared<Node>();
    auto third = std::make_shared<Node>();

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    std::cout << "original linked list:" << std::endl;
    display(head);

    std::cout << "push to front (before 1):" << std::endl;
    push(head, 11);
    display(head);

    std::cout << "append at the end (after 3):" << std::endl;
    append(head, 12);
    display(head);

    std::cout << "insert (after 2):" << std::endl;
    insert(second, 13);
    display(head);
}
