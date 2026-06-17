#include <jni.h>
#include <android/native_activity.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <random>
#include <algorithm>
#include <ghc/filesystem.hpp>
namespace fs = ghc::filesystem;
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <signal.h>
#include <pthread.h>
#include <codecvt>
#include <chrono>
#include <queue>






#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include "CustomGL/custom_ui.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <sys/system_properties.h>

#include <string>
#include <cmath>
#include <android/keycodes.h>

//====================================
#include "FONTS/DEFAULT.h"
//=====================================
#include <Includes/Utils.h>
#include <Includes/Dobby/dobby.h>
#if defined(__aarch64__)
#include "Arm64/And64InlineHook.hpp"
#else
#include "Substrate/SubstrateHook.h"
#endif
#include "KittyMemory/MemoryPatch.h"
#include "KittyScanner/KittyScanner.hpp"
#include "ENCRYPT/obfuscate.h"
#include "ENCRYPT/oxorany.h"
#include "RGB.h"
#include "Chams.h"
#include "Includes/nlohmann/json.hpp"
#include "Includes/json.h"

typedef uint32_t _DWORD;
typedef uint64_t _QWORD;
#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long
#define _BYTE unsigned char


using json = nlohmann::json;
int screenWidth = 0;
int screenHeight = 0;
float scaleGlobal, calcResX;
bool g_Initialized = false;
ImGuiWindow* g_window = NULL; // Added for menu.h compatibility
string GameName = oxorany("com.mojang.minecraftpe");
const char* MineLib = OBFUSCATE("libminecraftpe.so");


struct My_Patches {MemoryPatch
Font0, Font1, Font2, Font3, Font4, Font5, Font6, Font7, Font8, Font9, Font10,
NoHurtCam, NoCamDistortion, NoBoatRotation, NoCamSleep, PlaceCamera,
NoSlowDown,
LavaDrown, WaterDrown,
SlowDownTriggers,
Noclip,
AutoClickMine,
XrayCameraThird,
NoEmoteUseCooldown,
NoBlur1, NoBlur2,
FullBright,
AntiKnockBack,
NativeKeyHandler,
NoCaveVignette
;} hexPatches;


#include "offsets.h"
#include "dark_theme.h"
#include "Vector.h"
#include "hook_classes.h"
#include "variables.h"
#include "hook_utils.h"
#include "menu_utils.h"


extern "C" {
    JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_platforms_Platform2_init(JNIEnv* env, jclass cls);
    JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_platforms_Platform2_resize(JNIEnv* env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_platforms_Platform2_step(JNIEnv* env, jobject obj);
    JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_platforms_Platform2_imgui_Shutdown(JNIEnv* env, jobject obj);
    JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_platforms_Platform2_MotionEventClick(JNIEnv* env, jobject obj,jboolean down,jfloat PosX,jfloat PosY);
    JNIEXPORT jstring JNICALL Java_com_mojang_minecraftpe_platforms_Platform2_getWindowRect(JNIEnv *env, jobject thiz);
};

JNIEXPORT void JNICALL
Java_com_mojang_minecraftpe_platforms_Platform2_init(JNIEnv* env, jclass cls) {

    //SetUp Custom UI
    if(!g_Initialized) {
    ImGuiIO& io = ImGui::GetIO();
	
    //Set UI Style
	embraceTheDarkness();
 
    ImFontConfig CustomFont;
    CustomFont.FontDataOwnedByAtlas = false;

	static const ImWchar ranges[] = {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0100, 0x024F, // Extended Latin
        0x0370, 0x03FF, // Greek
        0x0400, 0x04FF, // Cyrillic
        0x0500, 0x052F, // Cyrillic Supplement
        0x2000, 0x206F, // General Punctuation
        0x2070, 0x209F, // Superscripts and Subscripts
        0x20A0, 0x20CF, // Currency Symbols
        0x2100, 0x214F, // Letterlike Symbols
        0x2150, 0x218F, // Number Forms
        0x2190, 0x21FF, // Arrows
        0x2200, 0x22FF, // Mathematical Operators
        0x2300, 0x23FF, // Miscellaneous Technical
        0x2400, 0x243F, // Control Pictures
        0x2440, 0x245F, // Optical Character Recognition
        0x2460, 0x24FF, // Enclosed Alphanumerics
        0x2500, 0x257F, // Box Drawing
        0x2580, 0x259F, // Block Elements
        0x25A0, 0x25FF, // Geometric Shapes
        0x2600, 0x26FF, // Miscellaneous Symbols
        0x2700, 0x27BF, // Dingbats
        0x3000, 0x303F, // CJK Symbols and Punctuation
        0x3040, 0x309F, // Hiragana
        0x30A0, 0x30FF, // Katakana
        0x4E00, 0x9FFF, // CJK Unified Ideographs
        0xFF00, 0xFFEF, // Halfwidth and Fullwidth Forms
        0,
    };

    io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom3), sizeof(Custom3), 30.f, &CustomFont, ranges);

	static bool loadedCfg = false;
     if (!loadedCfg){
         std::ifstream file(oxorany("/data/data/") + GameName + oxorany("/xal/config.json"));
         if (file.good()){
             loadConfig(oxorany("/data/data/") + GameName + oxorany("/xal/config.json"));
         }
         loadedCfg = true;
     }
	g_Initialized = true;
	}
    return;
}

JNIEXPORT void JNICALL
Java_com_mojang_minecraftpe_platforms_Platform2_resize(JNIEnv* env, jobject obj, jint width, jint height) {
	if (g_Initialized) {
    screenWidth = (int) width;
    screenHeight = (int) height;
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;
    io.DisplaySize = ImVec2((float)screenWidth, (float)screenHeight);
	static bool isLoaded = false;
	if (!isLoaded) {
		ImGuiStyle& style = ImGui::GetStyle();
	    scaleGlobal = calculateResolutionScale(screenWidth, screenHeight, 2480, 1116);
		calcResX = calculateResolutionX(screenWidth, 2480);
	    style.ScaleAllSizes(scaleGlobal * 3.5);
        io.FontGlobalScale = scaleGlobal;
		style.WindowBorderSize                  = scaleGlobal * 2;
        style.ChildBorderSize                   = scaleGlobal * 2;
        style.PopupBorderSize                   = scaleGlobal * 2;
        style.FrameBorderSize                   = scaleGlobal * 2;
        style.TabBorderSize                     = scaleGlobal * 2;
		isLoaded = true;
	}
	}
	return;
}

void Patches() {
    if (inMenu) {
        hexPatches.NoHurtCam.Restore();
        hexPatches.NoCamDistortion.Restore();
        hexPatches.NoBoatRotation.Restore();
        hexPatches.NoCamSleep.Restore();
        hexPatches.PlaceCamera.Restore();
        hexPatches.SlowDownTriggers.Restore();
        hexPatches.XrayCameraThird.Restore();
    } else {
        if (noHurtCam && !panic) {
            hexPatches.NoHurtCam.Modify();
        } else {
            hexPatches.NoHurtCam.Restore();
        }
        if (noCamDist && !panic) {
            hexPatches.NoCamDistortion.Modify();
        } else {
            hexPatches.NoCamDistortion.Restore();
        }
        if (noBoatRotation && !panic) {
            hexPatches.NoBoatRotation.Modify();
        } else {
            hexPatches.NoBoatRotation.Restore();
        }
        if (noCamSleep && !panic) {
            hexPatches.NoCamSleep.Modify();
        } else {
            hexPatches.NoCamSleep.Restore();
        }
        if (placeCam && !panic) {
            hexPatches.PlaceCamera.Modify();
        } else {
            hexPatches.PlaceCamera.Restore();
        }
        if (offSlowdownTrigger && !isLANGame && !panic) {
            hexPatches.SlowDownTriggers.Modify();
        } else {
            hexPatches.SlowDownTriggers.Restore();
        }
        if (xrayCam && !panic) {
            hexPatches.XrayCameraThird.Modify();
        } else {
            hexPatches.XrayCameraThird.Restore();
        }
		if (antiKnockback && !isLANGame && !panic) {
			hexPatches.AntiKnockBack.Modify();
		} else {
			hexPatches.AntiKnockBack.Restore();
		}
	}
    
    if (fontSize == 0 && !panic) {
        hexPatches.Font0.Modify();
    }
    if (fontSize == 1 && !panic) {
        hexPatches.Font1.Modify();
    }
    if (fontSize == 2 && !panic) {
        hexPatches.Font2.Modify();
    }
    if (fontSize == 3 && !panic) {
        hexPatches.Font3.Modify();
    }
    if (fontSize == 4 && !panic) {
        hexPatches.Font4.Modify();
    }
    if (fontSize == 5 && !panic) {
        hexPatches.Font5.Modify();
    }
    if (fontSize == 6 && !panic) {
        hexPatches.Font6.Modify();
    }
    if (fontSize == 7 && !panic) {
        hexPatches.Font7.Modify();
    }
    if (fontSize == 8 && !panic) {
        hexPatches.Font8.Modify();
    }
    if (fontSize == 9 && !panic) {
        hexPatches.Font9.Modify();
    }
    if (fontSize == 10 && !panic) {
        hexPatches.Font10.Modify();
    }
    
    if (noSlowDown && !isLANGame && !panic) {
        hexPatches.NoSlowDown.Modify();
    } else {
        hexPatches.NoSlowDown.Restore();
    }
    
    if (offDrown && !panic) {
        hexPatches.LavaDrown.Modify();
        hexPatches.WaterDrown.Modify();
    } else {
        hexPatches.LavaDrown.Restore();
        hexPatches.WaterDrown.Restore();
    }
    
    if (noclip && !isLANGame && !panic) {
        hexPatches.Noclip.Modify();
    } else {
        hexPatches.Noclip.Restore();
    }
    
    if (clickAutoMine && !panic) {
        hexPatches.AutoClickMine.Modify();
    } else {
        hexPatches.AutoClickMine.Restore();
    }
	
	if (noEmoteCooldown && !panic) {
		hexPatches.NoEmoteUseCooldown.Modify();
	} else {
		hexPatches.NoEmoteUseCooldown.Restore();
	}
	
	if (noBlur && !panic) {
		hexPatches.NoBlur1.Modify();
		hexPatches.NoBlur2.Modify();
	} else {
		hexPatches.NoBlur1.Restore();
		hexPatches.NoBlur2.Restore();
	}
	if (!panic) {
		if (xrayDefault || fullBright) {
			hexPatches.FullBright.Modify();
	    } else {
		    hexPatches.FullBright.Restore();
		}
	} else hexPatches.FullBright.Restore();
	
	if (noCaveVignette && !panic) {
		hexPatches.NoCaveVignette.Modify();
	} else {
		hexPatches.NoCaveVignette.Restore();
	}
}

