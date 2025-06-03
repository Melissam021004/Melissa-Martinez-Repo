#include "language_model.h"

#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>
#include <cstddef>
#include <cctype>
#include <vector>
#include <map>
#include <tuple>

using std::ifstream;    using std::map;     using std::string;
using std::fstream;     using std::tuple;   using std::vector;
using std::iostream;    using std::endl;    using std::cout;
using std::make_tuple;  using std::get;     

void get_freqs(map< tuple<string, string, string>, int> &freqs, vector<string> filenames){

    string s1 = "<START_1>";
    string s2 = "<START_2>";
    string e1 = "<END_1>";
    string e2 = "<END_2>";


    // iterates through every file
    for(int i = 0; i < (int)filenames.size(); i++){
        ifstream fn(filenames[i]);

        if(!fn){
            continue;
        }

        //setting up variables for loop
        string a = s1;
        string b = s2;
        string c;
        tuple<string, string, string> temp;

        //Loops through every word
        while(fn >> c){
            temp = make_tuple(a, b, c);

            //tuple does not already exist
            if(freqs.find(temp) == freqs.end()){
                freqs[temp] = 1;
            }
            else{
                freqs[temp] = freqs[temp] + 1;
            }

            //preparing for next loop
            a = b;
            b = c;
        }

        freqs[make_tuple(a, b, e1)] = 1;
        freqs[make_tuple(b, e1, e2)] = 1;
    }
}

//Return 0 is a is greater, 1 if b is greater
int comp(tuple<string, string, string> a, tuple<string, string, string> b){

    //Checking first string
    if((get<0>(a)).compare(get<0>(b)) > 0){
        return 0;
    }
    else if((get<0>(a)).compare(get<0>(b)) < 0){
        return 1;
    }

    //Checking second string
    if((get<1>(a)).compare(get<1>(b)) > 0){
        return 0;
    }
    else if((get<1>(a)).compare(get<1>(b)) < 0){
        return 1;
    }

    //Checking third string
    if((get<2>(a)).compare(get<2>(b)) > 0){
        return 0;
    }
    else if((get<2>(a)).compare(get<2>(b)) < 0){
        return 1;
    }
    return 0;
}

void alph_sort(map< tuple<string, string, string>, int> &freqs){
    map< tuple<string, string, string>, int> cp = freqs;
    map< tuple<string, string, string>, int> out;

    while(cp.size() > 0){
        tuple<string, string, string> min = (cp.begin())->first;
        int min_freq = (cp.begin())->second;

        for(auto it = cp.begin(); it != cp.end(); ++it){
            if(comp(min, it->first) == 1){
                min = it->first;
                min_freq = it->second;
            }
        }

        cp.erase(min);
        
        out[min] = min_freq;
    }

    freqs = out;
    
}

void freq_sort(map< tuple<string, string, string>, int> &freqs){
    map< tuple<string, string, string>, int> cp = freqs;

    while(cp.size() > 0){
        tuple<string, string, string> max_tup = (cp.begin())->first;
        int max_freq = (cp.begin())->second;

        for(auto it = cp.begin(); it != cp.end(); ++it){
            if(it->second > max_freq){
                max_tup = it->first;
                max_freq = it->second;
            }
            else if(it -> second == max_freq){
                if(comp(it->first, max_tup) == 1){
                    max_tup = it->first;
                    max_freq = it->second;
                }
            }
        }

        cout << max_freq << " - [" << get<0>(max_tup) << " " << get<1>(max_tup) << " " << get<2>(max_tup) << "]" << endl;

        cp.erase(max_tup);
        
    }

}

void print(map< tuple<string, string, string>, int> &freqs){
    for(auto it = freqs.begin(); it != freqs.end(); ++it){
        cout << it->second << " - [" << get<0>(it->first) << " " << get<1>(it->first) << " " << get<2>(it->first) << "]" << endl;
    }
}

void revprint(map< tuple<string, string, string>, int> &freqs){
    for(auto it = freqs.rbegin(); it != freqs.rend(); ++it){
        cout << it->second << " - [" << get<0>(it->first) << " " << get<1>(it->first) << " " << get<2>(it->first) << "]" << endl;
    }
}

void handle_f_command(map< tuple<string, string, string>, int> &freqs, string x, string y){

    int max_freq = 0;
    string z;

    for(auto it = freqs.begin(); it != freqs.end(); ++it){
        if((get<0>(it->first)).compare(x) == 0){
            if((get<1>(it->first)).compare(y) == 0){
                if(it->second > max_freq){
                    max_freq = it->second;
                    z = get<2>(it->first);
                }
            }
        }
        else{
            //first word does not match
            continue;
        }
    }
    if(max_freq == 0){
        //None found
        cout << "No trigrams of the form [" << x << " " << y << " ?]" << endl;
    }
    else{
        cout << max_freq << " - [" << x << " " << y << " " << z << "]" << endl;
    }
}