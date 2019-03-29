//emcc stu.c -s WASM=1 -O3 -s "EXPORTED_FUNCTIONS=['_main']" -o stu.js -o stu.html
//sample inputs : 1 1 101 lenin 98 95 74 2 101 1 1 102 kumar 67 45 76 2 101 2 102 3 2 102  
#include<stdio.h>
#include<string.h>
#include <emscripten.h>
int ns=0;
struct student
 { 
  	int rollno,tot;
  	char name[20],grade;
  	int mark[20][3];
  	float per;
 }s[20];

EMSCRIPTEN_KEEPALIVE int  valid(const char uname[20],const char pword[20])
{
   int x;
   if(strcmp(uname,"admin"))
   {
      if(strcmp(pword,"admin"))
      {
           x=1;
       }
   }
   else
  {
     x=0;
   }
  return x;
} 

EMSCRIPTEN_KEEPALIVE int  add(int rno,const char name[20],int m1,int m2,int m3)
{
 		s[ns].rollno=rno;
		strcpy(s[ns].name,name);		
		s[ns].tot = m1+m2+m3; 
		s[ns].per=s[ns].tot/3;
		if(s[ns].per<=100 && s[ns].per>90)
		{
			s[ns].grade='S';
		}
		else if(s[ns].per<90 && s[ns].per>80)
		{
			s[ns].grade='A';			
		}
		else  if(s[ns].per<=80 && s[ns].per>70)
		{
			s[ns].grade='B';
		}
		else if(s[ns].per<=70 && s[ns].per>60)
		{
			s[ns].grade='C';
		}
		else if(s[ns].per<=60 && s[ns].per>=50)
		{
			s[ns].grade='D';	
		}
		else
		{
			s[ns].grade='F';
		}		
	
	ns=ns+1;
	return ns;
   }
   EMSCRIPTEN_KEEPALIVE char view(int r)
   {
	int rno,i;
	rno= r;
	char res[1][20];
	res[0][0]=0;
	for(i=0;i<ns;i++)
	{
	   if(rno==s[i].rollno)
	  {
	  	/*printf("\tRollno : %d\n\tName : %s\n\tTotal Marks : %d\n\tPercentage:%.2f\n\tGrade : %c\n",s[i].rollno,s[i].name,s[i].tot,s[i].per,s[i].grade);*/
		res[0][0]=1;
		res[0][1]=s[i].rollno+'0';
		res[0][2]=s[i].name;
		res[0][3]=s[i].tot+'0';
		res[0][4]=s[i].grade+'0';
		
	   }  	
	}
	return res;
}
