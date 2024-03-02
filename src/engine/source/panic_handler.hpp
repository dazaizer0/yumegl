#pragma once

#include "../../config.h"

struct PanicHandler {
private :
	bool panic;

	void closeProgram();
public:
	PanicHandler(bool defaultMode);
	~PanicHandler() = default;

	bool getPanicMode();

	void turnOnPanicMode();
	void turnOffPanicMode();
	void switchPanicMode();
	
	void considerPanicMode();
};

PanicHandler::PanicHandler(bool defaultMode) { panic = defaultMode; }

void PanicHandler::closeProgram() {
	std::cerr << "-> Panic Handler : panic mode detected - closing program..." << std::endl;
	glfwTerminate();
	std::exit(0);
}

bool PanicHandler::getPanicMode() { return panic; }

void PanicHandler::turnOnPanicMode() { panic = true; }
void PanicHandler::turnOffPanicMode() { panic = false; }
void PanicHandler::switchPanicMode() { panic = !panic; }

void PanicHandler::considerPanicMode() {
	if (panic) {
		closeProgram();
	}
	else {
		std::cout << "panic: " << panic << "\n";
	}
}