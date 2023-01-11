#pragma once
#include <iostream>
#include "Application.h"
class Exception
{
	public:
		Exception(std::string message);
		int getNumber();
		std::string getMessage();
	private:
		int number;
		std::string message;
};

