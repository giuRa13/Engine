#pragma once

#include "Application.hpp"
#include <windows.h>
#define NOMINMAX

extern ENGINE::Application* ENGINE::CreateApplication(ApplicationCommandLineArgs args);


int main(int argc, char** argv)
{
	ENGINE::Log::Init();
	ENGINE_CORE_INFO("Initialized Log");

	auto app = ENGINE::CreateApplication({ argc, argv });
	app->Run();
	delete app;
}
