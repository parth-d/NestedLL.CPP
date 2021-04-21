#include "LList.h"

LList::LList() {
    head = new node;
    size = 0;
}

LList::LList(int x) {
    head = new node(x);
    size = 1;
}

node *LList::find_tail() const {
    if (head->data.value == -1723)
        return nullptr;
    node* temp = head;
    while (true)
    {
        if (temp->next == nullptr)
            return temp;
        temp = temp->next;
    }
}

void LList::append(int x) {
    node* tail = find_tail();
    if (tail == nullptr)
    {
        int data = x;
        head->data.value = data;
        size++;
        return;
    }
    tail->next = new node(x);
    size++;
}

void LList::prepend(int x) {
    if (find_tail() == nullptr)
    {
        append(x);
        return;
    }
    node* old_head = head;
    head = new node(x);
    head->next = old_head;
    size++;
}

void LList::append(LList *ll) {
    node* tail = find_tail();
    if (tail == nullptr)
    {
        head->holds_ll = true;
        head = new node(ll);
        size++;
        return;
    }
    tail->next = new node(ll);
    size++;
}

void LList::prepend(LList *ll) {
    if (find_tail() == nullptr)
    {
        append(ll);
        return;
    }
    node* old_head = head;
    head = new node(ll);
    head->next = old_head;
    size++;
}


void LList::print() const{
    cout << "[ ";
    if (size == 0)
    {
        cout << " ]";
        return;
    }
    if (find_tail() == nullptr)
    {
        cout << " ]";
        return;
    }
    node* temp = head;
    while (temp != nullptr)
    {
        if (temp->holds_ll)
            temp->data.ll->print();
        else
            cout << temp->data.value << " ";
        temp = temp->next;
    }
    cout << " ]";
}

void LList::copy_from(LList* ll)
{
    if (ll->size == 0)
        return;
    if (ll->find_tail() == nullptr)
    {
        head = new node;
        return;
    }
    node* ptr = ll->head;
    while (ptr != nullptr)
    {
        if (ptr->holds_ll)
            append(ptr->data.ll);
        else
            append(ptr->data.value);
        ptr = ptr->next;
    }
}

void LList::clear() {
    node* ptr = head;
    while (ptr != nullptr)
    {
        node* temp = ptr->next;
        if (ptr->holds_ll)
            ptr->data.ll->clear();
        delete ptr;
        size--;
        ptr = temp;
    }
    head = new node;
}
