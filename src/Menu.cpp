#include "SE_User.hpp"
#include "SE/gl/OpenGL.hpp"
#include "SE/app/Window.hpp"

/************   MENU    ********************/
SE_Menu::Menu_Base* DF_Game::User_Load_Menu( std::string Which )
{
//	sePrintf( SEPRINT_DEBUG, "In user-set menu load\n" );
	if( Which == "title" )
	{
		SE_Menu::Menu_Base* nMenu = new SE_Menu::Menu_Base;

		nMenu->Title = "Title";

		nMenu->Make_Buttons(4);

		nMenu->Buttons[0] = new SE_GUI::Button_Menu("Singleplayer","singleplayer",-200,-100);
		nMenu->Buttons[1] = new SE_GUI::Button_Menu("Multiplayer","multiplayer",-200,-52);
		nMenu->Buttons[2] = new SE_GUI::Button_Menu("Options","options",-200,-4);
		nMenu->Buttons[3] = new SE_GUI::Button_Menu("Quit","quit",-200,92);

		return nMenu;
	}
/*	else if( Which == "singleplayer" )
	{
		SE_Menu::Menu_Base* nMenu = new SE_Menu::Menu_Base;

		nMenu->Title = "SURVIVOR";

		nMenu->Make_Buttons(2);


		nMenu->Buttons[0] = new Menu_Buttons::Button_Menu("Continue Story","single/continue",-200,-100);
		nMenu->Buttons[1] = new Menu_Buttons::Button_Menu("Back","back",-200,-52);


		return nMenu;
	}
	else if( Which == "single/continue" )
	{
		//
	}
*/
	return (SE_Menu::Menu_Base*)(-1);
}

uint Draw_Switch = 0;
void DF_Game::User_GUI_Background()
{
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho( 0.f, SE_Window::Get_W(), SE_Window::Get_H(), 0, 0, 10 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_DEPTH_BUFFER_BIT);
	segl_Disable(GL_DEPTH_TEST);
	segl_Disable( GL_BLEND );
	segl_Disable( GL_LIGHTING );

	if( Draw_Switch <= 60 )
		segl_Use_Texture( 1 );//Engine.Resources.Resource_Req.GUI_Buttons );
	else
		segl_Disable( SEGL_TEXTURE );

	segl_Set1p( SEGL_SHADER, NULL );

	glColor4f( 0.8f, 0.8f, 0.8f, 0.9f );
/* 
	glBegin(GL_QUADS);
 		glTexCoord2f(0, 0);			glVertex2d(0, 0 );
		glTexCoord2f(0.5f, 0);		glVertex2d(SE_Window::Get_W()/2.f,0 );
		glTexCoord2f(0.5f, 0.5f);	glVertex2d(SE_Window::Get_W()/2.f,SE_Window::Get_H()/2.f );
		glTexCoord2f(0, 0.5f);		glVertex2d(0,SE_Window::Get_H()/2.f );
	glEnd(); 
	glClearColor( 1, 1, 1, 1 );
*/
//	if( Draw_Switch++ > 120 )
//		Draw_Switch = 0;
}
