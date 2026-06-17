#define HOOKAF(ret, func, ...) \
    ret (*orig##func)(__VA_ARGS__); \
    ret my##func(__VA_ARGS__)

bool removeDirectory(const std::string& path) {
             try {
                 if (fs::exists(path)) {
                     fs::remove_all(path);
                     return true;
                 } else {
                     return true;
                 }
             } catch (const fs::filesystem_error& e) {
                 return false;
             }
}

std::string format(const void* ptr) {
    uint64_t address_value = reinterpret_cast<uint64_t>(ptr);
    
    std::stringstream ss;
    ss << "0x" << std::hex << std::setw(16) << std::setfill('0') << address_value;
    return ss.str();
}

void insertionSortPlayers(std::vector<PlayerStruct>& players) {
    for (size_t i = 1; i < players.size(); ++i) {
        int j = i;

        while (j > 0 && players[j - 1].nickname > players[j].nickname) {
            std::swap(players[j], players[j - 1]);
            j = j - 1;
        }
    }
}

bool MobDetected(int actorId) {
    switch (actorId) {
		case 390: // Allay
		    return !noAllays;
		case 5006: // Armadillo
		    return !noArmadillos;
		case 4994: // Axolotl
		    return !noAxolotls;
		case 33043: // Bat
		    return !noBats;
		case 378: // Bee
		    return !noBees;
		case 5002: // Camel
		    return !noCamels;
		case 21323: // Cat
		    return !noCats;
		case 4874: // Chicken
		    return !noChickens;
		case 9072: // Cod
		    return  !noCods;
		case 916: // Copper Golem
		    return !noCopperGolems;
		case 4875: // Cow
		    return !noCows;
		case 8991: // Dolphin
		    return !noDolphins;
		case 2118424: // Donkey
        case 2118425: // Mule
		    return !noDonkeys;
		case 4985: // Fox
		    return !noFoxes;
		case 4996: // Frog
		    return !noFrogs;
		case 9089: // Glow Squid
		    return !noGlowSquids;
		case 4992: // Goat
		    return !noGoats;
		case 5011: // Happy Ghast
		    return !noHappyGhasts;
		case 4893: // Llama
		case 5021: // Wandering Llama
		    return !noLlamas;
		case 21270: // Ocelot
		    return !noOcelots;
		case 4977: // Panda
		    return !noPandas;
		case 21278: // Parrot
		    return !noParrots;
		case 4876: // Pig
		    return !noPigs;
		case 379: // Piglin
		    return !noPiglins;
		case 9068: // Pufferfish
		    return !noPufferfishes;
		case 4882: // Rabbit
		    return !noRabbits;
		case 9069: // Salmon
		    return !noSalmons;
		case 4877: // Sheep
		    return !noSheeps;
		case 5003: // Sniffer
		    return !noSniffers;
		case 8977: // Squid
		    return !noSquids;
		case 4989: // Strider
		    return !noStriders;
		case 9093: // Tadpole
		    return !noTadpoles;
		case 9071: // Tropical Fish
		    return !noTropicalfishes;
		case 4938: // Turtle
		    return !noTurtles;
		case 886: // Wandering Trader
		    return !noWanderingtraders;
		case 21262: // Wolf
		    return !noWolfs;
		case 68388: // Zombie Piglin
		    return !noZombiepiglins;
		case 199540: // Zombie Villager
		    return !noZombievillagers;
		case 788: // Iron Golem
		    return !noIronGolem;
        case 789: // Snowman
		    return !noSnowMan;
        case 16778099: // Villagers
		    return !noVillagers;
        case 2118423: // Horse
        case 2186010: // Skeleton Horse
        case 2186011: // Zombie Horse
            return !noHorses;
		case 90: // Boat
        case 524372: // Minecart
        case 524386: // Minecart with chest
        case 524384: // Minecart with hopper
        case 524385: // Minecart with tnt
        case 524388: // Minecart with command block
        case 317: // Armor Stand
		case 319: // Player
        case 307: // NPC
        case 64: // Item
        case 66: // Falling Block
        case 69: // XP
        case 77: // Fishing Hook
        case 95: // Lingering Potion Field
        case 12582992: // Arrow
        case 4194390: // Splash Potion
        case 4194405: // Lingering Potion
        case 12582985: // Trident
        case 4194372: // XP Bottle
        case 4194385: // Snowball
        case 4194447: // Wind Blow
        case 4194391: // Ender Pearl
        case 70: // Ender Eye
        case 4194386: // Egg
        case 83: // Painting
        case 4194383: // Ender Dragon Fireball
        case 88: // Lead
        case 72: // Firework
        case 65: // Primed TNT
        case 93: // Lightning Bolt
            return false;
    }
	return true;
}

ImU32 GetOreColor(std::string oreName) {
    if (oreName == oxorany("tile.diamond_ore") || oreName == oxorany("tile.deepslate_diamond_ore") || oreName == oxorany("tile.diamond_block"))
        return IM_COL32(0, 255, 255, 255);
    else if (oreName == oxorany("tile.gold_ore") || oreName == oxorany("tile.deepslate_gold_ore") || oreName == oxorany("tile.nether_gold_ore") || 
             oreName == oxorany("tile.gold_block") || oreName == oxorany("tile.raw_gold_block"))
        return IM_COL32(255, 255, 0, 255);
    else if (oreName == oxorany("tile.iron_ore") || oreName == oxorany("tile.deepslate_iron_ore") || oreName == oxorany("tile.iron_block") || 
             oreName == oxorany("tile.raw_iron_block"))
        return IM_COL32(255, 165, 0, 255);
    else if (oreName == oxorany("tile.coal_ore") || oreName == oxorany("tile.deepslate_coal_ore") || oreName == oxorany("tile.coal_block"))
        return IM_COL32(0, 0, 0, 255);
    else if (oreName == oxorany("tile.redstone_ore") || oreName == oxorany("tile.deepslate_redstone_ore") || oreName == oxorany("tile.redstone_block"))
        return IM_COL32(255, 0, 0, 255);
    else if (oreName == oxorany("tile.lapis_ore") || oreName == oxorany("tile.deepslate_lapis_ore") || oreName == oxorany("tile.lapis_block"))
        return IM_COL32(0, 0, 255, 255);
    else if (oreName == oxorany("tile.copper_ore") || oreName == oxorany("tile.deepslate_copper_ore") || oreName == oxorany("tile.copper_block") || 
             oreName == oxorany("tile.raw_copper_block"))
        return IM_COL32(184, 115, 51, 255);
    else if (oreName == oxorany("tile.emerald_ore") || oreName == oxorany("tile.deepslate_emerald_ore") || oreName == oxorany("tile.emerald_block"))
        return IM_COL32(0, 255, 0, 255);
    else if (oreName == oxorany("tile.netherite_block") || oreName == oxorany("tile.ancient_debris"))
        return IM_COL32(83, 83, 83, 255);
    else if (oreName == oxorany("tile.large_amethyst_bud") || oreName == oxorany("tile.small_amethyst_bud") || oreName == oxorany("tile.amethyst_cluster") || oreName == oxorany("tile.medium_amethyst_bud"))
        return IM_COL32(170, 0, 255, 255);
    else if (oreName == oxorany("tile.barrel"))
        return IM_COL32(139, 69, 19, 255);
    else if (oreName == oxorany("tile.obsidian"))
        return IM_COL32(30, 10, 60, 255);
	else if (oreName == oxorany("tile.quartz_ore"))
        return IM_COL32(255, 255, 255, 255);
}

bool allowToXrayRender(std::string tileName) {
    if (tileName == oxorany("tile.diamond_ore")) return xrayDiamond;
    else if (tileName == oxorany("tile.gold_ore")) return xrayGold;
    else if (tileName == oxorany("tile.iron_ore")) return xrayIron;
    else if (tileName == oxorany("tile.coal_ore")) return xrayCoal;
    else if (tileName == oxorany("tile.emerald_ore")) return xrayEmerald;
    else if (tileName == oxorany("tile.quartz_ore")) return xrayQuartz;
    else if (tileName == oxorany("tile.copper_ore")) return xrayCopper;
    else if (tileName == oxorany("tile.redstone_ore")) return xrayRedstone;
    else if (tileName == oxorany("tile.lapis_ore")) return xrayLapis;
    else if (tileName == oxorany("tile.nether_gold_ore")) return xrayGold;
    else if (tileName == oxorany("tile.deepslate_copper_ore")) return xrayCopper;
    else if (tileName == oxorany("tile.deepslate_gold_ore")) return xrayGold;
    else if (tileName == oxorany("tile.deepslate_iron_ore")) return xrayIron;
    else if (tileName == oxorany("tile.deepslate_coal_ore")) return xrayCoal;
    else if (tileName == oxorany("tile.deepslate_lapis_ore")) return xrayLapis;
    else if (tileName == oxorany("tile.deepslate_diamond_ore")) return xrayDiamond;
    else if (tileName == oxorany("tile.deepslate_redstone_ore")) return xrayRedstone;
    else if (tileName == oxorany("tile.deepslate_emerald_ore")) return xrayEmerald;
    else if (tileName == oxorany("tile.diamond_block")) return xrayDiamond;
    else if (tileName == oxorany("tile.emerald_block")) return xrayEmerald;
    else if (tileName == oxorany("tile.gold_block")) return xrayGold;
    else if (tileName == oxorany("tile.iron_block")) return xrayIron;
    else if (tileName == oxorany("tile.redstone_block")) return xrayRedstone;
    else if (tileName == oxorany("tile.netherite_block")) return xrayNetherite;
    else if (tileName == oxorany("tile.ancient_debris")) return xrayNetherite;
    else if (tileName == oxorany("tile.lapis_block")) return xrayLapis;
    else if (tileName == oxorany("tile.coal_block")) return xrayCoal;
    else if (tileName == oxorany("tile.copper_block")) return xrayCopper;
    else if (tileName == oxorany("tile.raw_iron_block")) return xrayIron;
    else if (tileName == oxorany("tile.raw_copper_block")) return xrayCopper;
    else if (tileName == oxorany("tile.raw_gold_block")) return xrayGold;
    else if (tileName == oxorany("tile.large_amethyst_bud")) return xrayAmethyst;
    else if (tileName == oxorany("tile.small_amethyst_bud")) return xrayAmethyst;
    else if (tileName == oxorany("tile.amethyst_cluster")) return xrayAmethyst;
    else if (tileName == oxorany("tile.medium_amethyst_bud")) return xrayAmethyst;
    else if (tileName == oxorany("tile.barrel")) return xrayBarrel;
    else if (tileName == oxorany("tile.obsidian")) return xrayObsidian;
    
    return false;
}

float distanceTo(vec3_t *playerPosition, vec3_t *target) {
    return std::sqrt(std::pow(playerPosition->x - target->x, 2) +
                     std::pow(playerPosition->y - target->y, 2) +
                     std::pow(playerPosition->z - target->z, 2));
}

float mobDistanceTo(vec3_t *playerPosition, vec3_t *target, float hitboxHeight) {
    // Вычисляем точки на хитбоксе
    float a1 = -hitboxHeight;
    float a5 = 0.0f;
    float a3 = -hitboxHeight / 2.0f;
    float a2 = (a1 + a3) / 2.0f;
    float a4 = (a3 + a5) / 2.0f;

    float hitboxPoints[] = {a1, a2, a3, a4, a5};

    float closestPoint = hitboxPoints[0];
    float minDistance = std::sqrt(std::pow(playerPosition->y - (target->y + hitboxPoints[0]), 2));

    for (int i = 1; i < 5; ++i) {
        float distance = std::sqrt(std::pow(playerPosition->y - (target->y + hitboxPoints[i]), 2));
        if (distance < minDistance) {
            minDistance = distance;
            closestPoint = hitboxPoints[i];
        }
    }

    return std::sqrt(std::pow(playerPosition->x - target->x, 2) +
                     std::pow(playerPosition->y - (target->y + closestPoint), 2) +
                     std::pow(playerPosition->z - target->z, 2));
}




float hackDistanceTo(vec3_t *playerPosition, vec3_t *target) {
    float targetY = target->y;

    if (targetY - 0.75 > playerPosition->y) {
        targetY -= 1;
    }

    return std::sqrt(std::pow(playerPosition->x - target->x, 2) +
                     std::pow(playerPosition->y - targetY, 2) +
                     std::pow(playerPosition->z - target->z, 2));
}

bool OWorldToScreen(glm::vec3 origin, glm::vec3 pos, glm::vec2& screen, glm::vec2 fov, glm::vec2 displaySize, glm::mat4 viewMatrix)
{
    pos = pos - origin;

    float x = glm::dot(glm::vec4(viewMatrix[0].x, viewMatrix[0].y, viewMatrix[0].z, viewMatrix[0].w), glm::vec4(pos.x, pos.y, pos.z, 1.0f));
    float y = glm::dot(glm::vec4(viewMatrix[1].x, viewMatrix[1].y, viewMatrix[1].z, viewMatrix[1].w), glm::vec4(pos.x, pos.y, pos.z, 1.0f));
    float z = glm::dot(glm::vec4(viewMatrix[2].x, viewMatrix[2].y, viewMatrix[2].z, viewMatrix[2].w), glm::vec4(pos.x, pos.y, pos.z, 1.0f));
    
    if (z > 0)
        return false;

    float mX = (float)displaySize.x / 2.0F;
    float mY = (float)displaySize.y / 2.0F;

    screen.x = mX + (mX * x / -z * fov.x);
    screen.y = mY - (mY * y / -z * fov.y);

    if (screen.x > displaySize.x * 2 || screen.y > displaySize.y * 2 || screen.x < -displaySize.x || screen.y < -displaySize.y)
        return false;

    return true;
}
