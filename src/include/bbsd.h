
#if !defined(__SYSTEM_BBSD_H__)
#define __SYSTEM_BBSD_H__
#include <functional>
#include <iostream>
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace Nest
{
	class BBSD
	{
	public:
		Config config{};

		BBSD(::std::function<void(Config&)>);
		void start();

	private:
		void fork_daemon();
	}; // class BBSD
}; // namespace Nest

#endif // !defined(__SYSTEM_BBSD_H__)
