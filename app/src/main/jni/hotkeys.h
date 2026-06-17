void HotkeyNotification (int currentHotkey) {
	switch (currentHotkey) {
		case 2: 
		if (!isLANGame) {
		    if (alwaysSprinting) {
				onFunctionSound = true;
		        AddNotification(oxorany("Always Sprinting ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	        } else {
				offFunctionSound = true;
		        AddNotification(oxorany("Always Sprinting OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	        }
		} else {
			errorFunctionSound = true;
			AddNotification(oxorany("Bedrock Anti Cheat Detected."), 6.0f, ImVec4(1.00f, 0.00f, 0.00f, 0.75f));
		}
		break;
		
		case 3: 
		if (!isLANGame) {
		    if (noSlowDown) {
				onFunctionSound = true;
		        AddNotification(oxorany("No SlowDown ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	        } else {
				offFunctionSound = true;
		        AddNotification(oxorany("No SlowDown OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	        }
		} else {
			errorFunctionSound = true;
			AddNotification(oxorany("Bedrock Anti Cheat Detected."), 6.0f, ImVec4(1.00f, 0.00f, 0.00f, 0.75f));
		}
		break;
		
		case 4:
		if (!isLANGame) {
		    if (fastFall) {
				onFunctionSound = true;
		        AddNotification(oxorany("Fast Fall ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	        } else {
				offFunctionSound = true;
		        AddNotification(oxorany("Fast Fall OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	        }
		} else {
			errorFunctionSound = true;
			AddNotification(oxorany("Bedrock Anti Cheat Detected."), 6.0f, ImVec4(1.00f, 0.00f, 0.00f, 0.75f));
		}
		break;
		
		case 5:
		if (!isLANGame) {
		    if (offDrown) {
				onFunctionSound = true;
		        AddNotification(oxorany("OFF Drowning ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	        } else {
				offFunctionSound = true;
		        AddNotification(oxorany("OFF Drowning OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	        }
		} else {
			errorFunctionSound = true;
			AddNotification(oxorany("Bedrock Anti Cheat Detected."), 6.0f, ImVec4(1.00f, 0.00f, 0.00f, 0.75f));
		}
		break;
		
		case 6:
		if (!isLANGame) {
		    if (step) {
				onFunctionSound = true;
		        AddNotification(oxorany("Step ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	        } else {
				offFunctionSound = true;
		        AddNotification(oxorany("Step OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	        }
		} else {
			errorFunctionSound = true;
			AddNotification(oxorany("Bedrock Anti Cheat Detected."), 6.0f, ImVec4(1.00f, 0.00f, 0.00f, 0.75f));
		}
		break;
		
		case 7:
		if (!isLANGame) {
		    if (ladderFly) {
				onFunctionSound = true;
		        AddNotification(oxorany("Ladder Fly ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	        } else {
				offFunctionSound = true;
		        AddNotification(oxorany("Ladder Fly OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	        }
		} else {
			errorFunctionSound = true;
			AddNotification(oxorany("Bedrock Anti Cheat Detected."), 6.0f, ImVec4(1.00f, 0.00f, 0.00f, 0.75f));
		}
		break;
		
		case 8:
		if (!isLANGame) {
		    if (noclip) {
				onFunctionSound = true;
		        AddNotification(oxorany("Noclip ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	        } else {
				offFunctionSound = true;
		        AddNotification(oxorany("Noclip OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	        }
		} else {
			errorFunctionSound = true;
			AddNotification(oxorany("Bedrock Anti Cheat Detected."), 6.0f, ImVec4(1.00f, 0.00f, 0.00f, 0.75f));
		}
		break;
		
		case 9:
		if (!isLANGame) {
		    if (offWaterTrigger) {
				onFunctionSound = true;
		        AddNotification(oxorany("No Water ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	        } else {
				offFunctionSound = true;
		        AddNotification(oxorany("No Water OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	        }
		} else {
			errorFunctionSound = true;
			AddNotification(oxorany("Bedrock Anti Cheat Detected."), 6.0f, ImVec4(1.00f, 0.00f, 0.00f, 0.75f));
		}
		break;
		
		case 10:
		if (!isLANGame) {
		    if (offSlowdownTrigger) {
				onFunctionSound = true;
		        AddNotification(oxorany("No Web ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	        } else {
				offFunctionSound = true;
		        AddNotification(oxorany("No Web OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	        }
		} else {
			errorFunctionSound = true;
			AddNotification(oxorany("Bedrock Anti Cheat Detected."), 6.0f, ImVec4(1.00f, 0.00f, 0.00f, 0.75f));
		}
		break;
		
		case 11: 
		if (!isLANGame) {
		    if (forceCreativeFly) {
				onFunctionSound = true;
		        AddNotification(oxorany("Force Creative Fly ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	        } else {
				offFunctionSound = true;
		        AddNotification(oxorany("Force Creative Fly OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	        }
		} else {
			errorFunctionSound = true;
			AddNotification(oxorany("Bedrock Anti Cheat Detected."), 6.0f, ImVec4(1.00f, 0.00f, 0.00f, 0.75f));
		}
		break;
		
		case 12:
		if (killAura) {
			onFunctionSound = true;
		    AddNotification(oxorany("KillAura ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("KillAura OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 13:
		if (hitBox) {
			onFunctionSound = true;
		    AddNotification(oxorany("HitBox ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("HitBox OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 14:
		if (swing) {
			onFunctionSound = true;
		    AddNotification(oxorany("Swing ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Swing OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 15:
		if (rotations) {
			onFunctionSound = true;
		    AddNotification(oxorany("Rotations ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Rotations OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 16:
		if (targetLock) {
			onFunctionSound = true;
		    AddNotification(oxorany("Target Lock ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Target Lock OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 17:
		if (mobAura) {
			onFunctionSound = true;
		    AddNotification(oxorany("MobAura ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("MobAura OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 18:
		if (killItems) {
			onFunctionSound = true;
		    AddNotification(oxorany("Kill Near Items ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Kill Near Items OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 19:
		if (antiFireball) {
			onFunctionSound = true;
		    AddNotification(oxorany("Anti Fireball ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Anti Fireball OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 20:
		if (fastBridge) {
			onFunctionSound = true;
		    AddNotification(oxorany("Auto Click Build ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Auto Click Build OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 21:
		if (enableFov) {
			onFunctionSound = true;
		    AddNotification(oxorany("Enable Fov ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Enable Fov OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 22:
		if (placeCam) {
			onFunctionSound = true;
		    AddNotification(oxorany("Place Camera ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Place Camera OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 23:
		if (xrayCam) {
			onFunctionSound = true;
		    AddNotification(oxorany("Xray Camera ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Xray Camera OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 24:
		if (xrayCaves) {
			onFunctionSound = true;
		    AddNotification(oxorany("Xray Caves ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Xray Caves OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 25:
		if (look360) {
			onFunctionSound = true;
		    AddNotification(oxorany("Freelook ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Freelook OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 26:
		if (damageFly) {
			onFunctionSound = true;
		    AddNotification(oxorany("Damage Fly ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Damage Fly OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 27:
		if (!isLANGame) {
		    if (strafe) {
				onFunctionSound = true;
		        AddNotification(oxorany("Strafe ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	        } else {
				offFunctionSound = true;
		        AddNotification(oxorany("Strafe OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	        }
		} else {
			errorFunctionSound = true;
			AddNotification(oxorany("Bedrock Anti Cheat Detected."), 6.0f, ImVec4(1.00f, 0.00f, 0.00f, 0.75f));
		}
		break;
		
		case 28:
		if (autoClicker) {
			onFunctionSound = true;
		    AddNotification(oxorany("Auto Clicker ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Auto Clicker OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
		
		case 29:
		if (xrayDefault) {
			onFunctionSound = true;
		    AddNotification(oxorany("Xray ON"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.75f));
	    } else {
			offFunctionSound = true;
		    AddNotification(oxorany("Xray OFF"), 6.0f, ImVec4(0.70f, 0.00f, 1.00f, 0.25f));
	    }
		break;
	}
}

bool DoKey (int keyAction, bool keyTick, int bindedHotkey) {
	if (keyAction == AKEY_EVENT_ACTION_DOWN) {
		if (keyTick) {
			if (bindedHotkey == 1) {
				panic = !panic;
				rebuildChunkGeometry = true;
			}
			if (!isLANGame) {
				if (bindedHotkey == 2) alwaysSprinting = !alwaysSprinting;
			    if (bindedHotkey == 3) noSlowDown = !noSlowDown;
			    if (bindedHotkey == 4) fastFall = !fastFall;
			    if (bindedHotkey == 5) offDrown = !offDrown;
				if (bindedHotkey == 6) step = !step;
				if (bindedHotkey == 7) ladderFly = !ladderFly;
				if (bindedHotkey == 8) noclip = !noclip;
				if (bindedHotkey == 9) offWaterTrigger = !offWaterTrigger;
				if (bindedHotkey == 10) offSlowdownTrigger = !offSlowdownTrigger;
				if (bindedHotkey == 11) forceCreativeFly = !forceCreativeFly;
			}
			if (bindedHotkey == 12) killAura = !killAura;
			if (bindedHotkey == 13) hitBox = !hitBox;
			if (bindedHotkey == 14) swing = !swing;
			if (bindedHotkey == 15) rotations = !rotations;
			if (bindedHotkey == 16) targetLock = !targetLock;
			if (bindedHotkey == 17) mobAura = !mobAura;
			if (bindedHotkey == 18) killItems = !killItems;
			if (bindedHotkey == 19) antiFireball = !antiFireball;
			if (bindedHotkey == 20) fastBridge = !fastBridge;
			if (bindedHotkey == 21) enableFov = !enableFov;
			if (bindedHotkey == 22) placeCam = !placeCam;
			if (bindedHotkey == 23) xrayCam = !xrayCam;
			if (bindedHotkey == 24) xrayCaves = !xrayCaves;
			if (bindedHotkey == 25) look360 = !look360;
			if (bindedHotkey == 26) damageFly = !damageFly;
			if (bindedHotkey == 27) strafe = !strafe;
			if (bindedHotkey == 28) autoClicker = !autoClicker;
			if (bindedHotkey == 29) {
				xrayDefault = !xrayDefault;
				rebuildChunkGeometry = true;
			}
			if (!panic) HotkeyNotification(bindedHotkey);
			keyTick = false;
			return true;
		}
	}
	if (keyAction == AKEY_EVENT_ACTION_UP) {
		keyTick = true;
		return true;
	}
	return true;
}

bool canVolumeUpTick = true;
bool canVolumeDownTick = true;
bool canBackTick = true;

bool canKeycodeQTick = true;
bool canKeycodeWTick = true;
bool canKeycodeETick = true;
bool canKeycodeRTick = true;
bool canKeycodeTTick = true;
bool canKeycodeYTick = true;
bool canKeycodeUTick = true;
bool canKeycodeITick = true;
bool canKeycodeOTick = true;
bool canKeycodePTick = true;
bool canKeycodeATick = true;
bool canKeycodeSTick = true;
bool canKeycodeDTick = true;
bool canKeycodeFTick = true;
bool canKeycodeGTick = true;
bool canKeycodeHTick = true;
bool canKeycodeJTick = true;
bool canKeycodeKTick = true;
bool canKeycodeLTick = true;
bool canKeycodeZTick = true;
bool canKeycodeXTick = true;
bool canKeycodeCTick = true;
bool canKeycodeVTick = true;
bool canKeycodeBTick = true;
bool canKeycodeNTick = true;
bool canKeycodeMTick = true;
bool canKeycodeNumpad0Tick = true;
bool canKeycodeNumpad1Tick = true;
bool canKeycodeNumpad2Tick = true;
bool canKeycodeNumpad3Tick = true;
bool canKeycodeNumpad4Tick = true;
bool canKeycodeNumpad5Tick = true;
bool canKeycodeNumpad6Tick = true;
bool canKeycodeNumpad7Tick = true;
bool canKeycodeNumpad8Tick = true;
bool canKeycodeNumpad9Tick = true;

bool (*old_Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler)(void *a1, void *a2, int keyCode, int keyAction);
bool new_Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler(void *a1, void *a2, int keyCode, int keyAction) {
	if (!inChatScreen) {
    if (hotkeyVolumeUp > 0) {
		if (keyCode == AKEYCODE_VOLUME_UP) {
			return DoKey(keyAction, canVolumeUpTick, hotkeyVolumeUp);
		}
	}
	
	if (hotkeyVolumeDown > 0) {
		if (keyCode == AKEYCODE_VOLUME_DOWN) {
	        return DoKey(keyAction, canVolumeDownTick, hotkeyVolumeDown);
		}
	}
	
	if (hotkeyBack > 0) {
		if (keyCode == AKEYCODE_BACK) {
			return DoKey(keyAction, canBackTick, hotkeyBack);
	    }
	}
	
	if (hotkey_Q > 0) {
            if (keyCode == AKEYCODE_Q) {
                return DoKey(keyAction, canKeycodeQTick, hotkey_Q);
            }
        }

        if (hotkey_W > 0) {
            if (keyCode == AKEYCODE_W) {
                return DoKey(keyAction, canKeycodeWTick, hotkey_W);
            }
        }

        if (hotkey_E > 0) {
            if (keyCode == AKEYCODE_E) {
                return DoKey(keyAction, canKeycodeETick, hotkey_E);
            }
        }

        if (hotkey_R > 0) {
            if (keyCode == AKEYCODE_R) {
                return DoKey(keyAction, canKeycodeRTick, hotkey_R);
            }
        }

        if (hotkey_T > 0) {
            if (keyCode == AKEYCODE_T) {
                return DoKey(keyAction, canKeycodeTTick, hotkey_T);
            }
        }

        if (hotkey_Y > 0) {
            if (keyCode == AKEYCODE_Y) {
                return DoKey(keyAction, canKeycodeYTick, hotkey_Y);
            }
        }

        if (hotkey_U > 0) {
            if (keyCode == AKEYCODE_U) {
                return DoKey(keyAction, canKeycodeUTick, hotkey_U);
            }
        }

        if (hotkey_I > 0) {
            if (keyCode == AKEYCODE_I) {
                return DoKey(keyAction, canKeycodeITick, hotkey_I);
            }
        }

        if (hotkey_O > 0) {
            if (keyCode == AKEYCODE_O) {
                return DoKey(keyAction, canKeycodeOTick, hotkey_O);
            }
        }

        if (hotkey_P > 0) {
            if (keyCode == AKEYCODE_P) {
                return DoKey(keyAction, canKeycodePTick, hotkey_P);
            }
        }

        if (hotkey_A > 0) {
            if (keyCode == AKEYCODE_A) {
                return DoKey(keyAction, canKeycodeATick, hotkey_A);
            }
        }

        if (hotkey_S > 0) {
            if (keyCode == AKEYCODE_S) {
                return DoKey(keyAction, canKeycodeSTick, hotkey_S);
            }
        }

        if (hotkey_D > 0) {
            if (keyCode == AKEYCODE_D) {
                return DoKey(keyAction, canKeycodeDTick, hotkey_D);
            }
        }

        if (hotkey_F > 0) {
            if (keyCode == AKEYCODE_F) {
                return DoKey(keyAction, canKeycodeFTick, hotkey_F);
            }
        }

        if (hotkey_G > 0) {
            if (keyCode == AKEYCODE_G) {
                return DoKey(keyAction, canKeycodeGTick, hotkey_G);
            }
        }

        if (hotkey_H > 0) {
            if (keyCode == AKEYCODE_H) {
                return DoKey(keyAction, canKeycodeHTick, hotkey_H);
            }
        }

        if (hotkey_J > 0) {
            if (keyCode == AKEYCODE_J) {
                return DoKey(keyAction, canKeycodeJTick, hotkey_J);
            }
        }

        if (hotkey_K > 0) {
            if (keyCode == AKEYCODE_K) {
                return DoKey(keyAction, canKeycodeKTick, hotkey_K);
            }
        }

        if (hotkey_L > 0) {
            if (keyCode == AKEYCODE_L) {
                return DoKey(keyAction, canKeycodeLTick, hotkey_L);
            }
        }

        if (hotkey_Z > 0) {
            if (keyCode == AKEYCODE_Z) {
                return DoKey(keyAction, canKeycodeZTick, hotkey_Z);
            }
        }

        if (hotkey_X > 0) {
            if (keyCode == AKEYCODE_X) {
                return DoKey(keyAction, canKeycodeXTick, hotkey_X);
            }
        }

        if (hotkey_C > 0) {
            if (keyCode == AKEYCODE_C) {
                return DoKey(keyAction, canKeycodeCTick, hotkey_C);
            }
        }

        if (hotkey_V > 0) {
            if (keyCode == AKEYCODE_V) {
                return DoKey(keyAction, canKeycodeVTick, hotkey_V);
            }
        }

        if (hotkey_B > 0) {
            if (keyCode == AKEYCODE_B) {
                return DoKey(keyAction, canKeycodeBTick, hotkey_B);
            }
        }

        if (hotkey_N > 0) {
            if (keyCode == AKEYCODE_N) {
                return DoKey(keyAction, canKeycodeNTick, hotkey_N);
            }
        }

        if (hotkey_M > 0) {
            if (keyCode == AKEYCODE_M) {
                return DoKey(keyAction, canKeycodeMTick, hotkey_M);
            }
        }
		
        if (hotkey_numpad_0 > 0) {                                               
            if (keyCode == AKEYCODE_NUMPAD_0) {                                 
                return DoKey(keyAction, canKeycodeNumpad0Tick, hotkey_numpad_0); 
            }                                                                     
        }                                                                         
                                                                             
        if (hotkey_numpad_1 > 0) {                                               
            if (keyCode == AKEYCODE_NUMPAD_1) {                                 
                return DoKey(keyAction, canKeycodeNumpad1Tick, hotkey_numpad_1); 
            }                                                                     
        }                                                                         
                                                                             
        if (hotkey_numpad_2 > 0) {                                               
            if (keyCode == AKEYCODE_NUMPAD_2) {                                 
                return DoKey(keyAction, canKeycodeNumpad2Tick, hotkey_numpad_2); 
            }                                                                     
        }                                                                         
                                                                             
        if (hotkey_numpad_3 > 0) {                                               
            if (keyCode == AKEYCODE_NUMPAD_3) {                                 
                return DoKey(keyAction, canKeycodeNumpad3Tick, hotkey_numpad_3); 
            }                                                                     
        }                                                                         
                                                                             
        if (hotkey_numpad_4 > 0) {                                               
            if (keyCode == AKEYCODE_NUMPAD_4) {                                 
                return DoKey(keyAction, canKeycodeNumpad4Tick, hotkey_numpad_4); 
            }                                                                     
        }                                                                         
                                                                             
        if (hotkey_numpad_5 > 0) {                                               
            if (keyCode == AKEYCODE_NUMPAD_5) {                                 
                return DoKey(keyAction, canKeycodeNumpad5Tick, hotkey_numpad_5); 
            }                                                                     
        }                                                                         
                                                                             
        if (hotkey_numpad_6 > 0) {                                               
            if (keyCode == AKEYCODE_NUMPAD_6) {                                 
                return DoKey(keyAction, canKeycodeNumpad6Tick, hotkey_numpad_6); 
            }                                                                     
        }                                                                         
                                                                             
        if (hotkey_numpad_7 > 0) {
            if (keyCode == AKEYCODE_NUMPAD_7) {                                 
                return DoKey(keyAction, canKeycodeNumpad7Tick, hotkey_numpad_7); 
            }                                                                     
        }                                                                         
                                                                             
        if (hotkey_numpad_8 > 0) {                                               
            if (keyCode == AKEYCODE_NUMPAD_8) {                                 
                return DoKey(keyAction, canKeycodeNumpad8Tick, hotkey_numpad_8); 
            }                                                                     
        }                                                                         
                                                                             
        if (hotkey_numpad_9 > 0) {                                               
            if (keyCode == AKEYCODE_NUMPAD_9) {                                 
                return DoKey(keyAction, canKeycodeNumpad9Tick, hotkey_numpad_9); 
            }                                                                     
        }                                                                         
	}
	return old_Java_com_mojang_minecraftpe_MainActivity_nativeKeyHandler(a1, a2, keyCode, keyAction);
}
