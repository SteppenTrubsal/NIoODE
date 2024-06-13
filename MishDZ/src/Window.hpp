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
	std::vector<graph> diffGraph;
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

void Window::renderGUI() {
	static double limA = 2.7182, limB = 5.7182;
	static double solX = 2.7182, solY = 2;
	static double h = 0.1;
	static int num = 10;
	static std::string sLimA = "exp(1)", sLimB = "exp(1)+3";
	static std::string equation = "(1/(x*y))*(((y^2)/(ln(x)))-1)";
	static std::string solution = "sqrt(2*(ln(x))^2+2*ln(x))";
	static std::string sH = "0.1";
	static std::string sSolX = "exp(1)";
	static std::string sSolY = "2";
	static bool sol = false, diff = false;
	static bool resFlag = true, diffFlag = true;

	static bool limExWin = false, isResReady = false;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("Main Window", nullptr,
		ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoBringToFrontOnFocus);

	float windowWidth = ImGui::GetContentRegionAvail().x;
	float sliderWidth = windowWidth / 3.0f;
	float textWidth = windowWidth / 2.0f;
	ImGui::PushItemWidth(textWidth);

	ImGui::LabelText("##label", uTC(u8"Решение задачи Коши: "));
	ImGui::SameLine(textWidth+85);
	ImGui::LabelText("###label", uTC(u8"Введите пределы x:"));

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
	ImGui::InputText("###TBla", &sLimA);
	ImGui::InputText("###TBlb", &sLimB);
	ImGui::PushItemWidth(45);
	ImGui::LabelText("###label", uTC(u8"y("));
	ImGui::SameLine(15);
	ImGui::InputText("###TBsx", &sSolX);
	ImGui::SameLine(55);
	ImGui::LabelText("###label", uTC(u8") = "));
	ImGui::SameLine(85);
	ImGui::InputText("###TBsy", &sSolY);
	ImGui::EndGroup();

	ImGui::PushItemWidth(sliderWidth);
	ImGui::SliderInt(uTC(u8"n"), &num, 2, 50);

	ImGui::Checkbox(uTC(u8"Результат"), &resFlag);
	ImGui::SameLine();
	ImGui::Checkbox(uTC(u8"Погрешность"), &diffFlag);

	if(ImGui::Button(uTC(u8"Рассчитать"))){
		mu::Parser parser;
		try {
			parser.SetExpr(sH);
			h = parser.Eval();
			parser.SetExpr(sLimA);
			limA = parser.Eval();
			parser.SetExpr(sLimB);
			limB = parser.Eval();
			parser.SetExpr(sSolX);
			solX = parser.Eval();
			parser.SetExpr(sSolY);
			solY = parser.Eval();
		}
		catch(mu::Parser::exception_type& e){
			std::cerr << e.GetMsg() << std::endl;
			limExWin = true;
			isTheResultReady = false;
			goto exEnd;
		}
		if (resFlag) {
			res = getResultGraphics(limA, limB, solY, equation, h, solution);
		}
		if (diffFlag) {
			diffGraph = getDiffGraph(limA, limB, num, solY, equation, solution);
		}
		isTheResultReady = true;
	}
	if (isTheResultReady) {
		ImGui::LabelText("##label", uTC(u8"Графики решений:"));
		if (resFlag) {
			if (ImPlot::BeginPlot("Solution")) {
				ImPlot::SetupAxes(uTC(u8"X"), uTC(u8"Y"));
				for (size_t i = 0; i < res.size(); i++) {
					ImPlot::PlotLine(res[i].name.c_str(), res[i].x.data(), res[i].y.data(), res[i].y.size());
				}
				ImPlot::EndPlot();
			}
		}

		if (diffFlag) {
			ImGui::LabelText("##label", uTC(u8"Графики погрешности:"));
			if (ImPlot::BeginPlot("Difference")) {
				ImPlot::SetupAxes(uTC(u8"H"), uTC(u8"D"));
				for (size_t i = 0; i < diffGraph.size(); i++) {
					ImPlot::PlotLine(diffGraph[i].name.c_str(), diffGraph[i].x.data(), diffGraph[i].y.data(), diffGraph[i].y.size());
				}
				ImPlot::EndPlot();
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