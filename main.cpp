
/**
 * Программа проверкаи работы 2-мерной
 * бесконечной матрицы
*/

#include <iostream>

#include "version.h"
#include "matrix.h"



#include <boost/program_options.hpp>

namespace po = boost::program_options;

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;



/**
 * \brief main
 *
 * Программа проверкаи работы 2-мерной бесконечной матрицы
 */
int main (int argc, char* argv[])
{
	try
	{
		logging::add_common_attributes();

		logging::add_file_log(
				keywords::file_name = "matrix.log",
				keywords::rotation_size = 10 * 1024 * 1024,
				keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0,0,0),
				keywords::format = "[%TimeStamp%]: %Message%",
				keywords::auto_flush = true,
				keywords::open_mode = std::ios_base::out
						// || std::ios_base::ate
				);

		logging::core::get()->set_logging_enabled(false);	



		po::options_description descr("Allowed options");
		descr.add_options()
			("help,h", "Produce help message")
			("version,v", "Version")
			("debug,d", "Enable loggigng")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, descr), vm);
		po::notify(vm);

		if(vm.count("help"))
		{
			std::cout << descr << std::endl;
			return 0;
		}

		if(vm.count("version"))
		{
			std::cout << "OTUS cpp" << std::endl;
			std::cout << "Homework 6. Sparse matrix." << std::endl;
			std::cout << "Version " << VER << std::endl << std::endl;
			return 0;
		}

		if(vm.count("debug"))
		{
			logging::core::get()->set_logging_enabled(true);	
		}


		BOOST_LOG_TRIVIAL(info) << "Start matrix test";



		my::matrix<int, 0> m;
		for(int i=0; i<10; i++)
		{
			m[i][i] = i;
			m[i][9-i] = i;
		}

		for(int i=1; i<9; i++)
		{
			for(int j=1; j<9; j++)
			{
				std::cout << m[i][j] << " ";
			}
			std::cout << std::endl;
		}


		BOOST_LOG_TRIVIAL(info) << "End matrix test";
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}

