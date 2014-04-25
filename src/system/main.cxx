/*-------------------------------------------------------*/
/* main.cxx     ( NestBBS Ver 3.00 )                     */
/*-------------------------------------------------------*/
/* author : me@davy.tw                                   */
/* target : main function entry                          */
/* cr.finde : 2014/03/31                                   */
/* up.finde : 2014/03/31                                   */
/*-------------------------------------------------------*/

#include "bbs.h"

void usage(char *exec)
{
	std::stringstream ss;
	ss
		<< "Usage: " << exec << " [options]\n"
		<< "\t-h                 show this help\n"
		<< "\t-c config_path     read from configuation file\n"
		<< "\t-t type            terminal mode, telnet (default) | tty\n"
		<< "\t-e encoding        encoding, big5 (default) | utf8\n"
		<< "\n"
		<< "daemon mode\n"
		<< "\t-d                 use daemon mode, imply -t telnet\n"
		<< "\t-p port            listen port\n"
		<< "\n"
		<< "non-daemon mode\n"
		<< "\t-D                 use non-daemon mode, imply -t tty\n"
		<< "\t-i ip              client IP (default 127.0.0.1)\n"
		<< "\n"
		<< "debug\n"
		<< "\t-u user            login as user directly without pw\n"
		<< "\n";
  std::cout << ss.str();
}

bool parseParams(int argc, char** argv, std::map<string, string> &options)
{
	char ch;
	while ((ch = getopt(argc, argv, "hc:t:e:dn:p:Di:u:")) != -1)
	{
		switch (ch)
		{
		case 'h':
			return false;
			break;
		case 'c':
			options["configure"] = optarg;
			break;
		case 't':
			if (options.find("type") == options.end())
				return false;
			options["type"] = optarg;
			if (options["type"] != "telnet"
			    && options["type"] != "tty")
				return false;
			break;
		case 'e':
			options["encoding"] = optarg;
			if (options["encoding"] != "big5"
					&& options["encoding"] != "gbk"
			    && options["encoding"] != "utf8")
				return false;
			break;
		case 'd':
			if (options.find("type") == options.end())
				return false;
			options["type"] = "telnet";
			break;
		case 'p':
			options["port"] = optarg;
			break;
		case 'D':
			if (options.find("type") == options.end())
				return false;
			options["type"] = "tty";
			break;
		case 'i':
			options["client_ip"] = optarg;
			break;
		case 'u':
			options["force_login"] = optarg;
			break;
		}
	}
	return true;
}

int main(int argc, char** argv)
{
	std::map<string, string> options;
	if (parseParams(argc, argv, options))
		Nest::Entry::start(options);
	else
		usage(argv[0]);

	return 0;
}
