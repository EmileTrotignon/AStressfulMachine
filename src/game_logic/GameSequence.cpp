//
// Created by emile on 05/03/19.
//

#include "GameSequence.h"
#include "../tinyxml/tinyxml.h"
#include <filesystem>


// Function prototypes
void save_all(); // Save the complete file
void load_all(); // Load the different values

using namespace std;
namespace fs = std::filesystem;


GameSequence::GameSequence(const string &savename_, const string &gamefiles_dir_) : savename(savename_),
                                                                                    gamefiles_dir(gamefiles_dir_),
                                                                                    current_level(nullptr)
{
    available_levels = filesystem_ls(gamefiles_dir + "/levels");
    conform_save_to_gamefiles();
    levels = vector<GameLevel *>();
    for (int i = 0; i < available_levels.size(); i++)
    {
        auto gl = new GameLevel(gamefiles_dir, available_levels[i]);
        levels.push_back(gl);
    }
    load_from_save();

}

void GameSequence::select_level(int level_index)
{
    if (levels.begin() <= current_level && current_level < levels.end())
    {

    }
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
    //    vector<vector<float>> average_speed;
    //    vector<vector<float>> average_memory_use;

    for (int i = 0; i < available_levels.size(); i++) // Fills attempts with empty string.
        // Todo : fill attempts with actual attempts
    {
        levels[i]->attempts = {};
        for (int j = 0; j < 5; j++)
        {
            levels[i]->attempts.push_back(
                    file_to_string("data/saves/" + savename + "/" + available_levels[i] + "/" + to_string(j)));
        }
    }
    load_to_xml();
}


void GameSequence::conform_save_to_gamefiles()
{
    // Todo : This should create new folders for levels that does not have one
    for (auto &l:available_levels)
    {
        fs::create_directory("data/saves/" + savename + "/" + l);
        for (int i = 0; i < 5; i++)
        {
            if (!fs::exists("data/saves/" + savename + "/" + l + "/" + to_string(i)))
            {
                ofstream a("data/saves/" + savename + "/" + l + "/" + to_string(i));
                a.close();
            }
        }
    }
}

void GameSequence::save_to_save()
{
    // Save all attempts for all levels
    for (int i = 0; i < available_levels.size(); i++)
    {
        for (int j = 0; j < levels[i]->attempts.size(); j++)
        {
            string_to_file(levels[i]->attempts[j],
                           "data/saves/" + savename + "/" + levels[i]->get_level_name() + "/" + to_string(j));
        }
    }
    save_to_xml();
}



void GameSequence::save_to_xml(){

    TiXmlDocument doc;
    //TiXmlElement* msg;
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );

    TiXmlElement * root = new TiXmlElement( "Player" );
    doc.LinkEndChild( root );

    TiXmlElement * level = new TiXmlElement( "Level" );
    root->LinkEndChild( level );
    level->SetAttribute("name", "Nom_du_niveau");

    if(succeeded_levels[1]==true){
        TiXmlElement * congrats = new TiXmlElement("Congrats");
        congrats->SetValue("True" ); // A voir si on change par la variable elle même
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

void GameSequence::load_to_xml(){
    TiXmlDocument doc( "/data/saves/save.xml" );
    doc.LoadFile();
    if(!doc.LoadFile())
    {
        throw runtime_error(doc.ErrorDesc());
    }
    else { // May be deleted if this verrification have problems.
        TiXmlElement *l_pRootElement = doc.RootElement();

        if (nullptr != l_pRootElement) {
            TiXmlElement *l_level = l_pRootElement->FirstChildElement("Level");

            if (nullptr != l_level) {
                std::cout << l_level->GetText(); // display the whole file directly

                TiXmlElement *l_congrats = l_level->FirstChildElement("Congrats");

                if (nullptr != l_congrats) {
                    std::cout << l_congrats->GetText();
                }
                //while( l_level )
                //{
                TiXmlElement *l_avg = l_level->FirstChildElement("Avg");

                if (nullptr != l_avg) {
                    std::cout << l_avg->GetText();
                }

                std::cout << std::endl;

                //l_level = l_level->NextSiblingElement( "level" ); If there was another <level> in the same file
                //}
            }
        }
    }
}
