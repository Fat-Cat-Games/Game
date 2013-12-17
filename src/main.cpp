#include "SE/module/Module.hpp"
#include "SE_User.hpp"

#ifdef _WIN32

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	return S_Engine::Main( 1, &lpCmdLine );
}

#else

int main( int argc, char** argv )
{
	S_Engine::Set_Module_Hook( DF_Game::Module_Hook );
	S_Engine::Set_User_Init( DF_Game::User_Initialize );
	S_Engine::Set_User_Clean( DF_Game::User_Cleanup );


	return S_Engine::Main( argc, argv );
}

#endif
