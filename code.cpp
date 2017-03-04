#include<fstream>
#include<iostream>
#include <string>
#include<stdlib.h>
#include <stdio.h>
#include<string.h>
 
using namespace std;
size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2)
 {
     const size_t m(s1.size());
     const size_t n(s2.size());
     if( m==0 ) return n;
     if( n==0 ) return m;
     size_t *costs = new size_t[n + 1];
     for( size_t k=0; k<=n; k++ ) costs[k] = k;
     size_t i = 0;
         for ( std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i )
         {
          costs[0] = i+1;
          size_t corner = i;
          size_t j = 0;
             
			 for ( std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j )
              {
               size_t upper = costs[j+1];
               if( *it1 == *it2 )
               {
		        costs[j+1] = corner;
	           }
                else
	            {
		         size_t t(upper<corner?upper:corner);
                costs[j+1] = (costs[j]<t?costs[j]:t)+1;
	            }
 
                corner = upper;
              }
         }
 
      size_t result = costs[n];
      delete [] costs;
 
      return result;
 }
int search(const std::string &userin)
{
       int match=0;
       std::string meaning;

	   	std::string word;

	   ifstream fin("wordmeanings.txt");

		
            while (!fin.eof())
	        {
           
             fin>> word;
           
			getline(fin,meaning);
		
	

                if (word.compare(userin) == 0)

	           {	
	             match++;
			     cout << meaning << endl;
			     ifstream fin("record.txt");
			     std::string recordl;
			      getline(fin,recordl);
		          std::ofstream os("record.txt");  
			      if (!os) { std::cerr<<"Error writing to ..."<<std::endl; } else 
			     {  
			      os << word << " "<< recordl;  
			     } 
			    return (match);
			
	         break;
	         }  
	        }
		return (match);
}
void suggest (char userin[])

{
	     std::string meaning;
		char word[9999];
        ifstream fin("wordmeanings.txt");
		int min=999;
		int min2=999;
  		int min3=999;
     	string bm,bm2,bm3;
        while (!fin.eof())
    	{

           	fin >> word;
	   	
		    int dis= uiLevenshteinDistance(userin,word);
		    
           if (min3>=dis)
               {
               	if (min2>dis)
               	{
               		if(min>=dis)
               		{
               			
                         bm3=bm2;
                         bm2=bm;
               			 min3=min2;
               			 min2=min;
               			 min=dis;
               		     bm=word;
               			  }
               			  
               		 else
               		 
						{
				
                         bm3=bm2;
						min3=min2;
               			min2=dis;
               	        bm2=word;
               	    }
                     	   
               	}
               	else
               	 	{
               	 		min3=dis;
               	 
               	 		bm3=word;
              
               	 	
         	    
               } 
    	}
    }
    
    cout <<"did you mean " << " (1) " <<bm <<" (2) " <<bm2 << " (3) " <<bm3  <<endl <<"Enter number of your desire word " ;
      	int select;
	     cin >>select;
		if(select==1)
	      search(bm);
		if(select==2)
		search(bm2);
		if(select==3)
		search(bm3);
	
	}
int synonym(char userin[])
{
	int match=0;
std::string synonym;
std::string word;
ifstream fin("Synonymsshort.txt");
int min=999;		
while (!fin.eof())
{

	fin >> word;
			getline(fin,synonym);	
  if (word.compare(userin) == 0)

{	
	        match++;
			cout<<"Synonym: " << synonym << endl;
			break;	
			return (match);
}

}
return (match);
}	
void printrecord(void)	
{
	   	std::string word;

	   ifstream fin("record.txt");
	   int i=1;
	   while (i<=10 &&!fin.eof())
	        {
           
	   fin>> word;
	   cout <<i << " "<<word <<endl ;
	   i++;
}
}
int main()
{
	 char userin[99999];

	begin:
    int choice;
    cout <<endl <<"Enter your Choice "<<endl << "(1) To find meaning (2) To find record of last searchs (3) To End program  "<<endl ;
    cin >> choice;
    switch(choice)
    {
    case 1:
    goto mean;
    break;
    case 2:
      goto record;
      case 3:
      return 0;
   default:
   cout << "Enter a correct choice ";
   goto begin;
    }
  
 
    record:
    	printrecord();
    	
	goto begin;
     
    mean:
		int match=0;
		 cout <<endl << "Enter your word  "<< endl <<endl;
    scanf("%s",userin);
    if(userin[1]==0)
    {
    	return 0;
    }
    else
{
    if(userin[0]>96)
    userin[0]=   userin[0]-32;
	int i=search(userin);	
     if(i==0)
	suggest(userin);
	else 
	synonym(userin);
}
goto begin;
return 0;
}

