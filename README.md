#ARMSim Calculator

high_level.cpp represents the high level program. It is the logical version of the ARM program in a high level language (C++). The program has been kept modular with proper functions defined at places of need.

Describing high_level.cpp

	Functions:
		void DRAW_INT(int x);	 => Draws the specified integer x on the LCD screen
		void lightLeftLed();  	 => Turns on the left LED representing that the variable recalled is undefined
		void lightRightLed(); 	 => Turns on the right LED representing that the evaluation of the expression has led to an Overflow
		void bcdToBinary();		 => Converts a binary coded decimal number to a binary number (not needed in the high level program)
		void SWIBlackButton();	 => Checks if any of the black buttons is pressed
		void SWIBlueButton();	 => Checks if any of the blue buttons is pressed
		void SETSEG8 (int p);	 => Light up 7 segment display and display the integer in p
		void clearLCD(); 		 => Clear the LCD Screen
		void clearLineLCD(); 	 => Clear one line on LCD Screen

		int add(int x,int y);	 => add two 32 bit integers
		int sub(int x,int y);	 => subtracts two 32 bit integers
		int mult(int x,int y);	 => multiply two 32 bit integers
		int divi(int x,int y);	 => divide two 32 bit integers

		int number(int& s,string expr) => extracts the number from the string expression
		int unary(int& s, string expr) => checks for unary operators after getting the number 
		int mulDiv(int& s,string expr) => checks for multiplication and division after applying all unary operators in the current strings. This function calls the unary function beforing doing the mul div evaluations
		int evaluate(string expr)      => Does the remaining evaluation of additions and subtractions. This function calls the mulDiv function beforing doing the remaining evaluations

	Main:
		The program at every stage prints the current state of the variables in the calculator and the instructions that a user can use to give input to the calculator. The input is taken in form of a character. The corresponding ARM equivalent is indicated at each important line in the program using comments in c++. The program is kept modular so as to implement the equivalent program in ARM with ease. The logical part of the various functions used is mentioned above in the functions section. The various variables used are mentioned as follows: 

		blackButton -> Indicates the alue of the black buttons pressed
		v[0]-v[9]   -> the 10 variables available to calculator user
		expr (STACK IN ARM)-> Expression to be evaluated == this in ARM will be added or stored in the stack
		

		The remaining recursive functions can be easily written in arm.


#Developer
	Prakhar Agrawal
	Contact: prakhar0409@gmail.com
	IIT Delhi, India