#include "Exception.h"

Exception::Exception(std::string message) {
	Application* app = Application::getInstance();
	this->number = app->exceptionNumber;
	this->message = message;
	app->exceptionNumber++;
}

int Exception::getNumber() {
	return this->number;
}
std::string Exception::getMessage() {
	return this->message;
}