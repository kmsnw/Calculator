#include <iostream>
#include <string>
#include <stack>

using namespace std;

double calculate(char op, double num1, double num2);
bool check(string str);

int main()
{
	cout<<"[사칙연산 계산기 프로그램]"<<endl;
	cout<<"-입력 조건: 사칙연산자로 이뤄진 연산식(|괄호X|합:+|차:-|곱:*|몫:/|)"<<endl;
	cout<<"-프로그램 종료: 0"<<endl; 
	cout<<">"<<endl;
	
	while(1)
	{
		string a;
		cout<<"입력: "; cin>>a;
		
		if(a=="0")
		{
			cout<<"프로그램을 종료합니다."<<endl;
			return 0;
		}
		
		if(!check(a)) //잘못된 문자열 입력시
		{
			cout<<"잘못된 입력."<<endl;
			cout<<">"<<endl;
			continue;
		}
		
		stack<double> operands;
		stack<char> operators;
	
	
		for(int i=0;i<a.length();i++)
		{
			if(isdigit(a[i])) //숫자일 때, 피연산자 스택에 push
			{
				int j=i;
				while(isdigit(a[j]))
				{
					j++;
					if(a[j]=='.')
					{
						j++;
					}
				}
				double oprnd = stod(a.substr(i, j-i));
				operands.push(oprnd); 
				i=j;
			}
		
			if(a[i]=='+' || a[i]=='-' || a[i]=='*' || a[i]=='/')//연산자일 때
			{
				char op = a[i];
				
				while(!operators.empty() && (operators.top()=='*' || operators.top()=='/') && (a[i] == '+' || a[i] == '-')) // +,- push 과정에서, top이 *,/일 때 미리 연산한 뒤 push
				{
					char oprtr = operators.top();
					operators.pop();
					double y= operands.top();
					operands.pop();
					double x = operands.top();
					operands.pop();
					double result = calculate(oprtr, x, y);
					operands.push(result);
				}
				
				operators.push(op); // 별다른 문제 없을시 바로 연산자 push
			}

		}
		
		while(!operators.empty()) // 스택에 있는 연산자 사용해서 연산 마무리
		{
			
			char c = operators.top();
			operators.pop();
			double y = operands.top();
			operands.pop();
			double x = operands.top();
			operands.pop();
			double result = calculate(c, x, y);
			operands.push(result);
			 
			
			
		}
		
		cout<<"결과: "<<operands.top()<<endl;
		cout<<">"<<endl;
	}
	return 0;
}

bool check(string str)
{
	bool istrue=false;
	int dotcount=0;
	
	
	for(int i=0; i<str.length(); i++)
	{
		if(isdigit(str[i]))
			istrue = true;
		else if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/' || str[i]=='.')
		{

			if(i==0 || i==str.length()-1)
				istrue = false;
			else if(str[i-1]=='+' || str[i-1]=='-' || str[i-1]=='*' || str[i-1]=='/' || str[i-1]=='.')
				istrue = false;
			else
			{
				istrue = true;
				if(str[i]=='.')
				{
					dotcount++;
				}
			}
			
		}
		else
			istrue = false;
		
		if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/' || i==str.length()-1)
		{
			if(dotcount>1)
				istrue = false;
			else
				dotcount = 0;
		}
		
		if(!istrue)
		{
			return istrue;
		}
	}
	return istrue;
}


double calculate(char op, double num1, double num2)
{
	switch(op)
	{
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '*':
			return num1 * num2;
		case '/':
			return num1 / num2;
		default:
			return 0;
	}
}