#include "menu.h"

JNIEXPORT void JNICALL
Java_com_mojang_minecraftpe_platforms_Platform2_step(JNIEnv* env, jobject obj) {
    if (g_Initialized) {
        removeDirectory(oxorany("/data/data/") + GameName + oxorany("/app_lib"));
        saveConfig(oxorany("/data/data/") + GameName + oxorany("/xal/config.json"));
        ImGuiIO& io = ImGui::GetIO();
        
        //Start Custom UI frame
        ImGui::NewFrame();
        
        BeginDraw();
        
        RenderNotifications();
        
        ImGui::EndFrame();
        ImGui::Render();
    }
}

JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_platforms_Platform2_imgui_Shutdown(JNIEnv* env, jobject obj){
    if (!g_Initialized)
        return;
     // Cleanup
    ImGui::DestroyContext();
    g_Initialized=false;
}

JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_platforms_Platform2_MotionEventClick(JNIEnv* env, jobject obj,jboolean down,jfloat PosX,jfloat PosY){
	if (g_Initialized) {
	ImGuiIO & io = ImGui::GetIO();
	io.MousePos = ImVec2(PosX, PosY);
	io.MouseDown[0] = down;
	}
}

JNIEXPORT jstring JNICALL Java_com_mojang_minecraftpe_platforms_Platform2_getWindowRect(JNIEnv *env, jobject thiz) {
    //get drawing window
    // TODO: accomplish getWindowSizePos()
	if (g_Initialized) {
    char result[512]="0|0|0|0";
	if (!panic) {
		if(g_window){
            sprintf(result,"%d|%d|%d|%d",(int)g_window->Pos.x,(int)g_window->Pos.y,(int)g_window->Size.x,(int)g_window->Size.y);
        }
	}
    return env->NewStringUTF(result);
	}
}

void *(*old_Intersects)(Mob *thiz, vec3_t *a2, vec3_t *a3);
void *Intersects(Mob *thiz, vec3_t *a2, vec3_t *a3) {
	if (panic) return old_Intersects(thiz, a2, a3);
	if (inMenu) return old_Intersects(thiz, a2, a3);
	if (thiz == localPlayer) {
		
		if (look360) {
			if (notSaved) {
				saveAngle = *thiz->getRotation();
				saveYHeadRot = thiz->getYHeadRot();
				notSaved = false;
		    }
			thiz->setRotationX(saveAngle.x);
			thiz->setRotationY(saveAngle.y);
			thiz->setYHeadRot(saveYHeadRot);
		} else {
			notSaved = true;
		}
		
		if (!isLANGame) {
		    if (derp) {
				thiz->setYHeadRot(derpGradys);
			    thiz->setYBodyRotation(derpGradys);
		    }
		}
		
		if (fireballRotation || itemRotation || !mobList.empty() || !playerList.empty()) {
			if (rotations) {
                if (!isLANGame && !emulateNativeAttack) thiz->setYBodyRotation(auraAngle.y);
			    thiz->setYHeadRot(auraAngle.y);
                thiz->setRotationX(auraAngle.x);
            }
            if (targetLock) {
                thiz->setRotationY(auraAngle.y);
            }
		}
    }
    return old_Intersects(thiz, a2, a3);
}

