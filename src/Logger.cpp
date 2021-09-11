#include "../include/Logger.h"

#include <iomanip>

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Info(std::string message)
{
	std::cout << "[INFO]\t" << message << std::endl << "------------------------------" << std::endl;
}

void Logger::Warn(std::string message)
{
	std::cout << "[WARNING]\t" << message << std::endl;
}

void Logger::Error(std::string message)
{
	std::cout << "[ERROR]\t" << message << std::endl;
}

void Logger::Trace(const std::string message, const std::tuple<float, float, float>& tuple)
{
	std::cout << "*******************************" << std::endl << "[TRACE]\t" << message << std::endl << std::endl;

	std::cout << std::get<0>(tuple) << "\t" << std::get<1>(tuple) << "\t" << std::get<2>(tuple);

	std::cout << std::endl << "*******************************" << std::endl;
}

void Logger::Trace(const std::string message, Matrix<float> matrix)
{
	std::cout << "*******************************" << std::endl << "[TRACE]\t" << message << std::endl << std::endl;

	for (uint32_t i = 0; i < matrix.GetColumns(); i++)
	{
		for (uint32_t j = 0; j < matrix.GetRows(); j++)
		{
			std::cout << std::setw(12) << matrix(j, i);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "*******************************" << std::endl;
}

void Logger::Trace(const std::string message, std::vector<float>& vector)
{
	std::cout << "*******************************" << std::endl << "[TRACE]\t" << message << std::endl;

	for (uint32_t i = 0; i < vector.size(); i++)
	{
		std::cout << vector.at(i) << ", ";
	}

	std::cout << std::endl << "*******************************"  << std::endl;
}

void Logger::Trace(const std::string message, float* matrix)
{
	std::cout << "*******************************" << std::endl << "[TRACE]\t" << message << std::endl << std::endl;

	for (uint32_t i = 0; i < 4; i++)
	{
		for (uint32_t j = 0; j < 4; j++)
		{
			std::cout << std::setw(12) << matrix[i * 4 + j];
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "*******************************" << std::endl;
}

void Logger::Trace(const std::string message, unsigned int number)
{
	std::cout << "[TRACE]\t" << message << number << std::endl;
}

