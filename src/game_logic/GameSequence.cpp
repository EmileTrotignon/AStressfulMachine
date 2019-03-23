//
// Created by emile on 05/03/19.
//

#include "GameSequence.h"
#include "../tinyxml/tinyxml.h"


// Function prototypes
void save_all(); // Save the complete file
void load_all(); // Load the different values

using namespace std;

GameSequence::GameSequence(const string &savename_, const string &gamefiles_dir_) : savename(savename_),
                                                                                    gamefiles_dir(gamefiles_dir_),
                                                                                    current_level(nullptr)
{
    available_levels = filesystem_ls(gamefiles_dir + "/levels");
    conform_save_to_gamefiles();
    load_from_save();

    for (int i = 0; i < available_levels.size(); i++)
    {
        levels.push_back(new GameLevel(gamefiles_dir, available_levels[i], attempts[i]));
    }
}

void GameSequence::select_level(int level_index)
{
    current_level = levels.begin() + level_index;
}

vector<string> GameSequence::get_available_levels() const
{
    return available_levels;
}

vector<GameLevel *>::iterator GameSequence::get_current_level()
{
    return current_level;
}

void GameSequence::load_from_save()
{
    // Todo : This should initialize :
    //    vector<bool> attempted;
    //    vector<bool> succeeded_levels; // vector<bool> succeeded_levels {false};
    //    vector<vector<string>> attempts;
    //    vector<vector<float>> average_speed;
    //    vector<vector<float>> average_memory_use;
}

void GameSequence::conform_save_to_gamefiles()
{
    // Todo : This should create new folders for levels that does not have one

}



/*
//======================================================================

void save_in_file(string &jeu){ // A CHAQUE DEMANDE DE SAUVEGARDE, createFile PUIS copy
    // int fileincrement=0;
   // string x = std::to_string(fileincrement);
    //string save = "save.xml";
    //createFile(save);
    //copFile(save);
    addName(jeu);
    while(!succeeded_levels){
        addTry(jeu);
        addAverage(jeu);
    }
    if(succeeded_levels){
        succeededLevel(jeu);
    }
   // fileincrement++;
}

//======================================================================

void createFile(string &name){ // &name : to create the file with a name.
    std::ofstream o(name+".xml");

    //return fstream
    //o << "Hello, World\n" << std::endl;
}

//======================================================================


//======================================================================

void copFile(string &name){ // copy-a-text-file-into-another // &name = name of the new file empty
    ifstream infile;
    infile.open("/data/saves/save.xml");
    ofstream outfile("/data/saves/"+name+".xml");
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

    string found, line;
    fstream myfile ("/data/saves/"+jeu+".xml");

    if (myfile.is_open()) // file opened
    {
        found = "<lvl ";
        while(getline(myfile,line)){ // Not at the end of the file
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
    fstream myfile ("/data/saves/"+jeu+".xml");
    if (myfile.is_open()) // file opened
    {
        if(succeeded_levels){
            found = "<congrats>";

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

    fstream myfile ("/data/saves/"+jeu+".xml");
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

    fstream myfile ("/data/saves/"+jeu+".xml"); //Path of the XML file
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


void load_from_save(string &jeu){
   // string filename = "save.xml";
    string tag = "player";
// string tag = "object";
    bool stripOtherTags = true;

    string text = getFile( jeu );
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
*/

void save_all(){

    TiXmlDocument doc;
    TiXmlElement* msg;
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );

    TiXmlElement * root = new TiXmlElement( "Player" );
    doc.LinkEndChild( root );

    TiXmlElement * level = new TiXmlElement( "Level" );
    root->LinkEndChild( level );
    level->SetAttribute("name", "Nom_du_niveau"); // Variable contenant le nom_du_niveau à ajouter

    if(succeeded_levels){ // toujours pas reconnu.
        TiXmlElement * congrats = new TiXmlElement("Congrats");
        congrats->SetValue("Yes" ); // A voir si on change par la variable elle même ou pas
        level->LinkEndChild( congrats );
    }
    else{
        TiXmlElement * congrats = new TiXmlElement("Congrats");
        congrats->SetValue("No" );
        level->LinkEndChild( congrats );
    }

    TiXmlElement * avg = new TiXmlElement("Avg");
    avg->SetValue("  " );
    level->LinkEndChild( avg );

    //dump_to_stdout( &doc );
    //doc.SaveFile( save_name );
    doc.SaveFile( "/data/saves/save.xml" );
}

void load_all(){
    TiXmlDocument doc( "/data/saves/save.xml" );
    doc.LoadFile();

    TiXmlElement *l_pRootElement = doc.RootElement();

    if( NULL != l_pRootElement )
    {
        TiXmlElement *l_level = l_pRootElement->FirstChildElement( "Level" );

        if ( NULL != l_level )
        {
            std::cout << l_level->GetText(); // display the hole file directly

            TiXmlElement *l_congrats = l_level->FirstChildElement( "Congrats" );

            if ( NULL != l_congrats )
            {
                std::cout << l_congrats->GetText();
            }
            //while( l_level )
            //{
                TiXmlElement *l_avg = l_level->FirstChildElement( "Avg" );

                if ( NULL != l_avg )
                {
                    std::cout << l_avg->GetText();
                }

                std::cout << std::endl;

                //l_level = l_level->NextSiblingElement( "level" ); If there was another <level> in the same file
            //}
        }
    }
}