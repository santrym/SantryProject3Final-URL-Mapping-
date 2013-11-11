#include <string>
#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <cctype>
#include <algorithm>    // std::find_if
#include <queue>
#include <iterator>
#include "URLGraph.h"
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

URLGraph::URLGraph()
{
	//sets switch to true aka 1.
	boolint = 1;
}


int URLGraph::BaseCaseBreadthFirstSearch(string parentURL, int dep)
{
	// base-case type function to make the original URL's depth equal to zero in the depthMap.
	depthMap.insert( std::pair<string,int> (parentURL, 0));
	// add parentURL to the queue
	queue.push(parentURL);

	//this performs the depth first search using the given parameters.
	// when the given depth is reached boolint will turn to 0, and the while loop will end.
	while(boolint == 1){
		BreadthFirstSearch(queue.front(), dep);
		queue.pop();
	}


	// Itorates throught the adjacency map, adjMap, and prints out the URL's and their children.

	map<string, vector<string> >::iterator p;
  
  	for(p = adjMap.begin(); p != adjMap.end(); p++) {
    	cout << "********" << p->first << "*******"  <<" => children:" << endl;
    	for(std::vector<string>::iterator it = p->second.begin(); it != p->second.end(); ++it){
    		cout << "   " + p->second.find(p) << endl;
    	}

  }

  return 0;
}




int URLGraph::BreadthFirstSearch(string parentURL, int dep)
{

	//inserts the parentURL into the colorMap and colors it yellow to indicate that it has been checked for neighbors/children.
	//colorMap.insert( std::pair<string, string> (parentURL, yellow));
	
	//stores parentURL
	string currentURL = parentURL;
	
	//stores dep in depth.
	int depth = dep;
	
	// creates a BreadthFirstTreeMaker object.
	BreadthFirstTreeMaker childFinder;
	
	// Retrieves the children/neighbors of the currentURL and stores them in a vector "children".
	vector<string> children = childFinder.BreadthFirstTreeMaker2(currentURL);
	
	// stores the parent's depth.
	int parentDepth = depthMap.find(currentURL)->second;
	

	// Add the children to the depthMap so their depth is one greater than their parent's depth.                 
    for(std::vector<string>::iterator it = children.begin(); it != children.end(); ++it){
        //checks if children are already in depthMap. If they are do nothing, if not add it, with depth equal
        //to their parents depth + 1.
        if (depthMap.find(*it) == depthMap.end()) {
            // add child to map and set it's depth.
            depthMap.insert( std::pair<string,int> (*it, parentDepth + 1));
        } else {
            //nothing
        }
    }


    vector<string> adjChildren;

    //This for loop checks if children are already colored, and if not are added to the colorMap, queue, and
    // the adjChildren vector.
	for(std::vector<string>::iterator it = children.begin(); it != children.end(); ++it) {
        //checks if URL in children is in the color map, and if not it is added.
        if (colorMap.find(*it) == colorMap.end()) {
            // if children not in color map, add it and color it yellow. Then add it to the queue.
            adjChildren.push_back(*it);
            colorMap.insert( std::pair<string,string> (*it, "yellow"));
            queue.push(*it);
        } else {
            //nothing
        }
    }

    //For when the adjChildren vector is filled, it is added as the parentURL's children in the adjMap.
    adjMap.insert( std::pair<string,string> (parentURL, adjChildren));	

	
	//Test the depth. If too deep it will end the process established in the URLGraph method.
	if(parentDepth >= depth){
		boolint = 0;
	}


	return 0;
}