void *(*old_NormalTick)(LocalPlayer *thiz);
void *NormalTick(LocalPlayer *thiz) {
	if (panic) return old_NormalTick(thiz);
	localPlayer = NULL;
	if (inMenu) {
		isLoaded = true;
		return old_NormalTick(thiz);
	}
	
	//inMemoryFunction = format("Instance: %llX", thiz);
	
	if (isLoaded) {
		thiz->displayClientMessage(oxorany("§l§0[§5Apollon Client§0]§r Good Luck, Have Fun!"), "");
		isLoaded = false;
	}
	
	localPlayer = thiz;
	vec2_t *playerRot = thiz->getRotation();
	vec3_t *playerPos = thiz->getPosition();
	globalPlayerRot = *playerRot;
	globalPlayerPos = *playerPos;
	Level *myLevel = thiz->getLevel();
	GameMode *myGameMode = thiz->getGameMode();
	BlockSource *myBlockSource = thiz->getDimensionBlockSource();

	if (myBlockSource && xrayDefault) {
    for (int i = renderOresESP.size() - 1; i >= 0; i--) {
        vec3_t orePosition = {(float)renderOresESP[i].orePos.x, (float)renderOresESP[i].orePos.y, (float)renderOresESP[i].orePos.z};
        vec3_t camPos = {CameraPos.x, CameraPos.y, CameraPos.z};
        float distanceToBlock = distanceTo(&camPos, &orePosition);
        
        if (distanceToBlock > 32.0f) {
            renderOresESP.erase(renderOresESP.begin() + i);
            removedCount++;
            continue;
        }
        
        // ПРОВЕРКА НА AIR БЛОК
        Block *currentBlock = myBlockSource->getBlock(renderOresESP[i].orePos);
        if (!allowToXrayRender(renderOresESP[i].oreName) || currentBlock->isAir()) {
            renderOresESP.erase(renderOresESP.begin() + i);
            removedCount++;
			continue;
        }
    }
    
    if (removedCount >= 32) {
        rebuildChunkGeometry = true;
        removedCount = 0;
    }
} else {
    renderOresESP.clear();
}
	
	if (showPosition) {
	    playerPosX = playerPos->x;
	    playerPosY = playerPos->y;
	    playerPosY = playerPosY - 1.62;
	    playerPosZ = playerPos->z;
	}
	
	if (thiz->getHealth() == 0) {
		if (deathPosition) {
			vec3_t *deathPos = thiz->getPosition();
	        playerDeathPosX = deathPos->x;
	        playerDeathPosY = deathPos->y;
	        playerDeathPosY = playerDeathPosY - 1.62;
	        playerDeathPosZ = deathPos->z;
		}
		return old_NormalTick(thiz);
	}
	
	if (damageFly) {
		myGameMode->attack(thiz, true);
		myGameMode->attack(thiz, true);
		thiz->swing();
	}
	
	if (!isLANGame) {
		#if defined(__ARM_ARCH_7A__)
		LocalPlayer *EntityAccess = (LocalPlayer *)((char *)thiz + 4);
		#else
		LocalPlayer *EntityAccess = (LocalPlayer *)((char *)thiz + 8);
		#endif
	    if (strafe) {
			EntityAccess->setOnGround(1, true);
			EntityAccess->setIsJumping(0, true);
		}
		if (noJumpDelay) EntityAccess->setNoJumpDelay(1, 0);
		if (alwaysSprinting) thiz->setSprinting(true);
	    if (ladderFly) thiz->setClimbing(true);
	    if (step) {
	        thiz->initializeMaxAutoStep(1.0625);
	    } else {
		    thiz->initializeMaxAutoStep(0.5625);
	    }
		if (creativeFly) {
			thiz->getAbilities()->getLayer(2)->setAbility(10, true);
			activatedCreativeFly = true;
		} else if (activatedCreativeFly && !creativeFly) {
			if (thiz->isAttackableGamemode()) thiz->getAbilities()->getLayer(2)->setAbility(10, false);
			activatedCreativeFly = false;
		}
		if (forceCreativeFly) {
			thiz->getAbilities()->getLayer(2)->setAbility(9, true);
			activatedForceCreativeFly = true;
		} else if (activatedForceCreativeFly && !forceCreativeFly) {
			if (thiz->isAttackableGamemode()) thiz->getAbilities()->getLayer(2)->setAbility(9, false);
			activatedCreativeFly = false;
		}
	} else thiz->initializeMaxAutoStep(0.5625);
	
	std::vector<Mob*> actors = myLevel->getRuntimeActorList();
	nearestMob = NULL;
	fireballRotation = false;
	itemRotation = false;
	mobList.clear();
	
	for (Mob *object : actors) {
		if (object != thiz) {
			if (antiInvis) object->setInvisible(false);
			vec3_t *targetPos = object->getPosition();
			vec2_t *targetHitBox = object->getAABBDim();
			vec2_t calcTargetHitBox = *targetHitBox;
			float distanceToActor = mobDistanceTo(playerPos, targetPos, calcTargetHitBox.y);
			
			int ActorId = object->getEntityTypeId();
			if (distanceToActor <= 10 && ActorId == 4194389) {
			    if (antiFireball) {
					if (rotations) {
                        vec3_t calcObjPos = *targetPos;
                        auraAngle = globalPlayerPos.CalcPlayerAngle(calcObjPos);
						fireballRotation = true;
				    }
					myGameMode->attack(object, true);
			        if (swing) thiz->swing();
				}
				continue;
			} else if (distanceToActor <= 7 && ActorId == 64) {
			    if (killItems) {
					if (rotations) {
                        vec3_t calcObjPos = *targetPos;
                        auraAngle = globalPlayerPos.CalcPlayerAngle(calcObjPos);
						itemRotation = true;
				    }
				    myGameMode->attack(object, true);
			        if (swing) thiz->swing();
			    }
				continue;
			} else {
				if (mobAura) {
				    if (distanceToActor <= mobAuraRange && object->getHealth() != 0 && MobDetected(ActorId)) mobList.push_back(object);
                }
			}
		}
	}
	
	nearestTarget = NULL;
	nearestKillTarget = NULL;
	nearFriendList.clear();
	playerList.clear();
	nearPlayerList.clear();
	nearPlayer.clear();
	std::vector<Player*> nearPlayers;
	
    myLevel->getGameplayUserManager()->forEachActivePlayer([&](Player& objectt) {
        nearPlayers.push_back(&objectt);
		return true;
    }, true);

	for (Player *objectt : nearPlayers) {
		 if (objectt == thiz) continue;
		vec2_t* AABB = objectt->getAABBDim();
		const std::string PlayerName = objectt->getName();
		const std::string PlayerNameTag = objectt->getNameTag();
		vec2_t Hitbox = *AABB;
				
        if (antiBot) {
            if (PlayerName.length() <= 1) continue;
			if (PlayerNameTag.length() <= 1) continue;
            if (!AABB) continue;
            if (Hitbox.y < 0.05f || Hitbox.x < 0.05f || Hitbox.y > 2.1f || Hitbox.x > 10.9f) continue;
        }
		
			bool isFriend = false;
			bool isBotList = false;

			for (std::string currentPlayer : botList) {
				if (currentPlayer == PlayerName) {
				    isBotList = true;
					break;
				}
			}
			
			if (!isBotList) {
				for (std::string currentPlayer : friendList) {
				    if (currentPlayer == PlayerName) {
					    if (playerNear) nearFriendList.push_back(PlayerName);
				        isFriend = true;
						break;
				    }
			    }
			}
			
			bool isAttackable = objectt->isAttackableGamemode();
			if (!isFriend && !isBotList) {
				AABB->x = hitBox ? hitBoxValue : 0.6;
				nearPlayer.push_back(PlayerName);
			}
					
			int targetHealth = objectt->getHealth();
			vec3_t* targetPos = objectt->getPosition();
			
            nearPlayerList.push_back({PlayerName, PlayerNameTag, targetPos, Hitbox, targetHealth, objectt->getHurtTime(), objectt->getPlatform(), !isAttackable, isFriend, isBotList});
					
            if (killAura) {
				float distanceTo = hackDistanceTo(playerPos, targetPos);
				if (distanceTo <= rotationsRange) {
                    if (isAttackable && !isFriend && !isBotList && targetHealth != 0) {
                        if (rotations || targetLock) {
                            if (distanceTo <= rotationsRange) {
                                playerList.push_back(objectt);
                            }
                        } else {
                            if (distanceTo <= killRange) {
                                playerList.push_back(objectt);
                            }
                        }
                    }
			    }
            }
	}
	
		if (!mobList.empty()) {
			switch (auraType) {
				case 0: {
					if (rotations || targetLock) {
						vec3_t *objPos = mobList[0]->getPosition();
						vec2_t *hitBox = mobList[0]->getAABBDim();
                        vec3_t calcObjPos = *objPos;
						vec2_t calcHitBox = *hitBox;
                        auraAngle = globalPlayerPos.CalcMobAngle(calcObjPos, calcHitBox.y);
					}
					bool canHurt = true;
					if (hurtCheck) canHurt = mobList[0]->canBeHurted();
					if (canMobAuraDamage && canHurt) {
						myGameMode->attack(mobList[0], true);
                        if (swing) thiz->swing();
                        canMobAuraDamage = false;
                    }
				break;
				}
				case 1: {
					float nearestMobDistance = 9999;
                    for (Mob *potentialTarget : mobList) {
						if (potentialTarget != NULL) {
							vec2_t *potentialHitBox = potentialTarget->getAABBDim();
							vec2_t calcPotentialHitBox = *potentialHitBox;
							float potentialDistance = mobDistanceTo(playerPos, potentialTarget->getPosition(), calcPotentialHitBox.y);
                            if (potentialDistance < nearestMobDistance && potentialDistance <= mobAuraRange) {
                                nearestMobDistance = potentialDistance;
                                nearestMob = potentialTarget;
                            }
						}
                    }
					if (nearestMob != NULL) {
						//inMemoryFunction = nearestMob->getNameTag();
						//nearActorId = nearestMob->getEntityTypeId();
						if (rotations || targetLock) {
							vec3_t* objPos = nearestMob->getPosition();
							vec2_t *hitBox = nearestMob->getAABBDim();
                            vec3_t calcObjPos = *objPos;
							vec2_t calcHitBox = *hitBox;
                            auraAngle = globalPlayerPos.CalcMobAngle(calcObjPos, calcHitBox.y);
						}
						bool canHurt = true;
						if (hurtCheck) canHurt = nearestMob->canBeHurted();
                        if (canMobAuraDamage && canHurt) {
                            myGameMode->attack(nearestMob, true);
                            if (swing) thiz->swing();
                            canMobAuraDamage = false;
                        }
					}
                break;
                }
				case 2: {
					float nearestMobDistance = 9999;
                    for (Mob *potentialTarget : mobList) {
						if (potentialTarget != NULL) {
							vec2_t *potentialHitBox = potentialTarget->getAABBDim();
							vec2_t calcPotentialHitBox = *potentialHitBox;
							float potentialDistance = mobDistanceTo(playerPos, potentialTarget->getPosition(), calcPotentialHitBox.y);
                            if (potentialDistance < nearestMobDistance && potentialDistance <= mobAuraRange) {
                                nearestMobDistance = potentialDistance;
                                nearestMob = potentialTarget;
                            }
						}
                    }
					if (nearestMob != NULL) {
						if (rotations || targetLock) {
							vec3_t* objPos = nearestMob->getPosition();
							vec2_t *hitBox = nearestMob->getAABBDim();
                            vec3_t calcObjPos = *objPos;
							vec2_t calcHitBox = *hitBox;
                            auraAngle = globalPlayerPos.CalcMobAngle(calcObjPos, calcHitBox.y);
						}
					    for (Mob*actors : mobList) {
						    if (maxMobAuraTick > currentMobTick) {
						        currentMobTick = currentMobTick + 1;
					        } else {
								bool canHurt = true;
						        if (hurtCheck) canHurt = actors->canBeHurted();
								if (canHurt) {
									myGameMode->attack(actors, true);
					                if (swing) thiz->swing();
						            currentMobTick = 1;
								}
						    }
					    }
					}
				break;
				}
			}
		}

    if (!playerList.empty()) {
        switch (auraType) {
			case 0: {
				vec3_t* objPos = playerList[0]->getPosition();
				if (rotations || targetLock) {
                    vec3_t calcObjPos = *objPos;
                    auraAngle = globalPlayerPos.CalcPlayerAngle(calcObjPos);
				}
				if (hackDistanceTo(playerPos, objPos) <= killRange) {
					bool canHurt = true;
					if (hurtCheck) canHurt = playerList[0]->canBeHurted();
					if (canKillAuraDamage && canHurt) {
						if (!emulateNativeAttack) {
                            myGameMode->attack(playerList[0], true);
						} else {
							doHandleAttack = true;
						}
                        if (swing) thiz->swing();
                        canKillAuraDamage = false;
                    }
				}
			break;
			}
            case 1: {
                float nearestDistance = 9999;
                for (Player *potentialTarget : playerList) {
					if (potentialTarget != NULL) {
						float potentialDistance = hackDistanceTo(playerPos, potentialTarget->getPosition());
                        if (potentialDistance < nearestDistance && potentialDistance <= rotationsRange) {
                            nearestDistance = potentialDistance;
                            nearestTarget = potentialTarget;
							if (potentialDistance <= killRange) {
								nearestKillTarget = potentialTarget;
							}
                        }
					}
                }
				if (nearestTarget != NULL) {
					//inMemoryFunction = std::to_string(*(int *)((uint64_t)nearestTarget + 0x47C));
					if (rotations || targetLock) {
                        vec3_t* objPos = nearestTarget->getPosition();
                        vec3_t calcObjPos = *objPos;
                        auraAngle = globalPlayerPos.CalcPlayerAngle(calcObjPos);
					}
					if (nearestKillTarget != NULL) {
						bool canHurt = true;
					    if (hurtCheck) canHurt = nearestTarget->canBeHurted();
						if (canKillAuraDamage && canHurt) {
						    if (!emulateNativeAttack) {
                                myGameMode->attack(nearestTarget, true);
						    } else {
							    doHandleAttack = true;
						    }
                            if (swing) thiz->swing();
                            canKillAuraDamage = false;
                        }
					}
				}
            break;
			}
            case 2: {
				float nearestDistance = 9999;
                for (Player *potentialTarget : playerList) {
					if (potentialTarget != NULL) {
						float potentialDistance = hackDistanceTo(playerPos, potentialTarget->getPosition());
                        if (potentialDistance < nearestDistance && potentialDistance <= rotationsRange) {
                            nearestDistance = potentialDistance;
                            nearestTarget = potentialTarget;
							if (potentialDistance <= killRange) {
								nearestKillTarget = potentialTarget;
							}
                        }
					}
                }
				if (nearestTarget != NULL) {
					if (rotations || targetLock) {
                        vec3_t* objPos = nearestTarget->getPosition();
                        vec3_t calcObjPos = *objPos;
                        auraAngle = globalPlayerPos.CalcPlayerAngle(calcObjPos);
					}
				    if (nearestKillTarget != NULL) {
						for (Player *actors : playerList) {
							if (maxKillTick > currentKillTick) {
                                currentKillTick = currentKillTick + 1;
                            } else {
								bool canHurt = true;
						        if (hurtCheck) canHurt = actors->canBeHurted();
								if (canHurt) {
							        myGameMode->attack(actors, true);
                                    if (swing) thiz->swing();
							        currentKillTick = 1;
								}
						    }
						}
                    }
				}
            break;
			}
        }
    }
    
    // ---- Auto Totem (Direct Memory Access) ----
    // Uses Player field offsets for Supplies and ArmorContainer
    // Supplies/PlayerInventory is inline at Player+0xB40 (arm64)
    // ArmorContainer is inline at Player+0xBC0 (arm64)
    // Offhand is slot 4 in armor container
    // ItemStack size ~0x90 (144 bytes) on arm64 for MCPE 1.21.x
    if (autoTotem && !panic && !inMenu && thiz->getHealth() > 0) {
        static auto lastTotemCheck = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTotemCheck).count();
        
        if (elapsed >= autoTotemDelay) {
            lastTotemCheck = now;
            
#if defined(__aarch64__)
            // Supplies (PlayerInventory) is inline at Player+0xB40
            PlayerInventory* supplies = (PlayerInventory*)((uint64_t)thiz + Fields64::SuppliesOffset);
            // ArmorContainer is inline at Player+0xBC0
            Container* armor = (Container*)((uint64_t)thiz + Fields64::ArmorContainerOffset);
            
            if (armor && supplies) {
                const uint64_t ITEM_STACK_SIZE = 0x90; // arm64 ItemStack size
                
                // Try pointer to items array at Container+0x138
                // Fallback: items are stored inline at that offset
                uint64_t containerItemsPtr = *(uint64_t *)((uint64_t)armor + 0x138);
                if (containerItemsPtr == 0) containerItemsPtr = ((uint64_t)armor + 0x138);
                
                // Offhand is slot 4 in armor container
                uint64_t offhandAddr = containerItemsPtr + (4 * ITEM_STACK_SIZE);
                ItemStack* offhandItem = (ItemStack*)offhandAddr;
                
                bool hasTotem = false;
                if (offhandItem && !offhandItem->isEmpty() && offhandItem->isTotem()) {
                    hasTotem = true;
                }
                
                if (!hasTotem) {
                    // Supplies first field (after vtable) is usually a Container* pointer
                    Container* inventory = *(Container**)((uint64_t)supplies + 0x8);
                    if (inventory) {
                        uint64_t invItemsPtr = *(uint64_t *)((uint64_t)inventory + 0x138);
                        if (invItemsPtr == 0) invItemsPtr = ((uint64_t)inventory + 0x138);
                        
                        // Search all 36 inventory slots for a totem
                        for (int slot = 0; slot < 36; slot++) {
                            uint64_t itemAddr = invItemsPtr + (slot * ITEM_STACK_SIZE);
                            ItemStack* item = (ItemStack*)itemAddr;
                            
                            if (item && !item->isEmpty() && item->isTotem()) {
                                // Swap totem <-> offhand via raw memcpy
                                char oldOffhand[ITEM_STACK_SIZE];
                                memcpy(oldOffhand, (void*)offhandAddr, ITEM_STACK_SIZE);
                                memcpy((void*)offhandAddr, (void*)itemAddr, ITEM_STACK_SIZE);
                                memcpy((void*)itemAddr, oldOffhand, ITEM_STACK_SIZE);
                                
                                hasTotem = true;
                                break;
                            }
                        }
                    }
                }
            }
#elif defined(__ARM_ARCH_7A__)
            // arm32: Supplies (PlayerInventory) inline at Player+SelectedSlot (0xB40)
            PlayerInventory* supplies = (PlayerInventory*)((uint64_t)thiz + Fields::SelectedSlot);
            // arm32: ArmorContainer inline at Player+ArmorContainerOffset (0xBC0)
            Container* armor = (Container*)((uint64_t)thiz + Fields::ArmorContainerOffset);
            
            if (armor && supplies) {
                const uint64_t ITEM_STACK_SIZE = 0x60; // arm32 ItemStack size (approximate)
                
                // Container items array pointer (arm32 offset ~0x98)
                uint64_t containerItemsPtr = *(uint64_t *)((uint64_t)armor + 0x98);
                if (containerItemsPtr == 0) containerItemsPtr = ((uint64_t)armor + 0x98);
                
                uint64_t offhandAddr = containerItemsPtr + (4 * ITEM_STACK_SIZE);
                ItemStack* offhandItem = (ItemStack*)offhandAddr;
                
                bool hasTotem = false;
                if (offhandItem && !offhandItem->isEmpty() && offhandItem->isTotem()) {
                    hasTotem = true;
                }
                
                if (!hasTotem) {
                    Container* inventory = *(Container**)((uint64_t)supplies + 0x4);
                    if (inventory) {
                        uint64_t invItemsPtr = *(uint64_t *)((uint64_t)inventory + 0x98);
                        if (invItemsPtr == 0) invItemsPtr = ((uint64_t)inventory + 0x98);
                        
                        for (int slot = 0; slot < 36; slot++) {
                            uint64_t itemAddr = invItemsPtr + (slot * ITEM_STACK_SIZE);
                            ItemStack* item = (ItemStack*)itemAddr;
                            
                            if (item && !item->isEmpty() && item->isTotem()) {
                                char oldOffhand[ITEM_STACK_SIZE];
                                memcpy(oldOffhand, (void*)offhandAddr, ITEM_STACK_SIZE);
                                memcpy((void*)offhandAddr, (void*)itemAddr, ITEM_STACK_SIZE);
                                memcpy((void*)itemAddr, oldOffhand, ITEM_STACK_SIZE);
                                
                                hasTotem = true;
                                break;
                            }
                        }
                    }
                }
            }
#else
            // x86_64 fallback (not fully implemented for auto totem)
            // Skip auto totem on unsupported architectures
#endif
        }
    }
    // ---- End Auto Totem ----     
    return old_NormalTick(thiz);
}

