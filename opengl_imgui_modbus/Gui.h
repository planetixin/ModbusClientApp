#pragma once
#include "includes.h"


class Gui
{
public:
	Gui(GLFWwindow* window);
	~Gui();
	void Update(float deltatime);
private:
	void MenuBar();

	void upperWindow();

	void RegisterWindow();


	bool SetIP();
	bool Connect();



	const GLFWwindow* window;

	int startRegister = 0;
	int page = 1;

	int port = 502;
	int width = 2;
	int height = 20;

	int octans[4] = { 192, 168, 0, 1 };
	std::string IP;
	uint16_t* registers = new uint16_t[width*height]();
	//std::vector<int> registers;

	modbus mb = modbus(IP, port);

	bool showWindow = true;
};

