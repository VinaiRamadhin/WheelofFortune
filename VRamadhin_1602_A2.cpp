#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

struct Puzzle{
	string category;
	char puzzle[80];
};

int readCategories(string categories[]){
	string category;
	int numCategories = 0;
	ifstream inputFile;
	inputFile.open("Categories.txt");
	if(!inputFile.is_open()){
		cout << "Error opening file. Aborting";
		exit(1);
	}
	while(numCategories < 50 && getline(inputFile, category)){
		categories[numCategories] = category;
		numCategories++;
	}
	inputFile.close();
	return numCategories;
}

string decryptPuzzle(char p[]){
	int length = strlen(p); 
    for (int i = 0; i < length; i++) {
        char c = p[i];

        if (c >= 'A' && c <= 'Z') {
            c -= 5; 
        }
            if (c < 'A') {
	           c += 26; 
        }
        else if (c >= 'a' && c <= 'z') {
            c -= 5; 
            if (c < 'a') 
                c += 26; 
        }
        p[i] = c;
    }

    return p;
}


int readPuzzles(Puzzle p[], string categories[], int maxPuzzles){
	ifstream in;
	in.open("WOF-Puzzles.txt");
	if(!in.is_open()){
		cout << "Error opening Input file";
		exit(1);
	}
	int count = 0;
	string category;
	char puzzle[80];
	while(count < maxPuzzles && getline(in, category)){
		in.getline(puzzle, 80);
		
		p[count].category = category;
		
		strcpy(p[count].puzzle, puzzle); 
		
		count++;
	}
	
	in.close();
	return count;
}

string chooseCategory(string categories[], int numCategories){
	srand((time(NULL)));
	
	int rand1 = rand() % numCategories;
	int rand2 = rand() % numCategories;
	int rand3 = rand() % numCategories;
	
	if(rand2 == rand1){
		rand2 = (rand2 + 1) % numCategories;
	}
	if(rand3 == rand1 || rand3 == rand2){
		rand3 = (rand3 + 1) % numCategories;
	}
	
	cout << "Choose a category from one of the following: "<< endl;
	cout <<"1. " << categories[rand1] << endl;
	cout <<"2. " << categories[rand2] << endl;
	cout <<"3. " << categories[rand3] << endl;
	
	int choice;
	cout << "Please enter your choice ";
	cin >> choice;
	if(choice == 1){
		return categories[rand1];
	} else if(choice == 2){
		return categories[rand2];
	} else if(choice == 3){
		return categories[rand3];
	}
	
}

string choosePuzzle(string category, Puzzle p[], int puzzleCount){
	srand((time(NULL)));
	
	int matchIndex[puzzleCount];
	int matchCount = 0;
	
	for(int i = 0;i < puzzleCount;i++){
		if(p[i].category == category){
			matchIndex[matchCount++] = i;
		}
	}
	
	int randIndex = rand() % matchCount;
	int chosen = matchIndex[randIndex];
	
	char decryptedPuzzle[80];
	strcpy(decryptedPuzzle, p[chosen].puzzle);
	string index = decryptPuzzle(decryptedPuzzle);
	
	return index;
}

void blankOutPuzzle(char p[]){
	int length = strlen(p);
	for(int i = 0;i < length;i++){
		if ((p[i] >= 'A' && p[i] <= 'Z') || (p[i] >= 'a' && p[i] <= 'z')) {
            p[i] = '#';
        }
	}	
}

char checkWildCard(){
	int choice;
	char letter;
	cout << "Do you have the wildcard? (0-No, 1-Yes): ";
	cin >> choice;
	if(choice == 1){
		cout << "Please enter another consonant: ";
		cin >> letter;
		return true;
	} else if(choice == 0){
		return false;
	}
	return letter;
}

void rstlne(string& puzzle) {
    for (int i = 0; i < puzzle.length(); i++) {
        if (puzzle[i] == 'R' || puzzle[i] == 'S' || puzzle[i] == 'T' || puzzle[i] == 'L' || puzzle[i] == 'N' || puzzle[i] == 'E') {
        } else if ((puzzle[i] >= 'A' && puzzle[i] <= 'Z') || (puzzle[i] >= 'a' && puzzle[i] <= 'z')) {
            puzzle[i] = '#'; 
        }
    }
}

char toUpper(char c){
	if(c >= 'a' && c <= 'z'){
		c = c - ' ';
	}
	return c;
}

void toUpperCase(char str[]) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        str[i] = toUpper(str[i]);
    }
}