void *(*old_PlayerAuthInputPacket)(void *a1, void *a2);
void *PlayerAuthInputPacket(void *a1, void *a2) {
	if (panic) return old_PlayerAuthInputPacket(a1, a2);
	if (!inMenu) {
		if (!isLANGame) {
		if (derp) {
		    if (derpGradys < 360) {
			    derpGradys = derpGradys + 30;
		    } else {
			    derpGradys = 0;
		    }
			#if defined(__ARM_ARCH_7A__)
			*(float *)((int)a1 + 36) = derpGradys;
			#else
			*(float *)((__int64)a1 + 48) = derpGradys;
			#endif
		}
		if (rotations) {
			if (fireballRotation || itemRotation || !mobList.empty() || !playerList.empty()) {
				#if defined(__ARM_ARCH_7A__)
				*(float *)((int)a1 + 36) = auraAngle.y;
				#else
				*(float *)((__int64)a1 + 48) = auraAngle.y;
				#endif
			}
		}
		}
	}
	return old_PlayerAuthInputPacket(a1, a2);
}

void *(*old_ClientInstance_onTick)(ClientInstance *thiz, void *a2, void *a3);
void *ClientInstance_onTick(ClientInstance *thiz, void *a2, void *a3) {
	CI = thiz;
	std::string currentScreenName = thiz->getScreenName();
	//inMemoryFunction = currentScreenName;
	if (currentScreenName == oxorany("hud_screen")) {
		inHudScreen = true;
		inMenu = false;
	} else {
		inHudScreen = false;
	}
	if (currentScreenName == oxorany("chat_screen")) {
		inChatScreen = true;
	} else {
		inChatScreen = false;
	}
	if (currentScreenName == oxorany("/hbui/index.html")) {
		manageWorldsScreen = true;
	} else {
		manageWorldsScreen = false;
	}
	if (panic) return old_ClientInstance_onTick(thiz, a2, a3);
	
	if (onFunctionSound) {
		thiz->playUI(oxorany("random.pop"), 0.2, 2);
		onFunctionSound = false;
	}
	if (offFunctionSound) {
		thiz->playUI(oxorany("random.pop2"), 0.2, 2);
		offFunctionSound = false;
	}
	if (errorFunctionSound) {
		thiz->playUI(oxorany("random.break"), 0.2, 2);
		errorFunctionSound = false;
	}
	if (inMenu) return old_ClientInstance_onTick(thiz, a2, a3);
	
	LevelRenderer *thisLevel = thiz->getLevelRenderer();
	//inMemoryFunction = format((void *)thiz);
	//inMemoryFunction = format((void *)thisLevel->getLevelRendererPlayer());
	
	if (rebuildChunkGeometry) {
		thisLevel->rebuildAllRenderChunkGeometry();
		rebuildChunkGeometry = false;
	}

	if (doHandleAttack) {
		thiz->handleDestoryOrAttackButtonPress();
		doHandleAttack = false;
	}
	
	if (autoClicker) {
		if (canClick) {
			thiz->handleDestoryOrAttackButtonPress();
			canClick = false;
		}
	}
    return old_ClientInstance_onTick(thiz, a2, a3);
}

