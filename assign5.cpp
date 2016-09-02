/******************************************************
** PROGRAM: assign5.cpp
** AUTHOR: Carlos Lopez Molina
** DATE: 2/28/16
** DESCRIPTION: TRANSLATE MORSE TO TEXT / TEXT TO MORSE
** INPUT: MORSE CODE OR TEXT
** Output: MORSE CODE OR TEXT
******************************************************/
#include <iostream>
#include <cstdlib> //CLEARS SCREEN

using namespace std;

/*********************************************************************
 ** FUNCTION: MORSE
 ** DESCRIPTION: TRANSLATE FROM TEXT TO MORSE CODE
 ** PARAMETERS: INPUT AND LENGTH
 ** PRE-CONDITIONS: USER MUST HAVE CHOSEN TO TRANSLATE TEXT TO MORSE
 ** POST-CONDITIONS: MORSE CODE PRINTED
 *********************************************************************/ 
void morse(char *input, int length){
	//Each Letter is assigned to the corresponding morse code [ROW]
	char upper[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char lower[27] = "abcdefghijklmnopqrstuvwxyz";
	char morse[26][5] = {{".-"},{"-..."},{"-.-."},{"-.."},{"."},{"..-."},{"--."},{"...."},{".."},{".---"},{"-.-"},{".-.."},{"--"},{"-."},{"---"},{".--."},{"--.-"},{".-."},{"..."},{"-"},{"..-"},{"...-"},{".--"},{"-..-"},{"-.--"},{"--.."}};
	
	//CHECKS TO SEE UPPER CASE AND LOWER CASE LETTERS
	char letter;
	int rows;
	for(int x = 0; x < length-1; x++){
		if(input[x] == ' '){
			cout << "       ";
		}	
		else if(input[x] != ' '){
			letter = input[x];
			for(int y = 0; y < 27; y++){
				if(upper[y] == letter || lower[y] == letter){
					rows = y; 
					y = 27;
				}
			}
			for(int w = 0; w < 5; w++){
				cout << morse[rows][w];
			}
			cout << "   ";
		}
	}	
	return;
}

/*********************************************************************
 ** FUNCTIONS: KEY
 ** DESCRIPTION: TRANSLATE TEXT TO MORSE [SUB FUNCTION]
 ** PARAMETERS: SUBINPUT, Y, AND SUBLENGTH
 ** PRE-CONDITIONS: MUST HAVE INPUTTED MORSE CODE INTO THE PREVIOUS FUNCTION
 ** POST-CONDITIONS: TEXT TRANSLATION PRINTED
 *********************************************************************/ 
void key(char *subinput, int &y, int sublength){
	bool translate;
	
	char morse[26][5] = {{".-"},{"-..."},{"-.-."},{"-.."},{"."},{"..-."},{"--."},{"...."},{".."},{".---"},{"-.-"},{".-.."},{"--"},{"-."},{"---"},{".--."},{"--.-"},{".-."},{"..."},{"-"},{"..-"},{"...-"},{".--"},{"-..-"},{"-.--"},{"--.."}};
	char upper[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	//BOOL IS TO CHECK IF EACH LETTER MATCHES WITH LETTER ON THE KEY
	//IF THE LETTER DOES NOT MATCH, IT WOULD BREAK FROM SECOND LOOP AND SET
	//TRANSLATE TO FALSE
	//IF THE TRANSLATE IS TRUE, THEN CORESPOND LETTER WILL PRINT
	for (int c = 0; c < 26; c++){
		for(int r = 0; r < sublength; r++){
			if (subinput[r] == morse[c][r]){
				translate = true;
			}
			else if (subinput[r] != morse[c][r]){
				translate = false;
				break;
			}
		}
		if (translate == true){
			cout << upper[c];
			if(y == 1){
				cout << " ";
			}
		}
	}

}

/*********************************************************************
 ** FUNCTIONS: WORD
 ** DESCRIPTION: TRANSLATE TE TO MORSE
 ** PARAMETERS: INPUT, X, N, SIZEOFINPUT
 ** PRE-CONDITIONS: MUST HAVE CHOSEN TO TRANSLATE TO TEXT
 ** POST-CONDITIONS: PRINTS OUT MORSE TRANSLATION
 *********************************************************************/ 
void word(char *input, int x, int n, int sizeofinput){
	char *subinput = NULL;
	int y;
	subinput = new char[5];
	
	for(n; n < sizeofinput; n++){
		if((input[n] == '.') || (input[n] == '-')){
			subinput[x] = input[n];
			x++;
		}
		else if(input[n] == ' '){
			subinput[x] = '\0';
			if (input[n+3] == ' '){
				y = 1;
				n = n + 7;
			}	
			else if (input[n+3] != ' '){
				y = 0;
				n = n + 3;
			}
			
			key(subinput,y,x+1);
			x = 0;
			delete []subinput;  //avoid memory leak
			word(input,x,n,sizeofinput);
			return;
			
		}
		else if(input[n] == '\0'){
			subinput[x] = '\0';
			y = 0;
			key(subinput,y,x+1);
			cout << endl;
			break;
			return;
		}
	}
}

/*********************************************************************
 ** FUNCTIONS: CHOICE
 ** DESCRIPTION: RECIEVES USER'S CHOICE TO TRANSLATE TEXT OR MORSE
 ** PARAMETERS: NONE
 ** PRE-CONDITIONS: NONE
 ** POST-CONDITIONS: TRANSLATE TO MORSE OR TRANSLATE TO TEXT
 *********************************************************************/ 
int choice(){
	int option;
	
	cout << " WELCOME TO THE CODE TRANSLATOR! " << endl;
	
	//ASK THE USER IF HE/SHE WANTS TO TRANSLATE TO MORSE OR TO TEXT
	cout << "Please enter your option: \n";
	cout << "(1) Translate TEXT to morse code \n";
	cout << "(2) Translate morse code to TEXT \n";
	cin >> option;
	cin.ignore();
	system("clear");
	
	return option;
}

/*********************************************************************
 ** FUNCTION: MAIN
 ** DESCRIPTION: HOLDS THE BACKBONE OF THE PROGRAM
 ** PARAMETERS: NONE
 ** Pre-Conditions: MUST HAVE TEXT OR MORSE CODE 
 ** Post-Conditions: MORSE CODE OR TEXT
 *********************************************************************/ 
int main(){
	int again;
	
	do{
		system("clear");
		char *input = NULL; //ask the user for the input
		int size = 1;// size of the array on the heap
		input = new char[size]; //array on the heap for user input
		int count = 0; 
		int option = choice();
		char input_char;
		
		//AFTER USER CHOOSES, THE USER IS ASKED TO INPUT TEXT
		if(option == 1){
			cout <<"Please enter word you would like to translate to morse code: \n";		
		}
		//AFTER USER, CHOOSES, THE USER IS ASKED TO INPUT MORSE CODE
		else if(option == 2){
			cout << "Please enter morse code: \n";
		}
		else if (option != 1,2){
			cout << "Invalid Option!" << endl;
			return 0;
		}
		
		//Get message
		//EACH CHARACTER WILL BE PUT IN ARRAY UNTILL REACHES '\n'
		while(cin.peek() != '\n'){
			input_char = cin.get();
			input[size-1] = input_char;
			count++;						
			char *temp = NULL;				//NEW TEMP ARRAY TO STORE CHARACTERS
			temp = new char[size+1];		//SIZE = COUNT + 1(NULL CHARACTER)
			
			for(int n = 0; n < size; n++){
				temp[n] = input[n];			//STORES CHARACTERS IN TEMP ARRAY
			}
			
			delete input;					//DELETE THE INPUT ARRAY
			input = temp;					//PUT CHARACTERS IN THE TEMP BACK TO INPUT	
			temp = NULL;					//SET TEMP POINTER TO NULL
			size++;							//INCREMENT SIZE BY ONE
		}
		
		input[count] = '\0';				//PUTS THE NULL CHARACTER IN THE NEW ARRAY
		//ONCE INPUT IS PUT IN A NEW ARRAY, CALL CORRESSPONDING FUNCTION	
		if(option == 1){
			morse(input,count+1);			
		}
		else if (option == 2){
			word(input,0,0,count+1);
		}
		
	cout << endl;
	cout << "Do you want to use text-morse again? \n";
	cout << "(1) AGAIN \n";
	cout << "(2) EXIT \n";
	cin >> again;
	}while(again == 1);
	
	return 0;
}
