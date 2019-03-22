//
// Created by emile on 05/03/19.
//

#include "GameSequence.h"


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <filesystem>

#define _SECOND ((int64) 10000000)
#define _MINUTE (60 * _SECOND)
#define _HOUR   (60 * _MINUTE)
#define _DAY    (24 * _HOUR)


using namespace std;

/*typedef struct _FILETIME {

    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME;
*/
// Function prototypes for save
void createFile(string &name); // Create a file named.
void copFile(); // Copy the whole code from processName() to createFile()
void addName(); // Add a nametag in the XML
void succeededLevel(); // Add succeededLevel
void addTry(); // Add the attempts.
void addAverage(); // Add The average.

// Function prototypes for load
string getFile( string filename );                         // Reads whole file into a string buffer
vector<string> getData( const string &text, string tag );  // Gets collection of items between given tags
void stripTags( string &text );                            // Strips any tags





GameSequence::GameSequence(const string &savename, const string &gamefiles_dir_) : gamefiles_dir(gamefiles_dir_),
                                                                                   current_level(nullptr)
{
    available_levels = filesystem_ls(gamefiles_dir + "/levels");
}

void GameSequence::select_level(const string &level)
{
    delete current_level;
    current_level = new GameLevel(gamefiles_dir, level);
}

vector<string> GameSequence::get_available_levels() const
{
    return available_levels;
}

GameLevel *GameSequence::get_current_level()
{
    return current_level;
}




//======================================================================

void save_in_file(){ // A CHAQUE DEMANDE DE SAUVEGARDE, createFile PUIS copy
    int fileincrement=0;
    string x = std::to_string(fileincrement);
    string save = "save";
    createFile(save+x);
    copFile(save+x);
    addName();
    while(!succeeded_levels){
        addTry();
        addAverage();
    }
    if(succeeded_levels){
        succeededLevel();
    }
    fileincrement++;
}

//======================================================================

void createFile(string &name){ // &name : to create the file with a name.
    std::ofstream o(name".xml");

    //o << "Hello, World\n" << std::endl;
}

//======================================================================


//======================================================================

void copFile(string &name){ // copy-a-text-file-into-another // &name = name of the new file empty
    ifstream infile;
    infile.open("/data/saves/save.xml");
    ofstream outfile("/data/saves/"name".xml");
    string content = "";
    int i;

    for(i=0 ; infile.eof()!=true ; i++) // get content of infile
        content += infile.get();

    i--;
    content.erase(content.end()-1);     // erase last character

    cout << i << " characters read...\n";
    infile.close();

    outfile << content;                 // output
    outfile.close();
}

//======================================================================

// &jeu pour pouvoir trouver le nom à mettre

void addName(string &jeu){

    string found, line,x;
    ofstream myfile ("/data/saves/"jeu".xml");
    if (myfile.is_open()) // file opened
    {
        found = "<lvl ";
        line=myfile.getline(myfile,x);


        while(getline(file,line)){ // Not at the end of the file
            if(found.compare(line)==0){// compare found with the line to get the exact position.
                myfile << " <lvl name='level '" << current_level <<'\n';

            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

}

//======================================================================

void succeededLevel(string &jeu){
    string found, line;
    ofstream myfile ("/data/saves/jeu.xml");
    if (myfile.is_open()) // file opened
    {
        if(succeeded_levels){
            found = "<congrats>"

            while(getline(myfile,line)){ // Not at the end of the file
                if(found.compare(line)==0){// compare found with the line to get the exact position.
                    myfile << "  <congrats>"<< succeeded_levels <<"</congrats>\n";
                }
            }
            myfile.close();
        }
        else cout << "Unable to open file";
    }
}

//======================================================================

void addTry(string &jeu){ // Add all of the tests the player send

    string found,line;

    ofstream myfile ("/data/saves/"+jeu+".xml");
    if (myfile.is_open()) // file opened
        // if()
    {
        found = "<attempts>";

        while(getline(myfile,line)){ // Not at the end of the file
            if(found.compare(line)==0){// compare found with the line to get the exact position.
                //myfile << "  <trial>\n";
                myfile << "    <attempt>\n";
                myfile << "     " << attempts << '\n';
                myfile << "    </attempt>\n";
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

}

//======================================================================

void addAverage(string &jeu){ // Add all of the tests the player send

    string found,line; // Word to find

    ofstream myfile ("/data/saves/"+jeu+".xml"); //Path of the XML file
    if (myfile.is_open()) // file opened
    {
        found = "</attempt>";

        while(getline(myfile,line)){ // Not at the end of the file
            if(found.compare(line)==0){// compare found with the line to get the exact position.
                //myfile << " <lvl> \n";
                myfile << " <avg>\n";
                myfile << "   " << average_speed  << '\n'; // variable who insert the average.
                myfile << "   " << average_memory_use  << '\n'; // variable who insert the average.
                myfile << " </avg>\n";
                //myfile << " </lvl>\n";
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

}

//======================================================================


        //  LOAD FROM SAVE.


//======================================================================


void load_from_save(){
    string filename = "jeu.xml";
    string tag = "level";
// string tag = "object";
    bool stripOtherTags = true;

    string text = getFile( filename );
    vector<string> all = getData( text, tag );
    for ( string &s : all )
    {
        if ( stripOtherTags ) stripTags( s );
        cout << s << '\n';
    }
}


//======================================================================


string getFile( string filename )
{
    string buffer;
    char c;

    ifstream in( filename );   if ( !in ) { cout << filename << " not found";   exit( 1 ); }
    while ( in.get( c ) ) buffer += c;
    in.close();

    return buffer;
}


//======================================================================


vector<string> getData( const string &text, string tag )
{
    vector<string> collection;
    unsigned int pos = 0, start;

    while ( true )
    {
        start = text.find( "<" + tag, pos );   if ( start == string::npos ) return collection;
        start = text.find( ">" , start );
        start++;

        pos = text.find( "</" + tag, start );   if ( pos == string::npos ) return collection;
        collection.push_back( text.substr( start, pos - start ) );
    }
}


//======================================================================


void stripTags( string &text )
{
    unsigned int start = 0, pos;

    while ( start < text.size() )
    {
        start = text.find( "<", start );    if ( start == string::npos ) break;
        pos   = text.find( ">", start );    if ( pos   == string::npos ) break;
        text.erase( start, pos - start + 1 );
    }
}


//======================================================================
