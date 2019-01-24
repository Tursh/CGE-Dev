/*
 * PlayingState.h
 *
 *  Created on: Jan 3, 2019
 *      Author: tursh
 */

#pragma once

#include <State/State.h>
#include <GUI/Button.h>
#include <World/Entities/Player.h>
#include <View/Camera.h>
#include <World/World.h>

class PlayingState : public CGE::State::State
{
    CGE::World::World world;
	CGE::Entities::Player player_;
	CGE::View::Camera camera_;
public:
	PlayingState();

	~PlayingState() override;

	void tick(float delta) override;

	void draw() override;
};


