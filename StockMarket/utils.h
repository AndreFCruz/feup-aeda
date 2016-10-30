#pragma once

#include <iostream>
#include <string>

#include "Date.h"

using namespace std;


unsigned short int getUnsignedShortInt(unsigned short int min, unsigned short int max, string msg = "", size_t width = 0);

template <class numT>
numT getValue(string msg = "", size_t width = 0);

Date getDate(string msg = "");

bool validFile(const string file);

char toUpper(char c);

string toUpper(string s);

void trim(string &value);

void showTitle(string title, ostream& out = cout);

