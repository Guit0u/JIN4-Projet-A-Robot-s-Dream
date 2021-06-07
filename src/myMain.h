#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "pugixml.hpp"
#include <map>
#include <stdio.h>
#include <iostream>
#include <string>

#include "DialogueBox.h"
#include "Player.h"
#include "Level.h"
#include "ContactListener.h"

enum class GameState
{
	gameplay,
	dialogue
};

int myMain();