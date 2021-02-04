#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace std;

class Student{
    protected:
       char name[20];
       int age;
       char gender;
       char PRN[12];            //no arithmetic operation to be performed, so string as data type               
       bool validatePRN() const;        //checks if the user has entered PRN in right format (11 digits)
       bool validateGender() const;
       bool validateAge() const;
    public:
       Student()
        {
          name[0]='\0';
          age=0;
          gender='\0';
          PRN[0]='\0';
        } 
       void getStudentDetails();             //user Input
       void display() const;                  //display details
       ~Student(){}
};

class Marks: public Student
{
   protected:
       int marks[5];                   
       bool validateMarks() const;         //checks if the user has entered marks in right format in the range 0 to 100
   public:
      Marks()
       {
          int i;
          for(i=0;i<5;i++)
            marks[i]=0;
       }
      void getMarks();
      void display() const;
      ~Marks(){}
};

class Result: public Marks
{
     float perc;
     char grade;                       //p or f for pass or fail
     void checkSubjectFail();               
     public:
         Result()
         {
            perc=0;
            grade='\0';
         }
         void calcPerc();            //calculates percentage and returns pass or fail on the basis of percentage
         void display() const;
         void displayFailSubject() const;
         ~Result(){}
};

void Student::display() const
{
    cout<<"\nName: "<<name;
    cout<<"\nPRN : "<<PRN;
}

bool Student::validatePRN() const
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

bool Student::validateGender() const
{
   return gender=='M'|| gender=='F' ? true : false;
}

bool Student::validateAge() const
{
   return age>0 ? true : false;
}

void Student::getStudentDetails()
{
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
    cout<<"\nEnter age: ";
    cin>>age;
    while(!validateAge())
      {
         cout<<"\nInvalid Age!Enter again: ";
         cin>>age;
      }
    cout<<"\nEnter gender(M or F): ";
    cin>>gender;
    while(!validateGender())
      {
         cout<<"\nInvalid gender! Enter 'M' or 'F' : ";
         cin>>gender;
      }
}

bool Marks::validateMarks() const
{
    for(int i=0;i<5;i++)
          if(marks[i]<0 || marks[i]>100)
            {
                cout<<"\nInvalid marks entered!\nEnter marks again: ";
                return false;
            }
    return true;
}

void Marks::getMarks()
{
    int i;
    cout<<"\nEnter marks in five subjects(out of 100) : ";
    for(i=0;i<5;i++)
       cin>>marks[i];
    while(!validateMarks())            //if both are true then only calculate percentage else take input again
       {
           for(i=0;i<5;i++)
              cin>>marks[i];
       }
}

void Marks::display() const
{
    cout<<"\nMarks in five subjects(out of 100) : ";
    for(int i=0;i<5;i++)
       cout<<marks[i]<<"\t";
}

void Result::display() const
{
    Student::display();
    Marks::display();
    cout<<"\nPercentage : "<<perc;
    displayFailSubject();
    if(grade=='F')
       cout<<"\nGrade : "<<grade<<"\nFinal Result : Fail";
    else
       cout<<"\nGrade : "<<grade<<"\nFinal Result : Pass";
}

void Result::calcPerc()
{
    int total=0;
    for(int i=0;i<5;i++)
       total+=marks[i];
    perc=(total*100.0)/500;                 //percentage = (total*100)/500 for 5 subjects
    if(perc>=90)
       grade = 'A';
    else if(perc>=80 && perc<90)
       grade = 'B';
    else if(perc>=65 && perc<80)
       grade = 'C';
    else if(perc>=45 && perc<65)
       grade = 'D';
    else if(perc>=33 && perc<45)
       grade = 'E';
    else if(perc<33)
       grade = 'F';
    checkSubjectFail();
}

void Result :: checkSubjectFail()
{
   for(int i=0;i<5;i++)
      if(marks[i]<33) 
         grade='F';
}

void Result::displayFailSubject() const
{
   for(int i=0;i<5;i++)
      if(marks[i]<33)
         cout<<"\nFailed in subject"<<i+1;
}

int main()
{
    int n,i;
    cout<<"\nEnter no of students : ";
    cin>>n;
    Result R[n];
    for(i=0;i<n;i++)
      {
        cout<<"\nEnter details of Student "<<i+1;
        R[i].getStudentDetails();
        R[i].getMarks();
      }
    cout<<"\nDetails accepted!";
    cout<<"\n\n\n\nDisplaying details...";
    for(i=0;i<n;i++)
      {
        R[i].calcPerc();
        cout<<"\n\n\nDetails of Student "<<i+1;
        R[i].display();
      }
    return 0;
}
