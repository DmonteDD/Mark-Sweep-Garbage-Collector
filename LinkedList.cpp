#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <math.h>
#include "LinkedList.hpp"

using namespace std;
    
    /*
	* Constructor Name: LinkedList()
    * Parameters : None
    * Description : Sets the head to NULL. 
    */
    LinkedList::LinkedList()
    {
        this->head = NULL;
    }
    /*
	* Function Name: find_free()
    * Parameters :  NodeSize
    * Return Type : int
    * Description : Finds and returns the position at which the allocation 
    *               can be done in freelist.
    */
    int LinkedList::find_free(int size)
    {
        //cout << " In Find Free \n";
        int s=size;
        int ret = -1;
        Node* temp = head;
        while(temp!=NULL)  
		{  
            //std::cout << temp->size<<" ";
            if(temp->size >= s )
            {
		        //std::cout << temp->size<< " | " << temp->addr << " | \n";  
        	    ret = temp->addr;
                break;
            }
            temp=temp->next;  
    	}  
		//std::cout<< std::endl;
        //cout << "Return " << ret << " \n"; 
        return ret;
    }
    /*
	* Function Name: freeNodeLL()
    * Parameters :  Address
    * Return Type : void
    * Description : Frees the node from the freelist and links the previous and 
    *               next node  if they exist.
    */
    void LinkedList::freeNodeLL(int addr)
    {
        Node *temp = head;
        Node *prev = head;
        //cout << "In freeNodeLL";
        while(temp->addr != addr)
        {
            prev=temp;
            temp=temp->next;
        }
        //cout << "\n prev->addr : " << prev->addr;
        //cout << "\n temp->addr : " << temp->addr;
        if(temp==head)
        {
            head=head->next;
            free(temp);
        }
        else if(temp->next==nullptr)
        {
            prev->next=nullptr;
            free(temp);
        }
        else
        {
            prev->next=temp->next;
        }
        
        
        
        return;
    }
    /*
	* Function Name: printList()
    * Parameters :  None
    * Return Type : void
    * Description : Prints the freelist.
    */
    void LinkedList::printList()  
	{       
        if (head == NULL) 
        {
            cout << "List is empty!" << endl;
        }
        else 
        {
            Node* temp = head;
            cout << " FREE LIST : [";
            while (temp != NULL) 
            {
                cout << " (" << temp->addr << "," << temp->size << ") ";
                temp = temp->next;
            }
           cout << " ]";
            cout << endl;
        }
	}

    /*
	* Function Name: countList()
    * Parameters :  None
    * Return Type : void
    * Description : counts the node in the freelist.
    */
    int LinkedList::countList()  
	{       
        int c=0;
        if (head == NULL) 
        {
            //cout << "List is empty!" << endl;
        }
        else 
        {
            Node* temp = head;
            while (temp != NULL) 
            {
                c++;
                //cout << temp->size << " ";
                temp = temp->next;
            }
            //cout << endl;
        }
        //cout << "Count =" << c << endl;
        return c;
	}	
