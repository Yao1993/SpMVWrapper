#include "json_io.h"
#include "benchmark.h"

#include <iostream>


#ifdef ENABLE_VTUNE
#include "ittnotify.h"
#endif

int main(int argc, char **argv)
{

	
	#ifdef ENABLE_VTUNE
	__itt_pause();
	#endif

	try
	{
		std::string input_filename = argc > 1? argv[1]: "C:/Users/tm42h7/Desktop/TPS/SpMVWrapper/cases/demo.json";
		benchmark_setting_t setting = parse_json(input_filename);

		auto r = start_benchmark(setting);

		dump_json(r);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(-1);
	}

	return 0;
}