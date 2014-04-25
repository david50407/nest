
#if !defined(__CONFIG_H__)
#define __CONFIG_H__

using std::string;
using std::vector;
using std::stringstream;

namespace Nest
{
	class Config
	{
	public:
		class System
		{
		public:
			string organize = "",
			       name = "",
			       EnName = "",
			       sysopNick = "SYSOP",
			       tagValid = "[SYSOP] To",
			       IPAddr = "",
						 hostname = "",
			       charset = "big5",
			       BBSHome = "/home/bbs";
			vector<string> hostAliases {IPAddr, hostname};
			int BBSUID = 1001, BBSGID = 1001;

			System() {};
		}; // class System

		class BBS
		{
		public:
			vector<int> ports = {23};
		};

	public:
		System system {};
		BBS bbs {};

		Config()
		{
			::std::ifstream fconfig("config.json");
			this->loadConfig(fconfig);
			fconfig.close();
		}
		void loadConfig(::json11::Json &json)
		{
			if (!json["bbs"].is_null())
			{
				if (json["bbs"]["ports"].is_array())
				{
					auto &ports = json["bbs"]["ports"].array_items();
					this->bbs.ports.clear();
					for (auto port : ports) {
						this->bbs.ports.push_back(port.int_value());
					}
				}
			}
		}
		void loadConfig(::std::string str)
		{
			string error;
			auto json = ::json11::Json::parse(str, error);
			if (!error.empty()) {
				::std::cerr << error << ::std::endl;
				exit(-1);
			}
			loadConfig(json);
		}
		void loadConfig(::std::ifstream &stream)
		{
			stringstream bufferstream;
			string buffer;
			if (stream)
			{
				while (getline(stream, buffer))
					bufferstream << buffer << ::std::endl;
				loadConfig(bufferstream.str());
			}
		}
	}; // class Config
}; // namespace Nest

#endif // !defined(__CONFIG_H__)
