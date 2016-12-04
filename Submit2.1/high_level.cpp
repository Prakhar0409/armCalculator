#include <bits/stdc++.h>
#include <iostream>
#include <string.h>

using namespace std;

void DRAW_INT(int x){}			//Draws integer on the LCD screen
void lightLeftLed(){			//Light the left LED on
	cout<<"Undefined variable: LEFT LED ON"<<endl<<endl;
}
void lightRightLed(){			//Light the left LED on
	cout<<"Overflow: RIGHT LED ON"<<endl<<endl;
}
void bcdToBinary(){}			//conver bcd to Binary;
void SWIBlackButtonCheck(){}	//Check if Black Buttons are pressed
void SWIBlueButtonCheck(){}		//Check if Blue Buttons are pressed
void SETSEG8 (int p){}			//Light up 7 segment display
void clearLCD(){}				//clear the LCD screen
void clearLineLCD(){}			//clear a single line on the LCD

int add(int x,int y){			//adds two 32 bit numbers
	long long ans=(long long)x+(long long)y;
	if(ans<INT_MIN || ans>INT_MAX){
		lightRightLed();		//overflow===In arm check the flags for these
	}
	return x+y;
}

int sub(int x,int y){			//subtracts two 32 bit numbers
	long long ans=(long long)x-(long long)y;;
	if(ans<INT_MIN || ans>INT_MAX){	
		lightRightLed();		//Overflow -- never occurs in subtract
	}
	return x-y;
}
int mul(int x,int y){			//multiplies two 32 bit numbers
	long long ans=(long long)x*(long long)y;;
	if(ans<INT_MIN || ans>INT_MAX){		
		lightRightLed();		//overflow===In arm check the flags for these
	}
	return x*y;
}
int divi(int x,int y){			//divides  two 32 bit numbers
	long long ans=(long long)x/(long long)y;;
	if(ans<INT_MIN || ans>INT_MAX){
		lightRightLed();		//Overflow
	}
	return x/y;
}

int number(int& s,string expr){		//extracts the number from the string expression
	long long res=expr[s++]-'0';
	while(expr[s]>='0' && expr[s]<='9'){
		res=res*10 + (int)(expr[s++]-'0');
	}
	if(res<INT_MIN || res>INT_MAX){
		lightRightLed();			//checks for overflow
	}
	int result=(int)res;
	return result;
}

int unary(int& s, string expr){	//checks for unary operators after getting the number 
	if(expr[s]>='0' && expr[s]<='9'){
		int tmp=number(s,expr);
		return tmp;
	}else if(expr[s]=='-'){
		s++;
		return -unary(s,expr);
	}else if(expr[s]=='+'){
		s++;
		return unary(s,expr);
	}
}

int mulDiv(int& s,string expr){	//checks for multiplication and division after applying all unary operators in the current strings
	int res=unary(s,expr);	
	while(expr[s]=='*' || expr[s]=='/'){
		if(expr[s++]=='*'){
			int tt=unary(s,expr);
			res=mul(res,tt);
			//res*=unary(s,expr);
		}else{
			int tt=unary(s,expr);
			res=divi(res,tt);
			//res/=unary(s,expr);
		}
	}
	return res;
}

int evaluate(string expr){
	int s=0;
	int res=mulDiv(s,expr);	//result upto all multiplications/divisions and unary operators done

	while(expr[s]=='+' || expr[s]=='-'){
		if(expr[s++]=='+'){
			int tt=mulDiv(s,expr);
			res=add(res,tt);
		}else{
			int tt=mulDiv(s,expr);
			res=divi(res,tt);
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
	clearLCD();
	cout<<"****************************PRINTING THE CURRENT STATE LIKE ON THE LCD*********************************"<<endl;
	cout<<"Black Button: "<<blackButton<<endl;
	for(int i=0;i<10;i++){
		if(def[i]==true){
			cout<<"v["<<i<<"]="<<v[i]<<" ";
		}else{
			cout<<"v["<<i<<"]="<<"u"<<" ";
		}
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
	if(c=='A' || c=='a' || c=='D' || c=='d'){			
	SWIBlackButtonCheck();		//checks if blackbutton is pressed
	/*
	*	SWITCH BASED ON R0 to increment or decrement alue of black Button
	*
	*/
	switch(c){
		case 'A': case 'a':
				blackButton--;blackButton=(blackButton+10)%10;
			break;
		case 'D': case 'd':
			blackButton++;blackButton=blackButton%10;
			break;
		default:	
			cout<<"Die in if 1";
		}

		SETSEG8 (blackButton);	//display on the 7 segment display
	}
	else{						//checks for the blue button press
	SWIBlueButtonCheck();
	/*
	*	SWITCH BASED ON R0 (one hot encoding) to any of the cases of + - * / or digits [0-9]
	*
	*/
		switch(c){
		case '0' ... '9':
			expr+=c;
			DRAW_INT((int)(c-'0'));
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
			res=evaluate(expr);	
			v[blackButton]=res;
			def[blackButton]=true;
			expr="";
			//clearLineLCD();
			break;
		case 'R': case 'r':		//recall
			if(def[blackButton]==false){
				//Light LEFT LED
				lightLeftLed();
				goto repeat;
			}
			char tmp[21];
			sprintf(tmp,"%d",v[blackButton]);
			expr=expr+tmp;
			break;

		default:
			cout<<"DIE in blue buttons"<<endl;
		}

	}
	
	cout<<endl;	
	cout<<endl;
	goto repeat;
}