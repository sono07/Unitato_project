#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../include/Matrix.h"

class Logger
{
private:
	std::string message;
public:
	/// <summary>
	/// Instantiates a Logger object
	/// </summary>
	Logger();
	~Logger();

	/// <summary>
	/// Prints out a message with header '[INFO]' followed by the specified message
	/// </summary>
	/// <param name="message">| The message to print out to the console</param>
	void Info(std::string message);

	/// <summary>
	/// Prints out a message with header '[WARNING]' followed by the specified message
	/// </summary>
	/// <param name="message">| The message to print out to the console</param>
	void Warn(std::string message);

	/// <summary>
	/// Prints out a message with header '[ERROR]' followed by the specified message
	/// </summary>
	/// <param name="message">| The message to print out to the console</param>
	void Error(std::string message);

	/// <summary>
	/// Prints out a message with header '[TRACE]' followed by the specified message and a data structure
	/// </summary>
	/// <param name="message">| The message to print out to the console</param>
	/// <param name="matrix">| The matrix which is to be printed in a matrix format</param>
	/// <param name="vector">| The vector which is to be printed in a vector format</param>
	/// <param name="number">| A number which is to be printed</param>
	/// <param name="tupple">| A tupple which is to be printed</param>
	void Trace(const std::string message, const std::tuple<float, float, float>& tupple);
	void Trace(const std::string message, Matrix<float> matrix);
	void Trace(const std::string message, std::vector<float>& vector);
	void Trace(const std::string message, float* matrix);
	void Trace(const std::string message, unsigned int number);
};