void *(*old_HudPlayerRenderer_update)(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9, void *a10);
void *HudPlayerRenderer_update(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9, void *a10) {
	if (!panic) {
		if (showPaperdoll) {
			#if defined(__ARM_ARCH_7A__)
			*(float *)((int)a1 + 8) = 0.3;
			#else
			*(float *)((__int64)a1 + 12) = 0.3;
			#endif
		}
	}
    return old_HudPlayerRenderer_update(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

void *(*old_InLanGame1)(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9, void *a10);
void *InLanGame1(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9, void *a10) {
	if (!inMenu) isLANGame = true;
    return old_InLanGame1(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

void *(*old_InLanGame2)(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9, void *a10);
void *InLanGame2(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9, void *a10) {
	if (!inMenu) isLANGame = true;
    return old_InLanGame2(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

void **(*old_InMainMenu)(void **a1, void **a2, void **a3, void **a4, void **a5, void **a6, void **a7, void **a8, void **a9, void **a10);
void **InMainMenu(void **a1, void **a2, void **a3, void **a4, void **a5, void **a6, void **a7, void **a8, void **a9, void **a10) {
	inMenu = true;
	isLANGame = false;
	nearestTarget = NULL;
	nearestKillTarget = NULL;
	nearestMob = NULL;
	localPlayer = NULL;
	fireballRotation = false;
	itemRotation = false;
	playerList.clear();
	nearPlayerList.clear();
	nearPlayer.clear();
	nearFriendList.clear();
	mobList.clear();
	renderOresESP.clear();
    return old_InMainMenu(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

int (*old_LevelRendererCamera_FogState)(void *a1);
int LevelRendererCamera_FogState(void *a1) {
	if (!panic) {
		if (fogState != 0) return fogState - 1;
	}
    return old_LevelRendererCamera_FogState(a1);
}

float (*old_PlayerFov)(void *a1, void *a2, void *a3, void *a4);
float PlayerFov(void *a1, void *a2, void *a3, void *a4) {
	if (!panic) {
		if (enableFov) return globalPlayerFov =  old_PlayerFov(a1, a2, a3, a4) + fov;
	}
	return globalPlayerFov = old_PlayerFov(a1, a2, a3, a4);
}

void (*old_DropItemTime)(void *a1);
void DropItemTime(void *a1) {
	if (panic) return old_DropItemTime(a1);
	if (fastDrop) {
	    #if defined(__ARM_ARCH_7A__)
		float currentTime = *(float *)((int)a1 + 436);
	    if (currentTime < 35) *(float *)((int)a1 + 436) = 35;
		#else
		float currentTime = *(float *)((__int64)a1 + 692);
	    if (currentTime < 35) *(float *)((__int64)a1 + 692) = 35;
		#endif
	}
    return old_DropItemTime(a1);
}

void (*old_Gravity)(...);
#if defined(__ARM_ARCH_7A__)
void Gravity(void *a1, void *a2, void *a3, int a4, void *a5, void *a6) {
#else
void Gravity(void *a1, void *a2, void *a3, __int64 a4, void *a5, void *a6) {
#endif
    if (panic) return old_Gravity(a1, a2, a3, a4, a5, a6);
    if (!isLANGame) {
		float mine = *(float *)(a4 + 28);
	    *(float *)(a4 + 28) = mine + gravityValue + 0.08;
		if (fastFall) {
			if (mine < 0) *(float *)(a4 + 28) = -99;
		}
	}
    return old_Gravity(a1, a2, a3, a4, a5, a6);
}

int (*old_AppPlatform_getMaxPlayers)(void *thiz);
int AppPlatform_getMaxPlayers(void *thiz) {
	if (!panic) return myMaxPlayers;
    return old_AppPlatform_getMaxPlayers(thiz);
}

bool (*old_Entitlement_UnlockMarket)(void *a1, void *a2);
bool Entitlement_UnlockMarket(void *a1, void *a2) {
	if (!panic) {
		if (unlockMarket && !manageWorldsScreen) return true;
	}
    return old_Entitlement_UnlockMarket(a1, a2);
}

int (*old_GameMode_FastBridge)(int a1, int a2, int *a3, int a4, int a5, int a6);
int GameMode_FastBridge(int a1, int a2, int *a3, int a4, int a5, int a6) {
	if (panic) return old_GameMode_FastBridge(a1, a2, a3, a4, a5, a6);
	if (fastBridge) {
		old_GameMode_FastBridge(a1, a2, a3, a4, a5, a6);
		return 0;
	}
    return old_GameMode_FastBridge(a1, a2, a3, a4, a5, a6);
}

float (*old_GameMode_BlockReach)(void *a1, void *a2, void *a3);
float GameMode_BlockReach(void *a1, void *a2, void *a3) {
	if (!panic) {
		if (blockReach) return 12;
	}
    return old_GameMode_BlockReach(a1, a2, a3);
}

void *(*old_LevelRendererPlayer_setupFog)(void *a1, void *a2, void *a3);
void *LevelRendererPlayer_setupFog(void *a1, void *a2, void *a3) {
	if (panic) return old_LevelRendererPlayer_setupFog(a1, a2, a3);
	if (antiBlind) {
		#if defined(__ARM_ARCH_7A__)
		*(bool *)((int)a1 + 1682) = true;
		#else
		*(bool *)((__int64)a1 + 2450) = true;
		#endif
	}
    return old_LevelRendererPlayer_setupFog(a1, a2, a3);
}

void (*old_SpeedHack)(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9, void *a10, void *a11, void *a12, void *a13);
void SpeedHack(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9, void *a10, void *a11, void *a12, void *a13) {
	if (panic) return old_SpeedHack(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
	if (!isLANGame) {
	    for (int i = 0; i < speedValue - 1; ++i) {
		    old_SpeedHack(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
        }
	}
    return old_SpeedHack(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
}

float (*old_JumpHack)(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
float JumpHack(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6) {
	if (panic) return 0.42;
	if (!isLANGame) {
	    if (jumpValue != 1) {
		    return 0.42 + ((jumpValue - 1) / 10);
	    }
	}
    return 0.42;
}

void (*old_WaterSpeed)(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
void WaterSpeed(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6) {
	if (panic) return old_WaterSpeed(a1, a2, a3, a4, a5, a6);
	if (!isLANGame) {
	    for (int i = 0; i < waterSpeedValue - 1; ++i) {
		    old_WaterSpeed(a1, a2, a3, a4, a5, a6);
        }
	}
    return old_WaterSpeed(a1, a2, a3, a4, a5, a6);
}

void (*old_LavaSpeed)(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
void LavaSpeed(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6) {
	if (panic) return old_LavaSpeed(a1, a2, a3, a4, a5, a6);
	if (!isLANGame) {
	    for (int i = 0; i < lavaSpeedValue - 1; ++i) {
		    old_LavaSpeed(a1, a2, a3, a4, a5, a6);
        }
	}
    return old_LavaSpeed(a1, a2, a3, a4, a5, a6);
}


#if defined(__ARM_ARCH_7A__)
int *(*old_WasInWater)(_DWORD *a1, int a2);
int *WasInWater(_DWORD *a1, int a2) {
	if (panic) return old_WasInWater(a1, a2);
	if (!isLANGame) {
	    if (!inMenu && offWaterTrigger) {
		    *(_DWORD *)(a1[7] + 4 * ((((unsigned int)(a1[8] - a1[7]) >> 2) - 1) & a2)) = -1;
	    }
	}
	return old_WasInWater(a1, a2);
}

int *(*old_ActorHeadInWater)(_DWORD *a1, int a2);
int *ActorHeadInWater(_DWORD *a1, int a2) {
	if (panic) return old_ActorHeadInWater(a1, a2);
	if (!isLANGame) {
	    if (!inMenu && offWaterTrigger) {
		    *(_DWORD *)(a1[7] + 4 * ((((unsigned int)(a1[8] - a1[7]) >> 2) - 1) & a2)) = -1;
	    }
	}
	return old_ActorHeadInWater(a1, a2);
}

int *(*old_WaterSplashEffect)(_DWORD *a1, int a2);
int *WaterSplashEffect(_DWORD *a1, int a2) {
	if (panic) return old_WaterSplashEffect(a1, a2);
	if (!isLANGame) {
	    if (!inMenu && offWaterTrigger) {
		    *(_DWORD *)(a1[7] + 4 * ((((unsigned int)(a1[8] - a1[7]) >> 2) - 1) & a2)) = -1;
	    }
	}
	return old_WaterSplashEffect(a1, a2);
}


#else


__int64 (*old_WasInWater)(_QWORD *a1, int a2);
__int64 WasInWater(_QWORD *a1, int a2) {
	if (panic) return old_WasInWater(a1, a2);
	if (!isLANGame) {
	    if (!inMenu && offWaterTrigger) {
		    *(_QWORD *)(a1[7] + 8LL * (((unsigned int)((unsigned __int64)(a1[8] - a1[7]) >> 3) - 1) & a2)) = -1;
	    }
	}
	return old_WasInWater(a1, a2);
}

__int64 (*old_ActorHeadInWater)(_QWORD *a1, int a2);
__int64 ActorHeadInWater(_QWORD *a1, int a2) {
	if (panic) return old_ActorHeadInWater(a1, a2);
	if (!isLANGame) {
	    if (!inMenu && offWaterTrigger) {
		    *(_QWORD *)(a1[7] + 8LL * (((unsigned int)((unsigned __int64)(a1[8] - a1[7]) >> 3) - 1) & a2)) = -1;
	    }
	}
	return old_ActorHeadInWater(a1, a2);
}

__int64 (*old_WaterSplashEffect)(_QWORD *a1, int a2);
__int64 WaterSplashEffect(_QWORD *a1, int a2) {
	if (panic) return old_WaterSplashEffect(a1, a2);
	if (!isLANGame) {
	    if (!inMenu && offWaterTrigger) {
		    *(_QWORD *)(a1[7] + 8LL * (((unsigned int)((unsigned __int64)(a1[8] - a1[7]) >> 3) - 1) & a2)) = -1;
	    }
	}
	return old_WaterSplashEffect(a1, a2);
}
#endif

bool canDamageGeyser = true;
void (*old_TitleMessage_setSubtitle)(void *, std::string, void *);
void TitleMessage_setSubtitle(void *a1, std::string a2, void *a3) {
	if (canDamageGeyser) {
		if (useGeyserCooldown) {
		     if (a2 == oxorany("§8˙˙˙˙˙˙˙˙§7˙˙") || a2 == oxorany("§8˙˙˙˙˙˙˙˙˙§7˙") || a2 == oxorany("§8˙˙˙˙˙˙˙˙˙˙§7")) {
		        canKillAuraDamage = true;
		        canMobAuraDamage = true;
		        canDamageGeyser = false;
	        }
		}
	} else {
		canDamageGeyser = true;
	}
	return old_TitleMessage_setSubtitle(a1, a2, a3);
}

unsigned __int8 (*old_Block_getRenderLayer)(Block *thiz, void *a2, const vec3_ti &blockPos);
unsigned __int8 Block_getRenderLayer(Block *thiz, void *a2, const vec3_ti &blockPos) {
    if (inMenu) return old_Block_getRenderLayer(thiz, a2, blockPos);
	if (xrayDefault && !panic) {
    BlockType *v5 = thiz->getBlockTypeClassCustom();
    if (!v5) return old_Block_getRenderLayer(thiz, a2, blockPos);

    #if defined(__ARM_ARCH_7A__)
    const std::string *blockName = (const std::string *)((char *)v5 + 4);
    #else
    const std::string *blockName = (const std::string *)((char *)v5 + 8);
    #endif

    if (!blockName || blockName->empty()) return old_Block_getRenderLayer(thiz, a2, blockPos);

    std::string blockView = *blockName;
    vec3_t orePosition = {(float)blockPos.x, (float)blockPos.y, (float)blockPos.z};
    vec3_t camPos = {CameraPos.x, CameraPos.y, CameraPos.z};
    float distanceToBlock = distanceTo(&camPos, &orePosition);
    
    if (allowToXrayRender(blockView)) {
        if (distanceToBlock <= 32.0f) {
            bool alreadyExists = false;
            for (XrayOres existingOre : renderOresESP) {
                if (existingOre.orePos.x == blockPos.x && 
                    existingOre.orePos.y == blockPos.y && 
                    existingOre.orePos.z == blockPos.z) {
                    alreadyExists = true;
                    break;
                }
            }
            
            if (!alreadyExists) {
                renderOresESP.push_back({blockView, blockPos, {(float)blockPos.x, (float)blockPos.y, (float)blockPos.z}, GetOreColor(blockView)});
            }
        } 
    }
	}
    return old_Block_getRenderLayer(thiz, a2, blockPos);
}

void (*old_BaseActorRenderer_renderText)(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
void BaseActorRenderer_renderText(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6) {
	if (panic) return old_BaseActorRenderer_renderText(a1, a2, a3, a4, a5, a6);
	if (esp && espNametag && inHudScreen) {
		std::string currentNameTag = *static_cast<std::string*>(a3);
	    for (PlayerStruct player : nearPlayerList) {
			if (player.isBot) continue;
			if (currentNameTag.find(player.nickname) != std::string::npos || currentNameTag == player.nameTag) {
				return;
			}
	    }
	}
    return old_BaseActorRenderer_renderText(a1, a2, a3, a4, a5, a6);
}



#include "hotkeys.h"



pthread_t cheatThread;
bool isHackLoaded = false;
void *hack_thread(void *) {
    if (!isHackLoaded) {
    ProcMap mineMap;
    do {
        mineMap = KittyMemory::getLibraryMap(MineLib);
		handle = dlopen(OBFUSCATE("libminecraftpe.so"), RTLD_LAZY);
    } while (!mineMap.isValid());
	
	RenderHook();
	
	#if defined(__aarch64__)

    DobbyHook(reinterpret_cast<void*>((const void*(*)(...))dlsym(handle, OBFUSCATE("Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler"))), reinterpret_cast<void*>(new_Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler), reinterpret_cast<void**>(&old_Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler));
	hexPatches.NativeKeyHandler = MemoryPatch::createWithHex(MineLib, Offsets64::NativeKeyHandler, "C0 03 5F D6");
	hexPatches.NativeKeyHandler.Modify();
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::NoNametags), (void *) BaseActorRenderer_renderText, (void **) &old_BaseActorRenderer_renderText);
	
	hexPatches.NoCaveVignette = MemoryPatch::createWithHex(MineLib, Offsets64::VignetteRenderer, "C0 03 5F D6");
	
	hexPatches.AntiKnockBack = MemoryPatch::createWithHex(MineLib, Offsets64::LerpMotion, "C0 03 5F D6");
	
	hexPatches.FullBright = MemoryPatch::createWithHex(MineLib, Offsets64::FullBright, "88 56 A8 52 00 01 27 1E C0 03 5F D6");//return 999.0f
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::Block_getRenderLayer), (void *) Block_getRenderLayer, (void **) &old_Block_getRenderLayer);
	
    A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::ClientInstanceOnTick), (void *) ClientInstance_onTick, (void **) &old_ClientInstance_onTick);
	
    A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::Subtitle), (void *) TitleMessage_setSubtitle, (void **) &old_TitleMessage_setSubtitle);
	
    A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::ShowPaperdoll), (void *) HudPlayerRenderer_update, (void **) &old_HudPlayerRenderer_update);
	
    A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::SetupFog), (void *) LevelRendererPlayer_setupFog, (void **) &old_LevelRendererPlayer_setupFog);
	
    A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::GetMaxPlayers), (void *) AppPlatform_getMaxPlayers, (void **) &old_AppPlatform_getMaxPlayers);
	
    A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::UnlockMarket), (void *) Entitlement_UnlockMarket, (void **) &old_Entitlement_UnlockMarket);
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::InMainMenu), (void *) InMainMenu, (void **) &old_InMainMenu);
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::InLanGame1), (void *) InLanGame1, (void **) &old_InLanGame1);
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::InLanGame2), (void *) InLanGame2, (void **) &old_InLanGame2);
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::Fov), (void *) PlayerFov, (void **) &old_PlayerFov);

	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::FogState), (void *) LevelRendererCamera_FogState, (void **) &old_LevelRendererCamera_FogState);

	hexPatches.Font0 = MemoryPatch::createWithHex(MineLib, Offsets64::Font, "00 00 00 3F");//0
	hexPatches.Font1 = MemoryPatch::createWithHex(MineLib, Offsets64::Font, "9A 99 19 3F");//1
	hexPatches.Font2 = MemoryPatch::createWithHex(MineLib, Offsets64::Font, "33 33 33 3F");//2
	hexPatches.Font3 = MemoryPatch::createWithHex(MineLib, Offsets64::Font, "CD CC 4C 3F");//3
	hexPatches.Font4 = MemoryPatch::createWithHex(MineLib, Offsets64::Font, "66 66 66 3F");//4
	hexPatches.Font5 = MemoryPatch::createWithHex(MineLib, Offsets64::Font, "00 00 80 3F");//5
	hexPatches.Font6 = MemoryPatch::createWithHex(MineLib, Offsets64::Font, "CD CC 8C 3F");//6
	hexPatches.Font7 = MemoryPatch::createWithHex(MineLib, Offsets64::Font, "9A 99 99 3F");//7
	hexPatches.Font8 = MemoryPatch::createWithHex(MineLib, Offsets64::Font, "66 66 A6 3F");//8
	hexPatches.Font9 = MemoryPatch::createWithHex(MineLib, Offsets64::Font, "33 33 B3 3F");//9
	hexPatches.Font10 = MemoryPatch::createWithHex(MineLib, Offsets64::Font, "00 00 C0 3F");//10
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::FastDrop), (void *) DropItemTime, (void **) &old_DropItemTime);
	
	hexPatches.NoHurtCam = MemoryPatch::createWithHex(MineLib, Offsets64::NoHurtCam, "C0 03 5F D6");
	
	hexPatches.NoCamDistortion = MemoryPatch::createWithHex(MineLib, Offsets64::NoCamDistortion, "C0 03 5F D6");
	
	hexPatches.NoBoatRotation = MemoryPatch::createWithHex(MineLib, Offsets64::NoBoatRotation, "C0 03 5F D6");
	
	hexPatches.NoCamSleep = MemoryPatch::createWithHex(MineLib, Offsets64::NoCamSleep, "C0 03 5F D6");
	
	hexPatches.PlaceCamera = MemoryPatch::createWithHex(MineLib, Offsets64::PlaceCamera, "C0 03 5F D6");
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::SpeedHack), (void *) SpeedHack, (void **) &old_SpeedHack);
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::NormalTick), (void*) NormalTick, (void**) &old_NormalTick);
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::Intersects), (void*) Intersects, (void**) &old_Intersects);
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::PlayerAuthInput), (void *) PlayerAuthInputPacket, (void **) &old_PlayerAuthInputPacket);
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::WaterTrigger1), (void *) WasInWater, (void **) &old_WasInWater);
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::WaterTrigger2), (void *) ActorHeadInWater, (void **) &old_ActorHeadInWater);
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::WaterTrigger3), (void *) WaterSplashEffect, (void **) &old_WaterSplashEffect);
	
	hexPatches.SlowDownTriggers = MemoryPatch::createWithHex(MineLib, Offsets64::SlowDownTriggers, "C0 03 5F D6");
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::JumpHack), (void *) JumpHack, (void **) &old_JumpHack);
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::WaterSpeed), (void *) WaterSpeed, (void **) &old_WaterSpeed);
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::LavaSpeed), (void *) LavaSpeed, (void **) &old_LavaSpeed);
	
	hexPatches.NoSlowDown = MemoryPatch::createWithHex(MineLib, Offsets64::NoSlowDown, "C0 03 5F D6");
	
	hexPatches.WaterDrown = MemoryPatch::createWithHex(MineLib, Offsets64::WaterDrown, "C0 03 5F D6");
	
	hexPatches.LavaDrown = MemoryPatch::createWithHex(MineLib, Offsets64::LavaDrown, "C0 03 5F D6");
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::Gravity), (void *) Gravity, (void **) &old_Gravity);
	
	hexPatches.Noclip = MemoryPatch::createWithHex(MineLib, Offsets64::Noclip, "C0 03 5F D6");
	
	hexPatches.AutoClickMine = MemoryPatch::createWithHex(MineLib, Offsets64::AutoClickMine, "C0 03 5F D6");
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::FastBridge), (void *) GameMode_FastBridge, (void **) &old_GameMode_FastBridge);
	
	A64HookFunction((void *)getAbsoluteAddress(MineLib, Offsets64::BlockReach), (void *) GameMode_BlockReach, (void **) &old_GameMode_BlockReach);
	
	hexPatches.XrayCameraThird = MemoryPatch::createWithHex(MineLib, Offsets64::XrayCameraThird, "C0 03 5F D6");
	
	hexPatches.NoEmoteUseCooldown = MemoryPatch::createWithHex(MineLib, Offsets64::IsEmoting, "00 00 80 D2 C0 03 5F D6");
	
	hexPatches.NoBlur1 = MemoryPatch::createWithHex(MineLib, Offsets64::NoBlur1, "C0 03 5F D6");
	hexPatches.NoBlur2 = MemoryPatch::createWithHex(MineLib, Offsets64::NoBlur2, "C0 03 5F D6");

