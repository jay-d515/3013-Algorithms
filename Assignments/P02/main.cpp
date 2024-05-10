/*************************************************************
* Name:
*       Jadyn Dangerfield
*
* Class: 
*       CMPS 3013 - Advanced Structures and Algorithms
*
* Program:
*       Program 2 - Using JSON and Getch
*
* Files:
* 
* Description:
*
*************************************************************/

#include "./headers/console.hpp"
#include "./headers/json.hpp"
#include "./headers/rang.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>

using namespace std;
using namespace rang;
using json = nlohmann::json;
// used to store the size of the console window
consoleSize console_size;

// function prototypes
json loadJsonFile(string filePath);
vector<string> partialMatch(nlohmann::json array, string substring);
void titleBar(string title, int length = console_size.width);
void horizontalBar(int length = console_size.width);
void printDefinition(nlohmann::json array, string substring);
void printMenu(vector<string> options);
void printHighlightedSubstr(string word, string substr, int loc);
void printCurrent(char k, string word);
void errorMessage(string message);


int main() {
  // stores the height and width of the console window
  console_size = getConsoleSize();
  // stores the character being typed
  char k;                          
  // stores the string that was typed
  string key;                
  // stores the current word being typed (concatenates the characters)  
  string substr = ""; 
  // stores any matches found in   
  vector<string> matches;
  // stores the location of the substring to change its color
  int loc;                
  // indicates whether characters are being deleted from the string
  bool deleting = false;
  // initializes an empty string to the variable str
  string str = "";
  // creates a path to the JSON file
  json myJson = loadJsonFile("./data/dictionary.json"); 

  // adds 3 strings to the end of the vector, "MainMenu"
  vector<string> mainMenu;
  mainMenu.push_back("Type letters and watch the results change.");
  mainMenu.push_back(
      "Hit the DEL key to erase a letter from your search string.");
  mainMenu.push_back(
      "When a single word is found, hit enter. (this is for real assignment.");

  // clears the console
  clearConsole();
  // prints a centered title to the console
  titleBar("Getch Example", console_size.width);
  // prints the menu of options and instructions to the console
  printMenu(mainMenu);

  // while a capital Z is not typed...
  while ((k = getch()) != 'Z') {
    clearConsole();
    titleBar("Getch Example", console_size.width);
    printMenu(mainMenu);

  // if the user pressed the enter key (ASCII value = 10)...
    if((int)k == 10 && matches.size() == 1){
      printDefinition(myJson, substr);
      break;
    }

    // if the user pressed the space key (ASCII value = 32)...
    if((int)k == 32){
    // appends a space to string substr
      substr += " ";
    }

    // if the space key was pressed (ASCII value = 32)...
    if ((int)k == 127) {
    // if the string is not empty...
      if (substr.size() > 0) {
        substr = substr.substr(0, substr.size() - 1);
        deleting = true;
      }
    }
    // if the character pressed is a letter...	
  else {
      deleting = false;
      // if the key pressed is not a letter...
      if (!isalpha(k)) {
    // if the space key was pressed (ASCII value = 32)...
        if((int)k == 32){          
          substr += "";             
        }

        else {                       
          errorMessage("Letters only!");
        }
        continue;
      }

      // if the key pressed is a lower case letter...
      if ((int)k < 97) {
        k += 32;
      }
    // concatenates the capitalized letter to the string
      substr += k; 
    }

    horizontalBar();
    printCurrent(k, substr);

    // Find any words in the JSON file that partially match
    // our substr word
    matches = partialMatch(myJson, substr);

  // if the key pressed is not a space (ASCII value = 32)...
    if ((int)k != 32) { 
      key = to_string(k);
      horizontalBar();
      cout << style::bold << style::underline << fg::black
           << "MATCHES: " << fg::green << matches.size() << style::reset
           << fg::reset << endl
           << endl;

    // loops through all the characters in the string...
      for (auto &c : substr)
        c = tolower(c);
      // iterates through the "matches" vector
      for (int i = 0; i < matches.size(); i++) {
    // if the current index is equal to 10...
        if(i == 10)         
          break;

        loc = matches[i].find(substr);

    // if the substring is found within the string...
        if (loc != string::npos) {
          printHighlightedSubstr(matches[i], substr, loc);
        }
        cout << " ";
      }
      cout << fg::reset << endl << endl << endl << endl;
    // if there is only one match...
      if (matches.size() == 1) {
        cout << "done? (hit enter)" << endl;

      }
    }
  }
  return 0;
}

