#include "pch.h"

#include "argsParser.h"
#include <iostream>

char Args::colorizing = 'R';
std::string Args::inputFilePath = "test.bmp";
std::string Args::outputFilePathForAsm = "test_out_asm.bmp";
std::string Args::outputFilePathForC = "test_out_cpp.bmp";
int Args::threadsNumber = 4;
bool Args::assembly = false;
bool Args::cPlusPlus = false;

bool Args::parseArgs(int argc, char** argv) {
	for(int i = 1; i < argc; ++i) {
		std::string temp(argv[i]);
		if(temp == "-c") {
			try {
				char color = *argv[++i];
				if(color == 'R' || color == 'G' || color == 'B') {
					colorizing = color;
				} else {
					std::cerr << "Wrong color passed! Default 'R' colorizing will be used!\n";
				}				
			} catch(const std::out_of_range &exception) {
				std::cerr << "Color parameter not properly passed! Default 'R' colorizing will be used!\n";
			}
		} else if(temp == "-i") {
			try {
				std::string filePath(argv[++i]);
				inputFilePath = filePath;
			} catch (const std::out_of_range &exception) {
				std::cerr << "Input file parameter not properly passed! Default 'test.bmp' input file will be used!\n";
			}		
		} else if(temp == "-oC") {
			try {
				std::string filePath(argv[++i]);
				outputFilePathForC = filePath;
			}
			catch (const std::out_of_range &exception) {
				std::cerr << "Output file for C++ parameter not properly passed! Default 'test_out_cpp.bmp' output file will be used!\n";
			}					
		}
		else if (temp == "-oA") {
			try {
				std::string filePath(argv[++i]);
				outputFilePathForAsm = filePath;
			}
			catch (const std::out_of_range &exception) {
				std::cerr << "Output file for Assembly parameter not properly passed! Default 'test_out_asm.bmp' output file will be used!\n";
			}
		} else if(temp == "-t") {
			try {
				int threads = atoi(argv[++i]);
				if(threads >= 0 && threads <= 64) {
					threadsNumber = threads;					
				} else {
					std::cerr << "Wrong number of threads specified! Default 4 threads will be used!\n";
				}				
			} catch (const std::out_of_range &exception) {
				std::cerr << "Number of threads parameter not properly passed! Default 4 threads will be used!\n";
			}	
		} else if(temp == "-A") {
			assembly = true;
		} else if(temp == "-C") {
			cPlusPlus = true;
		} else if(temp == "-h") {
			printHelp();
			return false;
		}	
	}
	return true;
}

void Args::printHelp() {
	std::cout << "\nUsage of program:\n\n"
		<< "-c [R, G, B]                 - color to colorize bitmap\n"
		<< "-i inputFilePath.bmp         - path to input bitmap file\n"
		<< "-oC outputFilePathForC.bmp   - path to output (colorized) bitmap by C++ algorithm\n"
		<< "-oA outputFilePathForAsm.bmp - path to output (colorized) bitmap by Assembly algorithm\n"		
		<< "-t [0-64]                    - number of threads as number within 0-64 range\n"
		<< "-A                           - if present, assembly algorithm will be used\n"
		<< "-C                           - if present, C++ algorithm will be used\n\n";
}