#elif defined(__ARM_ARCH_7A__)

    DobbyHook(reinterpret_cast<void*>((const void*(*)(...))dlsym(handle, OBFUSCATE("Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler"))), reinterpret_cast<void*>(new_Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler), reinterpret_cast<void**>(&old_Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler));
	hexPatches.NativeKeyHandler = MemoryPatch::createWithHex(MineLib, Offsets::NativeKeyHandler, "70 47");
	hexPatches.NativeKeyHandler.Modify();
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::NoNametags), (void *) BaseActorRenderer_renderText, (void **) &old_BaseActorRenderer_renderText);
	
	hexPatches.NoCaveVignette = MemoryPatch::createWithHex(MineLib, Offsets::VignetteRenderer, "70 47");
	
	hexPatches.AntiKnockBack = MemoryPatch::createWithHex(MineLib, Offsets::LerpMotion, "70 47");
	
	hexPatches.FullBright = MemoryPatch::createWithHex(MineLib, Offsets::FullBright, "00 20 C4 F2 B4 20 70 47");//return 90.0f
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::Block_getRenderLayer), (void *) Block_getRenderLayer, (void **) &old_Block_getRenderLayer);
	
    MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::ClientInstanceOnTick), (void *) ClientInstance_onTick, (void **) &old_ClientInstance_onTick);
	
    MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::Subtitle), (void *) TitleMessage_setSubtitle, (void **) &old_TitleMessage_setSubtitle);
	
    MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::ShowPaperdoll), (void *) HudPlayerRenderer_update, (void **) &old_HudPlayerRenderer_update);
	
    MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::SetupFog), (void *) LevelRendererPlayer_setupFog, (void **) &old_LevelRendererPlayer_setupFog);
	
    MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::GetMaxPlayers), (void *) AppPlatform_getMaxPlayers, (void **) &old_AppPlatform_getMaxPlayers);
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::UnlockMarket), (void *) Entitlement_UnlockMarket, (void **) &old_Entitlement_UnlockMarket);
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::InMainMenu), (void *) InMainMenu, (void **) &old_InMainMenu);
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::InLanGame1), (void *) InLanGame1, (void **) &old_InLanGame1);
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::InLanGame2), (void *) InLanGame2, (void **) &old_InLanGame2);
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::Fov), (void *) PlayerFov, (void **) &old_PlayerFov);

	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::FogState), (void *) LevelRendererCamera_FogState, (void **) &old_LevelRendererCamera_FogState);

	hexPatches.Font0 = MemoryPatch::createWithHex(MineLib, Offsets::Font, "00 00 00 3F");//0
	hexPatches.Font1 = MemoryPatch::createWithHex(MineLib, Offsets::Font, "9A 99 19 3F");//1
	hexPatches.Font2 = MemoryPatch::createWithHex(MineLib, Offsets::Font, "33 33 33 3F");//2
	hexPatches.Font3 = MemoryPatch::createWithHex(MineLib, Offsets::Font, "CD CC 4C 3F");//3
	hexPatches.Font4 = MemoryPatch::createWithHex(MineLib, Offsets::Font, "66 66 66 3F");//4
	hexPatches.Font5 = MemoryPatch::createWithHex(MineLib, Offsets::Font, "00 00 80 3F");//5
	hexPatches.Font6 = MemoryPatch::createWithHex(MineLib, Offsets::Font, "CD CC 8C 3F");//6
	hexPatches.Font7 = MemoryPatch::createWithHex(MineLib, Offsets::Font, "9A 99 99 3F");//7
	hexPatches.Font8 = MemoryPatch::createWithHex(MineLib, Offsets::Font, "66 66 A6 3F");//8
	hexPatches.Font9 = MemoryPatch::createWithHex(MineLib, Offsets::Font, "33 33 B3 3F");//9
	hexPatches.Font10 = MemoryPatch::createWithHex(MineLib, Offsets::Font, "00 00 C0 3F");//10
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::FastDrop), (void *) DropItemTime, (void **) &old_DropItemTime);
	
	hexPatches.NoHurtCam = MemoryPatch::createWithHex(MineLib, Offsets::NoHurtCam, "70 47");
	
	hexPatches.NoCamDistortion = MemoryPatch::createWithHex(MineLib, Offsets::NoCamDistortion, "70 47");
	
	hexPatches.NoBoatRotation = MemoryPatch::createWithHex(MineLib, Offsets::NoBoatRotation, "70 47");
	
	hexPatches.NoCamSleep = MemoryPatch::createWithHex(MineLib, Offsets::NoCamSleep, "70 47");
	
	hexPatches.PlaceCamera = MemoryPatch::createWithHex(MineLib, Offsets::PlaceCamera, "70 47");
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::SpeedHack), (void *) SpeedHack, (void **) &old_SpeedHack);
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::NormalTick), (void *) NormalTick, (void **) &old_NormalTick);
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::Intersects), (void*) Intersects, (void**) &old_Intersects);
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::PlayerAuthInput), (void*) PlayerAuthInputPacket, (void**) &old_PlayerAuthInputPacket);
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::WaterTrigger1), (void *) WasInWater, (void **) &old_WasInWater);
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::WaterTrigger2), (void *) ActorHeadInWater, (void **) &old_ActorHeadInWater);
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::WaterTrigger3), (void *) WaterSplashEffect, (void **) &old_WaterSplashEffect);
	
	hexPatches.SlowDownTriggers = MemoryPatch::createWithHex(MineLib, Offsets::SlowDownTriggers, "70 47");
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::JumpHack), (void *) JumpHack, (void **) &old_JumpHack);
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::WaterSpeed), (void *) WaterSpeed, (void **) &old_WaterSpeed);
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::LavaSpeed), (void *) LavaSpeed, (void **) &old_LavaSpeed);
	
	hexPatches.NoSlowDown = MemoryPatch::createWithHex(MineLib, Offsets::NoSlowDown, "70 47");
	
	hexPatches.WaterDrown = MemoryPatch::createWithHex(MineLib, Offsets::WaterDrown, "70 47");
	
	hexPatches.LavaDrown = MemoryPatch::createWithHex(MineLib, Offsets::LavaDrown, "70 47");
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::Gravity), (void *) Gravity, (void **) &old_Gravity);
	
	hexPatches.Noclip = MemoryPatch::createWithHex(MineLib, Offsets::Noclip, "70 47");
	
	hexPatches.AutoClickMine = MemoryPatch::createWithHex(MineLib, Offsets::AutoClickMine, "70 47");
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::FastBridge), (void *) GameMode_FastBridge, (void **) &old_GameMode_FastBridge);
	
	MSHookThumb((void *)getAbsoluteAddress(MineLib, Offsets::BlockReach), (void *) GameMode_BlockReach, (void **) &old_GameMode_BlockReach);
	
	hexPatches.XrayCameraThird = MemoryPatch::createWithHex(MineLib, Offsets::XrayCameraThird, "70 47");
	
	hexPatches.NoEmoteUseCooldown = MemoryPatch::createWithHex(MineLib, Offsets::IsEmoting, "00 20 70 47");
	
	hexPatches.NoBlur1 = MemoryPatch::createWithHex(MineLib, Offsets::NoBlur1, "70 47");
	hexPatches.NoBlur2 = MemoryPatch::createWithHex(MineLib, Offsets::NoBlur2, "70 47");
	
