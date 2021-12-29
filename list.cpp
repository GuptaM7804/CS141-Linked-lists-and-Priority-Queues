//Author: Manav Gupta
//UIC
//Project 5

#include "list.h"

using namespace std;

//
// Functions:
//

// 
// init_list
//
// Initializes list to empty; must be called before list can 
// be used with other functions.
//
void init_list(List& L)
{
    L.Head = nullptr; // head of the list is pointing to nullptr as it is currently empty
    L.Count = 0; // empty list count = 0
}
//
// print_list
//
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void print_list(List L)
{
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
// push_back_list
//
// Pushes the data onto the end of the list.
//
void push_back_list(List& L, NodeData d)
{
    Node* New = new Node(); // new node pointer created
    New->Data = d; // give new node's data user inputted data
    New->Next = nullptr; // node points to nullptr
        
    if (L.Head == nullptr)
        L.Head = New; // if list is empty, simply makes head = new node
    
    else
    {
        Node* cur = L.Head;
        while (cur->Next != nullptr)
        {
            cur = cur->Next;
        }
        
        cur->Next = New; // last node in the list points to the new node, making the new node the last node of the list
    }
    L.Count++; // increase count by one as new node has been added
}

//
// push_front_list
//
// Pushes the data onto the front of the list.
//
void push_front_list(List& L, NodeData d)
{
    Node* New = new Node();
    New->Data = d;
    New->Next = L.Head; // new node points to head
    
    L.Head = New; // head = new node, therefore new node becomes first node in the list
    L.Count++;  // increase count by one for each time function is called (new node is added)
}

//
// free_list
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void free_list(List& L)
{
    Node* cur = L.Head;
    
    while (cur != nullptr)
    {
        Node* temp = cur; // temp node points to cur
        cur = cur->Next; // cur points to next node
        delete temp; // delete temp (node before cur)
    }
    L.Head = nullptr; // head = nullptr and therefore list is empty
    L.Count = 0; // empty list count = 0
}

//
// search_list
//
// Search the list for the first occurrence of the given ID. If found,
// its position in the list is returned; positions are 0-based,
// meaning the first node is position 0. If not found, -1 is
// returned.
//
int search_list(List L, int ID)
{
   int index = 0;
   
   Node* cur = L.Head;
   
   while (cur != nullptr)
   {
      if (cur->Data.ID == ID)
      {
         return index;
      }
      cur = cur->Next;
      index++; // index is added by 1 until Id = cur->data.Id
   }
   
   return -1; // returns -1 if not found
}

//
// retrieve_from_list
//
// Retrieve's the data from node at the given position; the list 
// remains unchanged. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("retrieve_from_list: invalid position");
//
NodeData retrieve_from_list(List L, int pos)
{
    Node* cur = L.Head;
    
    if (pos >= L.Count || pos < 0)
      throw invalid_argument("retrieve_from_list: invalid position"); // if wrong position is given
        
    else
    {
        int n = 0;
        while (cur != nullptr)
        {
            if (n == pos) // when cur position = user given position, cur->data is returned
            {
                break; // leaves loop
            }
            cur = cur->Next;
            n++; // n is the position index of cur
        }
    }
    return cur->Data;
}

//
// remove_from_list
//
// Removes and frees the node at the given position, returning 
// the node's data. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("remove_from_list: invalid position");
//
NodeData remove_from_list(List& L, int pos)
{
    NodeData temp;
    Node* cur = L.Head;
    Node* prev = nullptr;
    
    if (pos >= L.Count || pos < 0)
    {
        throw invalid_argument("remove_from_list: invalid position"); // if wrong position is given
    }
    
    else
    {
        if (pos == 0){
            L.Head = L.Head->Next;
            temp = cur->Data;
            delete cur;
        }
        else
        {
            int n = 0;

            while (cur != nullptr)
            {
                if (n == pos)
                {
                    break;
                }

                prev = cur;
                cur = cur->Next;
                n++;
            }
            prev->Next = cur->Next; //prev next points to cur next instead of cur as cur is to be deleted
            temp = cur->Data;
            delete cur;
        }
    }
    L.Count -= 1; // reduce count by one as node deleted
    return temp;
}
