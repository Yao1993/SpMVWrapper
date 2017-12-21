#include "json_io.h"
#include "benchmark.h"

#include <iostream>

int main(int argc, char **argv)
{
	try
	{
		std::string input_filename = "C:/Users/tm42h7/Desktop/TPS/SpMVWrapper/cases/demo.json";
		benchmark_setting setting = parse_json(input_filename);
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