#include "Map.hpp"
#include "SE/module/Module.hpp"
#include "SE/gl/se_gl.hpp"
#include "SE/render/Camera.hpp"
#include "SE/app/Window.hpp"
#include "SE/cbs/HI_Lang.hpp"

#include "SE/physics/Physics.hpp"
#include "SE/physics/Object.hpp"

#define SIZE_X 24
#define SIZE_Y 10
#define SIZE_Z 2


#define PLR_W	0.5f
#define PLR_H	1.6f
#define PLR_L	0.1f

namespace UM_Map
{
	// Globals
	namespace Res
	{
		uint Tex_Ground = 0;
		Vector4f* HIL_Test_Color = NULL;

		uint Tex_AI = 0;
	}

	void Render();
	void Update();

	// Global
	
	uchar Map_Grid[ SIZE_Z ][ SIZE_Y ][ SIZE_X ];
	
	SE_Physics::Obj_ID Test_Obj = NULL;

	// Functions
	void Render_Cube( uint x, uint y, uint z );

	// Module
	SE_Module_ID m_Mod = NULL;

	uint Initialize( const std::vector<std::string>& mArgs );
	uint Cleanup();

	uint Get_Resources( const std::vector<std::string>& mArgs );
	void Create_Physics();
	void Create_Block( Vector3f& Pos, uint Height, uchar Type );
}
using namespace UM_Map;




void UM_Map::Turn( float d )
{

}


//float Trans_X = 0.f;
void UM_Map::Render()
{
//	SE_Render_Camera::Position(NULL).x() -= 0.01f;

	segl_Set_Frustum_Far( 256 );
	segl_Switch_3D();
	glPushMatrix();

	SE_Render_Camera::Mult( NULL );

	// Draw character
	if( Test_Obj )
	{
		glPushMatrix();
		segl_Use_Texture( Res::Tex_AI );

		Vector3f& Char_Pos = SE_Physics::Pos3D(Test_Obj);

		glTranslatef( -PLR_W/2.f, -PLR_H/2.f, -PLR_L/2.f );

		glBegin( GL_QUADS );
			glTexCoord2f(0,0);	glVertex3f( Char_Pos.x(), Char_Pos.y(), Char_Pos.z() );
			glTexCoord2f(1,0);	glVertex3f( Char_Pos.x() + PLR_W, Char_Pos.y(), Char_Pos.z() );
			glTexCoord2f(1,1);	glVertex3f( Char_Pos.x() + PLR_W, Char_Pos.y() + PLR_H, Char_Pos.z() );
			glTexCoord2f(0,1);	glVertex3f( Char_Pos.x(), Char_Pos.y() + PLR_H, Char_Pos.z() );
		glEnd();

		glPopMatrix();
	}

	glColor4f( 1, 1, 1, 1 );
	glTranslatef( -SIZE_X / 2.f, -SIZE_Y / 2.f, -SIZE_Z / 2.f );


	segl_Use_Texture( Res::Tex_Ground );

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
			glTexCoord2f(0,1);	glVertex3f( 0, 1, 0 );
			glTexCoord2f(1,1);	glVertex3f( 1, 1, 0 );
			glTexCoord2f(1,0);	glVertex3f( 1, 0, 0 );
			glTexCoord2f(0,0);	glVertex3f( 0, 0, 0 );
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
			glTexCoord2f(0,1);	glVertex3f( 0, 1, 0 );
			glTexCoord2f(1,1);	glVertex3f( 0, 1, 1 );
			glTexCoord2f(1,0);	glVertex3f( 0, 0, 1 );
			glTexCoord2f(0,0);	glVertex3f( 0, 0, 0 );
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
			glTexCoord2f(0,1);	glVertex3f( 1, 1, 0 );
			glTexCoord2f(1,1);	glVertex3f( 1, 1, 1 );
			glTexCoord2f(1,0);	glVertex3f( 1, 0, 1 );
			glTexCoord2f(0,0);	glVertex3f( 1, 0, 0 );
		glEnd();
	}
	
	glColor3f( 1, 1, 1 );
	glPopMatrix();
}



#include "SE/os/Input.hpp"
void UM_Map::Update()
{
//	sePrintf( SEPRINT_INFO, "%f\n", SE_Thread::Get_DT() );
	if( SE_Input::Is_Down( SE_Input_Codes::KEY_A ) )
		SE_Physics::Apply_Force( Vector3f( -0.125f, 0, 0 ), Test_Obj );

	if( SE_Input::Is_Down( SE_Input_Codes::KEY_D ) )
		SE_Physics::Apply_Force( Vector3f( +0.125f, 0, 0 ), Test_Obj );

	if( SE_Input::Is_Down( SE_Input_Codes::KEY_W ) )
		SE_Physics::Apply_Force( Vector3f( 0, 0, +0.125f ), Test_Obj );

	if( SE_Input::Is_Down( SE_Input_Codes::KEY_S ) )
		SE_Physics::Apply_Force( Vector3f( 0, 0, -0.125f ), Test_Obj );


	if( SE_Input::Is_Down( SE_Input_Codes::KEY_SPACE ) )
	{
		Vector3f Start = SE_Physics::Pos3D( Test_Obj );
		Vector3f End = Start;
		Start.y() += PLR_H / 2.f + .025f;
		End.y() += PLR_H / 2.f + 0.125f;


		if( SE_Physics::Ray_Test( Start, End ) )
			SE_Physics::Apply_Force( Vector3f( 0, -50, 0 ), Test_Obj );

//		sePrintf( SEPRINT_DEBUG, "Already set space %d->", SE_Input::Get( SE_Input_Codes::KEY_SPACE ) );
		SE_Input::Set( SE_Input_Codes::KEY_SPACE, 0 );
//		sePrintf( SEPRINT_DEBUG, "%d\n", SE_Input::Get( SE_Input_Codes::KEY_SPACE ) );
	}

	// Update Camera
	Vector3f& Cam_Pos = SE_Render_Camera::Position(NULL);
	Vector3f& Char_Pos = SE_Physics::Pos3D(Test_Obj);

	Cam_Pos.x() -= ( Cam_Pos.x() + Char_Pos.x() ) * SE_Thread::Get_DT();
	Cam_Pos.y() += ( Char_Pos.y() - Cam_Pos.y() ) * SE_Thread::Get_DT();
}

