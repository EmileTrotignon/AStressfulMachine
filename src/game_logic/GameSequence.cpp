#include <utility>

//
// Created by emile on 05/03/19.
//

#include "GameSequence.h"
#include "../tinyxml/tinyxml.h"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;


GameSequence::GameSequence(string savename_, fs::path saves_dir_, const fs::path &gamefiles_dir_) :
        saves_dir(move(saves_dir_)),
        savename(move(savename_)),
        gamefiles_dir(gamefiles_dir_),
        current_level(nullptr)
{
    available_levels = filesystem_ls(gamefiles_dir + "/levels");
    conform_save_to_gamefiles();
    levels = map<string, GameLevel *>();
    for (const string &level_name:available_levels)
    {
        auto gl = new GameLevel(gamefiles_dir, level_name);
        levels[level_name] = gl;
    }
    load_from_save();

}

void GameSequence::select_level(const string &level_name)
{
    current_level = levels[level_name];
}

vector<string> GameSequence::get_available_levels() const
{
    return available_levels;
}

GameLevel *GameSequence::get_current_level()
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

    for (auto s : levels) // Fills attempts with empty string.
        // Todo : fill attempts with actual attempts
    {
        s.second->attempts = {};
        for (int j = 0; j < 5; j++)
        {
            s.second->attempts.push_back(
                    file_to_string(saves_dir / savename / s.second->get_level_name() / to_string(j)));
        }
    }
    //load_from_xml();
}


void GameSequence::conform_save_to_gamefiles()
{
    // Todo : This should create new folders for levels that does not have one
    if (!fs::exists(saves_dir / "save.xml"))
    {
        ofstream a(saves_dir / savename / "save.xml");
        a.close();
    }
    for (auto &l:available_levels)
    {
        fs::create_directory(saves_dir / savename / l);
        for (int i = 0; i < 5; i++)
        {
            if (!fs::exists(saves_dir / savename / l / to_string(i)))
            {
                ofstream a(saves_dir / savename / l / to_string(i));
                a.close();
            }
        }
    }
}

void GameSequence::save_to_save()
{
    // Save all attempts for all levels
    for (auto p : levels)
    {
        for (int j = 0; j < p.second->attempts.size(); j++)
        {
            string_to_file(p.second->attempts[j],
                           saves_dir / savename / p.second->get_level_name() / to_string(j));
        }
    }
    //save_to_xml();
}


void GameSequence::save_to_xml()
{

    TiXmlDocument doc;
    //TiXmlElement* msg;
    auto *decl = new TiXmlDeclaration("1.0", "", "");
    doc.LinkEndChild(decl);

    auto *root = new TiXmlElement("Player");
    doc.LinkEndChild(root);

    auto *level = new TiXmlElement("Level");
    root->LinkEndChild(level);
    level->SetAttribute("name", "Nom_du_niveau");

    if (succeeded_levels[1] == true)
    {
        auto *congrats = new TiXmlElement("Congrats");
        congrats->SetValue("True"); // A voir si on change par la variable elle même
        level->LinkEndChild(congrats);
    } else
    {
        auto *congrats = new TiXmlElement("Congrats");
        congrats->SetValue("No");
        level->LinkEndChild(congrats);
    }


    auto *avg = new TiXmlElement("Avg");
    avg->SetValue("  ");
    level->LinkEndChild(avg);

    //dump_to_stdout( &doc );
    //doc.SaveFile( save_name );
    doc.SaveFile((saves_dir / savename / "save.xml").c_str());
}

void GameSequence::load_from_xml()
{
    TiXmlDocument doc((saves_dir / savename / "save.xml").c_str());
    doc.LoadFile();
    if (!doc.LoadFile())
    {
        throw runtime_error(doc.ErrorDesc());
    } else
    { // May be deleted if this verrification have problems.
        TiXmlElement *l_pRootElement = doc.RootElement();

        if (nullptr != l_pRootElement)
        {
            TiXmlElement *l_level = l_pRootElement->FirstChildElement("Level");

            if (nullptr != l_level)
            {
                std::cout << l_level->GetText(); // display the whole file directly

                TiXmlElement *l_congrats = l_level->FirstChildElement("Congrats");

                if (nullptr != l_congrats)
                {
                    std::cout << l_congrats->GetText();
                }
                //while( l_level )
                //{
                TiXmlElement *l_avg = l_level->FirstChildElement("Avg");

                if (nullptr != l_avg)
                {
                    std::cout << l_avg->GetText();
                }

                std::cout << std::endl;

                //l_level = l_level->NextSiblingElement( "level" ); If there was another <level> in the same file
                //}
            }
        }
    }
}
