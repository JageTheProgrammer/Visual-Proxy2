#pragma once
#include<stdint.h>
#include<string>
#include "discord_rpc.h"
#include "events.h"


void init_discord();
void update_rpc(const std::string& ingame);
