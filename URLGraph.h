#ifndef URLGRAPH_H
#define URLGRAPH_H 
#include <string>
#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <cctype>
#include <algorithm>    // std::find_if
#include <queue>
#include <map>
#include <iterator>
#include "BreadthFirstTreeMaker.h"
#include "SimpleCurl.h"

using namespace std;

/**
*
*	URLGraph
*
*	Mike Santry
*	11/10/2013
*
*	This class is Used to create a basic mapping of URLs found within other URL's HTTP files starting from one parent URL. This code should
*	make it possible to see the connections between URLs and the distances, or number of links between each page is.
*
*
**/


class URLGraph
{

private:

	// map for the actual URLs and their adjacency.
	map<string, vector<string> > adjMap;

	//holds the color of the URL. Used for the Breadth-First-Search.
	map<string, string> colorMap;

	//
	map<string, vector<string> > BreadthFirstSearchMap;

	//holds the level on which the URLs were found.
	map<string, int> depthMap;

	//The queue
	queue<string> queue;

	//The switch for when depth is met.
	int boolint; 





public:

	URLGraph(string parentURL, int depth);

	int BreadthFirstSearch(string parentURL, int depth);

	int BaseCaseBreadthFirstSearch(string parentURL, int dep)

};


#endif


