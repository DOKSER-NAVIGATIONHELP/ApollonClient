#include "Images/YT.h"
#include "Images/Telegram.h"
#include "Images/Discord.h"

#include "Images/amethyst_shard.h"
#include "Images/coal.h"
#include "Images/copper_ingot.h"
#include "Images/diamond.h"
#include "Images/dye_powder_blue.h"
#include "Images/emerald.h"
#include "Images/gold_ingot.h"
#include "Images/iron_ingot.h"
#include "Images/netherite_scrap.h"
#include "Images/redstone_dust.h"
#include "Images/quartz.h"
#include "Images/barrel_side.h"
#include "Images/obsidian.h"

#include "Images/horse.h"
#include "Images/villager.h"
#include "Images/iron_golem.h"
#include "Images/snow_golem.h"
#include "Images/donkey.h"
#include "Images/allay.h"
#include "Images/armadillo.h"
#include "Images/axolotl.h"
#include "Images/bat.h"
#include "Images/bee.h"
#include "Images/camel.h"
#include "Images/cat.h"
#include "Images/chicken.h"
#include "Images/cod.h"
#include "Images/copper_golem.h"
#include "Images/cow.h"
#include "Images/dolphin.h"
#include "Images/fox.h"
#include "Images/frog.h"
#include "Images/glow_squid.h"
#include "Images/goat.h"
#include "Images/happy_ghast.h"
#include "Images/llama.h"
#include "Images/ocelot.h"
#include "Images/panda.h"
#include "Images/parrot.h"
#include "Images/pig.h"
#include "Images/piglin.h"
#include "Images/pufferfish.h"
#include "Images/rabbit.h"
#include "Images/salmon.h"
#include "Images/sheep.h"
#include "Images/sniffer.h"
#include "Images/squid.h"
#include "Images/strider.h"
#include "Images/tadpole.h"
#include "Images/tropical_fish.h"
#include "Images/turtle.h"
#include "Images/wandering_trader.h"
#include "Images/wolf.h"
#include "Images/zombie_piglin.h"
#include "Images/zombie_villager.h"

void TickFunctions() {
	if (auraType < 2) {
		if (maxKillTick > currentKillTick && !canKillAuraDamage) {
	        currentKillTick = currentKillTick + 1;
		} else {
		    canKillAuraDamage = true;
			currentKillTick = 1;
		}
		if (maxMobAuraTick > currentMobTick && !canMobAuraDamage) {
	        currentMobTick = currentMobTick + 1;
		} else {
		    canMobAuraDamage = true;
			currentMobTick = 1;
		}
	}
	if (emulateNativeAttack) {
		rotations = true;
		targetLock = true;
	}
	if (autoClicker) {
		if (maxAutoClickTick > currentAutoClickTick && !canClick) {
	        currentAutoClickTick = currentAutoClickTick + 1;
		} else {
		    canClick = true;
			currentAutoClickTick = 1;
		}
	}
}

