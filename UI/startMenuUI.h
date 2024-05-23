#pragma once
#include <iostream>
#include "selectionUI.h"

static const COORD SELECT_COORDINATES = {1, 1};
//maybe singleton?
class StartMenuUI : public SelectionUI{
public:
    StartMenuUI(COORD coords) : SelectionUI(SELECT_COORDINATES){
    //credit to Alex Wargacki for the artwork
    std::cout << "                            ==(W{==========-      /===-                        \n"
                 "                              ||  (.--.)         /===-_---~~~~~~~~~------____  \n"
                 "                              | \\_,|**|,__      |===-~___                _,-' `\n"
                 "                 -==\\\\        `\\ ' `--'   ),    `//~\\\\   ~~~~`---.___.-~~      \n"
                 "             ______-==|        /`\\_. .__/\\ \\    | |  \\\\           _-~`         \n"
                 "       __--~~~  ,-/-==\\\\      (   | .  |~~~~|   | |   `\\        ,'             \n"
                 "    _-~       /'    |  \\\\     )__/==0==-\\<>/   / /      \\      /               \n"
                 "  .'        /       |   \\\\      /~\\___/~~\\/  /' /        \\   /'                \n"
                 " /  ____  /         |    \\`\\.__/-~~   \\  |_/'  /          \\/'                  \n"
                 "/-'~    ~~~~~---__  |     ~-/~         ( )   /'        _--~`                   \n"
                 "                  \\_|      /        _) | ;  ),   __--~~                        \n"
                 "                    '~~--_/      _-~/- |/ \\   '-~ \\                            \n"
                 "                   {\\__--_/}    / \\\\_>-|)<__\\      \\                           \n"
                 "                   /'   (_/  _-~  | |__>--<__|      |                          \n"
                 "                  |   _/) )-~     | |__>--<__|      |                          \n"
                 "                  / /~ ,_/       / /__>---<__/      |                          \n"
                 "                 o-o _//        /-~_>---<__-~      /                           \n"
                 "                 (^(~          /~_>---<__-      _-~                            \n"
                 "                ,/|           /__>--<__/     _-~                               \n"
                 "             ,//('(          |__>--<__|     /  Dungeon and Dragons--_          \n"
                 "            ( ( '))          |__>--<__|    |                 /' _---_~\\        \n"
                 "         `-)) )) (           |__>--<__|    |               /'  /     ~\\`\\      \n"
                 "        ,/,'//( (             \\__>--<__\\    \\            /'  //        ||      \n"
                 "      ,( ( ((, ))              ~-__>--<_~-_  ~--____---~' _/'/        /'       \n"
                 "    `~/  )` ) ,/|                 ~-_~>--<_/-__       __-~ _/                  \n"
                 "  ._-~//( )/ )) `                    ~~-'_/_/ /~~~~~~~__--~                    \n"
                 "   ;'( ')/ ,)(                              ~~~~~~~~~~                         \n"
                 "  ' ') '( (/                                                                    \n";
    }
private:

};
