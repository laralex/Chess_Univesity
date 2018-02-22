#pragma once

#include "visual-block.h"
#include "textable.h"
#include "clock.h"
#include "settings-part.h"

namespace Game
{
	// Панель с таймером 1 игрока
	class ClockTab : public Graphics::VisualBlock, public Textable
	{
		friend class ClockTable;
	public:
		ClockTab(uint start_min = 0, uint start_sec = 0);
		
		void setPlayerName(const std::string&);	// Имя игрока
		void setFontColor(const sf::Color& color); // Цвет игрока
		void draw(Graphics::Window&); // Отрисовка
		void setIsActive(bool is_active); // Ход ли этого игрока или нет
		void build(); // Сборка
		void reset(); // Сброс до изначальных значений
		bool tick(); // Тик на 1 секунду
		void applyFont();
	private:
		Clock m_clock; // Таймер 
		sf::Text m_player_name, m_clock_text; // Имя и значение таймера
		bool m_is_active; // Тикает ли в данный момент
	};

	// Панель с таймерами ОБОИХ игроков
	class ClockTable : public Graphics::VisualBlock, public Textable
	{
		public:
			ClockTable(const sf::Vector2f& pos, const sf::Vector2f& size);
			~ClockTable() {delete m_settings;}
			void draw(Graphics::Window& window); // Отрисовка
			void build(); // Сборка
			bool tick(); // Тик на 1 секунду
			void reset(); // Сброс до изначальных значений
			bool update(); // Обновление каждый кадр
			void setAllClocks(uint start_min, uint start_sec); // Установка обоих таймеров в определенное время
			void setActivePlayer(bool is_white_player_active) {m_is_current_turn_white = is_white_player_active; } // Выбрать активного игрока
			void setSettings(Utils::SettingsPart * settings) {m_settings = settings;}; // Настройки
			void switchPlayerIfMoveMade(bool is_white_turn); // Включение другого таймера, если ход был совершен
			void applyFont(); 
		private:
			Utils::SettingsPart * m_settings; // Настройки
			bool m_is_current_turn_white = true; // Активный игрок
			float m_clock_tab_height, m_clock_tab_padding; // Визуальное отображение
			ClockTab m_white_clock, m_black_clock; // Оба таймера
			uint m_init_min, m_init_sec; // Стартовые значения
			sf::Clock m_sf_clock; // Часы SFML могут замерять системное время
	};
	
}
