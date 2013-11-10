#ifndef BREADTHFIRSTTREEMAKER_H
#define BREADTHFIRSTTREEMAKER_H
#include <string>
#include <iostream>
#include <curl/curl.h>
#include "SimpleCurl.h"
#include <vector>
#include <cctype>
#include <algorithm>    // std::find_if
#include "URLGraph.h"
#include "BreadthFirstTreeMaker.h"

using namespace std;

class BreadthFirstTreeMaker
{

private:
	// holds the URLs that are found in the given URL 
	vector<string> childrenListOfURLs;

	// holds the simpleCurl
	SimpleCurl theCurl;

	// holds original URL.
	string originalURL;

public:

	int URLCollector(const string s);

  	BreadthFirstTreeMaker();

  	//bool not_url_char(char c);

  	//string::const_iterator 
  	//string::const_iterator url_end(string::const_iterator b, string::const_iterator e);

  	//string::const_iterator 
  	string::const_iterator url_beg(string::const_iterator b, string::const_iterator e);


  	//BreadthFirstTreeMaker();

  	vector<string> BreadthFirstTreeMaker2(string URL);

  	vector<string> URLCollector2(const string s);

};


#endif


