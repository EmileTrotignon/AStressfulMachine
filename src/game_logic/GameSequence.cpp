//
// Created by emile on 05/03/19.
//

#include "GameSequence.h"
#include "GameLevel.h"
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

void save_all(){

    TiXmlDocument doc;
    TiXmlElement* msg;
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );

    TiXmlElement * root = new TiXmlElement( "Player" );
    doc.LinkEndChild( root );

    TiXmlElement * level = new TiXmlElement( "Level" );
    root->LinkEndChild( level );
    level->SetAttribute("name", level_name); // c'est quel fonction qui get level_name dans GameLevel

    if(succeeded_levels){ // Toujours pas reconnu.
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