// function definitions

/**
* Name:
*       loadJsonFile
*
* Description:
*       loads a Json file and returns the data as a Json object
*
* Parameters:
*       string filePath | represents the path to a JSON file
*
* Returns:
*       json | a json object
*/
json loadJsonFile(string filePath) {

    // creates an input file stream called "filePath"
    ifstream fileStream(filePath);
    // creates a json object
    json myJson;

  // if the file does open...
    if (fileStream.is_open()) {
    // reads in data to the file
        fileStream >> myJson;
    // closes the file
        fileStream.close();
    } 
  // if the file does not open
  else {
    // prints an error message to the console stating that the file failed to open
        cerr << "Failed to open file: " << filePath << endl;
    // returns 1 to indicate an error
        return 1;
    }
  // returns the "myJson" object
    return myJson;
}

/**
* Name:
*       partialMatch
*
* Description:
*       Finds partial matches in a json object and returns them. It
*       doesn't matter where in the string the match is.
*
* Parameters:
*       json array | array to search
*       string substring     | substring to search for in each word
*
* Returns:
*       vector<string> - holding all the matches to substring
*/
vector<string> partialMatch(nlohmann::json array, string substring) {
  // holds the words that match the substring
  vector<string> matches;

  // if the substring is empty, the function returns the empty array of
  // matches, indicating that there are no matches for an empty substring.
  if (substring.size() == 0) {
  // returns the empty array of matches
    return matches;
  }
  // iterates through the keys in the json object
  for (auto &element : array.items()) {
    // sets the key to the current key-value pair
      string key = element.key();

    // if the substring is found in the key...
      if (key.find(substring) != string::npos) {

        for(int i = 0; i < substring.length(); i++) {
      // if the key-value is equal to the character in the substring AND
          // is not the last character in the substring...
          if(key[i] == substring[i] && i == substring.length() - 1) { 
        // appends the character to the end of the matches vector
            matches.push_back(key);
          }
          // if the key-value is equal to the character in the substring AND
          else if(key[i] == substring[i] && i != substring.length() - 1) {   
          }
      // if the key-value is not equal to the character in the substring AND
          // is the last character in the substring...
          else {  
      // the function breaks out of the loop
            break;
          }
        }
      }
  }
  // returns the array of matches
  return matches;
}

/**
* Name:
*       titleBar
* Description:
*       Prints a long background row of gray, with text centered, at the 
*       top of the console. 
*
* Parameters:
*       string title |  title to be displayed
*       int length   |  the desired length of the row
*
* Returns:
*       void
*/
void titleBar(string title, int length) {
  // calculates the number of spaces needed to center the title within the horizontal bar.
  string padding = string((length / 2) - (title.size() / 2), ' ');
  // adds the spaces needed, on both sides, to center the title within the horizontal bar.
  title = padding + title + padding;
   // sets the background color to black and foreground color to gray, then prints the title to the console.
  cout << bgB::black << fg::gray << title << fg::reset << bg::reset << endl;
}

/**
* Name:
*       horizontalBar
*
* Description:
*       Prints a horizontal bar of a given length.
*
* Parameters:
*       int length | length of the horizontal bar
*
* Returns:
*       void
*/
void horizontalBar(int length) {
  // the number of underscore characters that will form the horizontal bar.
  string line = string(length, '_');
  // sets the foreground color to gray, then prints the horizontal bar to the console.
  cout << fg::gray << line << fg::reset << bg::reset << endl;
}

