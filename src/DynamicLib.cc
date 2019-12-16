#include <iostream>
#include <stdexcept>
#include <dlfcn.h>
#include "util.hh"

#include "DynamicLib.hh"

DynamicLib::DynamicLib(const std::string& path) {
	char* error;
	dllib = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if ((error = dlerror()) != nullptr || !dllib)
		throw std::runtime_error{
			"dlopen(): " + (error == nullptr ? "NULL" : std::string{error})};
}

DynamicLib::~DynamicLib() {
	char* error;
	int ret = dlclose(dllib);
	if ((error = dlerror()) != nullptr || ret)
		std::cerr
			<< "dlclose(): " << (error == nullptr ? "NULL" : error)
			<< std::endl;
}

void* DynamicLib::operator[](const std::string& symbol_name) {
	char* error;
	void* symbol = dlsym(dllib, symbol_name.c_str());
	if ((error = dlerror()) != nullptr)
		throw std::runtime_error{
			"dlsym(): " + (error == nullptr ? "NULL" : std::string{error})};
	return symbol;
}
