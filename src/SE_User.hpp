#ifndef DF_GAME_SE_USER_DEFS
#define DF_GAME_SE_USER_DEFS

#include "SE/Types.hpp"
#include "SE/menu/Menu.hpp"

namespace DF_Game
{
	uint Module_Hook();
	uint User_Initialize( const std::vector<std::string>& mArgs );
	uint User_Cleanup();

	SE_Menu::Menu_Base* User_Load_Menu( std::string Which );
	void User_GUI_Background();

}


#endif
