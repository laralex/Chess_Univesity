#pragma once

#include "stdafx.h"
#include "visual-block.h"
#include "textable.h"
#include "command.h"

namespace Graphics
{
	// Один из пунктов меню
	class MenuTab : public VisualBlock, public Textable
	{
		friend class MenuBlock;
	protected:
		// Его название
		sf::Text m_text;
		// И связанная с нима команда
		const Command * command;
	public:
		// с-tor
		MenuTab(const std::string& title)
			: VisualBlock(), Textable(), command(0)
		{ 
			m_text.setString(title);
		}
		// d-tor
		~MenuTab()
		{
			if(command)
				delete command;
		}

		// Настройка
		void setPosition(const sf::Vector2f& new_pos);
		void setPosition(float x, float y);
		void applyFont();
		void setColor(const sf::Color& color) { m_text.setFillColor(color); }

		// Отрисовка
		void draw(Graphics::Window& window);

		// Запрос на выполнение связанной команды
		void execute() 
		{ 
			if (command) command->execute();
		}

		// Установить команду в слот
		void setCommand(Command* new_command) 
		{ 
			if(command) delete command;
			command = new_command;
		}

		// Удалить команду
		void deleteCommand()
		{
			if (command) delete command;
			command = nullptr;
		}
	};
}
