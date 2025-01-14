#include "ScriptGlue.hpp"
#include "ScriptEngine.hpp"
#include "../Input.hpp"
#include "../Core.hpp"
#include <iostream>
#include <box2d/b2_body.h>
#include <mono/metadata/object.h>
#include <mono/metadata/reflection.h>


namespace ENGINE
{
	static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;
	
#define ENGINE_ADD_INTERNAL_CALL(Name) mono_add_internal_call("ENGINE.InternalCalls::" #Name, Name)

	/*static void CppFunc()
	{
		std::cout << "This is written in C++!\n";
	}

	static void NativeLog_Vector(glm::vec3* parameter)
	{
		ENGINE_CORE_DEBUG("Value: {}", glm::to_string(*parameter));
	}*/

	/*static void NativeLog(MonoString* string, int parameter)
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
	}*/


	static bool Entity_HasComponent(UUID entityID, MonoReflectionType* componentType)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		ENGINE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		ENGINE_CORE_ASSERT(entity);

		MonoType* managedType = mono_reflection_type_get_type(componentType);
		ENGINE_CORE_ASSERT(s_EntityHasComponentFuncs.find(managedType) != s_EntityHasComponentFuncs.end());
		return s_EntityHasComponentFuncs.at(managedType)(entity);
	}

	static void TransformComponent_GetTranslation(UUID entityID, glm::vec3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		ENGINE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		ENGINE_CORE_ASSERT(entity);

		*outTranslation = entity.GetComponent<TransformComponent>().Translation;
	}

	static void TransformComponent_SetTranslation(UUID entityID, glm::vec3* translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		ENGINE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		ENGINE_CORE_ASSERT(entity);

		entity.GetComponent<TransformComponent>().Translation = *translation;
	}

	static void Rigidbody2DComponent_ApplyLinearImpulse(UUID entityID, glm::vec2* impulse, glm::vec2* point, bool wake)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		ENGINE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		ENGINE_CORE_ASSERT(entity);

		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		b2Body* body = (b2Body*)rb2d.RuntimeBody;
		body->ApplyLinearImpulse(b2Vec2(impulse->x, impulse->y), b2Vec2(point->x, point->y), wake);
	}

	static void Rigidbody2DComponent_ApplyLinearImpulseToCenter(UUID entityID, glm::vec2* impulse, bool wake)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		ENGINE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		ENGINE_CORE_ASSERT(entity);

		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		b2Body* body = (b2Body*)rb2d.RuntimeBody;
		body->ApplyLinearImpulseToCenter(b2Vec2(impulse->x, impulse->y), wake);
	}

	static bool Input_IsKeyDown(KeyCode keycode)
	{
		return Input::IsKeyPressed(keycode);
	}


	template<typename... Component>
	static void RegisterComponent()
	{
		([]()
			{
				std::string_view typeName = typeid(Component).name();  // struct ENGINE::TransformComponent
				size_t pos = typeName.find_last_of(':');
				std::string_view structName = typeName.substr(pos + 1);  // TransformComponent
				std::string managedTypename = fmt::format("ENGINE.{}", structName);  //ENGINE.TransformComponent

				MonoType* managedType = mono_reflection_type_from_name(managedTypename.data(), ScriptEngine::GetCoreAssemblyImage());
				if (!managedType)
				{
					ENGINE_CORE_ERROR("Could not find component type {}", managedTypename);
					return;
				}
				s_EntityHasComponentFuncs[managedType] = [](Entity entity) { return entity.HasComponent<Component>(); };
			}(), ...);
	}

	template<typename... Component>
	static void RegisterComponent(ComponentGroup<Component...>)
	{
		RegisterComponent<Component...>();
	}

	void ScriptGlue::RegisterComponents()
	{
		RegisterComponent(AllComponents{});
	}

	void ScriptGlue::RegisterFunctions()
	{
		//mono_add_internal_call("ENGINE.Main::NativeLog", NativeLog);
		//ENGINE_ADD_INTERNAL_CALL(NativeLog);
		//ENGINE_ADD_INTERNAL_CALL(NativeLog_Vector);
		//ENGINE_ADD_INTERNAL_CALL(NativeLog_VectorDot);

		ENGINE_ADD_INTERNAL_CALL(Entity_HasComponent);
		ENGINE_ADD_INTERNAL_CALL(TransformComponent_GetTranslation);
		ENGINE_ADD_INTERNAL_CALL(TransformComponent_SetTranslation);
		ENGINE_ADD_INTERNAL_CALL(Rigidbody2DComponent_ApplyLinearImpulse);
		ENGINE_ADD_INTERNAL_CALL(Rigidbody2DComponent_ApplyLinearImpulseToCenter);

		ENGINE_ADD_INTERNAL_CALL(Input_IsKeyDown);
	}

}