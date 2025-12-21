#include "language_model.h"
#include <map>
#include <tuple>
using std::ifstream;    using std::map;     using std::cerr;
using std::fstream;     using std::tuple;
using std::iostream;    using std::get;
using std::cout;        using std::endl;
using std::vector;      using std::string;

int main(int argc, char **argv) {

    //No arguments were provided
    if(argc < 2){
        cerr << "Invalid file list: " << endl;
        return 1;
    }

    //Opening the file with the names of the other files
    ifstream bigfile(argv[1]);

    //File did not open
    if(!(bigfile)){
        cerr << "Invalid file list: " << argv[1] << endl;
        return 1;
    }

    //Contains the names of the file names
    vector<string> filenames;
    string temp;

    //Storing the valid file names in a vector
    while(bigfile >> temp){

        //Attempting to open the file
        ifstream a(temp);

        //Checking if the file opened
        if(a){
            filenames.push_back(temp);
        }
        else{
            cerr << "Invalid file: " << temp << endl;
        }

    }

    //Map of trigrams and their frequencies
    map< tuple<string, string, string>, int> freqs;

    //Getting the trigrams and their frequencies
    get_freqs(freqs, filenames);

    //no second argument provided
    if(argc < 3){
        cerr << "Invalid command: valid options are a, d, c, and f" << endl;
        return 1;
    }

    //checking if command is longer than one letter
    string command = argv[2];
    if(command.length() > 1){
        cerr << "Invalid command: valid options are a, d, c, and f" << endl;
        return 1;
    }

    //executing different commands
    char com = *argv[2];
    switch(com){
        case('a'):
            alph_sort(freqs);
            print(freqs);
            break;
        case('d'):
            alph_sort(freqs);
            revprint(freqs);
            break;
        case('c'):
            freq_sort(freqs);
            break;
        case('f'):
            if(argc < 5){
                cerr << "Invalid argument list: f requires two additional command-line arguments" << endl;
                return 1;
            }
            handle_f_command(freqs, argv[3], argv[4]);
            break;
        default:
            cerr << "Invalid command: valid options are a, d, c, and f" << endl;
            return 1;
            break;
    }

    return 0;
}