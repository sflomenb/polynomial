#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <random>
using namespace std;
vector<string> read_files(const std::string& file_name){
    // REC 02 DCL04
    int num = 0;
    vector<string> num_array;
    /*
    STR50-CPP. Guarantee that storage for strings has sufficient space for character data and the null terminator
    The best solution for ensuring that data is not truncated and for guarding against buffer overflows is to use
    std::string instead of a bounded array, as in this compliant solution:
    */
    string line;
    ifstream input (file_name);
    if(input.is_open()){
        while(getline(input, line)){
            char *words = new char[line.length() + 1];
            if(!words) {    //MEM52-cpp Detect and handle memory allocation errors
                std::exit(1);
            }
            strcpy(words, line.c_str());
            // use strncpy to cope with buffer overflow
            char *word;
            word = strtok(words," ");
            //REC 05 STR 06 strtok
            while(word != NULL){
                // STR51-CPP. Do not attempt to create a std::string from a null pointer
                string temp(word);
                num_array.push_back(word);
                word = strtok(NULL, " ");
            }
            // MEM50-CPP: did not access after freeing
            // MEM51-CPP: Properly deallocate dynamically allocated resources
            delete[] words;
        }
        input.close();
    }
    else{
        cout << "Unable to open the file" << endl;

    }
    cout << "Your file is: ";
    for(auto iter : num_array){
        cout<< iter << " ";
    }
    cout << endl ;
    return num_array;
}
vector<long long> add(vector<long long> input1, vector<long long> input2){
    // Rule 4 Integer
    int i = 0;
    int j = 1;
    vector<long long> res;
    if(input1[0] < input2[0]){
        for( i = 0; i < (input2.size() - input1.size() + 1); i++){
            res.push_back(input2[i]);
        }
        i = input2.size() - input1.size() + 1;
        //STR53-CPP. Range check element access
        for( j = 1; j < input1.size(); j++){
            // RULE 04 INT, INT32-C Ensure that operations on signed integers do not result in overflow
            long long temp = input2[i] + input1[j];
            i++;
            res.push_back(temp);
        }
    }
    else if(input1[0] > input2[0]){

        for(i = 0; i < (input1.size() - input2.size() + 1); i++){
            res.push_back(input1[i]);
        }
        i = input1.size() - input2.size() + 1;
        for(j = 1; j < input2.size(); j++){
            long long temp = input1[i] + input2[j];
            i++;
            res.push_back(temp);
        }
    }
    else{
        res.push_back(input1[0]);
        for(i = 1; i < input1.size(); i++){
            long long temp = input1[i] + input2[i];
            res.push_back(temp);
        }
    }
    return res;
}
vector<long long> mod (vector<long long> input, long long modulus){
    for(int i = 1; i < input.size(); i++){
     //Int 33 ensure that division and remainder operations do not result in divide-by-zero errors
        if(input[i] >= 0){
            input[i] = input[i] % modulus;
        }
        else{
            input[i] = input[i] % modulus;
            input[i] = input[i] + modulus;
        }
    }
    // Check 0 after the calculation
    for(int i =1; i < input.size(); i++){
        if(input[i] == 0){
            input.erase(input.begin() + i);
            i--;
            input[0]--;
        }
        else{
            break;
        }
    }
    cout <<"After mod, your new polynomial is: ";
    for(auto iter: input){
        cout << iter <<" ";
    }
    cout << endl;
    return input;
}

vector<long long> multi(vector<long long> input1, vector<long long> input2){
    vector<long long> temp;
    vector<long long> res;
    res.push_back(0);
    int input1_size = input1.size() - 1;
    int input1_coe = input1_size - 1;
    int input2_size = input2.size() - 1;
    int input2_coe = input2_size - 1;
    for(int i = 1; i < input1.size(); i++){
        for(int j = 1; j < input2.size(); j++){
            int coe = input1_coe + input2_coe;
            input2_coe--;
            temp.push_back(coe+1);
            temp.push_back(input1[i] * input2[j]);
            for( int z = 0; z < coe; z++){
                temp.push_back(0);
            }
            res = add(temp, res);
            //clear the temp
            temp.clear();
        }
        input1_coe--;
        input2_coe= input2_size - 1;
    }
    cout <<"After multi, your new polynomial is: ";
    for(auto iter: res){
        cout << iter <<" ";
    }
    cout << endl;
    return res;
}

vector<long long> convert_to_long(vector<string> input){
    vector<long long> res;
    long long temp;
    std::string::size_type sz;
    for(auto iter: input){
        temp = stol(iter,&sz);
        res.push_back(temp);
    }
    return res;
}

int main(int argc, char* argv[]) {
    if((argv[1] != NULL)&& (argv[2]!= NULL)){
        // read files
        vector<string> input1 = read_files(argv[1]);
        vector<string> input2 = read_files(argv[2]);
        // convert to int vector
        vector<long long> input1_int = convert_to_long (input1);
        vector<long long> input2_int = convert_to_long (input2);
        // level 1
        vector<long long> res = add(input1_int,input2_int);
        cout <<"After addition, the new polynomial is: ";
        for(auto iter: res){
            cout << iter <<" ";
        }
        cout << endl;
        //  Level 2: modulus calculation
        // convert it to integer first
        if(argv[3] != NULL){
            std::string::size_type sz;
            long long modulus = stol(argv[3], &sz);
            res = mod(res, modulus);
        }
        // level 3 multiply argument 1 and argument 2
            res = multi(input1_int, input2_int);
    }
    return 0;
}