#else

    MSHookX86_64(reinterpret_cast<void*>((const void*(*)(...))dlsym(handle, OBFUSCATE("Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler"))), reinterpret_cast<void*>(new_Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler), reinterpret_cast<void**>(&old_Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler));
	hexPatches.NativeKeyHandler = MemoryPatch::createWithHex(MineLib, Offsets86_64::NativeKeyHandler, "C3");
	hexPatches.NativeKeyHandler.Modify();
	
	hexPatches.AntiKnockBack = MemoryPatch::createWithHex(MineLib, Offsets86_64::LerpMotion, "C3");
	
	hexPatches.FullBright = MemoryPatch::createWithHex(MineLib, Offsets86_64::FullBright, "B8 00 D0 77 44 66 0F 6E C0 C3");//return 999.0f
	hexPatches.SmoothLight = MemoryPatch::createWithHex(MineLib, Offsets86_64::SmoothLight, "31 C0 C3");//return 0
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::Block_getRenderLayer), (void *) Block_getRenderLayer, (void **) &old_Block_getRenderLayer);
	
    MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::ClientInstanceOnTick), (void *) ClientInstance_onTick, (void **) &old_ClientInstance_onTick);

    MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::Subtitle), (void *) TitleMessage_setSubtitle, (void **) &old_TitleMessage_setSubtitle);
	
    MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::ShowPaperdoll), (void *) HudPlayerRenderer_update, (void **) &old_HudPlayerRenderer_update);
	
    MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::SetupFog), (void *) LevelRendererPlayer_setupFog, (void **) &old_LevelRendererPlayer_setupFog);
	
    MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::GetMaxPlayers), (void *) AppPlatform_getMaxPlayers, (void **) &old_AppPlatform_getMaxPlayers);
	
    MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::UnlockMarket), (void *) Entitlement_UnlockMarket, (void **) &old_Entitlement_UnlockMarket);
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::InMainMenu), (void *) InMainMenu, (void **) &old_InMainMenu);
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::InGame), (void *) InGame, (void **) &old_InGame);
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::InLanGame1), (void *) InLanGame1, (void **) &old_InLanGame1);
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::InLanGame2), (void *) InLanGame2, (void **) &old_InLanGame2);
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::Fov), (void *) PlayerFov, (void **) &old_PlayerFov);

	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::FogState), (void *) LevelRendererCamera_FogState, (void **) &old_LevelRendererCamera_FogState);

	hexPatches.Font0 = MemoryPatch::createWithHex(MineLib, Offsets86_64::Font, "00 00 00 3F");//0
	hexPatches.Font1 = MemoryPatch::createWithHex(MineLib, Offsets86_64::Font, "9A 99 19 3F");//1
	hexPatches.Font2 = MemoryPatch::createWithHex(MineLib, Offsets86_64::Font, "33 33 33 3F");//2
	hexPatches.Font3 = MemoryPatch::createWithHex(MineLib, Offsets86_64::Font, "CD CC 4C 3F");//3
	hexPatches.Font4 = MemoryPatch::createWithHex(MineLib, Offsets86_64::Font, "66 66 66 3F");//4
	hexPatches.Font5 = MemoryPatch::createWithHex(MineLib, Offsets86_64::Font, "00 00 80 3F");//5
	hexPatches.Font6 = MemoryPatch::createWithHex(MineLib, Offsets86_64::Font, "CD CC 8C 3F");//6
	hexPatches.Font7 = MemoryPatch::createWithHex(MineLib, Offsets86_64::Font, "9A 99 99 3F");//7
	hexPatches.Font8 = MemoryPatch::createWithHex(MineLib, Offsets86_64::Font, "66 66 A6 3F");//8
	hexPatches.Font9 = MemoryPatch::createWithHex(MineLib, Offsets86_64::Font, "33 33 B3 3F");//9
	hexPatches.Font10 = MemoryPatch::createWithHex(MineLib, Offsets86_64::Font, "00 00 C0 3F");//10
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::FastDrop), (void *) DropItemTime, (void **) &old_DropItemTime);
	
	hexPatches.NoHurtCam = MemoryPatch::createWithHex(MineLib, Offsets86_64::NoHurtCam, "C3");
	
	hexPatches.NoCamDistortion = MemoryPatch::createWithHex(MineLib, Offsets86_64::NoCamDistortion, "C3");
	
	hexPatches.NoBoatRotation = MemoryPatch::createWithHex(MineLib, Offsets86_64::NoBoatRotation, "C3");
	
	hexPatches.NoCamSleep = MemoryPatch::createWithHex(MineLib, Offsets86_64::NoCamSleep, "C3");
	
	hexPatches.PlaceCamera = MemoryPatch::createWithHex(MineLib, Offsets86_64::PlaceCamera, "C3");
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::SpeedHack), (void *) SpeedHack, (void **) &old_SpeedHack);
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::NormalTick), (void*) NormalTick, (void**) &old_NormalTick);
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::Intersects), (void*) Intersects, (void**) &old_Intersects);
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::PlayerAuthInput), (void *) PlayerAuthInputPacket, (void **) &old_PlayerAuthInputPacket);
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::WaterTrigger1), (void *) WasInWater, (void **) &old_WasInWater);
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::WaterTrigger2), (void *) ActorHeadInWater, (void **) &old_ActorHeadInWater);
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::WaterTrigger3), (void *) WaterSplashEffect, (void **) &old_WaterSplashEffect);
	
	hexPatches.SlowDownTriggers = MemoryPatch::createWithHex(MineLib, Offsets86_64::SlowDownTriggers, "C3");
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::JumpHack), (void *) JumpHack, (void **) &old_JumpHack);
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::ElytraSpeed), (void *) ElytraSpeed, (void **) &old_ElytraSpeed);
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::WaterSpeed), (void *) WaterSpeed, (void **) &old_WaterSpeed);
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::LavaSpeed), (void *) LavaSpeed, (void **) &old_LavaSpeed);
	
	hexPatches.NoSlowDown = MemoryPatch::createWithHex(MineLib, Offsets86_64::NoSlowDown, "C3");
	
	hexPatches.WaterDrown = MemoryPatch::createWithHex(MineLib, Offsets86_64::WaterDrown, "C3");
	
	hexPatches.LavaDrown = MemoryPatch::createWithHex(MineLib, Offsets86_64::LavaDrown, "C3");
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::BoatSpeed), (void *) BoatSpeed, (void **) &old_BoatSpeed);
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::Gravity), (void *) Gravity, (void **) &old_Gravity);
	
	hexPatches.Noclip = MemoryPatch::createWithHex(MineLib, Offsets86_64::Noclip, "C3");
	
	hexPatches.AutoClickMine = MemoryPatch::createWithHex(MineLib, Offsets86_64::AutoClickMine, "C3");
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::FastBridge), (void *) GameMode_FastBridge, (void **) &old_GameMode_FastBridge);
	
	MSHookX86_64((void *)getAbsoluteAddress(MineLib, Offsets86_64::BlockReach), (void *) GameMode_BlockReach, (void **) &old_GameMode_BlockReach);
	
	hexPatches.XrayCameraThird = MemoryPatch::createWithHex(MineLib, Offsets86_64::XrayCameraThird, "C3");
	
	hexPatches.NoEmoteUseCooldown = MemoryPatch::createWithHex(MineLib, Offsets86_64::IsEmoting, "48 C7 C0 00 00 00 00 C3");
	
	hexPatches.NoBlur1 = MemoryPatch::createWithHex(MineLib, Offsets86_64::NoBlur1, "C3");
	hexPatches.NoBlur2 = MemoryPatch::createWithHex(MineLib, Offsets86_64::NoBlur2, "C3");
	
#endif
	
    isHackLoaded = true;
    return NULL;
	} else {
		pthread_kill(cheatThread, SIGUSR1);
	}
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);

    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_create(&cheatThread, NULL, hack_thread, NULL);

    return JNI_VERSION_1_6;
}



JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *vm, void *reserved) {}

