#include "json_reader.h"

int main(int argc, char **argv)
{
	std::string input_filename = "C:/Users/tm42h7/Desktop/TPS/SpMVWrapper/cases/demo.json";
	benchmark_setting setting = parse_json(input_filename);
	return 0;
}