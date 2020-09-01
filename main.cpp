#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <math.h>
#include <map> 
#include <string>
#include <cstring>
#include "Heap.hpp"
#include "Object.hpp"
//#include "gnuplot-iostream.h"

using namespace std;

int main(int argc, char *argv[])
{
	int alloc_addr,lineNo=0,lineNoArr=0,gcount=0;
	float p = 1.5; float usedret=0; int t = 60;
	int threadid,objectid,classid,objectsize,objectref,parentid,childid,slotno,fmfield,fieldsize,fieldtype;
	std::string lines,ids;
	char a,b,c,d1,e,f,g;
    std::ifstream infile(argv[1]);
	std::ofstream outfile;

	if (argc == 4)
	{
		std::cout << " argv[1]= " <<argv[1];
		std::cout << " argv[2]= " <<argv[2];
		std::cout << " argv[3]= " <<argv[3] << std::endl;
	}
	else
	{
		std::cout << "\n Please enter correct number of arguments" << std::endl;
		std::cout << "\n------------------HELP------------------" << std::endl;
		std::cout << " Argument 1 : <Input Trace File Name> " << std::endl;
		std::cout << " Argument 2 : <Output File Name> " << std::endl;
		std::cout << " Argument 3 : <Heap Size> " << std::endl;
		std::cout << " Example : >./Heap trace.trace stats.txt 30" << std::endl; 
		return -1;
	}
	Heap* H1 = new Heap(atoi(argv[3]));

	std::map<int,Object*> rootset;
	std::map<int,Object*> allocset;
	std::map<int,int> plot; 
	std::map<int,Object*>::iterator itr; 

    if(!infile.is_open())
    {
	    std::cout<<" \n Error in opening file!!!"<< std::endl;
       	return 0;
   	}
	else
	{
		freopen(argv[2],"a+",stdout);
		cout << "\nStart of Output \n";
		infile >> ids; 	
		while(!infile.eof())
		{

			//cout << " In here line  " << lineNo << "\n";
			if (ids == "a")
			{	
				
				lineNo++;
				//cout << " In here a " << lineNo << "\n";
				infile >> a >> threadid >> b >> objectid >> c >> objectsize >> d1 >> objectref >> e >> classid;	
				alloc_addr=H1->allocate(objectsize);
				if(alloc_addr == -1)
				{
					gcount++;
					cout << "\nfailed at line " << lineNo ;
					cout<< "\nBefore the " << gcount << " Garbage Collection: ";
					std::map<int,Object*> allocsetret;					
					H1->stats();
					H1->FreeList->printList();
					allocset=H1->collector(allocset,rootset,H1);	
					
					
					cout<< "After the " << gcount << " Garbage Collection: ";
				
					
					usedret = H1->stats();
					plot.emplace(gcount,usedret);
					H1->FreeList->printList();
				
					int prevsize = H1->size;
					if(usedret > t)
					{
						H1->size = H1->size * p;
						H1->liveNodes += 1;
						H1->free(prevsize,(H1->size) - prevsize);
					}
					alloc_addr=H1->allocate(objectsize);
					if(alloc_addr == -1)
					{
						cout<< "\nNo Memory Post GC";
						//freopen(argv[2],"a+",stdout);  
                		cout << "failed at line " << lineNo ;
                		H1->stats();					
						fclose(stdout);
    		   			exit(1);
					}	
				}
				
				Object* ob = new Object(threadid,objectid,objectsize,objectref,classid,alloc_addr);
			
				allocset.emplace(objectid,ob);
				lineNoArr++;
			}
			else if(ids== "+")
			{
				lineNo++;
				//cout << "\nLineNo + : " << lineNo << " =================================\n";
				infile >> a >> threadid >> b >> objectid;	
				Object *temp = nullptr;
				itr = allocset.find(objectid); 
				if(itr == allocset.end()) 
       				 cout << "Not present in map\n" ; 
    			else
        		{
					temp=itr->second;
				}
			
				rootset.emplace(objectid,temp);
				
			}
			else if(ids == "e")
			{
				freopen(argv[2],"a+",stdout);  
            	cout << "Successful completion ";           
				H1->stats();
				fclose(stdout);
			}	
			else if(ids == "-")
			{
				lineNo++;
				//cout << "\n\tLineNo - : " << lineNo << "=================================";
				infile >> a >> threadid >> b >> objectid;	
				rootset.erase(objectid);
			} 
			else if (ids == "w")
			{	
				lineNo++;
				//cout << "\nLineNo w : " << lineNo << " =================================";
				infile >> a >> threadid >> b >> parentid >> c >> slotno >> d1 >> childid >> e >> fmfield >> f >> fieldsize >> g >> fieldtype;	
				Object *temp = nullptr;
				itr = allocset.find(parentid);
				if(itr == allocset.end()) 
       				 cout << "\n Parent not present in map" ; 
    			else
        		{
					temp=itr->second;
					temp->objectRefSlots[slotno] =  childid;
				}
			}
			else
			{
				//cout << "\nLineNo crs: " << lineNo << " =================================";
				if(ids== "c" || ids == "r" || ids == "s")
				{
					lineNo++;
				}
			}
			infile >> ids;
		}	
		if(infile.eof())
		{
			//cout << "\n******** \nEND OF THE FILE\n********\n";
			freopen(argv[2],"a+",stdout);  
            cout << "Successful completion ";           
			H1->stats();
			fclose(stdout);

			stringstream ss;
			float ts=t;
			ss << "p" << p << "_t" << ts/100 << " _plot"<< ".txt";
			string h = ss.str();
			cout << h;
			std::ofstream plotfile;
			plotfile.open(h, std::ios::trunc );
			for (auto itrs = plot.begin(); itrs != plot.end();)
			{
				plotfile << itrs->first << " " << itrs->second << endl;
				itrs++;
			} 
			plotfile.close();
		
		}
	}
	outfile.close();
	return 0;

}
