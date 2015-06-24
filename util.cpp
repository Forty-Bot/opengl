#include "util.h"

#include <iostream>
#include <fstream>

std::string read_file(const char* filename) {
	
	std::ifstream in;
	in.exceptions(std::ifstream::failbit | std::ifstream::badbit); 
	try {
		in.open(filename, std::ios::in | std::ios::binary);
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	catch(std::ifstream::failure e) {
		std::cerr << "Error: " << e.what() << std::endl;
		throw(e);
	}

}