void BeginDraw() {
    if (!panic) {
     ImGuiIO &io = ImGui::GetIO();
     ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	 
	 ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f)); 
	 
	 static GLint youtube_icon = 0;
	 if (!youtube_icon) youtube_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(YoutubeIcon), sizeof(YoutubeIcon));
	 static GLint telegram_icon = 0;
	 if (!telegram_icon) telegram_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(TelegramIcon), sizeof(TelegramIcon));
	 static GLint discord_icon = 0;
	 if (!discord_icon) discord_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(DiscordIcon), sizeof(DiscordIcon));
	 
	 static GLint amethyst_shard_icon = 0;
	 if (!amethyst_shard_icon) amethyst_shard_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(AmethystShardIcon), sizeof(AmethystShardIcon));
	 static GLint coal_icon = 0;
	 if (!coal_icon) coal_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CoalIcon), sizeof(CoalIcon));
	 static GLint copper_ingot_icon = 0;
	 if (!copper_ingot_icon) copper_ingot_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CopperIngotIcon), sizeof(CopperIngotIcon));
	 static GLint diamond_icon = 0;
	 if (!diamond_icon) diamond_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(DiamondIcon), sizeof(DiamondIcon));
	 static GLint dye_powder_blue_icon = 0;
	 if (!dye_powder_blue_icon) dye_powder_blue_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(DyePowderBlueIcon), sizeof(DyePowderBlueIcon));
	 static GLint emerald_icon = 0;
	 if (!emerald_icon) emerald_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(EmeraldIcon), sizeof(EmeraldIcon));
	 static GLint gold_ingot_icon = 0;
	 if (!gold_ingot_icon) gold_ingot_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(GoldIngotIcon), sizeof(GoldIngotIcon));
	 static GLint iron_ingot_icon = 0;
	 if (!iron_ingot_icon) iron_ingot_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(IronIngotIcon), sizeof(IronIngotIcon));
	 static GLint netherite_scrap_icon = 0;
	 if (!netherite_scrap_icon) netherite_scrap_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(NetheriteScrapIcon), sizeof(NetheriteScrapIcon));
	 static GLint redstone_dust_icon = 0;
	 if (!redstone_dust_icon) redstone_dust_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(RedstoneDustIcon), sizeof(RedstoneDustIcon));
	 static GLint quartz_icon = 0;
	 if (!quartz_icon) quartz_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(QuartzIcon), sizeof(QuartzIcon));
	 static GLint barrel_side_icon = 0;
	 if (!barrel_side_icon) barrel_side_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(BarrelSideIcon), sizeof(BarrelSideIcon));
	 static GLint obsidian_icon = 0;
	 if (!obsidian_icon) obsidian_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ObsidianIcon), sizeof(ObsidianIcon));
	 
	 static GLint horse_icon = 0;
	 if (!horse_icon) horse_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(HorseIcon), sizeof(HorseIcon));
	 static GLint villager_icon = 0;
	 if (!villager_icon) villager_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(VillagerIcon), sizeof(VillagerIcon));
	 static GLint iron_golem_icon = 0;
	 if (!iron_golem_icon) iron_golem_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(IronGolemIcon), sizeof(IronGolemIcon));
	 static GLint snow_golem_icon = 0;
	 if (!snow_golem_icon) snow_golem_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(SnowGolemIcon), sizeof(SnowGolemIcon));
	 static GLint donkey_icon = 0;
	 if (!donkey_icon) donkey_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(DonkeyIcon), sizeof(DonkeyIcon));
	 static GLint allay_icon = 0;
	 if (!allay_icon) allay_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(AllayIcon), sizeof(AllayIcon));
	 static GLint armadillo_icon = 0;
	 if (!armadillo_icon) armadillo_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ArmadilloIcon), sizeof(ArmadilloIcon));
	 static GLint axolotl_icon = 0;
	 if (!axolotl_icon) axolotl_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(AxolotlIcon), sizeof(AxolotlIcon));
	 static GLint bat_icon = 0;
	 if (!bat_icon) bat_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(BatIcon), sizeof(BatIcon));
	 static GLint bee_icon = 0;
	 if (!bee_icon) bee_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(BeeIcon), sizeof(BeeIcon));
	 static GLint camel_icon = 0;
	 if (!camel_icon) camel_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CamelIcon), sizeof(CamelIcon));
	 static GLint cat_icon = 0;
	 if (!cat_icon) cat_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CatIcon), sizeof(CatIcon));
	 static GLint chicken_icon = 0;
	 if (!chicken_icon) chicken_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ChickenIcon), sizeof(ChickenIcon));
	 static GLint cod_icon = 0;
	 if (!cod_icon) cod_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CodIcon), sizeof(CodIcon));
	 static GLint copper_golem_icon = 0;
	 if (!copper_golem_icon) copper_golem_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CopperGolemIcon), sizeof(CopperGolemIcon));
	 static GLint cow_icon = 0;
	 if (!cow_icon) cow_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CowIcon), sizeof(CowIcon));
	 static GLint dolphin_icon = 0;
	 if (!dolphin_icon) dolphin_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(DolphinIcon), sizeof(DolphinIcon));
	 static GLint fox_icon = 0;
	 if (!fox_icon) fox_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(FoxIcon), sizeof(FoxIcon));
	 static GLint frog_icon = 0;
	 if (!frog_icon) frog_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(FrogIcon), sizeof(FrogIcon));
	 static GLint glow_squid_icon = 0;
	 if (!glow_squid_icon) glow_squid_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(GlowSquidIcon), sizeof(GlowSquidIcon));
	 static GLint goat_icon = 0;
	 if (!goat_icon) goat_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(GoatIcon), sizeof(GoatIcon));
	 static GLint happy_ghast_icon = 0;
	 if (!happy_ghast_icon) happy_ghast_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(HappyGhastIcon), sizeof(HappyGhastIcon));
	 static GLint llama_icon = 0;
	 if (!llama_icon) llama_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(LlamaIcon), sizeof(LlamaIcon));
	 static GLint ocelot_icon = 0;
	 if (!ocelot_icon) ocelot_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(OcelotIcon), sizeof(OcelotIcon));
	 static GLint panda_icon = 0;
	 if (!panda_icon) panda_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(PandaIcon), sizeof(PandaIcon));
	 static GLint parrot_icon = 0;
	 if (!parrot_icon) parrot_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ParrotIcon), sizeof(ParrotIcon));
	 static GLint pig_icon = 0;
	 if (!pig_icon) pig_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(PigIcon), sizeof(PigIcon));
	 static GLint piglin_icon = 0;
	 if (!piglin_icon) piglin_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(PiglinIcon), sizeof(PiglinIcon));
	 static GLint pufferfish_icon = 0;
	 if (!pufferfish_icon) pufferfish_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(PufferfishIcon), sizeof(PufferfishIcon));
	 static GLint rabbit_icon = 0;
	 if (!rabbit_icon) rabbit_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(RabbitIcon), sizeof(RabbitIcon));
	 static GLint salmon_icon = 0;
	 if (!salmon_icon) salmon_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(SalmonIcon), sizeof(SalmonIcon));
	 static GLint sheep_icon = 0;
	 if (!sheep_icon) sheep_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(SheepIcon), sizeof(SheepIcon));
	 static GLint sniffer_icon = 0;
	 if (!sniffer_icon) sniffer_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(SnifferIcon), sizeof(SnifferIcon));
	 static GLint squid_icon = 0;
	 if (!squid_icon) squid_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(SquidIcon), sizeof(SquidIcon));
	 static GLint strider_icon = 0;
	 if (!strider_icon) strider_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(StriderIcon), sizeof(StriderIcon));
	 static GLint tadpole_icon = 0;
	 if (!tadpole_icon) tadpole_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(TadpoleIcon), sizeof(TadpoleIcon));
	 static GLint tropical_fish_icon = 0;
	 if (!tropical_fish_icon) tropical_fish_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(TropicalfishIcon), sizeof(TropicalfishIcon));
	 static GLint turtle_icon = 0;
	 if (!turtle_icon) turtle_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(TurtleIcon), sizeof(TurtleIcon));
	 static GLint wandering_trader_icon = 0;
	 if (!wandering_trader_icon) wandering_trader_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(WanderingtraderIcon), sizeof(WanderingtraderIcon));
	 static GLint wolf_icon = 0;
	 if (!wolf_icon) wolf_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(WolfIcon), sizeof(WolfIcon));
	 static GLint zombie_piglin_icon = 0;
	 if (!zombie_piglin_icon) zombie_piglin_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ZombiepiglinIcon), sizeof(ZombiepiglinIcon));
	 static GLint zombie_villager_icon = 0;
	 if (!zombie_villager_icon) zombie_villager_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ZombievillagerIcon), sizeof(ZombievillagerIcon));
	 
	 float imageSize = ImGui::GetFontSize();
	 
     ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	 
	 if (!readMe) {
		 if (ImGui::Begin(OBFUSCATE("Description"), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
			 g_window = ImGui::GetCurrentWindow();
			 ImGui::SetWindowSize(ImVec2(screenWidth / 2, screenHeight / 1.25));
			 if (ImGui::BeginTabBar(OBFUSCATE("Tab"))) {
				 if (ImGui::BeginTabItem(OBFUSCATE("Русский"))) {
					 ImGui::SetWindowFontScale(2.0);
					 ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(redd/255, greenn/255, bluee/255, 1));
					 ImGui::Text(OBFUSCATE("Кодером клиента является ZEFF, никто не может\nобновить клиент на новую версию без сурс кода.\n\nКлиент ПОЛНОСТЬЮ БЕСПЛАТНЫЙ, если вы у\nкого-то его купили, то вы еблан."));
					 ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
					 ImGui::SetWindowFontScale(1.25);
					 ImGui::Text(OBFUSCATE("\nОфициальные источники:"));
					 ImGui::Image((ImTextureID)(intptr_t)youtube_icon, ImVec2(imageSize, imageSize));
					 ImGui::SameLine(calcResX * 70);
					 ImGui::Text(OBFUSCATE(": @zeff_source"));
					 ImGui::Image((ImTextureID)(intptr_t)telegram_icon, ImVec2(imageSize, imageSize));
					 ImGui::SameLine(calcResX * 70);
					 ImGui::Text(OBFUSCATE(": @zeff_cheats"));
					 ImGui::Image((ImTextureID)(intptr_t)discord_icon, ImVec2(imageSize, imageSize));
				     ImGui::SameLine(calcResX * 70);
				     ImGui::Text(OBFUSCATE(": https://discord.gg/RSC4ZrVjS8"));
					 ImGui::SetWindowFontScale(1.0);
					 ImGui::Separator();
                     ImGui::Text(OBFUSCATE("Обновление 4.6:"));
					 ImGui::Text(OBFUSCATE("\n- Обновлен Xray."));
					 ImGui::Text(OBFUSCATE("\n- Улучшен Anti Bot."));
					 ImGui::Text(OBFUSCATE("\n- Удалена выдача XP (фикс разработчиками игры, позже попробую реализовать иначе)."));
					 ImGui::Text(OBFUSCATE("\n- Удалены некоторые функции из Movement (редкая используемость)."));
					 ImGui::Text(OBFUSCATE("\nПатч 4.62:"));
					 ImGui::Text(OBFUSCATE("\n- Исправлен Xray в 32 Bit апк."));
					 ImGui::Text(OBFUSCATE("\nПриятной игры!"));
					 if (ImGui::Button(OBFUSCATE("Я ПРОЧИТАЛ(А)"))) {
						 readMe = true;
					 }
				     ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem(OBFUSCATE("English"))) {
				     ImGui::SetWindowFontScale(2.0);
					 ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(redd/255, greenn/255, bluee/255, 1));
					 ImGui::Text(OBFUSCATE("Client coder is ZEFF, no one can update client on new\nversion without source code.\n\nClient is FULL FREE, if you buy them from someone,\nthen you are an idiot."));
					 ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
					 ImGui::SetWindowFontScale(1.25);
					 ImGui::Text(OBFUSCATE("\nOfficial sources:"));
					 float imageSize = ImGui::GetFontSize();
					 ImGui::Image((ImTextureID)(intptr_t)youtube_icon, ImVec2(imageSize, imageSize));
					 ImGui::SameLine(calcResX * 70);
					 ImGui::Text(OBFUSCATE(": @zeff_source"));
					 ImGui::Image((ImTextureID)(intptr_t)telegram_icon, ImVec2(imageSize, imageSize));
					 ImGui::SameLine(calcResX * 70);
					 ImGui::Text(OBFUSCATE(": @zeff_cheats"));
					 ImGui::Image((ImTextureID)(intptr_t)discord_icon, ImVec2(imageSize, imageSize));
				     ImGui::SameLine(calcResX * 70);
				     ImGui::Text(OBFUSCATE(": https://discord.gg/RSC4ZrVjS8"));
					 ImGui::SetWindowFontScale(1.0);
					 ImGui::Separator();
				     ImGui::Text(OBFUSCATE("Update 4.6:"));
					 ImGui::Text(OBFUSCATE("\n- Updated Xray."));
					 ImGui::Text(OBFUSCATE("\n- Improved Anti Bot."));
					 ImGui::Text(OBFUSCATE("\n- Adding XP have been removed (fixed by the game developers, I'll try to implement it differently later)"));
					 ImGui::Text(OBFUSCATE("\n- Removed some functions from Movement (rarely used)."));
					 ImGui::Text(OBFUSCATE("\nPatch 4.62:"));
					 ImGui::Text(OBFUSCATE("\n- Fixed Xray in 32 Bit apk."));
					 ImGui::Text(OBFUSCATE("\nGood Luck!"));
					 if (ImGui::Button(OBFUSCATE("I READ THIS"))) {
						 readMe = true;
					 }
				     ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
	     }
	  } else  {
     #if defined(__aarch64__)
     if (ImGui::Begin(OBFUSCATE("The Apollon Client v4.62 | APK (x64 Bit) | Minecraft v1.21.111"), NULL, ImGuiWindowFlags_NoResize)) {
     #elif defined(__ARM_ARCH_7A__)
     if (ImGui::Begin(OBFUSCATE("The Apollon Client v4.62 | APK (x32 Bit) | Minecraft v1.21.111"), NULL, ImGuiWindowFlags_NoResize)) {
     #else
	 if (ImGui::Begin(OBFUSCATE("The Apollon Client v4.62 | APK (x86_64 Bit) | Minecraft v1.21.111"), NULL, ImGuiWindowFlags_NoResize)) {
     #endif
		g_window = ImGui::GetCurrentWindow();
	
		ImGui::SetWindowSize(ImVec2(screenWidth / 2.5, screenHeight / 1.5));
		
		float pointSize = calculateResolutionScale(screenWidth, screenHeight, 2480, 1116);
		BackGroundDots(250, 2 * pointSize, 5 * pointSize, 100 * pointSize);
		ImGuiStyle& style = ImGui::GetStyle();
        ImVec4 originalButtonColor = style.Colors[ImGuiCol_Button];
        ImVec4 originalButtonHoveredColor = style.Colors[ImGuiCol_ButtonHovered];
        ImVec4 originalButtonActiveColor = style.Colors[ImGuiCol_ButtonActive];
	
		style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.00f, 1.00f, 0.50f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.70f, 0.00f, 1.00f, 0.35f);
        style.FrameBorderSize = 0.0f;
		
		ImGui::BeginChild(OBFUSCATE("SidePanel"), ImVec2(calcResX * 150, 0), false);
		style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		if (pageId == 0) {
			style.Colors[ImGuiCol_Button] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
		}
		if (ImGui::Button(OBFUSCATE("Movement"))) pageId = 0;
		style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		if (pageId == 1) {
			style.Colors[ImGuiCol_Button] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
		}
		if (ImGui::Button(OBFUSCATE("Combat"))) pageId = 1;
		style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		if (pageId == 2) {
			style.Colors[ImGuiCol_Button] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
		}
		if (ImGui::Button(OBFUSCATE("Building"))) pageId = 2;
		style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		if (pageId == 3) {
			style.Colors[ImGuiCol_Button] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
		}
		if (ImGui::Button(OBFUSCATE("List"))) pageId = 3;
		style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		if (pageId == 4) {
			style.Colors[ImGuiCol_Button] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
		}
		if (ImGui::Button(OBFUSCATE("Visuals"))) pageId = 4;
		style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		if (pageId == 5) {
			style.Colors[ImGuiCol_Button] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
		}
		if (ImGui::Button(OBFUSCATE("Hotkeys"))) pageId = 5;
		style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		if (pageId == 6) {
			style.Colors[ImGuiCol_Button] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
		}
		if (ImGui::Button(OBFUSCATE("Other"))) pageId = 6;
		style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		if (pageId == 7) {
			style.Colors[ImGuiCol_Button] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.00f, 1.00f, 1.00f);
		}
		if (ImGui::Button(OBFUSCATE("Info"))) pageId = 7;
		ImGui::EndChild();
		
		style.Colors[ImGuiCol_Button] = originalButtonColor;
        style.Colors[ImGuiCol_ButtonHovered] = originalButtonHoveredColor;
        style.Colors[ImGuiCol_ButtonActive] = originalButtonActiveColor;
        style.FrameBorderSize = 2.0f;
  
		ImGui::SameLine();
        float lineHeight = ImGui::GetWindowHeight();
        ImVec2 startVertical = ImGui::GetCursorScreenPos();
        startVertical.y = ImGui::GetWindowPos().y;
        ImVec2 endVertical = ImVec2(startVertical.x, startVertical.y + lineHeight);
        ImGui::GetWindowDrawList()->AddLine(startVertical, endVertical, ImGui::GetColorU32(ImGuiCol_Separator), scaleGlobal * 2.0f);
        ImGui::SameLine(calcResX * 226);
		
        ImGui::BeginGroup();
        switch (pageId) {
			case 0:
				ImGui::PushItemWidth(calcResX * 100);
				if (ImGui::BeginTabBar(OBFUSCATE("Movements"))) {
					if (!isLANGame) {
					if (ImGui::BeginTabItem(OBFUSCATE("Speed"))) {
						ImGui::DragInt(OBFUSCATE("SpeedHack"), &speedValue, 0.05f, 1, 50);
						ImGui::SameLine();
                        ImGui::DragInt(OBFUSCATE("Water Speed"), &waterSpeedValue, 0.05f, 1, 50);
						ImGui::DragInt(OBFUSCATE("Lava Speed"), &lavaSpeedValue, 0.05f, 1, 50);
						ImGui::Checkbox(OBFUSCATE("Always Sprinting"), &alwaysSprinting);
			            ImGui::SameLine();
                        ImGui::Checkbox(OBFUSCATE("No SlowDown"), &noSlowDown);
						ImGui::Checkbox(OBFUSCATE("No Web"), &offSlowdownTrigger);
						ImGui::SameLine();
						ImGui::Checkbox(OBFUSCATE("No Jump Delay"), &noJumpDelay);
						ImGui::EndTabItem();
                    }
					}
					if (ImGui::BeginTabItem(OBFUSCATE("Other"))) {
						if (!isLANGame) {
						ImGui::DragFloat(OBFUSCATE("JumpHack"), &jumpValue, 0.05f, 1, 50, "%.0f");
						ImGui::PushItemWidth(calcResX * 300);
				        ImGui::SliderFloat(OBFUSCATE("Gravity"), &gravityValue, -0.08, 0.08, "%.2f");
                        ImGui::PushItemWidth(0);
						ImGui::Checkbox(OBFUSCATE("Fast Fall"), &fastFall);
				        ImGui::SameLine();
                        ImGui::Checkbox(OBFUSCATE("Step"), &step);
				        ImGui::Checkbox(OBFUSCATE("Ladder Fly"), &ladderFly);
				        ImGui::SameLine();
				        ImGui::Checkbox(OBFUSCATE("Noclip"), &noclip);
				        ImGui::Checkbox(OBFUSCATE("Creative Fly"), &creativeFly);
				        ImGui::SameLine();
				        ImGui::Checkbox(OBFUSCATE("Force Creative Fly"), &forceCreativeFly);
						ImGui::Checkbox(OBFUSCATE("No Water"), &offWaterTrigger);
						ImGui::SameLine();
						ImGui::Checkbox(OBFUSCATE("Strafe"), &strafe);
						DrawSeparatorToWindowEdge(endVertical, 16.0f);
						}
						ImGui::Text(OBFUSCATE("Bedrock Core Predicition Anti Cheat"));
						ImGui::Checkbox(OBFUSCATE("OFF Drowning"), &offDrown);
						ImGui::SameLine();
			        	ImGui::Checkbox(OBFUSCATE("Damage Fly\n(Sprint to control it)"), &damageFly);
						ImGui::EndTabItem();
                    }
					ImGui::EndTabBar();
                }
				break;
			case 1:
				if (ImGui::BeginTabBar(OBFUSCATE("Tab1"))) {
					if (ImGui::BeginTabItem(OBFUSCATE("Players"))) {
						ImGui::PushID(21);
				        ImGui::Checkbox(OBFUSCATE("KillAura"), &killAura);
				        if (killAura) {
                            ImGui::PushItemWidth(calcResX * 200);
                            if (ImGui::DragFloat(OBFUSCATE("Kill Range"), &killRange, 0.015f, 1.0f, 10.0f, "%.1f")) {
					            if (killRange > rotationsRange) rotationsRange = killRange;
					        }
					        if (rotations || targetLock) {
						        if(ImGui::DragFloat(OBFUSCATE("Rotations/Target Lock Range"), &rotationsRange, 0.015f, 1.0f, 100.0f, "%.1f")) {
							        if (killRange > rotationsRange) killRange = rotationsRange;
						        }
					        }
							if (!useGeyserCooldown) {
					            ImGui::DragInt(OBFUSCATE("Kill Delay"), &maxKillTick, 0.05f, 1, 150);
							    ImGui::SameLine();
							}
							ImGui::Checkbox(OBFUSCATE("Use Geyser Cooldown"), &useGeyserCooldown);
				        }
						ImGui::Checkbox(OBFUSCATE("HitBox"), &hitBox);
				        if (hitBox) {
					        ImGui::SameLine();
							ImGui::PushItemWidth(calcResX * 200);
					        ImGui::DragFloat(OBFUSCATE("##Size"), &hitBoxValue, 0.015f, 0.6f, 10.0f, "%.1f");
				        }
						ImGui::PushItemWidth(0);
				        DrawSeparatorToWindowEdge(endVertical, 16.0f);
				        ImGui::Text(OBFUSCATE("Aura Settings"));
				        ImGui::PushItemWidth(calcResX * 200);
						if (!useGeyserCooldown && !emulateNativeAttack) {
							ImGui::Combo(OBFUSCATE("Aura Type"), &auraType, AuraType, IM_ARRAYSIZE(AuraType));
						} else {
							ImGui::Combo(OBFUSCATE("Aura Type"), &auraType, AuraTypeGeyser, IM_ARRAYSIZE(AuraTypeGeyser));
							if (auraType == 2) auraType = 1;
						}
                        ImGui::PushItemWidth(0);
			            ImGui::Checkbox(OBFUSCATE("Swing"), &swing);
			            ImGui::SameLine();
						if (!emulateNativeAttack) {
							ImGui::Checkbox(OBFUSCATE("Rotations"), &rotations);
				            ImGui::Checkbox(OBFUSCATE("Target Lock"), &targetLock);
							ImGui::SameLine();
						}
						ImGui::Checkbox(OBFUSCATE("Hurt Check"), &hurtCheck);
						ImGui::Checkbox(OBFUSCATE("Simulate Native Attack\n(Split Touch Recommended)"), &emulateNativeAttack);
				        ImGui::PopID();
				        ImGui::EndTabItem();
                    }
					if (ImGui::BeginTabItem(OBFUSCATE("Mobs"))) {
						if (ImGui::BeginTabBar(OBFUSCATE("TabMobs"))) {
							ImGui::PushID(22);
					    	if (ImGui::BeginTabItem(OBFUSCATE("Main"))) {
				                ImGui::Checkbox(OBFUSCATE("MobAura"), &mobAura);
				                if (mobAura) {
					                ImGui::PushItemWidth(calcResX * 200);
                                    ImGui::DragFloat(OBFUSCATE("Kill Mob Range"), &mobAuraRange, 0.015f, 1.0f, 10.0f, "%.1f");
						    	    if (!useGeyserCooldown) {
								        ImGui::DragInt(OBFUSCATE("Kill Mob Delay"), &maxMobAuraTick, 0.05f, 1, 150);
								        ImGui::SameLine();
							        }
							        ImGui::Checkbox(OBFUSCATE("Use Geyser Cooldown"), &useGeyserCooldown);
                                    ImGui::PushItemWidth(0);
				                }
						
				                DrawSeparatorToWindowEdge(endVertical, 16.0f);
						
				                ImGui::Text(OBFUSCATE("Aura Settings"));
				                ImGui::PushItemWidth(calcResX * 200);
                                if (!useGeyserCooldown) {
							        ImGui::Combo(OBFUSCATE("Aura Type"), &auraType, AuraType, IM_ARRAYSIZE(AuraType));
						        } else {
							        ImGui::Combo(OBFUSCATE("Aura Type"), &auraType, AuraTypeGeyser, IM_ARRAYSIZE(AuraTypeGeyser));
							        if (auraType == 2) auraType = 1;
						        }
			                    ImGui::Checkbox(OBFUSCATE("Swing"), &swing);
			                    ImGui::SameLine();
			                    ImGui::Checkbox(OBFUSCATE("Rotations"), &rotations);
				                ImGui::Checkbox(OBFUSCATE("Target Lock"), &targetLock);
						        ImGui::SameLine();
						        ImGui::Checkbox(OBFUSCATE("Hurt Check"), &hurtCheck);
						        ImGui::PushItemWidth(0);
						        ImGui::EndTabItem();
                             }
						     if (ImGui::BeginTabItem(OBFUSCATE("Mob List"))) {
								ImGui::Text(OBFUSCATE("List of mobs that MobAura DOES NOT ATTACK"));
						        ImGui::BeginChild(OBFUSCATE("MobAuraPanel"), ImVec2(0, 0), true);
								ImGui::SetWindowFontScale(1.75);
				                ImGui::Checkbox(OBFUSCATE("##Horses"), &noHorses);
					            ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)horse_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Villagers"), &noVillagers);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)villager_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Snowmans"), &noSnowMan);
					            ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)snow_golem_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Iron Golems"), &noIronGolem);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)iron_golem_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								
								ImGui::Checkbox(OBFUSCATE("##Donkeys"), &noDonkeys);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)donkey_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Allays"), &noAllays);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)allay_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Armadillos"), &noArmadillos);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)armadillo_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Axolotls"), &noAxolotls);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)axolotl_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								
								ImGui::Checkbox(OBFUSCATE("##Bats"), &noBats);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)bat_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Bees"), &noBees);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)bee_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Camels"), &noCamels);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)camel_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Cats"), &noCats);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)cat_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								
								ImGui::Checkbox(OBFUSCATE("##Chickens"), &noChickens);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)chicken_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Cods"), &noCods);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)cod_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Copper Golems"), &noCopperGolems);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)copper_golem_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Cows"), &noCows);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)cow_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								
								ImGui::Checkbox(OBFUSCATE("##Dolphins"), &noDolphins);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)dolphin_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Foxes"), &noFoxes);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)fox_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Frogs"), &noFrogs);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)frog_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Glow Squids"), &noGlowSquids);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)glow_squid_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								
								ImGui::Checkbox(OBFUSCATE("##Goats"), &noGoats);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)goat_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Happy Ghasts"), &noHappyGhasts);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)happy_ghast_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Llamas"), &noLlamas);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)llama_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Ocelots"), &noOcelots);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)ocelot_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								
								ImGui::Checkbox(OBFUSCATE("##Pandas"), &noPandas);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)panda_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Parrots"), &noParrots);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)parrot_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Pigs"), &noPigs);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)pig_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Piglins"), &noPiglins);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)piglin_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								
								ImGui::Checkbox(OBFUSCATE("##Pufferfishes"), &noPufferfishes);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)pufferfish_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Rabbits"), &noRabbits);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)rabbit_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Salmons"), &noSalmons);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)salmon_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Sheeps"), &noSheeps);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)sheep_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								
								ImGui::Checkbox(OBFUSCATE("##Sniffers"), &noSniffers);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)sniffer_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Squids"), &noSquids);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)squid_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Striders"), &noStriders);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)strider_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Tadpoles"), &noTadpoles);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)tadpole_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								
								ImGui::Checkbox(OBFUSCATE("##Tropical fishes"), &noTropicalfishes);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)tropical_fish_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Turtles"), &noTurtles);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)turtle_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Wandering traders"), &noWanderingtraders);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)wandering_trader_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Wolfs"), &noWolfs);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)wolf_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								
								ImGui::Checkbox(OBFUSCATE("##Zombie piglins"), &noZombiepiglins);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)zombie_piglin_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								ImGui::SameLine();
					            ImGui::Checkbox(OBFUSCATE("##Zombie villagers"), &noZombievillagers);
								ImGui::SameLine();
								ImGui::Image((ImTextureID)(intptr_t)zombie_villager_icon, ImVec2(imageSize * 2.25, imageSize * 2.25));
								
								ImGui::SetWindowFontScale(1.0);
						        ImGui::EndChild();
							    ImGui::EndTabItem();
                            }
							ImGui::EndTabBar();
                        }
						ImGui::PopID();
						ImGui::EndTabItem();
                    }
					if (ImGui::BeginTabItem(OBFUSCATE("Other"))) {
						ImGui::Checkbox(OBFUSCATE("Kill Near Items"), &killItems);
				        ImGui::SameLine();
				        ImGui::Checkbox(OBFUSCATE("Anti Fireball"), &antiFireball);
						ImGui::PushItemWidth(calcResX * 200);
						ImGui::Checkbox(OBFUSCATE("Auto Clicker"), &autoClicker);
						ImGui::SameLine();
						if (autoClicker) {
						    ImGui::DragInt(OBFUSCATE("Auto Click Delay"), &maxAutoClickTick, 0.05f, 1, 150);
						}
						if (!isLANGame) {
							ImGui::Checkbox(OBFUSCATE("Anti Knockback"), &antiKnockback);
						}
						ImGui::Separator();
						ImGui::Checkbox(OBFUSCATE("Auto Totem"), &autoTotem);
						if (autoTotem) {
							ImGui::SameLine();
							ImGui::PushItemWidth(calcResX * 200);
							ImGui::SliderInt(OBFUSCATE("##TotemDelay"), &autoTotemDelay, 50, 3000, OBFUSCATE("%d ms"));
							ImGui::PopItemWidth();
						}
						ImGui::PushItemWidth(0);
						ImGui::EndTabItem();
                    }
					ImGui::EndTabBar();
                }
				break;
			case 2:
				ImGui::Checkbox(OBFUSCATE("1 Click Auto Mine"), &clickAutoMine);
                ImGui::SameLine();
                ImGui::Checkbox(OBFUSCATE("Auto Click Build (Hold Build Button)"), &fastBridge);
                ImGui::Checkbox(OBFUSCATE("Creative Block Reach"), &blockReach);
				break;
			case 3:
				ImGui::Checkbox(OBFUSCATE("Anti Bot"), &antiBot);
				if (ImGui::BeginTabBar(OBFUSCATE("Tab3"))) {
					if (ImGui::BeginTabItem(OBFUSCATE("All"))) {
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 1, 0, 1));
						ImGui::BeginChild(OBFUSCATE("PlayersPanel"), ImVec2(0, 0), true);
						if (!nearPlayerList.empty()) insertionSortPlayers(nearPlayerList);
			            for (PlayerStruct player : nearPlayerList) {
							if (!player.isBot) {
								if (player.isProtected) {
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
								} else if (player.isFriend) {
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 1, 1, 1));
								} else {
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 1, 0, 1));
								}
								ImGui::PushID(player.nickname.c_str());
								ImGuiColoredText(player.nameTag);
								if (!player.isFriend) {
                                    ImGui::SameLine();
								    if (ImGui::Button(OBFUSCATE("Add Friend"))) {
                                        friendList.push_back(player.nickname);
                                    }
						            ImGui::SameLine();
						            if (ImGui::Button(OBFUSCATE("Add Bot"))) {
                                        botList.push_back(player.nickname);
                                    }
								}
								ImGui::Separator();
				                ImGui::PopID();
							}
                        }
						ImGui::EndChild();
				        ImGui::EndTabItem();
				    }
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 1, 1, 1));
					if (ImGui::BeginTabItem(OBFUSCATE("Friends"))) {
						ImGui::BeginChild(OBFUSCATE("FriendsPanel"), ImVec2(0, 0), true);
			            for (std::string player : friendList) {
							ImGui::PushID(player.c_str());
							ImGuiColoredText(player);
                            ImGui::SameLine();
						    if (ImGui::Button(OBFUSCATE("Remove Friend"))) {
                                friendList.erase(std::remove(friendList.begin(), friendList.end(), player), friendList.end());
                            }
						    ImGui::Separator();
				            ImGui::PopID();
                        }
						ImGui::EndChild();
				        ImGui::EndTabItem();
				    }
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 0, 1));
					if (ImGui::BeginTabItem(OBFUSCATE("Bots"))) {
						ImGui::BeginChild(OBFUSCATE("BotsPanel"), ImVec2(0, 0), true);
			            for (std::string bot : botList) {
							ImGui::PushID(bot.c_str());
							ImGuiColoredText(bot);
                            ImGui::SameLine();
						    if (ImGui::Button(OBFUSCATE("Remove Bot"))) {
                                botList.erase(std::remove(botList.begin(), botList.end(), bot), botList.end());
                            }
						    ImGui::Separator();
				            ImGui::PopID();
                        }
						ImGui::EndChild();
				        ImGui::EndTabItem();
				    }
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
				    ImGui::EndTabBar();
				}
				break;
			case 4:
				if (ImGui::BeginTabBar(OBFUSCATE("Tab4"))) {
					if (ImGui::BeginTabItem(OBFUSCATE("Xray"))) {
						ImGui::Checkbox(OBFUSCATE("Xray Caves"), &xrayCaves);
						ImGui::SameLine();
						ImGui::Checkbox(OBFUSCATE("Xray Camera (Third Person)"), &xrayCam);
						ImGui::BeginChild(OBFUSCATE("XrayPanel"), ImVec2(0, 0), xrayDefault);
						if (ImGui::Checkbox(OBFUSCATE("Xray"), &xrayDefault)) {
							rebuildChunkGeometry = true;
						}
						if (xrayDefault) {
							ImGui::Separator();
							if (ImGui::Checkbox(OBFUSCATE("##Diamond"), &xrayDiamond)) {
								if (xrayDiamond) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 80);
				            ImGui::Image((ImTextureID)(intptr_t)diamond_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
							ImGui::SameLine(0, calcResX * 40);
							if (ImGui::Checkbox(OBFUSCATE("##Iron"), &xrayIron)) {
								if (xrayIron) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 110, calcResX * 110);
				            ImGui::Image((ImTextureID)(intptr_t)iron_ingot_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
							ImGui::SameLine(0, calcResX * 40);
							if (ImGui::Checkbox(OBFUSCATE("##Gold"), &xrayGold)) {
								if (xrayGold) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 180, calcResX * 180);
				            ImGui::Image((ImTextureID)(intptr_t)gold_ingot_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));

							if (ImGui::Checkbox(OBFUSCATE("##Coal"), &xrayCoal)) {
								if (xrayCoal) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 80);
				            ImGui::Image((ImTextureID)(intptr_t)coal_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
							ImGui::SameLine(0, calcResX * 40);
							if (ImGui::Checkbox(OBFUSCATE("##Copper"), &xrayCopper)) {
								if (xrayCopper) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 110, calcResX * 110);
				            ImGui::Image((ImTextureID)(intptr_t)copper_ingot_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
							ImGui::SameLine(0, calcResX * 40);
							if (ImGui::Checkbox(OBFUSCATE("##Lapis"), &xrayLapis)) {
								if (xrayLapis) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 180, calcResX * 180);
				            ImGui::Image((ImTextureID)(intptr_t)dye_powder_blue_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
							
							if (ImGui::Checkbox(OBFUSCATE("##Emerald"), &xrayEmerald)) {
								if (xrayEmerald) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 80);
				            ImGui::Image((ImTextureID)(intptr_t)emerald_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
							ImGui::SameLine(0, calcResX * 40);
							if (ImGui::Checkbox(OBFUSCATE("##Redstone"), &xrayRedstone)) {
								if (xrayRedstone) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 110, calcResX * 110);
				            ImGui::Image((ImTextureID)(intptr_t)redstone_dust_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
							ImGui::SameLine(0, calcResX * 40);
							if (ImGui::Checkbox(OBFUSCATE("##Amethyst"), &xrayAmethyst)) {
								if (xrayAmethyst) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 180, calcResX * 180);
				            ImGui::Image((ImTextureID)(intptr_t)amethyst_shard_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
							
							if (ImGui::Checkbox(OBFUSCATE("##Netherite"), &xrayNetherite)) {
								if (xrayNetherite) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 80);
				            ImGui::Image((ImTextureID)(intptr_t)netherite_scrap_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
							ImGui::SameLine(0, calcResX * 40);
							if (ImGui::Checkbox(OBFUSCATE("##Quartz"), &xrayQuartz)) {
								if (xrayQuartz) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 110, calcResX * 110);
				            ImGui::Image((ImTextureID)(intptr_t)quartz_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
							ImGui::SameLine(0, calcResX * 40);
							if (ImGui::Checkbox(OBFUSCATE("##Obsidian"), &xrayObsidian)) {
								if (xrayObsidian) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 180, calcResX * 180);
				            ImGui::Image((ImTextureID)(intptr_t)obsidian_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
							
							if (ImGui::Checkbox(OBFUSCATE("##Barrel"), &xrayBarrel)) {
								if (xrayBarrel) rebuildChunkGeometry = true;
							}
							ImGui::SameLine(calcResX * 80);
				            ImGui::Image((ImTextureID)(intptr_t)barrel_side_icon, ImVec2(imageSize * 1.5, imageSize * 1.5));
						}
						ImGui::EndChild();
						ImGui::EndTabItem();
				    }
					if (ImGui::BeginTabItem(OBFUSCATE("Render"))) {
				        ImGui::PushItemWidth(calcResX * 250);
				        ImGui::Combo(OBFUSCATE("Fog Mode"), &fogState, FogStatement, IM_ARRAYSIZE(FogStatement));
						bool seeThickness;
				        if (chamsint == 1) {
							seeThickness = false;
						} else if (chamsint > 1) {
							seeThickness = true;
						}
						if (chamsint > 1) DrawSeparatorToWindowEdge(endVertical, 16.0f);
				        ImGui::PushItemWidth(calcResX * 450);
				        ImGui::Combo(OBFUSCATE("Current Chams"), &chamsint, Chams, IM_ARRAYSIZE(Chams));
				        if (chamsint > 1) {
                            ImGui::PushItemWidth(calcResX * 42);
                            ImGui::ColorEdit3(OBFUSCATE("##Visible Color"), (float *) &visibleColor);
                            ImGui::SameLine();
                            ImGui::Checkbox(OBFUSCATE("RGB"), &enableRainbow);
				        }
                        if (chamsint == 6 || chamsint == 7) {
							ImGui::SameLine();
                            ImGui::ColorEdit3(OBFUSCATE("##In Wall Color"), (float *) &inWallColor);
                            ImGui::SameLine();
                            ImGui::Checkbox(OBFUSCATE("RGB "), &enableRainbowWall);
                        }
                        ImGui::PushItemWidth(0);
				        if (chamsint > 1) DrawSeparatorToWindowEdge(endVertical, 16.0f);
						ImGui::Checkbox(OBFUSCATE("Enable FOV"), &enableFov);
                        if (enableFov) {
					        ImGui::SameLine();
                            ImGui::PushItemWidth(calcResX * 500);
                            ImGui::SliderFloat(OBFUSCATE("##FOV"), &fov, -90.0f, 90.0f, "%.0f");
                            ImGui::PushItemWidth(0);
                        }
						ImGui::Checkbox(OBFUSCATE("FullBright"), &fullBright);
				        ImGui::SameLine();
			        	ImGui::Checkbox(OBFUSCATE("OSMT FPS Boost"), &osmtBoost);
						ImGui::SameLine();
						ImGui::Checkbox(OBFUSCATE("Freelook"), &look360);
                        ImGui::Checkbox(OBFUSCATE("No Hurt Cam"), &noHurtCam);
			 	        ImGui::SameLine();
				        ImGui::Checkbox(OBFUSCATE("No Cam Distortion"), &noCamDist);
				        ImGui::Checkbox(OBFUSCATE("No Boat Rotation Limit"), &noBoatRotation);
						ImGui::SameLine();
				        ImGui::Checkbox(OBFUSCATE("No Sleep Vignette"), &noCamSleep);
                        ImGui::Checkbox(OBFUSCATE("Place Camera (Third Person)"), &placeCam);
						ImGui::SameLine();
			            ImGui::Checkbox(OBFUSCATE("Anti Invisible"), &antiInvis);
						if (!isLANGame) {
			            ImGui::Checkbox(OBFUSCATE("Derp"), &derp);
				        ImGui::SameLine();
						}
						ImGui::Checkbox(OBFUSCATE("No Blur"), &noBlur);
						ImGui::SameLine();
						ImGui::Checkbox(OBFUSCATE("Anti Blindness"), &antiBlind);
						if (antiBlind) {
							if (fogState == 0) fogState = 1;
						}
						ImGui::EndTabItem();
				}
		 	    if (ImGui::BeginTabItem(OBFUSCATE("UI"))) {
					ImGui::PushID(23);
					if (ImGui::BeginTabBar(OBFUSCATE("TabUI"))) {
						if (ImGui::BeginTabItem(OBFUSCATE("Main"))) {
					        ImGui::PushItemWidth(calcResX * 300);
			            	ImGui::SliderInt(OBFUSCATE("Font Size"), &fontSize, 0, 10);
					        ImGui::Checkbox(OBFUSCATE("Always Show Paperdoll"), &showPaperdoll);
					        ImGui::SameLine();
					        ImGui::Checkbox(OBFUSCATE("No Cave Vignette"), &noCaveVignette);
					        ImGui::Checkbox(OBFUSCATE("Death Position"), &deathPosition);
					        if (showPosition) DrawSeparatorToWindowEdge(endVertical, 16.0f);
				            ImGui::Checkbox(OBFUSCATE("Show Position"), &showPosition);
				            if (showPosition) {
                                ImGui::DragFloat(OBFUSCATE("Offset X"), &offsetTextPosX, 0.05f, -1500.0f, 1500.0f, "%.0f");
					            ImGui::DragFloat(OBFUSCATE("Offset Y"), &offsetTextPosY, 0.05f, -1000.0f, 1000.0f, "%.0f");
				            }
					        if (showPosition || playerNear) DrawSeparatorToWindowEdge(endVertical, 16.0f);
				            ImGui::Checkbox(OBFUSCATE("Near Players"), &playerNear);
				            if (playerNear) {
                                ImGui::DragFloat(OBFUSCATE("Offset X  "), &offsetTextPlayerNearPosX, 0.05f, -1500.0f, 1500.0f, "%.0f");
					            ImGui::DragFloat(OBFUSCATE("Offset Y  "), &offsetTextPlayerNearPosY, 0.05f, -1000.0f, 1000.0f, "%.0f");
					        }
					        ImGui::PushItemWidth(0);
						    ImGui::EndTabItem();
				        }
						if (ImGui::BeginTabItem(OBFUSCATE("ESP"))) {
							ImGui::Checkbox(OBFUSCATE("ESP"), &esp);
							if (esp) {
								ImGui::Checkbox(OBFUSCATE("Box"), &espBox);
								ImGui::SameLine();
								ImGui::Checkbox(OBFUSCATE("Line"), &espLine);
								ImGui::SameLine();
								ImGui::Checkbox(OBFUSCATE("Distance"), &espDistance);
								ImGui::Checkbox(OBFUSCATE("Nametag"), &espNametag);
								ImGui::SameLine();
								ImGui::Checkbox(OBFUSCATE("Health"), &espHealth);
								ImGui::SameLine();
								ImGui::Checkbox(OBFUSCATE("Platform"), &espPlatform);
							}
							ImGui::EndTabItem();
				        }
					    ImGui::EndTabBar();
                    }
					ImGui::PopID();
			        ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
				break;
			case 5:
				ImGui::BeginChild(OBFUSCATE("HotkeyPanel"), ImVec2(0, 0), true);
				ImGui::PushItemWidth(calcResX * 300);
				ImGui::Text(OBFUSCATE("Replace Android Buttons:"));
                ImGui::Combo(OBFUSCATE("KEYCODE_VOLUME_UP"), &hotkeyVolumeUp, Hotkeys, IM_ARRAYSIZE(Hotkeys));
				ImGui::Combo(OBFUSCATE("KEYCODE_VOLUME_DOWN"), &hotkeyVolumeDown, Hotkeys, IM_ARRAYSIZE(Hotkeys));
				ImGui::Combo(OBFUSCATE("KEYCODE_VOLUME_BACK"), &hotkeyBack, Hotkeys, IM_ARRAYSIZE(Hotkeys));
				ImGui::Separator();
				ImGui::Text(OBFUSCATE("Replace Physical Keyboard Buttons:"));
				ImGui::Combo(OBFUSCATE("KEYCODE_A"), &hotkey_A, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_B"), &hotkey_B, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_C"), &hotkey_C, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_D"), &hotkey_D, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_E"), &hotkey_E, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_F"), &hotkey_F, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_G"), &hotkey_G, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_H"), &hotkey_H, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_I"), &hotkey_I, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_J"), &hotkey_J, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_K"), &hotkey_K, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_L"), &hotkey_L, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_M"), &hotkey_M, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_N"), &hotkey_N, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_O"), &hotkey_O, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_P"), &hotkey_P, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_Q"), &hotkey_Q, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_R"), &hotkey_R, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_S"), &hotkey_S, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_T"), &hotkey_T, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_U"), &hotkey_U, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_V"), &hotkey_V, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_W"), &hotkey_W, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_X"), &hotkey_X, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_Y"), &hotkey_Y, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_Z"), &hotkey_Z, Hotkeys, IM_ARRAYSIZE(Hotkeys));
				ImGui::Combo(OBFUSCATE("KEYCODE_NUMPAD_0"), &hotkey_numpad_0, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_NUMPAD_1"), &hotkey_numpad_1, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_NUMPAD_2"), &hotkey_numpad_2, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_NUMPAD_3"), &hotkey_numpad_3, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_NUMPAD_4"), &hotkey_numpad_4, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_NUMPAD_5"), &hotkey_numpad_5, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_NUMPAD_6"), &hotkey_numpad_6, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_NUMPAD_7"), &hotkey_numpad_7, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_NUMPAD_8"), &hotkey_numpad_8, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::Combo(OBFUSCATE("KEYCODE_NUMPAD_9"), &hotkey_numpad_9, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                ImGui::PushItemWidth(0);
				ImGui::EndChild();
				break;
			case 6:
				if (ImGui::BeginTabBar(OBFUSCATE("Tab2"))) {
					if (ImGui::BeginTabItem(OBFUSCATE("Exploits/Tweaks"))) {
				        ImGui::Checkbox(OBFUSCATE("Unlock Marketplace Items"), &unlockMarket);
                        ImGui::Checkbox(OBFUSCATE("Fast Item Drop"), &fastDrop);
						ImGui::SameLine();
						ImGui::Checkbox(OBFUSCATE("No Emote Use Cooldown"), &noEmoteCooldown);
						ImGui::EndTabItem();    
			    }
				if (ImGui::BeginTabItem(OBFUSCATE("LAN"))) {
				    ImGui::PushItemWidth(calcResX * 300);
				    ImGui::DragInt(OBFUSCATE("Host Max Players\n(Needs to re-enter the world)"), &myMaxPlayers, 0.05f, 1, 1000);
				    ImGui::EndTabItem();
                }
				if (ImGui::BeginTabItem(OBFUSCATE("Config"))) {
					ImGui::Text(OBFUSCATE("Config Load/Save Path: /sdcard/Download/Apollon.json")); 
					std::string loadPath = oxorany("/sdcard/Download/Apollon.json");
					if (ImGui::Button(OBFUSCATE("Load"))) {
					    std::ifstream file(loadPath);
                        if (file.good()){
                            loadConfig(loadPath);
                        }
						onFunctionSound = true;
		                AddNotification(oxorany("Config Loaded"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
				    }
				    ImGui::SameLine();
				    if (ImGui::Button(OBFUSCATE("Save"))) {
					    saveConfig(loadPath);
						onFunctionSound = true;
		                AddNotification(oxorany("Config Saved"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
				    }
					ImGui::EndTabItem();
                }
				ImGui::EndTabBar();
                }
				break;
            case 7:
				//ImGui::Text(inMemoryFunction.c_str());
				//ImGui::DragInt(OBFUSCATE("ActorId"), &nearActorId, 0.05f, 1, 50);
				ImGui::Text(OBFUSCATE("Thanks MCPELIFE for a decent pairip bypass :)"));
                DrawSeparatorToWindowEdge(endVertical, 16.0f);
                ImGui::Text(OBFUSCATE("Mod Version: v4.62")); 
                ImGui::Text(OBFUSCATE("Game Version: 1.21.111"));
                #if defined(__aarch64__)
                ImGui::Text(OBFUSCATE("Bit: 64")); 
                #elif defined(__ARM_ARCH_7A__)
                ImGui::Text(OBFUSCATE("Bit: 32"));
				#else
				ImGui::Text(OBFUSCATE("Bit: 86_64"));
                #endif
                DrawSeparatorToWindowEdge(endVertical, 16.0f);
				float imageSize = ImGui::GetFontSize();
				ImGui::Image((ImTextureID)(intptr_t)youtube_icon, ImVec2(imageSize, imageSize));
				ImGui::SameLine(calcResX * 35);
				ImGui::Text(OBFUSCATE(": @zeff_source"));
				DrawSeparatorToWindowEdge(endVertical, 16.0f);
				ImGui::Image((ImTextureID)(intptr_t)telegram_icon, ImVec2(imageSize, imageSize));
				ImGui::SameLine(calcResX * 35);
				ImGui::Text(OBFUSCATE(": @zeff_cheats"));
                DrawSeparatorToWindowEdge(endVertical, 16.0f);
				ImGui::Image((ImTextureID)(intptr_t)discord_icon, ImVec2(imageSize, imageSize));
				ImGui::SameLine(calcResX * 35);
				ImGui::Text(OBFUSCATE(": https://discord.gg/RSC4ZrVjS8"));
                DrawSeparatorToWindowEdge(endVertical, 16.0f);
                ImGui::Text(OBFUSCATE("Made By ZEFF"));
                break;
        }
        ImGui::EndGroup();
		ImGui::PopStyleVar(ImGuiStyleVar_WindowTitleAlign);
    }
	}
	}
	
	if (CI != NULL) {
		if (!inMenu && !panic) {
			if (inHudScreen) {
				glm::mat4 currentViewMatrix = CI->getViewMatrix();
                LevelRenderer *Render = CI->getLevelRenderer();
                if (Render) {
                    LevelRendererCamera *RenderPlayer = Render->getLevelRendererPlayer();
                    if (RenderPlayer) {
                        glm::vec2 currentFov = RenderPlayer->getFov();
                        CameraPos = RenderPlayer->getCameraPos();
                    
                        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
                        if (xrayDefault) RenderOreESP(draw_list, CameraPos, currentFov, currentViewMatrix);
                        if (deathPosition) RenderDeathPosition(draw_list, CameraPos, currentFov, currentViewMatrix);
                        if (esp) RenderESP(draw_list, CameraPos, currentFov, currentViewMatrix);
                    }
                }
			}
        }
	}
	if(!inMenu) {
		  if (showPosition) {
			  char textBuffer[100];
	          snprintf(textBuffer, sizeof(textBuffer), OBFUSCATE("Current position: %.2f, %.2f, %.2f"), playerPosX, playerPosY, playerPosZ);
	          DrawBackgroundText(textBuffer, offsetTextPosX, offsetTextPosY, ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
		  }
		  if (playerNear) {
			  char textBuffer[100];
			  char textBuffer2[100];
			  if (nearPlayer.empty()) {
				  snprintf(textBuffer, sizeof(textBuffer), OBFUSCATE("No players around you!"));
				  DrawBackgroundText(textBuffer, offsetTextPlayerNearPosX, offsetTextPlayerNearPosY, ImVec4(1, 0, 0, 1), ImVec4(0, 0, 0, 0.5));
			  } else {
				  snprintf(textBuffer, sizeof(textBuffer), OBFUSCATE("Players around you: %d"), nearPlayer.size());
				  DrawBackgroundText(textBuffer, offsetTextPlayerNearPosX, offsetTextPlayerNearPosY, ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 0.5));
			  }
			  if (!nearFriendList.empty()) {
			      snprintf(textBuffer2, sizeof(textBuffer2), OBFUSCATE("Friends around you: %d"), nearFriendList.size());
				  DrawBackgroundText(textBuffer2, offsetTextPlayerNearPosX, offsetTextPlayerNearPosY + 40 * scaleGlobal, ImVec4(0, 1, 1, 1), ImVec4(0, 0, 0, 0.5));
		      }
		  }
	 }
	 
    if (enableRainbow) {
        visibleColor.x = redd/255;
        visibleColor.y = greenn/255;
        visibleColor.z = bluee/255;
    }
    if (enableRainbowWall) {
        inWallColor.x = redd/255;
        inWallColor.y = greenn/255;
        inWallColor.z = bluee/255;
    }
    performRGBChange();
    Patches();
	if (!useGeyserCooldown) TickFunctions();
}
