#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    //1.	Read the list of values from the given “Sample_input.txt”
    //2.	Implement the Run code Encoding compression technique as discussed in the class.
    //3.	The output should also be written in a text file named”Run_code_encoding.txt”

    ifstream input;
    input.open("Sample_input.txt");
    ofstream output;
    output.open("Run_code_encoding.txt");



    string character;

    //read the comma-delineated file into a vector of strings
    
    vector<string> characters;
    while (getline(input, character, ',')) {
        characters.push_back(character);
    }

    //print the vector of strings
    cout << "The vector of strings is: " << endl;
    for (int i = 0; i < characters.size(); i++) {
        cout << characters[i] << endl;
    }

    int count = 1;
    string current;
    string next;
    vector<string> encoded = {};
    vector<int> encoded_count = {};

    //loop through the vector of strings and count the number of times each string appears consecutively
    for (int i = 0; i < characters.size()-1; i++) {
        current = characters[i];
        next = characters[i + 1];
        if (current == next) {
            count++;
        }
        else {
            encoded.push_back(current);
            encoded_count.push_back(count);
            count = 1;
        }
    }
    encoded.push_back(current);
    encoded_count.push_back(count);
    count = 1;

    //print the encoded vector of strings
    cout << "The encoded vector of strings is: " << endl;
    for (int i = 0; i < encoded.size(); i++) {
        cout << encoded[i] << endl;
    }

    count = 1;
    //change consecutive counts of 1 to the sum of nearby counts of 1 times -1
    for (int i = 0; i < encoded_count.size()-1; i++) {
        if(encoded_count[i] == 1){
            for (int j = i+1; j < encoded_count.size()-1; j++) {
                //find the length of the consecutive counts of 1
                if (encoded_count[j] == 1) {
                    count++;
                }
                else {
                    break;
                }
            }
            //change the consecutive counts of 1 to the sum of nearby counts of 1 times -1
            encoded_count[i] = count * -1;
            //remove the nearby counts of 1
            encoded_count.erase(encoded_count.begin() + i + 1, encoded_count.begin() + i + count);
            count = 1;
        }
    }

    //print the encoded vector of counts
    cout << "The encoded vector of counts is: " << endl;
    for (int i = 0; i < encoded_count.size(); i++) {
        cout << encoded_count[i] << endl;
    }


    //write the encoded vector of strings to the output file with the count before each string
    int offset = 0;
    for (int i = 0; i < encoded.size(); i++) {
        if (encoded_count[i] > 0 && i!=encoded.size() -1) {
            output << encoded_count[i - offset] << "," << encoded[i] << ",";
        }
        else if (encoded_count[i] > 0 && i == encoded.size() - 1) {
            output << encoded_count[i - offset] << "," << encoded[i];
        }
        else {
            output << encoded_count[i] << ",";
            for (int j = 0; j < encoded_count[i - offset] * -1; j++) {
                output << encoded[i + offset] << ",";
                offset++;
            }
            i += offset;
            
        }
    }
    

    return 0;
}