void UM_Map::Create_Physics()
{
	// start from highest down
	for( uint z = 0; z < SIZE_Z; z++ ){
	for( uint x = 0; x < SIZE_X; x++ )
	{
		std::vector< uint > Pos_Start, Pos_End;
		uchar State = 0;//Map_Grid[z][0][x] != 0; // 0 = space, 1 = block
		// Get height
		for( uint y = 0; y < SIZE_Y; y++ )
		{
			if( Map_Grid[z][y][x] != 0 && State == 0 )
			{
				Pos_Start.push_back( y );
				State = 1;
			}

			else if( Map_Grid[z][y][x] == 0 && State == 1 )
			{
				Pos_End.push_back( y );
				State = 0;
			}
		}

		if( Pos_Start.size() > Pos_End.size() ) // Ends at bottom
			Pos_End.push_back( SIZE_Y );

		// Got all blocks
		Vector3f nPos;
		for( uint i = 0; i < Pos_Start.size(); i++ )
		{
			sePrintf( SEPRINT_INFO, "\t( %u, %u ), %u - %u = %u\n", x, z, Pos_End[i], Pos_Start[i], Pos_End[i] - Pos_Start[i] );
			nPos.Set( x, Pos_Start[i], z );
			Create_Block( nPos, Pos_End[i] - Pos_Start[i], Map_Grid[z][Pos_Start[i]][x] );
		}
	}}
}

#include "SE/physics/Physics.hpp"
void UM_Map::Create_Block( Vector3f& Pos, uint Height, uchar Type )
{
//	sePrintf( SEPRINT_DEBUG, "\tBlock (%g,%g,%g), %u\n", Pos.x(), Pos.y(), Pos.z(), Height );
/*	Pos.y() -= Height / 2.f;
	btTransform Trans; Trans.setIdentity();
	Trans.setOrigin( Pos );

	btVector3 Local_Inertia( 0, 0, 0 );

	btBoxShape* Shape = new btBoxShape( btVector3(0.5f, Height / 2.f, 0.5f) );

	btRigidBody* Body = SE_Physics::Make_Body( 0, Pos, Shape, 0, FILE_LINE );*/

	Pos.y() -= SIZE_Y / 2.f;
	Pos.z() -= SIZE_Z / 2.f;
	Pos.x() -= SIZE_X / 2.f;
	SE_Physics::Gen_Object( Pos, Vector3f( 1, Height, 1 ), 0, SE_PHYS_SHAPE_RECT );
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

	for( uint x = 1; x < SIZE_X; x+=2 )
		Map_Grid[1][SIZE_Y-4][x] = 1;

	for( uint x = 0; x < SIZE_X; x+=4 )
		Map_Grid[0][SIZE_Y-2][x] = 1;

	for( uint x = 1; x < SIZE_X; x+=4 )
		Map_Grid[0][SIZE_Y-3][x] = 1;


	Res::HIL_Test_Color = (Vector4f*)SE_HIL::Get( "test", "color" );

	SE_Render_Camera::Position(NULL).Set( SIZE_X / 2.f, SIZE_Y / 2.f - 2.5, -4 );
	SE_Render_Camera::Rotation(NULL).x() = -180;
	SE_Render_Camera::Rotation(NULL).x() += 15;

	SE_Physics::Set_World_Bound_Y( SIZE_Y / 2.f + 1 );/// 2.f );
	SE_Physics::Set_World_Bound_Z( SIZE_Z / 2.f + 1 );/// 2.f );

	SE_Physics::Set_Gravity( 10 );

	Create_Physics();
	Test_Obj = SE_Physics::Gen_Object( Vector3f( 0, SIZE_Y / 2.f - 5, -.5f ), Vector3f( PLR_W, PLR_H, PLR_L ), 10.f, SE_PHYS_SHAPE_CAPSULE );
	SE_Physics::Set_Upright( Test_Obj );

	return SE_SUCCESS;
}

uint UM_Map::Cleanup()
{
	return SE_SUCCESS;
}

uint UM_Map::Get_Resources( const std::vector<std::string>& mArgs )
{
	Res::Tex_Ground = Texture_Load( "resources/world/ground.png" );
	Res::Tex_AI = Texture_Load( "resources/ai.png" );

	return SE_SUCCESS;
}




void UM_Map::Register_Module()
{
	m_Mod = S_Engine::Generate_Module( "umbrelaya-map" );

	S_Engine::Register_Module_Engine( m_Mod, S_Engine::Reg_Mod_Time::MED_LEVEL + 30, Initialize, Cleanup );
	S_Engine::Register_Module_Render( m_Mod, S_Engine::Reg_Mod_Time::MED_LEVEL + 30, Get_Resources, NULL );

	S_Engine::Register_Module_Thread_Render( Render, S_Engine::Module_Positions::POS_START + 5, 200 );
	S_Engine::Register_Module_Thread_Logic( Update, S_Engine::Module_Positions::POS_EARLY, 32 );
}
