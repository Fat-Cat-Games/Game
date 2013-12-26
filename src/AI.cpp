#include "AI.hpp"
#include "SE/physics/Physics.hpp"


namespace UM_AI
{
	struct AI_Obj
	{
		AI_Stats m_Stats;

	};

	void Render_AI( AI_Obj* This );
}
using namespace UM_AI;




AI_Obj* UM_AI::Make_Simple( Vector3f& Pos )
{
	AI_Obj This = new AI_Obj;


	btTransform Trans; Trans.setIdentity();
	Trans.setOrigin( Pos );

	btVector3 Local_Inertia( 0, 0, 0 );

	btCapsuleShape* Shape = new btCapsuleShape( nSize.x,nSize.y-(nSize.x*2.f) );

	/*
	Shape->calculateLocalInertia(AI_Mass,Local_Inertia);

	btDefaultMotionState* Motion_State = new btDefaultMotionState(Trans);
	Engine.Mem_Add( Motion_State, "ai motion state" );

	btRigidBody::btRigidBodyConstructionInfo Body_Info(AI_Mass,Motion_State,Shape,Local_Inertia);

	Body_Info.m_friction=2;
	Body_Info.m_linearDamping=0.5;

	btRigidBody* Body = new btRigidBody(Body_Info);	  
	Engine.Mem_Add( Body, "ai body" );
	*/
	btRigidBody* Body = SE_Physics::Make_Body( 10, Pos, Shape, 0, FILE_LINE );
//	Body->setFriction( 2 );
//	Body->setUserPointer( new E_Objects::Bullet_Data( E_Objects::Bullet_Data::ID_AI, Body, (void*)this, "AI" ) );

	//do not rotate
	Body->setAngularFactor(btVector3(0,0,0));

	this->Phys_Body=Body;
}


// MODULE

void UM_AI::Register_Module()
{

}
