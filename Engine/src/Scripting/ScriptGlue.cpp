#include "ScriptGlue.hpp"
#include "ScriptEngine.hpp"
#include "../Input.hpp"
#include "../Core.hpp"
#include <iostream>
#include <mono/metadata/object.h>


namespace ENGINE
{
	
#define ENGINE_ADD_INTERNAL_CALL(Name) mono_add_internal_call("ENGINE.InternalCalls::" #Name, Name)

	/*static void CppFunc()
	{
		std::cout << "This is written in C++!\n";
	}

	static void NativeLog_Vector(glm::vec3* parameter)
	{
		ENGINE_CORE_DEBUG("Value: {}", glm::to_string(*parameter));
	}*/

	static void NativeLog(MonoString* string, int parameter)
	{
		char* cStr = mono_string_to_utf8(string);
		std::string str(cStr);
		mono_free(cStr);

		std::cout << str << "-" << parameter << std::endl;
	}

	static void NativeLog_Vector(glm::vec3* parameter, glm::vec3* outResult)
	{
		ENGINE_CORE_DEBUG("Value : {}", glm::to_string(*parameter));
		*outResult = glm::normalize(*parameter);
	}
	
	static float NativeLog_VectorDot(glm::vec3* parameter)
	{
		ENGINE_CORE_DEBUG("Value : {}", glm::to_string(*parameter));
		return glm::dot(*parameter, *parameter);
	}


	static void Entity_GetTranslation(UUID entityID, glm::vec3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntityByUUID(entityID);
		*outTranslation = entity.GetComponent<TransformComponent>().Translation;
	}

	static void Entity_SetTranslation(UUID entityID, glm::vec3* translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntityByUUID(entityID);
		entity.GetComponent<TransformComponent>().Translation = *translation;
	}

	static bool Input_IsKeyDown(KeyCode keycode)
	{
		return Input::IsKeyPressed(keycode);
	}


	void ScriptGlue::RegisterFunctions()
	{
		//mono_add_internal_call("ENGINE.Main::NativeLog", NativeLog);
		ENGINE_ADD_INTERNAL_CALL(NativeLog);
		ENGINE_ADD_INTERNAL_CALL(NativeLog_Vector);
		ENGINE_ADD_INTERNAL_CALL(NativeLog_VectorDot);

		ENGINE_ADD_INTERNAL_CALL(Entity_GetTranslation);
		ENGINE_ADD_INTERNAL_CALL(Entity_SetTranslation);
		ENGINE_ADD_INTERNAL_CALL(Input_IsKeyDown);
	}

}