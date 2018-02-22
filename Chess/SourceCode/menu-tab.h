#pragma once

#include "stdafx.h"
#include "visual-block.h"
#include "textable.h"
#include "command.h"

namespace Graphics
{
	// ���� �� ������� ����
	class MenuTab : public VisualBlock, public Textable
	{
		friend class MenuBlock;
	protected:
		// ��� ��������
		sf::Text m_text;
		// � ��������� � ���� �������
		const Command * command;
	public:
		// �-tor
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

		// ���������
		void setPosition(const sf::Vector2f& new_pos);
		void setPosition(float x, float y);
		void applyFont();
		void setColor(const sf::Color& color) { m_text.setFillColor(color); }

		// ���������
		void draw(Graphics::Window& window);

		// ������ �� ���������� ��������� �������
		void execute() 
		{ 
			if (command) command->execute();
		}

		// ���������� ������� � ����
		void setCommand(Command* new_command) 
		{ 
			if(command) delete command;
			command = new_command;
		}

		// ������� �������
		void deleteCommand()
		{
			if (command) delete command;
			command = nullptr;
		}
	};
}
