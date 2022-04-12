#include "Gui.h"

Gui::Gui(GLFWwindow* window) : window(window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	//ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;


	mb.modbus_connect();
	//for (int row = 0; row < 100; row++)
	//{

	//	for (int collumn = 0; collumn < width; collumn++)
	//	{
	//		//registers.push_back(0);

	//	}
	//}
}

Gui::~Gui()
{
}

void Gui::Update(float deltatime)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	MenuBar();
	upperWindow();

	RegisterWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::MenuBar()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Save"))
		{
			ImGui::EndMenu();

		}
			//std::cout << "save";
		// Exit...
	}
	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("Propeties"))
		{
			ImGui::EndMenu();
		}
			//std::cout << "propeties";
		// Exit...
	}
	ImGui::EndMainMenuBar();
}



void Gui::upperWindow()
{
	if (showWindow)
	{
		ImGui::Begin("Ip setting", &showWindow);

		ImGui::InputInt("port", &port, 0);

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.15f);
		ImGui::InputInt("##1", &octans[0], 0);
		ImGui::SameLine();
		ImGui::InputInt("##2", &octans[1], 0);
		ImGui::SameLine();
		ImGui::InputInt("##3", &octans[2], 0);
		ImGui::SameLine();
		ImGui::InputInt("##4", &octans[3], 0);
		ImGui::SameLine();
		ImGui::Text("Adress Ip");

		ImGui::InputInt("start Register", &startRegister, 0);
		ImGui::SameLine();
		ImGui::InputInt("width", &width, 0);
		ImGui::SameLine();
		ImGui::InputInt("height", &height, 0);

		
		if (ImGui::Button("Connect"))
		{
			SetIP();

			Connect();
		}
		ImGui::End();
	}
}

void Gui::RegisterWindow()
{
	ImGui::Begin("Registers");

	//--pages---------------------------------------//
	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.05f);
	if (ImGui::Button("<"))
		page--;
	ImGui::SameLine();
	ImGui::InputInt("##Page", &page, 0);
	ImGui::SameLine();
	if (ImGui::Button(">"))
		page++;

	int size = width * height;
	int address = startRegister + (page - 1) * size;
	
	int sizeo = (sizeof(registers) / sizeof(*registers));
	if(sizeo != width* height)
		registers = new uint16_t[width * height]();
	mb.modbus_set_slave_id(0);
	mb.modbus_read_holding_registers(address, size, registers);


	//--table-----------------------------------------//
	ImGui::BeginTable("table", width*2, 0);

	for (int row = 0; row < height; row++)
	{
		ImGui::TableNextRow();
		
		for (int collumn = 0; collumn < width; collumn++)
		{


			int place = row + collumn * height;
			int rplace = place + address;


			ImGui::TableNextColumn();


			std::stringstream rs;
			rs << rplace;
			ImGui::Text(rs.str().c_str());
			ImGui::TableNextColumn();

			
			std::stringstream ss;
			ss << "##" << row << ',' << collumn;
			int v = registers[place];
			ImGui::InputInt(ss.str().c_str(), &v, 0);
			if (v != registers[place])
			{
				registers[place] = v;
				mb.modbus_write_register(place, registers[place]);

			}
				


			//net.SetRegister(row, collumn, net.registers[place]);
			
			//net.SetRegister(row, net.registers[collumn + row * net.width]);

		}
	}
	//mb.modbus_write_registers(address, size, registers);

	//net.SetRegisters();
	//net.SetRegister(0, 1, 20);
	//net.GetRegisters();

	ImGui::EndTable();


	ImGui::End();
}


bool Gui::SetIP()
{
	std::stringstream ss;
	for (int i = 0; i < 4; i++)
	{
		ss << octans[i];
		if (i < 3)
			ss << ".";
	}
	IP = ss.str();

	return true;
}

bool Gui::Connect()
{
	bool result;
	mb = modbus(IP, port);
	mb.modbus_set_slave_id(0);
	result = mb.modbus_connect();
	return result;
}
