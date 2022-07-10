// Copyright to Avram Traian. 2022 - 2022.
// File created on June 13 2022.

#pragma once

#include "CoreMinimal.h"

#include "Layer.h"
#include "Window.h"
#include "Events/Event.h"

namespace Blueberry {

	/**
	* Holds the command line arguments.
	*/
	struct CommandLineArguments
	{
		// The list of command line arguments.
		CharT** Arguments = nullptr;

		// The count of the command line arguments.
		uint32_t Count = 0;

		const CharT* operator[](SizeT index) const { return Arguments[index]; }
	};

	/**
	* Specifies the Application behavior.
	*/
	struct ApplicationSpecification
	{
		// The application name.
		String Name;

		// The application initial working directory.
		String WorkingDirectory;

		// The primary window's title.
		String WindowTitle;

		// The command line arguments.
		CommandLineArguments CommandLineArgs;
	};

	class BLUEBERRY_API Application
	{
	public:
		Application(const ApplicationSpecification& spec, bool& out_status);
		virtual ~Application();

	public:
		static Application* Get() { return s_Instance; }

		static void OnEvent(const Window* window, Event& e);

	public:
		int32_t Run();

		void AddLayer(Layer* layer);

		const Vector<Window*>& GetWindows() const { return m_Windows; }

		void AddWindow(Window* window);

		/**
		* Retrieves the application specification.
		* 
		* @returns The application specification.
		*/
		const ApplicationSpecification& GetSpecification() const { return m_Specification; }

	private:
		ApplicationSpecification m_Specification;

		bool m_IsRunning = false;

		Vector<Layer*> m_Layers;

		Vector<Window*> m_Windows;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication(const CommandLineArguments& command_args, bool& out_status);

}