#pragma once

#include <windows.h>
#define NOMINMAX

extern ENGINE::Application* ENGINE::CreateApplication();


int main(int argc, char** argv)
{
	ENGINE::Log::Init();
	ENGINE_CORE_INFO("Initialized Log");

	auto app = ENGINE::CreateApplication();
	app->Run();
	delete app;
}
