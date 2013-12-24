#include "Map.hpp"
#include "SE/module/Module.hpp"
#include "SE/gl/se_gl.hpp"
#include "SE/app/Window.hpp"
#include "SE/cbs/HI_Lang.hpp"

#define SIZE_X 24
#define SIZE_Y 10
#define SIZE_Z 2


namespace UM_Map
{
	// Globals
	namespace Res
	{
		uint Tex_Ground = 0;
		Vector4f* HIL_Test_Color = NULL;
	}

	void Render();
	void Update();

	// Global
	
	uchar Map_Grid[ SIZE_Z ][ SIZE_Y ][ SIZE_X ];


	// Functions
	void Render_Cube( uint x, uint y, uint z );

	// Module
	SE_Module_ID m_Mod = NULL;

	uint Initialize( const std::vector<std::string>& mArgs );
	uint Cleanup();

	uint Get_Resources( const std::vector<std::string>& mArgs );
}
using namespace UM_Map;




void UM_Map::Turn( float d )
{

}


float Trans_X = 0.f;
void UM_Map::Render()
{
	Trans_X -= 0.01f;

	segl_Set_Frustum_Far( 16 );
	segl_Switch_3D();
	glPushMatrix();

//	glTranslatef( -SE_Window::Get_W() / 2.f, -SE_Window::Get_H() / 2.f, 0 );
//	glTranslatef( -SIZE_X / 2.f, -SIZE_Y / 2.f, -SIZE_Z / 2.f );

//	glRotatef( 30, 0, 0, 1 );

	glTranslatef( Trans_X, SIZE_Y - 2.5, -2 );
	glRotatef( -180, 1, 0, 0 );
	glRotatef( 15, 1, 0, 0 );

	glColor4f( 1, 1, 1, 1 );
	segl_Use_Texture( Res::Tex_Ground );

	glTranslatef( -0.5f, -0.5f, -0.5f );

	for( uint z = 0; z < SIZE_Z; z++ ){
	for( uint y = 0; y < SIZE_Y; y++ ){
	for( uint x = 0; x < SIZE_X; x++ )
	{
		Render_Cube( x, y, z );
	}}}

	glPopMatrix();
	segl_Switch_2D();
}