void revealLetter(char letter, char p[], char c[]) {
    int i = 0;
    while (p[i] != '\0') {
        if (p[i] == letter) {
            c[i] = letter;
        }
        i++;
    }
}

string revealLetter(string decryptedPuzzle) {
    string reveal;
    char cons1, cons2, cons3, vowel, wildCard, choice;

    cout << "Enter three consonants: ";
    cin >> cons1 >> cons2 >> cons3;
    cout << endl;

    cout << "Enter one vowel: ";
    cin >> vowel;
    cout << endl;
    
    cout << "Do you have a wild card?(y/n): "; 
    cin >> wildCard; 
    wildCard = toUpper(wildCard);
    
    
    if (wildCard == 'Y') {
        cout << "Enter a fourth consonant: "; 
        cin >> choice;
        cout << endl;
        choice = toUpper(choice); 
    }
    
    
    cons1 = toUpper(cons1);
    cons2 = toUpper(cons2);
    cons3 = toUpper(cons3);
    vowel = toUpper(vowel);

    
    string revealChars = "RSTLNE";

    
    for (int i = 0; i < decryptedPuzzle.length(); i++) {
        char c = decryptedPuzzle[i];
        bool foundChar = false;

        
        for (size_t j = 0; j < revealChars.length(); j++) {
            if (c == revealChars[j] || c == cons1 || c == cons2 || c == cons3 || c == vowel || (wildCard == 'Y' && c == choice)) {
                foundChar = true;
                break;
            }
        }

        
        if (foundChar) {
            reveal += c;
        } else if (isalpha(c)) {
            reveal += '#'; 
        } else {
            reveal += c; 
        }
    }

    cout << "The puzzle is now: " << reveal << endl;
    return reveal;
}

string revealPrize(){
	int randNum = rand() % 25 + 1; 

    if (randNum <= 3) {
        return "Car";
    } else if (randNum <= 22) {
        return "$40,000.00";
    } else if (randNum <= 24) {
        return "$45,000.00";
    } else {
        return "Jackpot ($100,000.00)";
    }
}

int main(){
	
	int MAXCATEGORIES = 90;
	int MAXPUZZLES = 2000;
	string categories[MAXCATEGORIES];
	Puzzle puzzles[MAXPUZZLES];
    int categoryCount = readCategories(categories);

    
    int puzzleCount = readPuzzles(puzzles,categories, MAXPUZZLES);
    
    cout << "# of categories read from the file: " << categoryCount << endl;
    cout << "# of puzzles read from the file: " << puzzleCount << endl;

	int totalCategories = categoryCount; 
	int totalPuzzles = puzzleCount; 
	
	string chosen = chooseCategory(categories, totalCategories);
	cout << endl;
	
	cout << "You chose: " << chosen << endl;


	char randpuzzle[80];
	strcpy(randpuzzle, choosePuzzle(chosen, puzzles, puzzleCount).c_str());
	
	char originalPuzzle[80];
	strcpy(originalPuzzle, randpuzzle); 
	
	char answer[80];
	strcpy(answer, originalPuzzle); 
		
	cout << endl;
	blankOutPuzzle(originalPuzzle);
	cout << endl;
		
	cout << "The puzzle to start with is : " << originalPuzzle << endl;
	cout << endl;

	cout << "Revealing R, S, T , L, N, E ... " << endl;
	cout << endl;
	
	string decryptedP = randpuzzle;
	rstlne(decryptedP);;
	cout << "The puzzle is now: " << decryptedP << endl;
	cout << endl; 
	
    string revealedLetters = revealLetter(randpuzzle);
	
	srand(time(NULL)); 


    int totalAttempts = 3;

    cin.ignore(INT_MAX, '\n');

    for (int i = 1; i <= totalAttempts; i++) {
        char guesses[80];
        cout << "Enter your guess: ";
        cin.getline(guesses, 80);
        toUpperCase(guesses); 
        toUpperCase(answer); 
		
		char result = strcmp(guesses, answer);
        if (result == 0) {
            cout << "Congratulations! You got it right!" << endl;
            string prize = revealPrize();
            cout << "OK, let's see your prize." << endl;
            cout << "It is ..... " << prize << endl;
            return 0; 
        } else {
            cout << "Sorry. " << guesses << " is not correct." << endl;
            if (i < totalAttempts) {
                cout << "You have " << totalAttempts - i << " tries left." << endl;
            }
        }
	}

    cout << "Sorry, you couldn't guess the puzzle. The correct answer was: " << answer << endl;
    cout << "Better luck next time!" << endl;
	
	return 0;	
}
