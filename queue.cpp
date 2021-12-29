//Author: Manav Gupta
//UIC
//Project 5

#include "pqueue.h"

using namespace std;


//
// pq_init
//
// Initializes list to empty; must be called before list can 
// be used with other queue functions.
//
void pq_init(List& L)
{
    L.Head = nullptr; // head of the list is pointing to nullptr as it is currently empty
    L.Count = 0; // empty list count = 0
}

void pq_sort_list(List& L)
{
    if (L.Count > 2)
    {
        Node* cur;
        Node* cur2;

        for (cur = L.Head; cur != nullptr; cur = cur->Next) 
        {
            for (cur2 = L.Head; cur2 != nullptr; cur2 = cur2->Next) 
            {
                if (cur->Data.Priority < cur2->Data.Priority) 
                {
                    Node* temp = cur;
                    cur = cur2;
                    cur2 = temp;
                }
            }
            cur2 = L.Head;
        }
    }
    else if (L.Count == 2)
    {
        Node* cur = L.Head;
        Node* cur2 = cur->Next;
                
        if (cur->Data.Priority > cur2->Data.Priority)
        {
            Node* temp = cur;
            cur = cur2;
            cur2 = temp;
        }
    }
}

void pq_sort_list2(List& L)
{
    Node* cur = L.Head;
    Node* cur2 = L.Head;
    
    for (cur = L.Head; cur != nullptr; cur = cur->Next) 
    {
        for (cur2 = L.Head ; cur2 != nullptr; cur2 = cur2->Next) 
        {
            if (cur->Data.Priority < cur2->Data.Priority) 
            {
                Node* temp = new Node();
                
                temp->Data.ID = cur->Data.ID;
                temp->Data.Priority = cur->Data.Priority;
                
                cur->Data.ID = cur2->Data.ID;
                cur->Data.Priority = cur2->Data.Priority;
                
                cur2->Data.ID = temp->Data.ID;
                cur2->Data.Priority = temp->Data.Priority;
                
                delete temp;
            }
        }
        cur2 = L.Head;
    }
}

//
// pq_print
// 
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void pq_print(List L)
{
    pq_sort_list(L);
    
    Node* cur = L.Head; // cur points to first node in list
    
    if (cur == nullptr)
        cout << "List: " << endl; // trying to print before adding or after deleting any or all elements of the list
    
    else
    {
        cout << "List: ";
        
        while (cur->Next != nullptr) // loops till second last node in list
        {
            cout << "(" << cur->Data.ID << "," << cur->Data.Priority << ") ";
            cur = cur->Next;
        }
        cout << "(" << cur->Data.ID << "," << cur->Data.Priority << ")" << endl;
    }
}

//
// pq_front
//
// Returns the ID at the front of the priority queue. Throws 
// an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_front: queue empty");
//
int pq_front(List L)
{
    if (L.Count == 0)
    {
        throw invalid_argument("pq_front: queue empty");
    }
    
    Node* cur = L.Head;
    return cur->Data.ID;
}

//
// pq_dequeue
//
// Removes the data element at the front of the queue, removing the
// node as well and freeing this memory. Nothing is returned.
// Throws an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_dequeue: queue empty");
//
void pq_dequeue(List& L)
{
    if (L.Count == 0)
    {
        throw invalid_argument("pq_dequeue: queue empty");
    }
    
    else if(L.Count == 1)
    {
        Node* cur = L.Head;
        delete cur;
        L.Head = nullptr;
    }
    else
    {
        Node* cur = L.Head;
        Node* temp = cur; // temp node points to cur
        cur = cur->Next; // cur points to next node
        delete temp; // delete temp (node before cur)
        L.Head = cur;
    }
    L.Count -= 1;
}

