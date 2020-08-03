
#include <stdlib.h>
#include <iostream>
#include <string>

void encode(int, std::string &);

int main(int argc, char *argv[]) {
    int key, direction;
    std::string phrase, key_string;

    while (true) {
        std::string command;
        std::cout << "Tell me, do you want to encode or decode a phrase?" << std::endl;
            getline(std::cin, command);
        if (command == "encode") 
            direction = 1;
        else  if (command == "decode")
            direction = -1;
        else {
            std::cout << "Sorry I did not understand you, let's try this again." << std::endl;
            continue;
        }
    
        std::cout << "Please input your key: ";
        getline(std::cin, key_string);
        key = std::stoi(key_string);
        std::cout << "Please input your phrase: ";
        getline(std::cin, phrase);
        encode(key * direction, phrase);
        std::cout << phrase << std::endl;

    }
}

void encode(int key, std::string &phrase) {
    for (int i = 0; i < phrase.size(); i++) {
        if (isalpha(phrase[i])) {
            if (phrase[i] >= 97) {
                phrase[i] = (phrase[i] - 97 + key + 26) % 26 + 97;
            } else {
                phrase[i] = (phrase[i] - 65 + key + 26) % 26 + 65;
            }
        }
    }
}




















