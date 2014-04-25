/*-------------------------------------------------------*/
/* bbsd.cxx     ( NestBBS Ver 3.00 )                     */
/*-------------------------------------------------------*/
/* author : me@davy.tw                                   */
/* target : BBS daemon                                   */
/* create : 2014/04/08                                   */
/* update : 2014/04/08                                   */
/*-------------------------------------------------------*/

#define __BBSD_CXX__

#include "bbs.h"
#define QLEN    3

namespace Nest
{
	BBSD::BBSD(::std::function<void(Config&)> yield)
	{
		yield(this->config);
	}

	void BBSD::start()
	{
		fork_daemon();
		// TODO: trap_signals
		// TODO: init_SHM
		// TODO: listen_connection // fork here
		// TODO: init_terminal
		// TODO: init_term
		// TODO: bbs main
	}

	void BBSD::fork_daemon()
	{
		// adjust resource : 16 mega is enough
		// struct rlimit limit;
		// limit.rlim_cur = limit.rlim_max = 16 * 1024 * 1024;
		// setrlimit(RLIMIT_DATA, &limit);

		// change directory to bbshome
		chdir(this->config.system.BBSHome.c_str());
		umask(077);

		// fork daemon process
		struct sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;

		int port;
		for (int p : this->config.bbs.ports)
		{
			if (fork() == 0)  // child
			{
				port = p;
				break;
			}
			sleep(1);
		}
    int so = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    time_t val = 1;
		struct linger ld;
    setsockopt(so, SOL_SOCKET, SO_REUSEADDR, (char *) &val, sizeof(val));
    ld.l_onoff = ld.l_linger = 0;
    setsockopt(so, SOL_SOCKET, SO_LINGER, (char *) &ld, sizeof(ld));
		sin.sin_port = htons(port);
		if ((bind(so, (struct sockaddr *) &sin, sizeof(sin)) < 0) || (listen(so, QLEN) < 0))
			exit(1);
	}
} // namespace Nest
