#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <cstddef>
#include <cctype>
#include <vector>
#include <tuple>
#include <map>

using std::vector;      using std::tuple;
using std::string;      using std::map;

/* get_freqs
 * Goes through the files in filenames and either creates tuples with a freq of 1
 * or updates the existing tuple's frequency by incrementing by one. These tuples
 * and their frequencies are saved in the map freqs.
 */
void get_freqs(map< tuple<string, string, string>, int> &freqs, vector<string> filenames);

/* comp
 * compares two tuples to see which one comes first lexicographically in ascending order.
 * Will return 0 if tuple a comes first and 1 if tuple b comes first.
 */
int comp(tuple<string, string, string> a, tuple<string, string, string> b);

/* alph_sort
 * Sorts the passed freqs argument into lexicographical ascending order.
 */
void alph_sort(map< tuple<string, string, string>, int> &freqs);

/* freq_sort
 * Sorts the passed freqs argument into frequency order.
 * Will sort alphabetically if the frequencies are the same.
 */
void freq_sort(map< tuple<string, string, string>, int> &freqs);

/* print
 * Will print the passed freqs argument in the order it is already in.
 * The frequency and then the tuple will be printed.
 */
void print(map< tuple<string, string, string>, int> &freqs);

/* revprint
 * Will reverse print the passed freqs argument.
 * The frequency and then the tuple will be printed.
 */
void revprint(map< tuple<string, string, string>, int> &freqs);

/* handle_f_command
 * Handles the f command by finding the most frequently occuring tuple
 * that begins with strings x and y and printing it. Ties are broken alphabetically. 
 * If there's no matches, a message will be printed indicating so.
 */
void handle_f_command(map< tuple<string, string, string>, int> &freqs, string x, string y);

#endif