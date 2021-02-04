#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace std;

class Student{
       int marks[5];
       char name[20];
       char PRN[12];            //no arithmetic operation to be performed, so string as data type
       float perc;
       char grade;              //p or f for pass or fail
       bool validateMarks();     //checks if the user has entered marks in right format in the range 0 to 100
       bool validatePRN();        //checks if the user has entered PRN in right format (12 digits)
    public: 
      void getInput();             //user Input
      void display();             //display details
      char calcPerc();            //calculates percentage and returns pass or fail on the basis of percentage
      void checkSubjectFail();
};

void Student :: checkSubjectFail()
{
   for(int i=0;i<5;i++)
     {
        if(marks[i]<33) 
           {
              cout<<"\nFailed in subject "<<i+1;
              grade='F';
           }
     }
}

bool Student::validatePRN()
{
    int len=strlen(PRN);
    if(len!=11)
      {
          cout<<"\nInvalid PRN!\nEnter PRN again: ";
          return false;
      }
    for(int i=0;i<len;i++)
      {
          if(PRN[i]<48 || PRN[i]>57)             //ascii value for digits
            {
                cout<<"\nInvalid PRN!\nEnter PRN again: ";
                return false;
            }
      }
    return true;
}

bool Student::validateMarks()
{
    for(int i=0;i<5;i++)
          if(marks[i]<0 || marks[i]>100)
            {
                cout<<"\nInvalid marks entered!\nEnter marks again: ";
                return false;
            }
    return true;
}

void Student::getInput()
{
    int i;
    cout<<"\nEnter name : ";
    fflush(stdin);
    gets(name);
    cout<<"\nEnter PRN (11digits) : ";
    fflush(stdin);
    gets(PRN);
    while(!validatePRN())
      {
          fflush(stdin);
          gets(PRN);
      }
    cout<<"\nEnter marks in five subjects(out of 100) : ";
    for(i=0;i<5;i++)
       cin>>marks[i];
    while(!validateMarks())            //if both are true then only calculate percentage else take input again
       {
           for(i=0;i<5;i++)
              cin>>marks[i];
       }
    
    grade=calcPerc();
    checkSubjectFail();
}

void Student::display()
{
    cout<<"\nName: "<<name;
    cout<<"\nPRN : "<<PRN;
    cout<<"\nMarks in five subjects(out of 100) : ";
    for(int i=0;i<5;i++)
       cout<<marks[i]<<"\t";
    if(grade=='F')
    {
       cout<<"\nPercentage : not calculated";
       cout<<"\nGrade : "<<grade<<"\nFinal Result : Fail";
    }
    else
     {
       cout<<"\nPercentage : "<<perc;
       cout<<"\nGrade : "<<grade<<"\nFinal Result : Pass";
     }
}

char Student::calcPerc()
{
    int total=0;
    for(int i=0;i<5;i++)
       total+=marks[i];
    perc=(total*100.0)/500;                 //percentage = (total*100)/500 for 5 subjects
    if(perc>=90)
       return 'A';
    else if(perc>=80 && perc<90)
       return 'B';
    else if(perc>=65 && perc<80)
       return 'C';
    else if(perc>=45 && perc<65)
       return 'D';
    else if(perc>=33 && perc<45)
       return 'E';
    else if(perc<33)
       return 'F';
}

int main()
{
    unsigned int n,i;
    cout<<"\nEnter no of students: ";
    cin>>n;
    Student S[n];
    for(i=0;i<n;i++)
      {
        cout<<"\nEnter details of Student "<<i+1;
        S[i].getInput();
      }
    cout<<"\nDetails accepted!";
    cout<<"\n\n\n\nDisplaying details...";
    for(i=0;i<n;i++)
      {
        cout<<"\n\n\nDetails of Student "<<i+1;
        S[i].display();
      }
    return 0;
}
