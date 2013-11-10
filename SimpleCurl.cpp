/**
All code here adapted (modified as little as possible) from 
www.luckyspin.org
Adaptation by Gary Lewandowski, 14 October 2007.

Original header comments follow.
**/

/*
 * This is a very simple example of how to use libcurl from within 
 * a C++  program. The basic idea is that you want to retrieve the 
 * contents of a web page as a string. Obviously, you can replace 
 * the buffer object with anything you want and adjust elsewhere 
 * accordingly.
 * 
 * Hope you find it useful..
 * 
 * Todd Papaioannou 
 */

#include <string>
#include <iostream>
#include <curl/curl.h>
#include "SimpleCurl.h"

using namespace std;

   int SimpleCurl::writer(char *data, size_t size, size_t nmemb,
                  std::string *buffer)
   {
  // What we will return
     int result = 0;

  // Is there anything in the buffer?
     if (buffer != NULL)
     {
    // Append the data to the buffer
       buffer->append(data, size * nmemb);

    // How much did we write?
       result = size * nmemb;


    //m Vector of URLs within the URL
    //   vector<string> urlArray;
     }

     return result;
   }

   SimpleCurl::SimpleCurl(string url)
   {
	if (getURL(url) == -1) exit(-1);
   }

   int SimpleCurl::getURL(string url)
    {
	     buffer = "";
       // Create our curl handle
       curl = curl_easy_init();

       if (curl)
       {
         // Now set up all of the curl options
         curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
         curl_easy_setopt(curl, CURLOPT_HEADER, 0);
         curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

         // Attempt to retrieve the remote page
         result = curl_easy_perform(curl);

         // Always cleanup
         curl_easy_cleanup(curl);

         // Did we succeed?
         if (result != CURLE_OK)
         {
                cout << "Error: [" << result << "] - " << errorBuffer;
		            return -1;
         }
         return buffer.length();
       }
       return 0;
     }



  

  string SimpleCurl::getRetrievedDocument()
  { 
	return buffer;
  }

