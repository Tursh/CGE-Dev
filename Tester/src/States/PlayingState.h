/*
 * PlayingState.h
 *
 *  Created on: Jan 3, 2019
 *      Author: tursh
 */

#pragma once

#include <State/State.h>
#include <GUI/Button.h>

class PlayingState : public CGE::State::State
{
public:
	PlayingState();
	~PlayingState();
	void tick(float delta);
	void draw();
};


