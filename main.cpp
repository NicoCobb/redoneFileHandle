#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
// #define DEBUG

using namespace std;

class VocabWord {
    private:
        string word;
        string partOfSpeech;
        string def;
        string exampleSentence;
        
    public:
        //constructors
        VocabWord() {
            word = "--";
            partOfSpeech = "--";
            def = "--";
            exampleSentence = "--";
        };
        
        VocabWord(string newWord, string pos, string definition, string example) {
            word = newWord;
            partOfSpeech = pos;
            def = definition;
            exampleSentence = example;
        };
    
        //getters
        string getWord() {
            return word;
        };
        
        string getPos() {
            return partOfSpeech;
        };
        
        string getDefinition() {
            return def;
        };
        
        string getExampleSentence() {
            return exampleSentence;
        };
        
};

vector <VocabWord*> *vocabList;

int convertToAscii(string toConvert) {
    int converted;
    
    for (int i = 0; i < toConvert.size(); i++)
    {
        converted+= (int)toConvert[i]; 
    }
    
    return converted;
};

void quickSortAlphabetical(int left, int right) {
#ifdef DEBUG
    cout << "beginning sort for alphabetical \n";
#endif
    int i = left;
    int j = right;
    VocabWord *temp;
    int pivot = int (vocabList->at((left + right) / 2)->getWord()[0]);

#ifdef DEBUG
    cout << "pivot: " << pivot << "\n";
    cout << "hey: " << vocabList->at((left + right) / 2)->getWord()[0] << "\n";
    cout << "hey: " << vocabList->at(1)->getWord()[0] << "\n";
#endif
    
    //split the vector based on the pivot and shift all values beneath it to the left using ascii values
    while (i <=j) {
#ifdef DEBUG
    cout << "sorting... \n";
#endif    
        while (convertToAscii(vocabList->at(i)->getWord()) < pivot) {
            i++;
        };
        while (convertToAscii(vocabList->at(i)->getWord()) < pivot) {
            j--;
        };
        if (i <= j) {
            temp = vocabList->at(i);
            vocabList->at(i) = vocabList->at(j);
            vocabList->at(j) = temp;
            i++;
            j--;
        };
    };
};

void help() {
    cout << "add: add new vocab words \n";
    cout << "study: study the your vocab list in either alphabetical or random order \n";
    cout << "end: end the program \n";
};


void populateArray() {
    ifstream workingFile("vocabList.txt");
    
    vocabList->clear();
    if (workingFile.is_open()) {
       string nextLine;

       vector<string> temporaryParameters;
       while ( getline(workingFile, nextLine)) {
           
#ifdef DEBUG
            cout << nextLine << "\n";
            cout << "now we gonna string some streams. no rivers round here oh nonono \n";
#endif
            //convert each line to a stringStream so that I can parse through it
            istringstream ss(nextLine);
            string temp;
            //array of strings to temporarily hold the inputs for the VocabWord
            
#ifdef DEBUG
            cout << "uuuuuuuuuh \n";
#endif
            
            while (getline(ss, temp, '|')) {

                temporaryParameters.push_back(temp);
            };
            
#ifdef DEBUG
      cout << "gonna make a word \n";
#endif
      
            if (temporaryParameters.size() != 0) {
                VocabWord *nextWord = new VocabWord(temporaryParameters[0], temporaryParameters[1], temporaryParameters[2], temporaryParameters[3]);
                temporaryParameters.clear();
               
                //add the new VocabWord to vocabList
                vocabList->push_back(nextWord);
            };
       };
      //create an instance of VocabWord based off of the given line
      


    }
    else {
       cout << "unable to open file \n";
    };
    
#ifdef DEBUG
    cout << "end populateArray \n";
#endif

};

void addVocab(string word, string pos, string definition, string sentence) {
    ofstream workingFile("vocabList.txt", ios_base::app);
    if (workingFile.is_open()) {
        workingFile << word << "|" << pos << "|" << definition << "|" << sentence << "\n";
        populateArray();
    }
    else {
        cout << "unable to open file \n";
    };
};

void study() {
    int counter = 0;

    //the word that will be studied
    string word;
    //decides if teh study method will continue to loop or not
    bool keepStudying = true;
    
    while(keepStudying == true) {
        
        //begin studying by asking for the matching word
        cout << "what word matches this definition? \n" << vocabList->at(counter)->getDefinition() << "\n";
        getline (cin, word);
        
        if (word == vocabList->at(counter)->getWord()) {
            cout << "Correct! what is the matching part of speech? \n";
            string partSpeech;
            getline (cin, partSpeech);
            if (partSpeech == vocabList->at(counter)->getPos()) {
                cout << "Correct! \n Would you like to continue to the next word? \n";
                cout << "Enter 'yes' to continue or 'no' to stop studying \n";
                bool properResponse = false;
                while (properResponse == false) {
                    string choice;
                    getline (cin, choice);
                    if (choice == "yes") {
                        properResponse = true;
                    } else if (choice == "no") {
                        properResponse = true;
                    } else {
                        cout << "Please enter yes or no \n";
                    };
                }
            } else {
                cout << "no of course that's not the part of speech. how bad at this can you be. git gud. \n";
            };
        } else {
            cout << "hahahahahahahaha no you're wrong. \n";
        }
        counter++;
        if (counter >= vocabList->size()) {
        cout << "you have reached the end of the list! exiting back to main menu \n";
        keepStudying = false;
        };
    };
    
};

void studyRandomly() {
    //randomizes the words
    random_shuffle(vocabList->begin(), vocabList->end() );
    //uses new order of words for study
    study();
};

//retrieve all of the necessary information to execute 'add' from the user
void promptUserAdd() {
    cout << "what word would you like to add? \n";
    string word;
    getline(cin, word);
    cout << "what is its part of speech? \n";
    string pos;
    getline(cin, pos);
    cout << "what is the definition? \n";
    string definition;
    getline(cin, definition);
    cout << "what is an example sentence? \n";
    string sentence;
    getline(cin, sentence);
    
    //add in the word to the list
    addVocab(word, pos, definition, sentence);
};

void studyAlphabetical() {
    
    //alphabetizes the words
#ifdef DEBUG
    cout << vocabList->at(0)->getWord() << "\n";
#endif
    quickSortAlphabetical(0, (vocabList->size() - 1));
    //uses new order of words for study
    study();
};

//retrieve all of the necessary information to execute 'study' from the user
void promptUserStudy() {
    cout << "would you like to study (1)alphabetically or (2)randomly? \n";
    string yesNo;
    getline(cin, yesNo);
    if (yesNo == "1") {
        studyAlphabetical();
    } else if (yesNo == "2") {
        studyRandomly();
    } else {
        cout << "please enter 1 for alphabetically and 2 for randomly. \n";
        promptUserStudy();
    };
};

int main() {
    vocabList = new vector<VocabWord*>();
    vocabList->clear();
    
#ifdef DEBUG
    cout << "about to populate array \n";
#endif

    populateArray();
    cout << "this is a tool for studying vocab lists. enter 'help' to see your options \n";
    string userInput;
    bool keepGoing = true;
    
    while (keepGoing == true) {
        getline(cin, userInput);
        if (userInput == "help") {
            help();
        } else if (userInput == "add") {
            promptUserAdd();
        } else if (userInput == "study") {
            promptUserStudy();
        } else if (userInput == "end") {
            keepGoing = false;
        }
        else {
            cout << "please enter one of the given commands. enter 'help' to see your options \n";
        };
    }
    return 0;
};
