#include <string>
#include <iostream>
#include <curl/curl.h>
#include "SimpleCurl.h"
#include <vector>
#include "BreadthFirstTreeMaker.h"
#include <cctype>
#include <algorithm>    // std::find_if
#include "URLGraph.h"

using namespace std;


bool not_url_char(char c)
{
	// characters, in addition to alphanumerics, that can appear in a URL
	static const string url_ch = "~;/?:@=&$-_.+!*'(),";

	// see whether c can appear in a URL and return the negative
	return !(isalnum(c) || find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}



string::const_iterator 
url_end(string::const_iterator b, string::const_iterator e)
{
	return find_if(b, e, not_url_char);
}



/**
*
*	This method finds the URLs within the string and stores them in the vector childrenListOfURLs.
*
**/
int BreadthFirstTreeMaker::URLCollector(const string s)
  	{
      	//vector<string> ret;
      	typedef string::const_iterator iter;
      	iter b = s.begin(), e = s.end();

      	//look through the entire input
      	while(b != e){
       	 	// look for one or more letters followed by ://
       	  	b = url_beg(b, e);
       	 	// if we found it
       	 	if(b != e){
      	    	 //get the rest of URL
      	     	iter after = url_end(b,e);

      	     	// remember the URL
      	     	childrenListOfURLs.push_back(string(b, after));

             	// advance b and check for more URL's on this line
             	b = after;
         	 }        
      	 }
      return 0;
  	}




string::const_iterator 
BreadthFirstTreeMaker::url_beg(string::const_iterator b, string::const_iterator e)
{
	static const string sep = "://";

	typedef string::const_iterator iter;

	// i marks where the seperator was found
	iter i = b;

	while((i = search(i, e, sep.begin(), sep.end())) != e){

		// make sure the seperator isn't at the beginning or end of the line.
		if(i != b && i + sep.size() != e){
			// beg marks the beginning of the protocol-name
			iter beg = i;
			while(beg != b && isalpha(beg[-1]))
				--beg;

			// is there at least one appropriate character befoire and after the seperator
			if(beg != i && !not_url_char(i[sep.size()]))
				return beg;

		}

		// the seperator we found wasn't part of a URL; advance i past this seperator
		i += sep.size();
	}
	return e;

}




/**
*	This is the method which takes the URL. Then uses a simpleCurl to get the HTML file as a string
*	and then uses URLCollector to find the URLs within the HTML string.
**/

BreadthFirstTreeMaker::BreadthFirstTreeMaker()
{
	//This will be the URL that is searched for other URL's within the page.
	originalURL = "http://www.cs.xu.edu/~lewandow";
	//This uses the class SimpleCurl to go through the originalURL and return the page as a string trype
	theCurl.getURL(originalURL);
	//This simply sets the string found in the previous step to the string variable "theActualString".
	string theActualString = theCurl.getRetrievedDocument();
	//This stores the URLs found in "theActualString" into the vector "childrenListOfURLS".
	URLCollector(theActualString);

	URLGraph graph;

	graph.BaseCaseBreadthFirstSearch(originalURL, 4);

	//graph.URLGraph(originalURL, 4);
	
}

/**
*
*	The main of my program which initiates the program.
*
**/

int main() 
{
	BreadthFirstTreeMaker b;

	return 0;
}




/**
*
*  This will be used by the URL graph in order to get the URL's within the URL. Just using this so 
*  the original BreadthFirstTreeMaker can use the example URL "http://www.cs.xu.edu/~lewandow".
*
**/

vector<string> BreadthFirstTreeMaker::BreadthFirstTreeMaker2(string URL)
{
	
	vector<string> childrenListOfURLs2;
	originalURL = URL;
	theCurl.getURL(originalURL);
	string theActualString = theCurl.getRetrievedDocument();
	childrenListOfURLs2 = URLCollector2(theActualString);


	//returns the children vector.
	return childrenListOfURLs2;
}




/**
*
*	This does the same thing as URLCollector except instead of changing the vector
*	found in this class it changes the parameter provided vector.
*
**/

vector<string> BreadthFirstTreeMaker::URLCollector2(const string s)
  	{
      	// Vector to be returned
  		vector<string> retVector;

      	//vector<string> ret;
      	typedef string::const_iterator iter;
      	iter b = s.begin(), e = s.end();

      	//look through the entire input
      	while(b != e){
       	 	// look for one or more letters followed by ://
       	  	b = url_beg(b, e);
       	 	// if we found it
       	 	if(b != e){
      	    	 //get the rest of URL
      	     	iter after = url_end(b,e);

      	     	// remember the URL
      	     	retVector.push_back(string(b, after));

             	// advance b and check for more URL's on this line
             	b = after;
         	 }        
      	 }

      	return retVector;
  	}


