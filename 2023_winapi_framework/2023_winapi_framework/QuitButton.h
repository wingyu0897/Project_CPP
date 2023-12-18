#pragma once
#include "Button.h"
class QuitButton
	: public Button
{
public:
	QuitButton();
	~QuitButton();
public:
	void Click() override;
};

