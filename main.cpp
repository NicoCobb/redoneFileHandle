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
    int i = left;
    int j = right;
    VocabWord *temp;
    int pivot = convertToAscii(vocabList->at((left + right) / 2)->getWord());
    
    //split the vector based on the pivot and shift all values beneath it to the left using ascii values
    while (i <=j) {
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
    cout << "add: add new vocab words";
    cout << "study: study the your vocab list in either alphabetical or random order";
};


void populateArray() {
    cout << "populating array \n";
    ifstream workingFile("vocabList.txt");
    
#ifdef DEBUG
    cout << "created text file \n";
#endif
    
    vocabList->clear();
    if (workingFile.is_open()) {
       cout << "file is open \n";
       string nextLine;
       cout << "soooo what's gonna happen if we do getline when there's an empty file? \n";
       cout << nextLine << "\n";
       vector<string> temporaryParameters;
       while ( getline(workingFile, nextLine)) {
           cout << nextLine << "\n";
            //convert each line to a stringStream so that I can parse through it
            cout << "now we gonna string some streams. no rivers round here oh nonono \n";
            istringstream ss(nextLine);
            string temp;
            //array of strings to temporarily hold the inputs for the VocabWord
            
            cout << "uuuuuuuuuh";
            while (getline(ss, temp, '|')) {
                cout << "infinite loop? \n";
                temporaryParameters.push_back(temp);
            };
       };
      //create an instance of VocabWord based off of the given line
      cout << "gonna make a word";
      VocabWord *nextWord = new VocabWord(temporaryParameters[0], temporaryParameters[1], temporaryParameters[2], temporaryParameters[3]);
      temporaryParameters.clear();
       
      //add the new VocabWord to vocabList
      vocabList->push_back(nextWord);
    }
    else {
       cout << "unable to open file";
    };
    cout << "end populateArray";
};

void addVocab(string word, string pos, string definition, string sentence) {
    ofstream workingFile("vocabList.txt");
    if (workingFile.is_open()) {
        workingFile << word << "|" << pos << "|" << definition << "|" << sentence;
        populateArray();
    }
    else {
        cout << "unable to open file";
    };
};  

void study() {
    int counter = 0;
    cout << "what word matches this definition? \n" << vocabList->at(counter)->getDefinition();
    string word;
    getline (cin, word);
    if (word == vocabList->at(counter)->getWord()) {
        cout << "Correct! what is the matching part of speech?";
        string partSpeech;
        getline (cin, partSpeech);
        if (partSpeech == vocabList->at(counter)->getPos()) {
            cout << "Correct! would you like to continue to the next word?";
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
    cout << "about to populate array \n";
    populateArray();
    cout << "this is a tool for studying vocab lists. enter 'help' to see your options";
    string userInput;
    getline(cin, userInput);
    if (userInput == "help") {
        help();
    } else if (userInput == "add") {
        promptUserAdd();
    } else if (userInput == "study") {
        promptUserStudy();
    } else {
        cout << "please enter one of the given commands. enter 'help' to see your options";
    };

    return 0;
};