void UM_Map::Render_Cube( uint x, uint y, uint z )
{
	if( Map_Grid[z][y][x] == 0 )
		return;

	glPushMatrix();

	glTranslatef( x, y, z );

	// Front
	if( z == 0 || Map_Grid[z - 1][y][x] == 0 )
	{
		if( Res::HIL_Test_Color )
			glColor3f( Res::HIL_Test_Color->r() - 0.1f, Res::HIL_Test_Color->g() - 0.1f, Res::HIL_Test_Color->b() - 0.1f );
		else
			glColor3f( 0.9f, 0.9f, 0.9f );

		glBegin( GL_QUADS );
			glTexCoord2f(0,0);	glVertex3f( 0, 1, 0 );
			glTexCoord2f(1,0);	glVertex3f( 1, 1, 0 );
			glTexCoord2f(1,1);	glVertex3f( 1, 0, 0 );
			glTexCoord2f(0,1);	glVertex3f( 0, 0, 0 );
		glEnd();
	}
	// Top
	if( y == 0 || Map_Grid[z][y - 1][x] == 0 )
	{
		if( Res::HIL_Test_Color )
			glColor3f( Res::HIL_Test_Color->r(), Res::HIL_Test_Color->g(), Res::HIL_Test_Color->b() );
		else
			glColor3f( 1, 1, 1 );

		glBegin( GL_QUADS );
			glTexCoord2f(0,0);	glVertex3f( 0, 0, 1 );
			glTexCoord2f(1,0);	glVertex3f( 1, 0, 1 );
			glTexCoord2f(1,1);	glVertex3f( 1, 0, 0 );
			glTexCoord2f(0,1);	glVertex3f( 0, 0, 0 );
		glEnd();
	}
	// Bottom
	if( y == SIZE_Y - 1 || Map_Grid[z][y + 1][x] == 0 )
	{
		if( Res::HIL_Test_Color )
			glColor3f( Res::HIL_Test_Color->r() - 0.3f, Res::HIL_Test_Color->g() - 0.3f, Res::HIL_Test_Color->b() - 0.3f );
		else
			glColor3f( 0.7f, 0.7f, 0.7f );

		glBegin( GL_QUADS );
			glTexCoord2f(0,0);	glVertex3f( 0, 1, 0 );
			glTexCoord2f(1,0);	glVertex3f( 1, 1, 0 );
			glTexCoord2f(1,1);	glVertex3f( 1, 1, 1 );
			glTexCoord2f(0,1);	glVertex3f( 0, 1, 1 );
		glEnd();
	}
	// Left
	if( x == 0 || Map_Grid[z][y][x - 1] == 0 )
	{
		if( Res::HIL_Test_Color )
			glColor3f( Res::HIL_Test_Color->r() - 0.2f, Res::HIL_Test_Color->g() - 0.2f, Res::HIL_Test_Color->b() - 0.2f );
		else
			glColor3f( 0.8f, 0.8f, 0.8f );

		glBegin( GL_QUADS );
			glTexCoord2f(0,0);	glVertex3f( 0, 1, 0 );
			glTexCoord2f(1,0);	glVertex3f( 0, 1, 1 );
			glTexCoord2f(1,1);	glVertex3f( 0, 0, 1 );
			glTexCoord2f(0,1);	glVertex3f( 0, 0, 0 );
		glEnd();
	}
	// Right
	if( x == SIZE_X - 1 || Map_Grid[z][y][x + 1] == 0 )
	{
		if( Res::HIL_Test_Color )
			glColor3f( Res::HIL_Test_Color->r() - 0.2f, Res::HIL_Test_Color->g() - 0.2f, Res::HIL_Test_Color->b() - 0.2f );
		else
			glColor3f( 0.8f, 0.8f, 0.8f );

		glBegin( GL_QUADS );
			glTexCoord2f(0,0);	glVertex3f( 1, 1, 0 );
			glTexCoord2f(1,0);	glVertex3f( 1, 1, 1 );
			glTexCoord2f(1,1);	glVertex3f( 1, 0, 1 );
			glTexCoord2f(0,1);	glVertex3f( 1, 0, 0 );
		glEnd();
	}
	
	glColor3f( 1, 1, 1 );
	glPopMatrix();
}



void UM_Map::Update()
{

}



// Module

uint UM_Map::Initialize( const std::vector<std::string>& mArgs )
{
	for( uint z = 0; z < SIZE_Z; z++ )
		for( uint y = 0; y < SIZE_Y; y++ )
			for( uint x = 0; x < SIZE_X; x++ )
				Map_Grid[z][y][x] = 0;



	for( uint x = 0; x < SIZE_X; x++ )
		Map_Grid[0][SIZE_Y-1][x] = 1;

	for( uint x = 0; x < SIZE_X; x+=2 )
		Map_Grid[1][SIZE_Y-1][x] = 1;

	for( uint x = 0; x < SIZE_X; x+=4 )
		Map_Grid[0][SIZE_Y-2][x] = 1;


	Res::HIL_Test_Color = (Vector4f*)SE_HIL::Get( "test", "color" );

	return SE_SUCCESS;
}

uint UM_Map::Cleanup()
{
	return SE_SUCCESS;
}

uint UM_Map::Get_Resources( const std::vector<std::string>& mArgs )
{
	Res::Tex_Ground = Texture_Load( "resources/world/ground.png" );

	return SE_SUCCESS;
}




void UM_Map::Register_Module()
{
	m_Mod = S_Engine::Generate_Module( "umbrelaya-map" );

	S_Engine::Register_Module_Engine( m_Mod, S_Engine::Reg_Mod_Time::MED_LEVEL + 30, Initialize, Cleanup );
	S_Engine::Register_Module_Render( m_Mod, S_Engine::Reg_Mod_Time::MED_LEVEL + 30, Get_Resources, NULL );

	S_Engine::Register_Module_Thread_Render( Render, S_Engine::Module_Positions::POS_EARLY, 200 );
	S_Engine::Register_Module_Thread_Logic( Update, S_Engine::Module_Positions::POS_EARLY, 32 );
}
