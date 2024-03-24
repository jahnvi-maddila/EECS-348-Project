#include <iostream>
#include <conio.h>
#include <stack>
using namespace std;
int main() {
  int b1,b2,choice,output=0;
  string expression;
  bool val1, val2;
  cout << "Basic boolean calculator\n";
  cout<<"Enter a boolean expression with T for 1 and F for 0\n";
  cin>>expression;
  cout<<"\nEnter second boolean value: ";
  cin>>b2;
  cout<<"\nEnter 1 for and, 2 for or, 3 xor, 4 for not: ";
  cin>>choice;
  val1=(b1==1)? true : false;
  val2=(b2==1)? true : false;
  
  switch (choice)
  {
  case 1: output=val1&val2;
  break;
  
  case 2: output=val1|val2;
  break;

  case 3: output=(((!val1)&val2)|(val1&(!val2)));
  break;
  
  case 4:
    int c2;
    cout<<"\nDo you want first or second not?(1/2)";
    cin>>c2;
    if(c2==1){
      output=!val1;
    }
    else{
      output=!val2;
    }
  default: cout<<"\nWrong choice!";
    break;
  }

  char c1;
  c1=(output)? 'T' : 'F';
  cout<<"\nOutput for your choices is: "<<c1;

  return 0;
}