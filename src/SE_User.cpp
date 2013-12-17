#include "SE_User.hpp"

/* The user should use these functions to hook their modules
 * or other data into the engine.
 *
 * This file is to hook modules into the engine to avoid
 * constructor fiasco. Just include the header, and call
 * its Register_Module function.
 *
 * Anything registered here has no module attatched.
 * Anything that required NO MODULE ID should be put here.
 */

#include "SE/module/Module.hpp"
#include "SE/module/Events.hpp"
#include "SE/module/Event_Defs.hpp"

// Include Headers
#include "SE/debug/Debug.hpp"
#include "SE/module/Thread.hpp"
#include "SE/app/Window.hpp"
#include "SE/filesys/Filesystem.hpp"
#include "SE/gl/OpenGL.hpp"
#include "SE/gl/se_gl.hpp"
#include "SE/menu/Menu.hpp"
#include "SE/os/Input.hpp"
#include "SE/render/Texture.hpp"
#include "SE/render/Font.hpp"
#include "SE/gui/GUI.hpp"
#include "SE/physics/Physics.hpp"
#include "SE/utility/UID.hpp"
#include "SE/cbs/HI_Lang.hpp"


uint DF_Game::Module_Hook()
{
	SE_Debug::Register_Module();
	SE_Thread::Register_Module();
	SE_Window::Register_Module();
	SE_Filesys::Register_Module();
	SE_GL_Interfaces::Register_Module();
	segl::Register_Module();
	SE_Menu::Register_Module();
	SE_Input::Register_Module();
	SE_Texture::Register_Module();
	SE_Font::Register_Module();
	SE_GUI::Register_Module();
	SE_Physics::Register_Module();
	SE_HIL::Register_Module();

	SE_GUI::Set_GUI_Background( User_GUI_Background );

	SE_Physics::Set_Scene( SE_PHYS_SCENE_2 );

	return SE_SUCCESS;
}

uint DF_Game::User_Initialize( const std::vector<std::string>& mArgs )
{
	SE_Menu::Set_Load_Menu( User_Load_Menu );

	// Start on title screen
	S_Engine::Event_Add_Engine( new SE_Events::Event_Var<std::string>( SE_Modules::Mod_GUI, Event_GUI::EVENT_MENU_LOAD, "title" ) );
			

	return SE_SUCCESS;
}

uint DF_Game::User_Cleanup()
{
	return SE_SUCCESS;
}

