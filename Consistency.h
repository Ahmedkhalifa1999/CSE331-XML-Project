/********************************************************
 * [FILE NAME]: consistency.h
 *
 * [Author]: Ismail Amr
 *
 * [CREATED ON]: Dec 12, 2021
 *
 * [DESCRIPTION]: Header file for consistency functions
 *******************************************************/

#ifndef CONSISTENCY_H_
#define CONSISTENCY_H_


#include <iostream>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;
/*************************************************
 *            Function Prototypes                *
 *************************************************/


 /*****************************************************************
  * [Function_Name]: detection
  *
  * [Description]: -> this functions loops over xml string by character and checks for
  *		 opening and closing tags in terms of correctness and matching.
  *
  *	  -> this function stores the opening tags and check them against closing tags.
  *	  -> if all match the content of stack is cleared and the function returns true.
  *	  -> if any tag is missing, the stack is not empty and the function returns false.
  *
  *	   time complexity = O(n)
  *    space complexity = O(n)
  *    where n is size of the string.
  *
  * [in]: string of xml file
  *
  * [return]: boolean to indicate whether the xml is valid or not
  *
  *****************************************************************/
bool detection(string& xml);

/*****************************************************************
 * [Function_Name]: correction
 *
 * [Description]: This is a general solution to make xml valid.
 *
 *       this function takes errortag stack from detection function
 *		 and insert missing tags in their suitable location to make xml valid
 *
 *       time complexity= O(n) where n is the size of errortag stack
 *
 * [in]: string of invalid xml file
 *
 * [return]: string of valid xml file
 *
 *****************************************************************/
string correction(string& xml);

bool locate(string tagname, string& xml, char type);

#endif /* CONSISTENCY_H_ */
