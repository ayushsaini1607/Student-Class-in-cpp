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
    public:
       Student()
        {
          name[0]='\0';
          age=0;
          gender='\0';
          PRN[0]='\0';
        } 
       void getStudentDetails();             //user Input
       void displayStudentDetails() const;                  //display details
       ~Student(){}
};

class Marks: public Student
{
   protected:
       int ut_marks[5];                   
       bool validateMarks() const;         //checks if the user has entered marks in right format in the range 0 to 100
   public:
      Marks()
       {
          int i;
          for(i=0;i<5;i++)
            ut_marks[i]=0;
       }
      void getMarks();
      void displayMarks() const;
      ~Marks(){}
};

class Sports: public Student
{
   protected:
      int sp_marks;
      bool validateMarks() const;
   public:
      Sports()
        {
           sp_marks=0;
        }
      void getSports();
      void displaySports() const;
      ~Sports(){}
};

class Result: public Marks, public Sports
{
     float total;
     float perc;
     char ut_grade;                       //p or f for pass or fail
     char sp_grade;
     void checkSubjectFail();              
     public:
         Result()
         {
            total=0;
            perc=0;
            ut_grade='\0';
            sp_grade='\0';
         }
         void calcPerc();            //calculates percentage and returns pass or fail on the basis of percentage
         void calcSportsGrade();
         void displayResult() const;
         ~Result(){}
};

void Student::displayStudentDetails() const
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
    do
    {
       cin>>age;
       if(age<0)
          cout<<"\nInvalid age!Enter again: ";
    }while(age<0);
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
          if(ut_marks[i]<0 || ut_marks[i]>100)
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
       cin>>ut_marks[i];
    while(!validateMarks())            //if both are true then only calculate percentage else take input again
       {
           for(i=0;i<5;i++)
              cin>>ut_marks[i];
       }
}

void Marks::displayMarks() const
{
    cout<<"\nMarks in five subjects(out of 100) : ";
    for(int i=0;i<5;i++)
       cout<<ut_marks[i]<<"\t";
}

void Sports::getSports()
{
   cout<<"\nEnter marks in Sports(out of 100) : ";
   cin>>sp_marks;
   while(!validateMarks())
    {
       cin>>sp_marks;
    }
}

void Sports::displaySports() const
{
   cout<<"\nMarks in Sports : "<<sp_marks;
}

bool Sports::validateMarks() const
{
   if(sp_marks<0 || sp_marks>100)
     {
        cout<<"\nInvalid Marks entered!\nEnter marks again";
        return false;
     }
   return true;
}

void Result::displayResult() const
{
    Marks::displayStudentDetails();
    displayMarks();
    displaySports();
    cout<<"\nTotal : "<<total<<" / 500";
    cout<<"\nPercentage : "<<perc;
    cout<<"\nUnit Test Grade : "<<ut_grade;
    cout<<"\nSports Grade : "<<sp_grade;
    if(ut_grade=='F' || sp_grade=='F')
       cout<<"\nFinal Result : Fail";
    else
       cout<<"\nFinal Result : Pass";
}

void Result::calcPerc()
{
    for(int i=0;i<5;i++)
       total+=ut_marks[i];
    perc=(total*100.0)/500;                 //percentage = (total*100)/500 for 5 subjects
    if(perc>=90)
       ut_grade = 'A';
    else if(perc>=80 && perc<90)
       ut_grade = 'B';
    else if(perc>=65 && perc<80)
       ut_grade = 'C';
    else if(perc>=45 && perc<65)
       ut_grade = 'D';
    else if(perc>=33 && perc<45)
       ut_grade = 'E';
    else if(perc<33)
       ut_grade = 'F';
   checkSubjectFail();  
}

void Result :: checkSubjectFail()
{
   for(int i=0;i<5;i++)
     {
        if(ut_marks[i]<33) 
           {
              cout<<"\nFailed in subject "<<i+1;
              ut_grade='F';
           }
     }
}

void Result::calcSportsGrade()
{
   if(sp_marks>=90)
       sp_grade = 'A';
    else if(sp_marks>=80 && sp_marks<90)
       sp_grade = 'B';
    else if(sp_marks>=65 && sp_marks<80)
       sp_grade = 'C';
    else if(sp_marks>=45 && sp_marks<65)
       sp_grade = 'D';
    else if(sp_marks>=33 && sp_marks<45)
       sp_grade = 'E';
    else if(sp_marks<33)
       sp_grade = 'F';
}

int main()
{
    int n,i;
   //  cout<<"\nSize of result : "<<sizeof(Result);
   //  cout<<"\nSize of student : "<<sizeof(Student);
   //  cout<<"\nSize of marks: "<<sizeof(Marks);
   //  cout<<"\nSize of sports : "<<sizeof(Sports);
    cout<<"\nEnter no of students : ";
    cin>>n;
    Result R[n];
    for(i=0;i<n;i++)
      {
        cout<<"\nEnter details of Student "<<i+1;
        R[i].Marks::getStudentDetails();
        R[i].getMarks();
        R[i].getSports();
      }
    for(i=0;i<n;i++)
      {
        R[i].calcPerc();
        R[i].calcSportsGrade();
      }
    cout<<"\nDetails accepted!";
    cout<<"\n\n\n\nDisplaying details...";
    for(i=0;i<n;i++)
      {
        cout<<"\n\n\nDetails of Student "<<i+1;
        R[i].displayResult();
      }
    return 0;
}
