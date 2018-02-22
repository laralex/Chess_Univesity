#pragma once

// Интерфейс команд

class Command
{
protected:
	Command() {}
public:
	virtual void execute() const = 0;
};

class EmptyCommand : public Command
{
	public:
		void execute() const {}
};
