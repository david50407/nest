/*-------------------------------------------------------*/
/* entry.cxx     ( NestBBS Ver 3.00 )                    */
/*-------------------------------------------------------*/
/* author : me@davy.tw                                   */
/* target : Real main entry                              */
/* create : 2014/04/08                                   */
/* update : 2014/04/08                                   */
/*-------------------------------------------------------*/

#define __ENTRY_CXX__

#include "bbs.h"

using std::map;
using std::string;

namespace Nest
{
	void Entry::start(map<string, string> options)
	{
		std::unique_ptr<BBSD> bbsd(new BBSD([&options] (Config& config) {
			if (options.find("port") != options.end())
			{
				config.bbs.ports.clear();
				config.bbs.ports.push_back(::std::stoi(options["port"]));
			}
		}));

		bbsd->start();
	}
} // namespace Nest
