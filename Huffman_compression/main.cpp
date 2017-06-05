#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdio>
#include "linkedlist.h"
using namespace std;


WordSLList::~WordSLList() {
    for (WordSLLNode *p; !isEmpty(); ) {
        p = head->next;
        delete head;
        head = p;
    }
}
void WordSLList::addToList(string el) {
	WordSLLNode *tmp;
    for (tmp = head; tmp != 0; tmp = tmp->next){
         if(tmp->info == el){
		tmp->count+=1;
		tmp->size+=tmp->info.size();
		break;
		}
	}
   if(tmp==0){
	
       	 if (tail != 0) {      
        		WordSLLNode *tmp=0;
			WordSLLNode *tmp2=0;
			if(el<head->info){
				head=new WordSLLNode(el,head);
			}else if(tail->info>el){
				for(tmp=head->next,tmp2=head;tmp!=0 && tmp->info<el;tmp=tmp->next,tmp2=tmp2->next);
   	 			if(tmp!=0){
					tmp2->next=new WordSLLNode(el,tmp);
	 			}
			}else {
			 		tail->next=new WordSLLNode(el);
					tail=tail->next;
				}
					
    	 }else head = tail = new WordSLLNode(el);
	 
	}    
}
/*void WordSLList::deleteWord(string el) {
	if(isInList(el)){   
		if (head != 0)                    
	        	 if (head == tail && el == head->info) { 
		             delete head;                      
		              head = tail = 0;
        	 }
        		 else if (el == head->info) {  
             		 WordSLLNode *tmp = head;
             		 head = head->next;
             		 delete tmp;            
        	 }
         	 else {                       
             		 WordSLLNode *pred, *tmp;
             	 	 for (pred = head, tmp = head->next; 
               	  	 tmp != 0 && !(tmp->info == el);
                       	 pred = pred->next, tmp = tmp->next);
             	 if (tmp != 0) {
                	  pred->next = tmp->next;
                 	  if (tmp == tail)
                 	     tail = pred;
                  	     delete tmp;
              }
		cout<<"This Word is deleted."<<endl;
         }
	}else {
		cout<<"This Word is not in List,So you cant delete!"<<endl;}
	
}
*/
bool WordSLList::isInList(string el) const {
    WordSLLNode *tmp;
    for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
         return tmp != 0;
	
}

void WordSLList::printAll() const {
   for (WordSLLNode *tmp = head; tmp != 0; tmp = tmp->next){
        cout << tmp->info << " ";
	cout << tmp->count<<" ";
	cout<<tmp->id<<" ";
	cout<<tmp->size<<endl;
	}
}
void readFileIntoLL(WordSLList *myList){

	char c;
	string temp="";
	ifstream inFile("input.txt");
	if(!inFile){
		cout<<"Unable to open file!";
		}
	 inFile.get(c);
	while (!inFile.eof()){
		 if((c>95 && c<123) || (c>64 && c<91) || (c>31 && c<64)){
			temp+=c;
		 }
		 else{
			if(temp!=""){
			myList->addToList(temp);
			}
			temp="";
			}
	 		       
	 inFile.get(c);
	}
	inFile.close();
}
/*void WordSLList::dictionary(){
	int tmpnum;
	string word;
	bool unsorted=true;
	while(unsorted){
		unsorted=false;
		WordSLLNode *cur=head;
		while(cur->next!=0){
			if(cur->info > cur->next->info){
				tmpnum=cur->id;
				cur->id=cur->next->id;
				cur->next->id=tmpnum;
				
				word=cur->info;
				cur->info=cur->next->info;
				cur->next->info=word;				

				tmpnum=cur->size;
				cur->size=cur->next->size;
				cur->next->size=tmpnum;

				tmpnum=cur->count;
				cur->count=cur->next->count;
				cur->next->count=tmpnum;

				unsorted=true;
			}
		cur=cur->next;
		}
	}
	ofstream myfile;
        myfile.open ("dictionary.txt");
	WordSLLNode *tmp;
	myfile<<"Word->Count->id"<<endl;
	for(tmp=head;tmp!=0;tmp=tmp->next){
        
	myfile<<tmp->info<<" "<<tmp->count<<" "<<tmp->id<<endl;

	}
	myfile.close();
}
*/

void WordSLList::add_id(){
	int count=1;
	WordSLLNode *tmp;
	for(tmp=head;tmp!=0;tmp=tmp->next){
		tmp->id=count;
		
		count+=1;
	}
	bool unsorted=true;
	int tmpnum;
	string word;
	while(unsorted){
		unsorted=false;
		WordSLLNode *cur=head;
		while(cur->next!=0){
			if(cur->size<cur->next->size){
				word=cur->info;
				cur->info=cur->next->info;
				cur->next->info=word;				

				tmpnum=cur->size;
				cur->size=cur->next->size;
				cur->next->size=tmpnum;

				tmpnum=cur->count;
				cur->count=cur->next->count;
				cur->next->count=tmpnum;

				unsorted=true;
			}
		cur=cur->next;
		}
	}
}

