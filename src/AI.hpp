#ifndef UM_AI
#define UM_AI


namespace UM_AI
{
	struct AI_Obj;

	struct AI_Stats
	{
		std::string Name;
	};

	AI_Obj* Make_Simple( Vector3f& Pos );

	void Register_Module();
}




#endif
