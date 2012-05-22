/*
 * string_utilities.hpp
 *
 *  Created on: May 4, 2011
 *      Author: ethan
 */

#ifndef STRING_UTILITIES_HPP_
#define STRING_UTILITIES_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>  // For exit and transform

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;

// remove leading and trailing spaces
inline string trim(string source)
{
	string t = " ";
  source.erase( source.find_last_not_of(t) + 1);
  source.erase(0 , source.find_first_not_of(t) );
  return source;
}

// remove all non-alphabetic characters from the string
inline string removeNonAlpha(string source) {
	string returnStr;
  for (string::iterator it=source.begin(); it<source.end(); it++) {
		if ( isalpha(*it)) {
			returnStr.append(1,*it);
		}
  }
  return returnStr;
}

// Remove multiple white spaces in a row
inline string removeMultipleSpaces(string source)
{
  string search = "  "; // this is 2 spaces
  size_t index;

  // remove 1 character from the string at index
  while( (index = source.find(search)) != string::npos ){
    source.erase(index,1);
  }

  return source;
}

string truncateString(string s) {
  if (s.size() > 30) {
    s = s.substr(0,27);     // Change it to the first 27 chars
    s.append("...",3);  // + "..."
  }
  return s;
}



  // Extract strings from a text file, one string per line.
  vector<string> getLinesFromFile(string filename) {

    vector<string> lines;
    ifstream inFile(filename.c_str());
    if (!inFile) {
      cerr << "File does not exist: " << filename << endl;
      exit(0);
    }
    string line;

    while( getline(inFile,line) ) {
      line = removeNonAlpha(line); // remove all non-alphabetic characters
      line = trim(line);            // trim opening & trailing whitespace
      line = removeMultipleSpaces(line); // Remove multiple spaces
      // convert to upper case
      std::transform(line.begin(), line.end(),line.begin(), ::toupper);

      if (line.length() > 0) {  // If not an empty string
        lines.push_back(line);  // add it
      }
    }
    inFile.close();
    return lines;
  }
#endif /* STRING_UTILITIES_HPP_ */
