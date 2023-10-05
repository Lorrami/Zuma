#pragma once

#include "Level.h"

class Application
{
public:
	static Application* s_Instance;

	void Start();
	static Application& Get();

	sf::Time GetDeltaTime() const { return m_DeltaTime; }
	Level& GetCurrentLevel() { return m_Level; }
	sf::Vector2i GetMouseRelativeLocation() const { return m_MouseLocation; }
	sf::Vector2i GetWindowSize() const { return sf::Vector2i(m_WindowLength, m_WindowHeight); }
	sf::RenderWindow& GetCurrentWindow() { return m_Window; }

private:
	const unsigned int m_WindowLength = 1080;
	const unsigned int m_WindowHeight = 720;

	sf::Time m_DeltaTime{};

protected:
	sf::RenderWindow m_Window{};
	sf::Vector2i m_MouseLocation{};
	Level m_Level{};

private:
	void InitWindow();
	void Run();
	void HandleEvents();

};