#include <iostream>
#include <fstream>
#include <string>

#include "binary_tree.h"
#include "binary_tree.cpp"

void add_dictionary(binary_tree<std::string, int> [26], binary_tree<std::string, int> [10]);

void main() {
	binary_tree<std::string, int> dictionary[26], dictionary_int[10];
	bool is_cummulative = false, exit = false;
	std::string temp;
	while (!exit) {
		//checks if there is a previous dictionary present
		for (int i = 0; i < 26; i++) {
			temp = "dic_";
			temp.push_back(char(i + 97));
			if (dictionary[i].load_file(temp)) {
				is_cummulative = true;
			}
		}
		for (int i = 0; i < 10; i++) {
			temp = "dic_";
			temp.push_back(char(i + 97));
			if (dictionary_int[i].load_file(temp)) {
				is_cummulative = true;
			}
		}
		//runs if there is a previous dictionary
		if (is_cummulative) {
			int answer;
			std::cout << "previous dictionaries found" << std::endl << std::endl;
			do {
				std::cout << "choose an option from the list" << std::endl << "1. search number of occurences in dictionary" << std::endl << "2. add a dictionary" << std::endl << "3. close program" << std::endl;
				std::cin >> answer;
			} while (answer > 4 && answer < 0);
			std::cout << std::endl;
			if (answer == 1) {
				std::string query;
				do {
					std::cout << std::endl << "enter search query: ";
					std::cin >> query;
					if (!((query[0] >= 'a' && query[0] <= 'z') || (query[0] >= '0' && query[0] <= '9'))) {
						std::cout << "invalid search term" << std::endl;
					}
				} while ((!((query[0] >= 'a' && query[0] <= 'z') || (query[0] >= '0' && query[0] <= '9'))));
				std::cout << "the number of occurences of this word is " << dictionary[int(query[0]) - 97].search(query);
			}
			else if (answer == 2) {
				add_dictionary(dictionary, dictionary_int);
			}
			else {
				exit = true;
			}
			std::cout << std::endl << std::endl << std::endl;
		}
		//runs if there is no previous dictionary
		else {
			int answer;
			std::cout << "no previous dictionaries found" << std::endl << std::endl;
			do {
				std::cout << "choose an option from the list" << std::endl << "1. add a dictionary" << std::endl << "2. close program" << std::endl;
				std::cin >> answer;
			} while (answer > 3 && answer < 0);
			if (answer == 1) {
				add_dictionary(dictionary, dictionary_int);
			}
			else {
				exit = true;
			}
			std::cout << std::endl;
		}
	}
}

//function to add a file to dictionary
void add_dictionary(binary_tree<std::string, int> dictionary[26], binary_tree<std::string, int> dictionary_int[10]) {
	std::ifstream in_file;
	std::string file_name;
	std::cout << std::endl <<  "please enter file name to add to dictionary: ";
	std::cin >> file_name;
	std::cout << std::endl;
	file_name += ".txt";
	in_file.open(file_name.c_str());
	std::string temp;
	char temp_char;
	if (in_file.is_open()) {
		//loop to insert word into repective dictionary
		do {
			in_file.get(temp_char);
			temp_char = tolower(temp_char);
			//analyses text character by character to produce usale strings
			while (temp_char > '!' && !in_file.eof()) {
				if ((temp_char >= 'a' && temp_char <= 'z') || (temp_char >= '0' && temp_char <= '9')) {
					temp.push_back(temp_char);
				}
				do {
					in_file.get(temp_char);
				} while (!(temp_char >= 0 && temp_char <128));
			}
			//to detremine whether to put word in alphabet dictionary or numeric one
			if (!temp.empty()) {
				if (temp[0] >= 'a') {
					dictionary[int(temp[0]) - 97].insert(temp);
				}
				else {
					dictionary_int[int(temp[0]) - 48].insert(temp);
				}
			}
			temp.clear();
		}  while (!in_file.eof());
		temp.clear();
		//saves each letter and number into a file
		for (int i = 0; i < 26; i++) {
			temp = "dic_" ;
			temp.push_back(char(i + 97));
			dictionary[i].save_file(temp);
		}
		for (int i = 0; i < 10; i++) {
			temp = "dic_";
			temp.push_back(char(i + 97));
			dictionary_int[i].save_file(temp);
		}
		std::cout << std::endl << "disctionary saved" << std::endl;
	}
	else {
		std::cout << "error: unable to open file" << std::endl;
	}
	in_file.close();
}