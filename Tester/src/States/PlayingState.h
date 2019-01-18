/*
 * PlayingState.h
 *
 *  Created on: Jan 3, 2019
 *      Author: tursh
 */

#pragma once

#include <State/State.h>
#include <GUI/Button.h>
#include <Entities/Player.h>
#include <View/Camera.h>

class PlayingState : public CGE::State::State
{
	CGE::Entities::Player player_;
	CGE::View::Camera camera_;
public:
	PlayingState();

	~PlayingState() override;

	void tick(float delta) override;

	void draw() override;
};


