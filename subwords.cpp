#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <set>
using namespace std;
set<string> permutations(string word) {
    set<string> words;
    string other;
    if (word.length() == 0) { words.insert(""); return words; }
    for (int i = 0; i < word.length(); i++) {
        other = word;
        other.erase(other.begin() + i);
        for (string substr : permutations(other)) {
            if (substr != "") { words.insert(substr); }
            words.insert(word.at(i) + substr);
        }
        for (int j = i + 1; j < word.length(); j++) {
            if (word.at(j) == word.at(i)) { word.erase(word.begin() + j); }
        }
    }
    return words;
}
int main(int argc, char **argv) {
    fstream file("words.txt");
    if (!file.is_open()) { throw runtime_error("Error when opening file"); }
    unsigned const int NWORDS = 81484;
    string word, chosen_word;
    default_random_engine dre(time(nullptr));
    uniform_int_distribution<int> di(0, NWORDS);
    int n = di(dre);
    map<string, bool> dict;
    file >> word;
    while (!file.eof()) {
        dict.emplace(word, false);
        n--;
        if (n == 0) { chosen_word = word; }
        file >> word;
    }
    if (argc == 2) { chosen_word = argv[1]; }
    cout << "The word is " << chosen_word << ':' << endl << endl;
    for (string perm : permutations(chosen_word)) {
        if ((perm.length() >= 3) && (dict.count(perm) == 1)) { cout << perm << endl; }
    }
    return 0;
}