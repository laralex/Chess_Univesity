#pragma once

#include "stdafx.h"
#include "menu-tab.h"
#include "visual-block.h"
#include "textable.h"
#include "mouse-behaviour.h"
#include "settings-part.h"

namespace Graphics
{
	// Меню
	class MenuBlock : public VisualBlock, public Textable, public MouseBehaviour
	{
	private:
	protected:
		// Цвет для активного и неактивного пункта меню
		sf::Color m_active_color, m_inactive_color;
		// Текстура пункта меню
		std::shared_ptr<sf::Texture> m_tab_texture;
		// Пункты меню
		std::vector<MenuTab*> m_tabs;
		// Номер активного пункта и число пунктов
		uint m_tabs_number, m_max_tab_height, m_actual_tab_height;
		int m_active_tab;
		// Флаг, есть ли необработанная пока что смена пункта меню
		bool m_tab_switched;
		// Настройки
		Utils::SettingsPart * m_settings;
	public:
		// c-tor & d-tor
		MenuBlock(const sf::Vector2f pos, const sf::Vector2f size)
			: VisualBlock(pos.x,pos.y,size.x,size.y), Textable(), m_tabs(), m_active_tab(0),
			  m_tab_switched(false), m_tabs_number(0)
			{ }
		~MenuBlock()
		{ 
			for(auto it = m_tabs.begin(); it != m_tabs.end(); ++it)
				delete *it;
			delete m_settings;
		}

		// Добавление нового пункта 2 способами
		void addTab(const std::string& tab_name);
		void operator+=(const std::string& tab_name);

		// Установка цветов активного и неактивного пункта
		void setSettings(Utils::SettingsPart * settings) { m_settings = settings; }
		void setActiveColor(const sf::Color color) { m_active_color = color; }
		void setInactiveColor(const sf::Color color) { m_inactive_color = color; }
		void setMaxTabHeight(uint height) { m_max_tab_height = height; }
		void setTabTexture(const std::shared_ptr<sf::Texture>& texture) { m_tab_texture = texture; }
		void setTabTexture(const std::string filepath);
		void applyFont() {}

		// Переход к пунктам ниже-выше
		void moveNextTab();
		void movePrevTab();
		void setActiveTab(int tab_num);

		// Связывает конкретный пункт с командой
		void setCommand(int tab_num, const Command* command);

		// Сформировать визуальное расположение меню и пунктов 
		// Имеет смысл вызывать, когда все необходимые настройки меню уже применены
		void build();

		// Отрисовка на экран
		void draw(Graphics::Window& window);

		// Обработка мыши
		void mouse_down(const sf::Vector2i&);
		void mouse_up(const sf::Vector2i&);
		void hover(const sf::Vector2i&);
		void dishover(const sf::Vector2i&);
		bool needsToProcessMouse(const sf::Vector2i&);
	};

}