int pq_prio_index(List L, int priority)
{
    Node* cur = L.Head;
    
    int n = 0;
    
    while (cur!= nullptr)
    {
        if (cur->Data.Priority > priority)
            break;
        cur = cur->Next;
        n++;
    }
    return n;
}
//
// pq_enqueue
//
// Inserts the given (ID,priority) pair into the queue based on
// the priority, ordered low to high. If elements already exist with
// the same priority, this new element comes after those elements.
// Example: suppose the queue currently contains the following 
// (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to enqueue (79,25) yields the following result:
//
//   (10,19) (84,25) (79,25) (21,50)
//
// If the ID is already in the queue, then the pair is repositioned 
// based on the new priority. For example, suppose the queue is as
// shown above, and we enqueue (84,50). The result is now
//
//   (10,19) (79,25) (21,50) (84,50)
//
void pq_enqueue(List& L, int ID, int priority)
{
    pq_sort_list(L);
    
    int index = search_list(L, ID);
    
    if (index == -1)
    {
        int n = pq_prio_index(L, priority);
     
        if (n > 0 && n < L.Count)
        {
            Node* cur = L.Head;
            Node* prev = nullptr;

            while (cur!= nullptr)
            {
                if (cur->Data.Priority > priority)
                    break;
                prev = cur;
                cur = cur->Next;
            }
            Node* New = new Node();
            New->Data.ID = ID;
            New->Data.Priority = priority;

            prev->Next = New;
            New->Next = cur;
            L.Count++;
        }
        else if (n > 0 && n == L.Count)
        {
            Node* cur = L.Head;
            Node* New = new Node();
            New->Data.ID = ID;
            New->Data.Priority = priority;
            
            while (cur->Next != nullptr)
            {
                cur = cur->Next;
            }
            
            cur->Next = New;
            New->Next = nullptr;
            L.Count++;
        }
        else if (L.Count == 1)
        {
            Node* cur = L.Head;
            
            if (cur->Data.Priority > priority)
            {
                Node* New = new Node();
                New->Data.ID = ID;
                New->Data.Priority = priority;
                
                L.Head = New;
                New->Next = cur;
                L.Count++;
            }
            else
            {
                NodeData d;
                d.ID = ID;
                d.Priority = priority;
                push_back_list(L, d);
            }
        }
        else
        {
            NodeData d;
            d.ID = ID;
            d.Priority = priority;
            
            push_front_list(L, d);
        }
    }
    else
    {
        if (L.Count > 1)
        {
            Node* cur = L.Head;

            while (cur != nullptr)
            {
                if (cur->Data.ID == ID)
                    break;
                cur = cur->Next;
            }
            
            cur->Data.Priority = priority;
            
            pq_sort_list2(L);
            
        }
        else
        {
            Node* cur = L.Head;
            
            cur->Data.Priority = priority;
            
            pq_sort_list2(L);
        }
    }
}

//
// pq_nudge
// 
// Nudges the element with the given ID forward one element in the
// queue. The element takes on the same priority as the element
// that now follows it.  Example: suppose the queue currently contains
// the following (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to "nudge" 21 forward produces this result:
//
//   (10,19) (21,25) (84,25)
//
// If the ID is already at the front of the queue, nothing happens.
// If the ID is not in the queue, throws "invalid_argument" exception, i.e.
// throw invalid_argument("pq_nudge: ID not found");
//
void pq_nudge(List& L, int ID)
{
    int index = search_list(L, ID);
    
    if (index == -1)
    {
        throw invalid_argument("pq_nudge: ID not found");
    }
    
    else
    {
        if (L.Count > 1)
        {
            if (index > 0)
            {
                Node* cur = L.Head;
                Node* prev = nullptr;

                while (cur != nullptr)
                {
                    if (cur->Data.ID == ID)
                        break;
                    prev = cur;
                    cur = cur->Next;
                }
                cur->Data.Priority = prev->Data.Priority;
                NodeData tempData;
                tempData.ID = cur->Data.ID;
                cur->Data.ID = prev->Data.ID;
                prev->Data.ID = tempData.ID;
            }
        }
    }
}

//
// pq_clear
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void pq_clear(List& L)
{
    free_list(L);
}

//
// pq_duplicate
//
// Makes a complete copy of the given list L and returns this duplicate.
// A "deep" copy is made, meaning all nodes and data are duplicated in 
// the new, returned list.
//
List pq_duplicate(List L)
{
    List C;
    pq_init(C);
    pq_sort_list(L);
    Node* cur = L.Head;
    
    while (cur != nullptr)
    {
        push_back_list(C, cur->Data);
        
        cur = cur->Next;
    }
    
    return C;
}