void WordSLList::compressor(){
	add_id();
	int count;
	char c;
	string temp="";
	ifstream inFile("input.txt");
	ofstream myfile;
    myfile.open ("compressor.txt");
	if(!inFile){
		cout<<"Unable to open file!";
		
	}
	 inFile.get(c);
		count=0;
	while (!inFile.eof()){
		count++;
		 if((c>95 && c<123) || (c>64 && c<91) || (c>31 && c<64)) {
			temp+=c;
		 }else{
			if(temp!=""){
			WordSLLNode *tmp;
			
		for(tmp=head;temp!=tmp->info;tmp=tmp->next);
        		if(count%7000==0){
				myfile<<tmp->id<<endl;
			}else {
			myfile<<tmp->id<<" ";
			}
			temp="";
			}
	 	}       
	 inFile.get(c);	
	}
	inFile.close();
	myfile.close();			
}
void WordSLList::decompressor(){
	int b;
	int count=1;
	WordSLLNode *tmp;
	ifstream inFile("compressor.txt");
	ofstream myfile;
        myfile.open ("decompressor.txt");
	if(!inFile){
		cout<<"Unable to open file!";
	}
	 inFile>>b;
	while (!inFile.eof()){
		for(tmp=head;tmp->id!=b;tmp=tmp->next);
			if(count%30000==0){
		myfile<<tmp->info<<" "<<endl;
			}else {
				myfile<<tmp->info<<" ";
	 		 }
	 inFile>>b;
		count+=1;
	}
	inFile.close();
	myfile.close();
	
}
/*void LowerCase(string &s)
{
    int dif='a'-'A';
    for(int i=0;i<s.length();i++)
    {
        if((s[i]>='A')&&(s[i]<='Z'))
            s[i]+=dif;
    }
}
*/

/*void WordSLList::n_count(int n){
	int max,min,j;
	int maxcount[n]; int mincount[n]; string min_info[n]; string max_info[n];
	WordSLLNode *tmp;
	string maxword,minword;
	max=0;
	min=head->count;
	for(tmp=head;tmp!=0;tmp=tmp->next){
		if(tmp->count > max){
			max=tmp->count;
			maxword=tmp->info;
		}if(tmp->count < min){
			min=tmp->count;
			minword=tmp->info;
		}
	}
	max_info[0]=maxword; min_info[0]=minword; maxcount[0]=max; mincount[0]=min;
	int i=1;
	while(i<n){
		max=0; min=head->count;
		for(tmp=head;tmp!=0;tmp=tmp->next){
			if((tmp->count > max-1) && (tmp->count < maxcount[i-1]+1)){
				for(j=0;j<i && tmp->info!=max_info[j];j++);
					if(tmp->info!=max_info[j]){				
					   max=tmp->count; maxword=tmp->info;
					}				
			}if((tmp->count < min +1) && (tmp->count > mincount[i-1]-1)){
				for(j=0;j<i && tmp->info!=min_info[j];j++);
					if(tmp->info!=min_info[j]){				
					   min=tmp->count; minword=tmp->info;
					}
				
			}
		}
		max_info[i]=maxword; min_info[i]=minword; maxcount[i]=max; mincount[i]=min;
		i++;
	}
	cout<<"Most Used Words;"<<endl;
	for(i=0;i<n;i++){
		cout<<i+1<<". "<<max_info[i]<<" is used "<<maxcount[i]<<" time(s)"<<endl;	
	}
	cout<<"Least Used Words;"<<endl;
	for(i=0;i<n;i++){
		cout<<i+1<<". "<<min_info[i]<<" is used "<<mincount[i]<<" time(s)"<<endl;
	}
}
*/

int main(){
	clock_t start;
   	double duration;
	WordSLList *myList=new WordSLList();
	start=clock();
	readFileIntoLL(myList);
	myList->add_id();
	duration = ( clock() - start ) / (double) CLOCKS_PER_SEC; 
			cout<<"Text is compiled in "<<duration<<" seconds."<<endl;
	int choice=0;
	string word;
	cout<<"1.Compressor\n2.Decompressor\n"<<"Select a Choice :";
	cin>>choice;
	while(choice!=3){
		 if(choice==1){
			start = clock();
			myList->compressor();	
			duration = ( clock() - start ) / (double) CLOCKS_PER_SEC; 		
			cout<<"Text is compressed in "<<duration<<" seconds."<<endl;
		}else if(choice==2){
			start = clock();
			myList->decompressor();
			duration = ( clock() - start ) / (double) CLOCKS_PER_SEC; 
			cout<<"Text is decompressed in "<<duration<<" seconds."<<endl;
		}
	cout<<"1.Compressor\n2.Decompressor\n"<<"Select a Choice :";
	cin>>choice;
	}

}


