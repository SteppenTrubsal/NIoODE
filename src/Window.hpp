#pragma once
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui-SFML.h>
#include <implot.h>


class Window
{
public:
	Window();
	~Window();


	void start();
	void stop();
private:
	void mainLoop();
	void renderGUI();
	static void PushStyleCompact()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, (float)(int)(style.FramePadding.y * 0.60f)));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x, (float)(int)(style.ItemSpacing.y * 0.60f)));
	}
	static const char* uTC(const char8_t* str)
	{
		return reinterpret_cast<const char*> (str);
	}
	static void PopStyleCompact()
	{
		ImGui::PopStyleVar(2);
	}
	sf::RenderWindow window;
	bool isStarted = false;
	bool isTheResultReady = false;
	std::vector<graph> res;
};
Window::Window() :
	window(sf::VideoMode(1024, 728), L"LAB 4")
{}

Window::~Window()
{
}

void Window::start()
{
	if (isStarted)
	{
		return;
	}
	else
	{
		isStarted = true;
		mainLoop();
	}


}

void Window::stop()
{
	if (isStarted)
	{
		isStarted = false;
	}
}

void Window::mainLoop()
{
	if (!ImGui::SFML::Init(window)) return;
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromFileTTF("Fonts/arial.ttf", 16.f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	ImGui::SFML::UpdateFontTexture();

	ImGui::StyleColorsLight();
	io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
	ImPlot::CreateContext();

	sf::Clock deltaClock;
	while (window.isOpen() && isStarted)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(window, event);
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		ImGui::SFML::Update(window, deltaClock.restart());
		renderGUI();
		window.clear();

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	ImPlot::DestroyContext();
}
	/*static int number = 10;
	static bool limExWin = false;
	static std::string funk = "(1-6*x)*exp(2*x)";
	static std::string lim1 = "0", lim2 = "2/3", preciseMeaningStr = "-2";
	static double dLim1 = 0, dLim2 = 2./3., preciseMeaning = -2.;


	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("Main Window", nullptr,
		ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::LabelText("##label", uTC(u8"Численное интегрирование: "));

	ImGui::BeginGroup();
	ImGui::LabelText("##label", uTC(u8"Введите подынтегральное выражение (без dx):"));
	ImGui::InputText("##TBf", &funk);
	ImGui::EndGroup();

	ImGui::SameLine();
	ImGui::BeginGroup();
	ImGui::LabelText("##label", uTC(u8"Введите пределы интегрирования:"));
	ImGui::InputText("##TBl1", &lim1);

	ImGui::InputText("##TBl2", &lim2);
	ImGui::EndGroup();
	float windowWidth = ImGui::GetContentRegionAvail().x;


	float sliderWidth = windowWidth / 3.0f;


	ImGui::PushItemWidth(sliderWidth);
	ImGui::SliderInt(uTC(u8"Кол-во"), &number, 0, 500);
	ImGui::SameLine();
	ImGui::InputText(uTC(u8"Точное значение"), &preciseMeaningStr);
	ImGui::PopItemWidth();
	if (ImGui::Button(uTC(u8"Рассчитать")))
	{
		mu::Parser parser;

		try
		{
			parser.SetExpr(lim1);
			dLim1 = parser.Eval();
			parser.SetExpr(lim2);
			dLim2 = parser.Eval();
			parser.SetExpr(preciseMeaningStr);
			preciseMeaning = parser.Eval();
			res = getRes(dLim1, dLim2, funk, preciseMeaning, number);

		}
		catch (mu::Parser::exception_type& e)
		{
			std::cerr << e.GetMsg() << std::endl;
			limExWin = true;
			isTheResultReady = false;
			goto exEnd;
		}
		isTheResultReady = true;

	}
	if (isTheResultReady)
	{
		{
			ImGui::LabelText("##label", uTC(u8"Графики:"));

			for (size_t i = 0; i < res.size(); i++)
			{
				if (ImPlot::BeginPlot(res[i].name.c_str())) {
					ImPlot::SetupAxes(uTC(u8"X"), uTC(u8"Y"));
					ImPlot::PlotLine("##plot", res[i].x.data(), res[i].y.data(), res[i].y.size());
					ImPlot::EndPlot();
				}
			}



		}

	}

exEnd:
	if (limExWin)
	{
		ImGui::Begin(uTC(u8"Ошибка!"), &limExWin, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text(uTC(u8"Неверно введены пределы или функция"));
		if (ImGui::Button(uTC(u8"Закрыть")))
			limExWin = false;
		ImGui::End();
	}

	ImGui::End();*/

void Window::renderGUI() {
	static double limA = 2.7182, limB = 5.7182;
	static double solX = 2.7182, solY = 2;
	static double h = 0.1;
	static std::string sLimA = "2.7182", sLimB = "5.7182";
	static std::string equation = "(1/x*y)*((y^2/ln(x))-1)";
	static std::string solution = "sqrt(2*(ln(x))^2+2*ln(x))";
	static std::string sH = "0.1";

	static bool limExWin = false, isResReady = false;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("Main Window", nullptr,
		ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::LabelText("##label", uTC(u8"Решение задачи Коши: "));

	ImGui::BeginGroup();
	ImGui::LabelText("###label", uTC(u8"y' = "));
	ImGui::SameLine(80);
	ImGui::InputText("###TBe", &equation);
	ImGui::LabelText("###label", uTC(u8"y = "));
	ImGui::SameLine(80);
	ImGui::InputText("###TBs", &solution);
	ImGui::LabelText("###label", uTC(u8"Введите h:"));
	ImGui::SameLine(80);
	ImGui::InputText("###TBlh", &sH);
	ImGui::EndGroup();

	ImGui::SameLine();
	ImGui::BeginGroup();
	ImGui::LabelText("###label", uTC(u8"Введите пределы x:"));
	ImGui::InputText("###TBla", &sLimA);
	ImGui::InputText("###TBlb", &sLimB);
	ImGui::EndGroup();

	if(ImGui::Button(uTC(u8"Рассчитать"))){
		mu::Parser parser;
		try {
			parser.SetExpr(sH);
			h = parser.Eval();
			parser.SetExpr(sLimA);
			limA = parser.Eval();
			parser.SetExpr(sLimB);
			limB = parser.Eval();
		}
		catch(mu::Parser::exception_type& e){
			std::cerr << e.GetMsg() << std::endl;
			limExWin = true;
			isTheResultReady = false;
			goto exEnd;
		}
		res = getResultGraphics(limA, limB, solY, equation, h, solution);
		isTheResultReady = true;
		if (isTheResultReady) {
			ImGui::LabelText("##label", uTC(u8"Графики:"));

			for (size_t i = 0; i < res.size(); i++){
				if (ImPlot::BeginPlot(res[i].name.c_str())) {
					ImPlot::SetupAxes(uTC(u8"X"), uTC(u8"Y"));
					ImPlot::PlotLine("##plot", res[i].x.data(), res[i].y.data(), res[i].y.size());
					ImPlot::EndPlot();
				}
			}
		}
	}

exEnd:
	if (limExWin)
	{
		ImGui::Begin(uTC(u8"Ошибка!"), &limExWin, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text(uTC(u8"Неверно введены пределы или функция"));
		if (ImGui::Button(uTC(u8"Закрыть")))
			limExWin = false;
		ImGui::End();
	}

	ImGui::End();
}