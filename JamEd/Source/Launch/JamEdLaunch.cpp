#include "Launch/Launch.h"

namespace Blueberry {

	class JamEdApplication : public Application
	{
	public:
		JamEdApplication()
		{
		}

		virtual ~JamEdApplication() override
		{
		}
	};

	Application* CreateApplication()
	{
		return new JamEdApplication();
	}

}