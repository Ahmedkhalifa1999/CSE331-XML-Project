#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*
*Function to repeat a string n times its used to repeat tabs
*time complexity = O(n)
*space complexity = O(n)
*/
string repeat(string s, int n) {
    string repeat;
    for (int i = 0; i < n; i++)
        repeat += s;

    return repeat;
}

//Function to prettify the XML file by keeping the indentation for each level

void prettifying(string* text)
{
    
    int flagt = 1;                //flag for the number of tabs  
    //adding spaces at the end of the string to make the loop in prettifying work
    text->insert((text->end()), ' ');
    text->insert((text->end()), ' ');
    long l = text->size()-2;
    string t("    ");
    string n("\n");
    string s = "";                //creating new string to hold the old string modified
	for (long i = 0; i < l; i++)  //looping on the string
	{

        if (text->at(i) == '>' && text->at(i + 2) != '/')     //tag closing
        {
            s = s + text->at(i);
            if (text->at(i + 1) == '<')                      //tag opening
            {
                s += n;                                      //adding new line
                s += repeat(t, flagt);                       //adding tab
                flagt++;
            }
            else                                             //data
            {
                s += n;
                s += repeat(t, flagt);
            }
        }

        else if (text->at(i) == ' ' && text->at(i + 1) == '<')  //removing spaces before opening tag
        {
            continue;
        }
   
        //closing tags 

        else if ((text->at(i) == '<' && text->at(i + 1) == '/') || (text->at(i) == '<' && text->at(i + 1) == ' ' && text->at(i + 2) == '/') || (text->at(i) == '/' && text->at(i + 1) == '>') || (text->at(i) == '?' && text->at(i + 1) == '>'))
        {


            s += n;
            s += repeat(t, flagt - 1);
            s = s + text->at(i);
            flagt--;

        }
        //else if (text->at(i) == ',')     //start new line after , in the data for better shape
        //{
        //    s = s + text->at(i);
        //    s += n;
        //    s += repeat(t, flagt);
        //}
        else
        {
            s = s + text->at(i);
        }
    }
    *text = s;                          //modifying the old string with new one
}
