#include <bits/stdc++.h>
#include <iostream>
#include <string.h>

using namespace std;

void DRAW_INT(int x);
void lightLeftLed();
void bcdToBinary();
void SWIBlackButtonCheck();
void SWIBlueButtonCheck();

int add(int x,int y){
	return x+y;
}

int sub(int x,int y){
	return x-y;
}
int mul(int x,int y){
	return x*y;
}
int divi(int x,int y){
	return x/y;
}

int number(int& s,string expr){
	int res=expr[s++]-'0';

	while(expr[s]>='0' && expr[s]<='9'){
		res=res*10 + (int)(expr[s++]-'0');
	
	}
	
	return res;
}

int factor(int& s, string expr){
	if(expr[s]>='0' && expr[s]<='9'){
	
		int tmp=number(s,expr);
		//cout<<"herherhehrehrehreherh with tmp::"<<tmp<<endl;
		return tmp;
	}else if(expr[s]=='-'){
		s++;
		return -factor(s,expr);
	}else if(expr[s]=='+'){
		s++;
		return factor(s,expr);
	}
}

int term(int& s,string expr){
	int res=factor(s,expr);
	while(expr[s]=='*' || expr[s]=='/'){
		if(expr[s++]=='*'){
			int tt=factor(s,expr);
			res=mul(res,tt);
			//res*=factor(s,expr);
		}else{
			int tt=factor(s,expr);
			res=divi(res,tt);
			//res/=factor(s,expr);
		}
	}
	return res;
}

int evaluate(string expr){
	int s=0;
	int res=term(s,expr);	//result upto all multiplications and divisions done

	while(expr[s]=='+' || expr[s]=='-'){
		
		if(expr[s++]=='+'){
			int tt=term(s,expr);
			res=add(res,tt);
			//res+=term(s,expr);
		}else{
			int tt=term(s,expr);
			res=divi(res,tt);
			//res-=term(s,expr);
		}

	}
	return res;
}


int main(){
	int blackButton=0;			//stores the value of left button
	int v[10]={0};				//the 10 variables to be stored in memory in ARM
	bool def[10]={false};		//the booleans telling if the variable has been preassigned
	string expr="";				//String storing the expression
	
repeat:							//label to cause infinite loop


	cout<<"****************************PRINTING THE CURRENT STATE LIKE ON THE LCD*********************************"<<endl;
	//cout<<"Current State"<<endl;
	cout<<"Black Button: "<<blackButton<<endl;
	for(int i=0;i<10;i++){
		cout<<"v["<<i<<"]="<<v[i]<<" ";
	}
	cout<<endl;
	cout<<"Expression: "<<expr<<endl;
	cout<<endl;


	cout<<"You have the following options."<<endl;
	cout<<"Press 'A' for left and 'D' for right black button"<<endl;
	cout<<"Press 0-9 to enter a digit"<<endl;
	cout<<"Press E for assign and R for recall"<<endl;


	int res=0;		  			//stores evaluated result
	char c;						//character that stores input
	cin>>c;
	if(c=='B'){			//checks if blackbutton is pressed
	SWIBlackButtonCheck();		
	/*
	*	SWITCH BASED ON R0 to increment or decrement alue of black Button
	*
	*/
		
	}
	if(c=='N'){		//checks for the blue button press
	SWIBlueButtonCheck();
	/*
	*	SWITCH BASED ON R0 to any of the cases of + - * / or digits [0-9]
	*
	*/
	}
	//function that converts one hot encoding to decimal or binary form and then the switch case occurs
	bcdToBinary();
	cout<<endl;	
	//applying switch case to the converted character or digit
	switch(c){
		case 'A': case 'a':
				blackButton--;blackButton=(blackButton+10)%10;
			break;
		case 'D': case 'd':
			blackButton++;blackButton=blackButton%10;
			break;
		case '0' ... '9':
			//Now c is in BCD form digit and probably last expression as well
			expr+=c;
			//v[blackButton]=v[blackButton]*10+(int)c-48;
			break;
		case '+':
			expr+="+";
			break;
		case '-':
			expr+="-";
			break;
		case '*':
			expr+="*";
			break;
		case '/':
			expr+="/";
			break;
		case 'E': case 'e':		//evaluate
			
			//cout<<"expt before evaluate::"<<expr<<endl;
			res=evaluate(expr);
			//cout<<"tlllll::"<<tll<<endl;
			//v[blackButton]=atoi(num.c_str());//,nullptr,10);
			v[blackButton]=res;
			expr="";
			num="";
			break;
		case 'R': case 'r':		//recall
			if(def[blackButton]==false){
				//Light LED

				cout<<"Undefined value called: Light left LED"<<endl;
				lightLeftLed();
			}
			char tmp[21];
			sprintf(tmp,"%d",v[blackButton]);
			expr=expr+tmp;
			break;

	default:
			cout<<"bye"<<endl;
	}

	cout<<endl;
	goto repeat;
}