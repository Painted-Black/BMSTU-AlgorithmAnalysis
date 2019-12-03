#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int SYMB_NUMBER = 128; // ascii-table

int KMP(const string &text, const string& substring);
int BM(const string &text, const string &pattern);
vector<size_t> slides(const string &pattern);
vector<size_t> preffix(const string &substring);
#endif // SEARCH_H
