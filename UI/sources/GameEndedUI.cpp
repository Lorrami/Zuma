#include "GameEndedUI.h"

#include "Application.h"

#include <sstream>
#include <iostream>
#include <string>

void GameEndedUI::Init(const bool gameState)
{
	m_CurrentState = gameState;
	InitTexts();
	/*InitStartButton();
	InitLeaveButton();*/
}

void GameEndedUI::InitTexts()
{
	if (!m_Font->loadFromFile("../../../Resources/Text1.ttf"))
		return; 

	if (m_CurrentState)
	{
		InitTextsForWin();
	}
	else
	{
		InitTextsForLoose();
	}
	InitMainMenuButton();
	InitTimer();
}

void GameEndedUI::InitTextsForWin()
{
	m_ResultText = new sf::Text(*m_Font, "YOU WIN!");
	sf::FloatRect resultRect = m_ResultText->getLocalBounds();
	m_ResultText->setOrigin(sf::Vector2f(resultRect.left + resultRect.width / 2.0f,
		resultRect.top + resultRect.height / 2.0f));
	m_ResultText->setPosition(sf::Vector2f(540.f, 250.f));
	m_ResultText->setFillColor(sf::Color::Green);

	m_PlayerScoreText = new sf::Text(*m_Font, "Gained score: " + std::to_string(dynamic_cast<Spaceship*>(Application::Get().GetCurrentLevel().GetPlayer())->PlayerScoreComponent.GetCurrentScore()));
	sf::FloatRect textRect = m_PlayerScoreText->getLocalBounds();
	m_PlayerScoreText->setOrigin(sf::Vector2f(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f));
	m_PlayerScoreText->setPosition(sf::Vector2f(540.f, 300.f));
}

void GameEndedUI::InitTextsForLoose()
{
	m_ResultText = new sf::Text(*m_Font, "YOU LOST :(");
	sf::FloatRect resultRect = m_ResultText->getLocalBounds();
	m_ResultText->setOrigin(sf::Vector2f(resultRect.left + resultRect.width / 2.0f,
		resultRect.top + resultRect.height / 2.0f));
	m_ResultText->setPosition(sf::Vector2f(540.f, 250.f));
	m_ResultText->setFillColor(sf::Color::Red);

	m_PlayerScoreText = new sf::Text(*m_Font, "Gained score: " + std::to_string(dynamic_cast<Spaceship*>(Application::Get().GetCurrentLevel().GetPlayer())->PlayerScoreComponent.GetCurrentScore()));
	sf::FloatRect textRect = m_PlayerScoreText->getLocalBounds();
	m_PlayerScoreText->setOrigin(sf::Vector2f(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f));
	m_PlayerScoreText->setPosition(sf::Vector2f(540.f, 300.f));
}

void GameEndedUI::InitMainMenuButton()
{

}

void GameEndedUI::InitTimer()
{
	float time = Application::Get().GetCurrentLevel().GetGlobalGameTime();
	if (time >= 0.f && time < 10.f)
	{
		m_GlobalTimer = new sf::Text(*m_Font, "Spent time: " + FormatTimer(time, 3) + " sec.");
	}
	else if (time >= 10.f && time < 60.f)
	{
		m_GlobalTimer = new sf::Text(*m_Font, "Spent time: " + FormatTimer(time, 4) + " sec.");
	}
	else if (time >= 60.f)
	{
		int minutes = time / 60;
		m_GlobalTimer = new sf::Text(*m_Font, "Spent time: " + std::to_string(minutes) + " min. " + FormatTimer(time - minutes * 60, 4) + " sec.");
	}

	sf::FloatRect textRect = m_GlobalTimer->getLocalBounds();
	m_GlobalTimer->setOrigin(sf::Vector2f(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f));
	m_GlobalTimer->setPosition(sf::Vector2f(540.f, 350.f));
}

std::string GameEndedUI::FormatTimer(float time, int digits)
{
	std::ostringstream ss;
	ss.precision(digits);
	ss << time;
	return ss.str();
}

void GameEndedUI::Update()
{
	if (CheckMainMenuButton())
	{
		Application::Get().GetCurrentLevel().Init();
		return;
	}

	Application::Get().GetCurrentWindow().draw(*m_MainMenuButton);
	Application::Get().GetCurrentWindow().draw(*m_ResultText);
	Application::Get().GetCurrentWindow().draw(*m_PlayerScoreText);
	Application::Get().GetCurrentWindow().draw(*m_GlobalTimer);
}

bool GameEndedUI::CheckMainMenuButton()
{
	return true;
}

//
//void MainMenuUI::InitStartButton()
//{
//	if (m_StartButtonTexture->loadFromFile("../../../Resources/StartButton.png"))
//	{
//		m_StartButton->setTexture(m_StartButtonTexture);
//		m_StartButton->setSize(sf::Vector2f(230, 90));
//		m_StartButton->setOrigin(sf::Vector2f(m_StartButton->getSize().x / 2, m_StartButton->getSize().y / 2));
//		m_StartButton->setPosition(sf::Vector2f(540.f, 460.f));
//	}
//}
//
//void MainMenuUI::InitLeaveButton()
//{
//	if (m_LeaveButtonTexture->loadFromFile("../../../Resources/LeaveButton.png"))
//	{
//		m_LeaveButton->setTexture(m_LeaveButtonTexture);
//		m_LeaveButton->setSize(sf::Vector2f(110, 90));
//		m_LeaveButton->setOrigin(sf::Vector2f(m_LeaveButton->getSize().x / 2, m_LeaveButton->getSize().y / 2));
//		m_LeaveButton->setPosition(sf::Vector2f(540.f, 560.f));
//	}
//}
//
//void MainMenuUI::Update()
//{
//	if (CheckStartButton())
//	{
//		Application::Get().GetCurrentLevel().OnGameStarted();
//		return;
//	}
//	else if (CheckLeaveButton())
//	{
//		Application::Get().Stop();
//		return;
//	}
//
//	Application::Get().GetCurrentWindow().draw(*m_StartButton);
//	Application::Get().GetCurrentWindow().draw(*m_LeaveButton);
//	Application::Get().GetCurrentWindow().draw(*m_PlayerScoreText);
//	Application::Get().GetCurrentWindow().draw(*m_WelcomeText);
//}
//
//bool MainMenuUI::CheckStartButton()
//{
//	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
//		return false;
//
//	if (m_StartButton->getGlobalBounds().contains(
//		sf::Vector2f((float)Application::Get().GetMouseRelativeLocation().x,
//			(float)Application::Get().GetMouseRelativeLocation().y)))
//	{
//		return true;
//	}
//	return false;
//}
//
//bool MainMenuUI::CheckLeaveButton()
//{
//	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
//		return false;
//
//	if (m_LeaveButton->getGlobalBounds().contains(
//		sf::Vector2f((float)Application::Get().GetMouseRelativeLocation().x,
//			(float)Application::Get().GetMouseRelativeLocation().y)))
//	{
//		return true;
//	}
//	return false;
//
//}
