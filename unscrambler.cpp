#include <iostream>
#include <cstring>
#include <fstream>
#include <unordered_set>

using namespace std;

void sortLargestToSmallest(string results[], int total);

int main() {
  ifstream file;
  file.open("words.txt");
  if (file.fail()) {
    cout << "Cannot open dictionary" << endl;
    exit(1);
  }
  string line;
  unordered_set<string> uset;
  while (getline(file, line)) {
    uset.insert(line);
  }
  file.close();

  char word[100];
  bool loop;
  loop = true;
  while (loop) {
    cout << endl << "Enter scrambled letters (no spaces and no numbers)" << endl;
    cin.getline(word, 100);
    cout << endl;
    int check = 0;
    for (int i = 0; i < strlen(word); i++) {
      if (isalpha(word[i]) && !isspace(word[i])) {
        check++;
      }
    }
    if (check == strlen(word)) {
      loop = false;
    }
    else {
      cout << "Invalid input.";
    }
  }
  unordered_set<char> inputWordUset;
  for (int i = 0; i < strlen(word); i++) {
    inputWordUset.insert(word[i]);
  }

  int sizeCheck = strlen(word);
  bool check[sizeCheck];
  unordered_set<string>::iterator it = uset.begin();
  int total = 0;
  string results[1000];
  while (it != uset.end()) {
    string setWord = *it;
    int setWordSize = setWord.length();
    if (setWord.length() > 1 && setWord.length() <= strlen(word)) {
      for (int k = 0; k < strlen(word); k++) {
        check[k] = true;
      }
      char setArray[setWordSize];
      for (int i = 0; i < setWord.length(); i++) {
        setArray[i] = setWord[i];
      }
      int matches = 0;
      for (int i = 0; i < setWord.length(); i++) {
        if (inputWordUset.find(setArray[i]) != inputWordUset.end()) { // if true
          for (int j = 0; j < strlen(word); j++) {
            if (setArray[i] == word[j]) {
              if (check[j]) {// == true
                matches++;
                check[j] = false;
                break; // go to the next letter in the set word that is being analyzed
              }
            }
          }
        }
        else {
          break;
        }
      }
      if (matches == setWord.length()) {
        results[total] = setWord;
        total++;
      }
    }
    it++;
  }

  sortLargestToSmallest(results, total);

  for (int i = 0; i < total; i++) {
    cout << results[i] << endl;
  }
  cout << "Total words: " << total << endl << endl;
}


void sortLargestToSmallest(string results[], int total) {
  for (int i = 1; i < total; i++) {
    string temp = results[i];
    int j = i - 1;
    while (j >= 0 && temp.length() > results[j].length()) {
      results[j + 1] = results[j];
      j--;
    }
    results[j + 1] = temp;
  }
}
