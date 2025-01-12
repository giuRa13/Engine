#include "ScriptEngine.hpp"
#include "../Core.hpp"
#include "../Log.hpp"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>


namespace ENGINE
{
	struct ScriptEngineData
	{
		MonoDomain* RootDomain = nullptr;
		MonoDomain* AppDomain = nullptr;
		MonoAssembly* CoreAssembly = nullptr;
	};
	static ScriptEngineData* s_Data;


	void ScriptEngine::Init()
	{
		s_Data = new ScriptEngineData();

		InitMono();
	}

	void ScriptEngine::Shutdown()
	{

	}

	void ScriptEngine::InitMono()
	{
		mono_set_assemblies_path("monon/lib");

		MonoDomain* rootDomain = mono_jit_init("ENGINEJITRuntime");
		ENGINE_CORE_ASSERT(rootDomain);
		// Store the root domain pointer
		s_Data->RootDomain = rootDomain;
		// Create an App Domain
		s_Data->AppDomain = mono_domain_create_appdomain("ENGINEScriptRuntime", nullptr);
		mono_domain_set(s_Data->AppDomain, true);
	}

	void ScriptEngine::ShutdownMono()
	{

	}
}