/**
 * printDefinition
 *
 * Description:
 *        Prints the definition of a word to the screen.
 * Params:
 *      json array | json object of key-value pairs
 *      substring  | substring to search for in each word
 * Returns:
 *      void
 */
void printDefinition(nlohmann::json array, string substring){
  // iterates through the array of key-value pairs
  for (auto &element : array.items()) {
    // sets the key to the current key-value pair
      string key = element.key();

      // if the substring is found in the key...
      if (key.find(substring) != string::npos) {
        // prints the key and its corresponding value to the console
        cout << key << " -> " << element.value() << endl;
      }
  }
}

/**
* Name:
*       printMenu
*
* Description:
*       Prints a numbered menu to the screen, in the color cyan, that 
*       directs the user on how to work the program.
*
* Parameters:
*       vector<string> options | vector of directions to print
*
* Returns:
*       void
*/
void printMenu(vector<string> options) {
  // integer variable used to number the menu items
  int i = 1;
  // iterates through each string in the options vector.
  for (auto s : options) {
  // for each string in the vector, the item number is printed, followed
  // by a period (all in cyan) and a space (in bold back).
    cout << fg::black << style::bold << i << ". " << style::reset << fg::cyan
  // the forground and background colors are reset to their default values.
         << s << fg::reset << bg::reset << endl;
    i++;
  }
  // the forground and background colors are reset to their default values.
  cout << fg::reset << bg::reset;
}

/**
* Name:
*       printHighlightedSubstr
*
* Description:
*       Given a word, print the substring underlined in red and blue for 
*       the rest of the word.
*
* Parameters:
*       string  word  | word to be printed
*       string substr | substring to highlight in red
*       int loc       | location of substring within the word
*
* Returns:
*       void
*/
void printHighlightedSubstr(string word, string substr, int loc) {
  // iterates over each character within the word
  for (int j = 0; j < word.size(); j++) {
    // if we are printing the substring turn it red
    if (j >= loc && j <= loc + substr.size() - 1) {
    // the character is printed and underlined, to the console, in red.
      cout << fg::red << style::underline << word[j] << fg::blue
           << style::reset;

    } 
  // if the character is not apart of the substring...
  else {
    // the character is printed to the console in blue.
      cout << fg::blue << word[j] << fg::reset << style::reset;
    }
  }
}

/**
* Name:
*       printCurrent
*
* Description:
*       Prints the current key pressed and the current substr to the       
*       screen.
*
* Parameters:
*       char k      | last character pressed.
*       string word | current substring being printed.
*
* Returns:
*       void
*/
void printCurrent(char k, string word) {
  // prints the string "Key Pressed:" in green and bold to the console, 
  // followed by the character k, in yellow.
  cout << fg::green << style::bold << "KeyPressed: \t\t" << style::reset
       << fgB::yellow;
  // if the character pressed is the backspace (ASCII value of 127)...
  if (int(k) == 127) {
  // the string "del" is printed to the console, in red.
    cout << "del";
  } 
  // if the character pressed is not the backspace...
  else {
  // the charcter is printed to the console, in yellow.
    cout << k;
  }
  // the string "=" is printed to  the console, in green, followed by the 
  // integer value of the character k, in yellow.
  cout << " = " << (int)k << fg::reset << endl;
  // prints the string "Current Substring:" in green and bold to the           
  // console, followed by the current substring, in blue."
  cout << fg::green << style::bold << "Current Substr: \t" << fg::reset
       << fgB::blue << word << fg::reset << style::reset << endl;
  cout << endl;
}

/**
* Name:
*       errorMessage
*
* Description:
*       Prints an error message to the screen.
*
* Parameters:
*       string message | message to print
*
* Returns:
*       void
*/
void errorMessage(string message) {
  // prints the error message to the console, with a background color of
  // red and a foreground color of gray.
  cout << bgB::red << fgB::gray << message << fg::reset << bg::reset << endl;
  // pauses the execution of the function for 1 second to give the user         
  // time to read the message.
  sleep(1);
}