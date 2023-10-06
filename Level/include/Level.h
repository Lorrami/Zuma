#pragma once

#include "Spaceship.h"
#include "DangerZone.h"
#include "MainMenuUI.h"
#include "InGameUI.h"

#include <vector>
#include <iostream>

enum class GameState : int
{
	MainMenu = -1,
	InProgress = 0,
	Win = 1,
	Loose = 2
};

class Level
{
private:
	MainMenuUI* m_MainMenuUI = new MainMenuUI();
	InGameUI* m_InGameUI = new InGameUI();

	sf::RenderWindow* m_CurrentWindow{};
	float m_ZoneTimer = 0.f;
	float m_TimeForAsteroids = 0.1f;
	GameState m_CurrentGameState = GameState::MainMenu;
	int m_ZonesCount = 3;
	int m_PointsPerAsteroid = 100;
	bool m_IsPlayerInDangerZone = false;

	const sf::Vector2i m_AsteroidSpeedRangeActive{ 300, 800 };
	const sf::Vector2i m_AsteroidSpeedRangeUnactive{ 100, 400 };
	sf::Vector2i m_AsteroidSpeedRange = m_AsteroidSpeedRangeUnactive;

	const sf::Vector2i m_AsteroidSizeRange{ 20, 50 };
	
	Spaceship* m_Player{};

	std::vector<DrawableObject*> m_DrawableObjects{};
	std::vector<DrawableObject*> m_PendingAddObjects{};
	std::vector<DrawableObject*> m_PendingRemoveObjects{};

	void OnGameInProgress();
	void CheckWinLooseConditions();
	void SpawnPlayer();
	void SpawnDangerZones();
	void SpawnAsteroids();
	void AdjustAsteroidsParameters();
	void OnGameInMainMenu();
	void OnWin();
	void OnLoose();
	void ClearLevel();

public:
	void Init();
	void Add(DrawableObject* objectToAdd);
	void Remove(DrawableObject* objectToRemove);
	void UpdateGameState();
	void Update();
	void Draw();

	void OnGameStarted();

	void ZonePassed();
	void OnDrawableObjectHit(const int damage, DrawableObject* hitObject, DrawableObject* hitCauser);

	DrawableObject* GetPlayer() const { return m_Player; }
	std::vector<DrawableObject*>& GetAllObjectsOnScreen() { return m_DrawableObjects; }
	bool GetPlayerStateInDangerZone() const { return m_IsPlayerInDangerZone; }
	void SetPlayerStateInDangerZone(const bool state) { m_IsPlayerInDangerZone = state; }

	GameState GetCurrentGameState() const { return m_CurrentGameState; }

	float GetZoneTimer() const { return m_ZoneTimer; }
	void UpdateZoneTimer(const float timer)
	{ 
		std::cout << m_ZoneTimer << std::endl;
		m_ZoneTimer = timer; }

};