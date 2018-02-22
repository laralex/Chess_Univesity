#pragma once

#include "visual-block.h"
#include "textable.h"
#include "clock.h"
#include "settings-part.h"

namespace Game
{
	// ������ � �������� 1 ������
	class ClockTab : public Graphics::VisualBlock, public Textable
	{
		friend class ClockTable;
	public:
		ClockTab(uint start_min = 0, uint start_sec = 0);
		
		void setPlayerName(const std::string&);	// ��� ������
		void setFontColor(const sf::Color& color); // ���� ������
		void draw(Graphics::Window&); // ���������
		void setIsActive(bool is_active); // ��� �� ����� ������ ��� ���
		void build(); // ������
		void reset(); // ����� �� ����������� ��������
		bool tick(); // ��� �� 1 �������
		void applyFont();
	private:
		Clock m_clock; // ������ 
		sf::Text m_player_name, m_clock_text; // ��� � �������� �������
		bool m_is_active; // ������ �� � ������ ������
	};

	// ������ � ��������� ����� �������
	class ClockTable : public Graphics::VisualBlock, public Textable
	{
		public:
			ClockTable(const sf::Vector2f& pos, const sf::Vector2f& size);
			~ClockTable() {delete m_settings;}
			void draw(Graphics::Window& window); // ���������
			void build(); // ������
			bool tick(); // ��� �� 1 �������
			void reset(); // ����� �� ����������� ��������
			bool update(); // ���������� ������ ����
			void setAllClocks(uint start_min, uint start_sec); // ��������� ����� �������� � ������������ �����
			void setActivePlayer(bool is_white_player_active) {m_is_current_turn_white = is_white_player_active; } // ������� ��������� ������
			void setSettings(Utils::SettingsPart * settings) {m_settings = settings;}; // ���������
			void switchPlayerIfMoveMade(bool is_white_turn); // ��������� ������� �������, ���� ��� ��� ��������
			void applyFont(); 
		private:
			Utils::SettingsPart * m_settings; // ���������
			bool m_is_current_turn_white = true; // �������� �����
			float m_clock_tab_height, m_clock_tab_padding; // ���������� �����������
			ClockTab m_white_clock, m_black_clock; // ��� �������
			uint m_init_min, m_init_sec; // ��������� ��������
			sf::Clock m_sf_clock; // ���� SFML ����� �������� ��������� �����
	};
	
}
