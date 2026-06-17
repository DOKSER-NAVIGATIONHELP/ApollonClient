#if defined(__aarch64__)
namespace Offsets64 {
	enum Offsets64 {
		Font = 0x263C304,//Default 1 float
		NoHurtCam = 0x5103870,//CameraBobSystem::tick
		NoCamDistortion = 0xDF56A14,//CameraPortalDistortionSystem::_tick
		NoBoatRotation = 0x5114BB8,//CameraVehicleRotationLookSystem::tick
		NoCamSleep = 0xDF57550,//_tickSleepFade SUB
		PlaceCamera = 0xE1DC87C,//CameraBlendSystem::_tick
		WaterTrigger1 = 0x66578D8,//<WasInWaterFlagComponent,EntityId ActorHeadWasInWater
		WaterTrigger2 = 0x93B7B9C,//<ActorHeadInWaterFlagComponent,EntityId SUB
		WaterTrigger3 = 0x5E35F94,//<WaterSplashEffectRequestComponent,EntityId SUB
		SlowDownTriggers = 0x954C0E4,//BlockMovementSlowdownMultiplierSystemImpl::applySlowdownOnMove sub
		NoSlowDown = 0x945D230,//ItemUseSlowdownSystemImpl::doItemUseSlowdownSystem sub
		WaterSpeed = 0x9E52A70,//(doWaterMoveSystem sub
		LavaSpeed = 0x9407F30,//(doLavaMoveSystem sub
		Noclip = 0x93D2760,//MoveCollisionSystem::System sub
		XrayCameraThird = 0xE1DB2A4,//CameraAvoidanceSystem::tick
		LavaDrown = 0x9DB9528,//MobMovementGravity::tickLavaGravity loc
		WaterDrown = 0x9DB7558,//MobMovementGravity::tickPlayerWaterGravity loc
		Fov = 0x7BBDB00,//9CameraAPI returns float
		SpeedHack = 0x9498748,//doDefaultMoveSystems 2
		JumpHack = 0x9D8D7F0,//return 0.42
		Gravity = 0x9D88C20,//-0.08 float
		AutoClickMine = 0xCCC2258,//8GameMode STP
		FastBridge = 0xCCC3650,//"GameMode::useItemOn (client)"
		BlockReach = 0xCCC4B70,//returns 7 or 12 float
		PlayerAuthInput = 0xA772168,//"Player`s Head rotation"
		NativeKeyHandler = 0xCFA5130,//...nativeKeyHandler

		InMainMenu = 0x6086AB4,//23CubemapBackgroundScreen
		InLanGame1 = 0xE26A008,//NetherNet::SimpleNetworkInterfaceImpl::SendPacket
		InLanGame2 = 0xE26A234,//NetherNet::SimpleNetworkInterfaceImpl::ReadPacket

		FastDrop = 0x6358EDC,//GuiData::_tickItemDrop intertnal float field
		UnlockMarket = 0x76CF620,//Entitlement::isOwned
		GetMaxPlayers = 0xE14C3C4,//AppPlatform::getMaxPlayers
		FogState = 0x7C08F08,//LevelRendererCamera::_getFogDensitySettingType
		SetupFog = 0x7C00420,//LevelRendererPlayer::setupFog
		FullBright = 0x6C6B95C,//BaseOptions::getGamma
		ForEachActivePlayer = 0xCE9B8F4,//GameplayUserManager::forEachActivePlayer
		GetRuntimeActor = 0xD6B0D68,//Level::getRuntimeActorList
		IsAttackable = 0xC95B500,//Actor::isAttackableGamemode
		Attack = 0xCCC075C,//GameMode::_attack
		LerpMotion = 0xC947CDC,//Actor::lerpMotion
		NormalTick = 0x6BEDA24,//LocalPlayer::normalTick
		Swing = 0x6BF031C,//LocalPlayer::swing
		SetSprinting = 0x6BF05B8,//LocalPlayer::setSprinting
		GetEntityTypeId = 0xC937698,//Actor::getEntityTypeId
		GetHealth = 0xC9437D0,//Actor::getHealth
		SetClimbing = 0xC945610,//Actor::setClimbing
		SetYHeadRot = 0xC95AF30,//Actor::setYHeadRot
		SetYBodyRot = 0xC86C5D4,//Mob::setYBodyRotation
		SetInvisible = 0xC9597B8,//Actor::setInvisible
		Intersects = 0xC94727C,//Actor::intersects
		GetYHeadRot = 0xC95AE58,//Actor::getYHeadRot
		InitMaxAutoStep = 0xC956C54,//Actor::_initializeMaxAutoStep
		GetAABBDim = 0xC93AE58,//Actor::getAABBDim
		IsEmoting = 0xCE072A8,//Player::isEmoting
		NoBlur1 = 0x7BBE1E4,//FullScreenEffectRenderer::renderHeadlocked
		NoBlur2 = 0x7BBEAB4,//FullScreenEffectRenderer::render
		ShowPaperdoll = 0x6373FB8,//HudPlayerRenderer::update
		Subtitle = 0x63164C4,//TileMessage::setSubtitle
		GetAbilities = 0xCDF943C,//Player::getAbilities
		GetLayer = 0xCDF9450,//LayeredAbilities::getLayer
		SetAbility = 0xCDF87E0,//Abilities::setAbility
		ClientInstanceOnTick = 0x6478734,//ClientInstance::onTick
		HandleDestroyOrAttack = 0x6462B60,//ClientInputCallbacks::handleDestoryOrAttackButtonPress
		PlayUI = 0x648AED8,//ClientInstance::playUI
		SetNoJumpDelay = 0xCDDB410,//MobJump::setNoJumpDelay
		SetOnGround = 0x6F42DFC,//ActorEntityAccess::addOrRemoveComponent<OnGroundFlagComponent>
		MobIsJumping = 0xCDD8840,//ActorEntityAccess::addOrRemoveComponent<FlagComponent<MobIsJumpingFlag>>
		DisplayMessage = 0x6BF196C,//LocalPlayer::displayClientMessage
		Block_getRenderLayer = 0xD52E0F4,//Block::getRenderLayer
		RebuildAllChunkGeometry = 0x7BF10A8,//LevelRenderer::rebuildAllRenderChunkGeometry
		VignetteRenderer = 0x6376084,//HudVignetteRenderer::render
		NoNametags = 0x6AEE80C,//BaseActorRenderer::renderText
		ScreenName = 0x648482C,//ClientInstance::getScreenName
		GetNameTag = 0xC94C468,//Actor::getNameTag
		GetDimensionBlockSource = 0xC9318F0,//Actor::getDimensionBlockSource
		GetBlock = 0xCEE4E74,//BlockSource::getBlock
		IsAir = 0xCFA78FC,//Block::isAir
		// Auto Totem - Using direct field access (no function calls needed)
		// Container functions not required - using Player field offsets directly
		ContainerGetItem = 0x0,//NOT USED - using direct memory instead
		ContainerSetItem = 0x0,//NOT USED - using direct memory instead
		ContainerGetSize = 0x0,//NOT USED
		SuppliesGetContainer = 0x0,//NOT USED - Supplies* at Player+0xB40
		PlayerGetArmorContainer = 0x0,//NOT USED - ArmorContainer* at Player+0xBC0
		PlayerGetSupplies = 0x0,//NOT USED
	};
}

namespace Fields64 {
	enum Fields64 {
		GetGamemode = 0x9C0,//Player::getGameMode
		GetLevel = 0x1D0,//Actor::getLevel
		GetPosition = 0x208,//Actor::getPosition
		ActorRotation = 0x218,//Actor::setRotationX
		GetName = 0xB30,//Player::getName
		GetHurtTime = 0x194,//Mob::hurtEffects
		GetCameraPos = 0x65C,//LevelRendererCamera::getCameraPos
		GetLevelRendererPlayer = 0x3A0,//LevelRenderer::getLevelRendererPlayer
		GetLevelRenderer = 0xC0,//ClientInstance::getLevelRenderer
		BlockTypeClass = 0x78,//inside Block::getDescriptionId
		GetPlatform = 0x46C,//Player::getPlatform
		GetGameplayUserManager = 0x430,//inside Level::forEachPlayer
		ViewMatrix = 0x318,//ClientInstance Cheat Engine
		FovX = 0xF28,//LevelRendererPlayer Game Guardian 0.3~0.7 fovX
		FovY = 0xF3C,//LevelRendererPlayer Game Guardian 0.8~1.5 fovY
		SuppliesOffset = 0xB40,//PlayerInventory* inline (ADD X0,X0,#0xB40 at 0xce3e128)
		ArmorContainerOffset = 0xBC0,//Container inline for armor (ADD X0,X0,#0xBC0 at 0xce3e198)
		SelectedSlot = 0x0,//TODO: find selected slot offset within PlayerInventory
	};
}



#elif defined(__ARM_ARCH_7A__)



namespace Offsets {
	enum Offsets {
		Font = 0x2457A3C,//Default 1 float
		NoHurtCam = 0x30733BC,//CameraBobSystem::tick
		NoCamDistortion = 0x9919F88,//CameraPortalDistortionSystem::_tick
		NoBoatRotation = 0x307F7CC,//CameraVehicleRotationLookSystem::tick
		NoCamSleep = 0x991A8BC,//_tickSleepFade PUSH
		PlaceCamera = 0x9AF4DE0,//CameraBlendSystem::_tick
		WaterTrigger1 = 0x400C628,//<WasInWaterFlagComponent,EntityId xref
		WaterTrigger2 = 0x61D42CC,//<ActorHeadInWaterFlagComponent,EntityId xref
		WaterTrigger3 = 0x39FD5E0,//<WaterSplashEffectRequestComponent,EntityId xref
		SlowDownTriggers = 0x6309998,//BlockMovementSlowdownMultiplierSystemImpl::applySlowdownOnMove loc
		NoSlowDown = 0x6252B34,//ItemUseSlowdownSystemImpl::doItemUseSlowdownSystem loc
		WaterSpeed = 0x698E914,//(doWaterMoveSystem loc
		LavaSpeed = 0x6212324,//(doLavaMoveSystem loc
		Noclip = 0x61E9E30,//MoveCollisionSystem::System loc
		XrayCameraThird = 0x9AF3B68,//CameraAvoidanceSystem::tick
		LavaDrown = 0x691342C,//MobMovementGravity::tickLavaGravity loc
		WaterDrown = 0x6911AC0,//MobMovementGravity::tickPlayerWaterGravity loc
		Fov = 0x5011158,//9CameraAPI returns float
		SpeedHack = 0x628025C,//doDefaultMoveSystems 2
		JumpHack = 0x68F030C,//return 0.42
		Gravity = 0x68EC9B4,//-0.08 float
		AutoClickMine = 0x8B43D86,//8GameMode STP
		FastBridge = 0x8B44C5C,//"GameMode::useItemOn (client)"
		BlockReach = 0x8B45B34,//returns 7 or 12 float
		PlayerAuthInput = 0x6FEBC80,//"Player`s Head rotation"
		NativeKeyHandler = 0x3F68B30,//...nativeKeyHandler

		InMainMenu = 0x3BAFF50,//23CubemapBackgroundScreen
		InLanGame1 = 0x9B5C0AC,//NetherNet::SimpleNetworkInterfaceImpl::SendPacket
		InLanGame2 = 0x9B5C288,//NetherNet::SimpleNetworkInterfaceImpl::ReadPacket

		FastDrop = 0x3DAC710,//GuiData::_tickItemDrop intertnal float field
		UnlockMarket = 0x4C25EB8,//Entitlement::isOwned
		GetMaxPlayers = 0x9A86F3A,//AppPlatform::getMaxPlayers
		FogState = 0x5050A60,//LevelRendererCamera::_getFogDensitySettingType
		SetupFog = 0x5054C9C,//LevelRendererPlayer::setupFog
		FullBright = 0x44A1398,//BaseOptions::getGamma
		ForEachActivePlayer = 0x8C9C3C0,//GameplayUserManager::forEachActivePlayer
		GetRuntimeActor = 0x92C1180,//Level::getRuntimeActorList
		IsAttackable = 0x88D587C,//Actor::isAttackableGamemode
		Attack = 0x8B4297C,//GameMode::_attack
		LerpMotion = 0x88C6758,//Actor::lerpMotion
		NormalTick = 0x4445304,//LocalPlayer::normalTick
		Swing = 0x444726C,//LocalPlayer::swing
		SetSprinting = 0x4447444,//LocalPlayer::setSprinting
		GetEntityTypeId = 0x88B9E3A,//Actor::getEntityTypeId
		GetHealth = 0x88C320C,//Actor::getHealth
		SetClimbing = 0x88C4A32,//Actor::setClimbing
		SetYHeadRot = 0x88D5464,//Actor::setYHeadRot
		SetYBodyRot = 0x8824688,//Mob::setYBodyRotation
		SetInvisible = 0x88D4368,//Actor::setInvisible
		Intersects = 0x88C601C,//Actor::intersects
		GetYHeadRot = 0x88D53B0,//Actor::getYHeadRot
		InitMaxAutoStep = 0x88D22D6,//Actor::_initializeMaxAutoStep
		GetAABBDim = 0x88BC7BE,//Actor::getAABBDim
		IsEmoting = 0x8C2D734,//Player::isEmoting
		NoBlur1 = 0x501176C,//FullScreenEffectRenderer::renderHeadlocked
		NoBlur2 = 0x5011E20,//FullScreenEffectRenderer::render
		ShowPaperdoll = 0x3DC18BC,//HudPlayerRenderer::update
		Subtitle = 0x3D7AAE4,//TileMessage::setSubtitle
		GetAbilities = 0x8C23658,//Player::getAbilities
		GetLayer = 0x8C23664,//LayeredAbilities::getLayer
		SetAbility = 0x8C22E94,//Abilities::setAbility
		ClientInstanceOnTick = 0x3E8BCC0,//ClientInstance::onTick
		HandleDestroyOrAttack = 0x3E7BBB6,//ClientInputCallbacks::handleDestoryOrAttackButtonPress
		PlayUI = 0x3E9981C,//ClientInstance::playUI
		SetNoJumpDelay = 0x8C0D328,//MobJump::setNoJumpDelay
		SetOnGround = 0x46ADF34,//ActorEntityAccess::addOrRemoveComponent<OnGroundFlagComponent>
		MobIsJumping = 0x8C0B288,//ActorEntityAccess::addOrRemoveComponent<FlagComponent<MobIsJumpingFlag>>
		DisplayMessage = 0x4448490,//LocalPlayer::displayClientMessage
		Block_getRenderLayer = 0x9185D74,//Block::getRenderLayer
		RebuildAllChunkGeometry = 0x503CA52,//LevelRenderer::rebuildAllRenderChunkGeometry
		VignetteRenderer = 0x3DC36C4,//HudVignetteRenderer::render
		NoNametags = 0x438BCDC,//BaseActorRenderer::renderText
		ScreenName = 0x3E94D7C,//ClientInstance::getScreenName
		GetNameTag = 0x88C9BA8,//Actor::getNameTag
		GetDimensionBlockSource = 0x88B572A,//Actor::getDimensionBlockSource
		GetBlock = 0x8CD120C,//BlockSource::getBlock
		IsAir = 0x9182C46,//Block::isAir
	};
}

namespace Fields {
	enum Fields {
		GetGamemode = 0x6B0,//Player::getGameMode
		GetLevel = 0x140,//Actor::getLevel
		GetPosition = 0x164,//Actor::getPosition
		ActorRotation = 0x16C,//Actor::setRotationX
		GetName = 0x7A0,//Player::getName
		GetHurtTime = 0x10C,//Mob::hurtEffects
		GetCameraPos = 0x3E4,//LevelRendererCamera::getCameraPos
		GetLevelRendererPlayer = 0x1C0,//LevelRenderer::getLevelRendererPlayer
		GetLevelRenderer = 0x50,//ClientInstance::getLevelRenderer
		BlockTypeClass = 0x3C,//inside Block::getDescriptionId
		GetPlatform = 0x328,//Player::getPlatform
		GetGameplayUserManager = 0x21C,//inside Level::forEachPlayer
		ViewMatrix = 0x194,//ClientInstance Cheat Engine
		FovX = 0xB50,//LevelRendererPlayer Game Guardian 0.3~0.7 fovX
		FovY = 0xB64,//LevelRendererPlayer Game Guardian 0.8~1.5 fovY
		// Auto Totem - Inventory fields
		SelectedSlot = 0xB40,//Supplies field in Player (ADD X0,X0,#0xB40 at 0xce3e128)
		ArmorContainerOffset = 0xBC0,//ArmorContainer field in Player (ADD X0,X0,#0xBC0 at 0xce3e198)
	};
}



#else


//1.21.100
namespace Offsets86_64 {
	enum Offsets86_64 {
		Font = 0x249E1E4,//Default 1 float
		NoHurtCam = 0x5755BC0,//CameraBobSystem::tick
		NoCamDistortion = 0xED16D20,//CameraPortalDistortionSystem::_tick
		NoBoatRotation = 0x5768890,//CameraVehicleRotationLookSystem::tick
		NoCamSleep = 0xED17830,//_tickSleepFade PUSH
		PlaceCamera = 0xF034B20,//CameraBlendSystem::_tick
		WaterTrigger1 = 0x9FD7790,//<WasInWaterFlagComponent,EntityId xref
		WaterTrigger2 = 0x9FD7B70,//<ActorHeadInWaterFlagComponent,EntityId xref
		WaterTrigger3 = 0x65B7710,//<WaterSplashEffectRequestComponent,EntityId xref
		SlowDownTriggers = 0xA198230,//BlockMovementSlowdownMultiplierSystemImpl::applySlowdownOnMove loc
		NoSlowDown = 0xA097930,//ItemUseSlowdownSystemImpl::doItemUseSlowdownSystem loc
		BoatSpeed = 0xA9DE3B0,//BoatMoveControlSystem::boatControl<true> loc
		ElytraSpeed = 0xA0BFBF0,//(doGlideMoveSystem loc
		WaterSpeed = 0xAA90FB0,//(doWaterMoveSystem loc
		LavaSpeed = 0xA02F440,//(doLavaMoveSystem loc
		Noclip = 0x9FF7820,//MoveCollisionSystem::System sub
		XrayCameraThird = 0xF033410,//CameraAvoidanceSystem::tick
		LavaDrown = 0xA981210,//MobMovementGravity::tickLavaGravity loc
		WaterDrown = 0xA97EFF0,//MobMovementGravity::tickPlayerWaterGravity loc
		Fov = 0x8592EC0,//9CameraAPI returns float
		SpeedHack = 0xA13A9E0,//doDefaultMoveSystems 2
		JumpHack = 0xA96A650,//return 0.42
		Gravity = 0xA965410,//-0.08 float
		AutoClickMine = 0xD943AE0,//8GameMode STP
		FastBridge = 0xD945070,//"GameMode::useItemOn (client)"
		BlockReach = 0xD946380,//returns 7 or 12 float
		PlayerAuthInput = 0xB21A5A0,//"Player`s Head rotation"
		NativeKeyHandler = 0xF070650,//...nativeKeyHandler

		InMainMenu = 0x67DBC40,//23CubemapBackgroundScreen
		InGame = 0x67EF680,//16InGamePlayScreen
		InLanGame1 = 0xF0DBFE0,//NetherNet::SimpleNetworkInterfaceImpl::SendPacket
		InLanGame2 = 0xF0DC1B0,//NetherNet::SimpleNetworkInterfaceImpl::ReadPacket

		FastDrop = 0x6AD8FA0,//GuiData::_tickItemDrop intertnal float field
		UnlockMarket = 0x807F570,//Entitlement::isOwned
		GetMaxPlayers = 0xEF441D0,//AppPlatform::getMaxPlayers
		FogState = 0x8629E40,//LevelRendererCamera::_getFogDensitySettingType
		SetupFog = 0x8588B80,//LevelRendererPlayer::setupFog
		SmoothLight = 0x74D9970,//BaseOptions::getSmoothLighting
		FullBright = 0x74DA110,//BaseOptions::getGamma
		ForEachPlayer = 0xE3E4DF0,//Level::forEachPlayer
		GetRuntimeActor = 0xE3E5C70,//Level::getRuntimeActorList
		IsAttackable = 0xD5891A0,//Actor::isAttackableGamemode
		Attack = 0xD942000,//GameMode::_attack
		LerpMotion = 0xD574CE0,//Actor::lerpMotion
		NormalTick = 0x7445C50,//LocalPlayer::normalTick
		Swing = 0x7448CD0,//LocalPlayer::swing
		SetSprinting = 0x7448FA0,//LocalPlayer::setSprinting
		GetEntityTypeId = 0xD563450,//Actor::getEntityTypeId
		GetHealth = 0xD5702A0,//Actor::getHealth
		SetClimbing = 0xD572400,//Actor::setClimbing
		SetYHeadRot = 0xD588C50,//Actor::setYHeadRot
		SetYBodyRot = 0xD48F7D0,//Mob::setYBodyRotation
		SetInvisible = 0xD587470,//Actor::setInvisible
		Intersects = 0xD574240,//Actor::intersects
		GetYHeadRot = 0xD588B80,//Actor::getYHeadRot
		InitMaxAutoStep = 0xD5848C0,//Actor::_initializeMaxAutoStep
		GetAABBDim = 0xD567170,//Actor::getAABBDim
		IsEmoting = 0xDAAD610,//Player::isEmoting
		NoBlur1 = 0x85CA160,//FullScreenEffectRenderer::renderHeadlocked
		NoBlur2 = 0x85CAAE0,//FullScreenEffectRenderer::render
		ShowPaperdoll = 0x6B71010,//HudPlayerRenderer::update
		Subtitle = 0x6AE1070,//TileMessage::setSubtitle
		GetAbilities = 0xDA9EFC0,//Player::getAbilities
		GetLayer = 0xDA9EFE0,//LayeredAbilities::getLayer
		SetAbility = 0xDA9E550,//Abilities::setAbility
		ClientInstanceOnTick = 0x6C91250,//ClientInstance::onTick
		HandleDestroyOrAttack = 0x6C72FF0,//ClientInputCallbacks::handleDestoryOrAttackButtonPress
		AddLevels = 0xDAC61C0,//Player::addLevels
		PlayUI = 0x6CAA8F0,//ClientInstance::playUI
		SetNoJumpDelay = 0xDA73280,//MobJump::setNoJumpDelay
		SetOnGround = 0x7811720,//ActorEntityAccess::addOrRemoveComponent<OnGroundFlagComponent>
		MobIsJumping = 0xDA705E0,//ActorEntityAccess::addOrRemoveComponent<FlagComponent<MobIsJumpingFlag>>
		DisplayMessage = 0x744AAD0,//LocalPlayer::displayClientMessage
		Block_getRenderLayer = 0xE2F5D00,//Block::getRenderLayer
		RebuildAllChunkGeometry = 0x860EB50,//LevelRenderer::rebuildAllRenderChunkGeometry
		// Auto Totem - NOT USED (using direct memory)
		ContainerGetItem = 0x0,
		ContainerSetItem = 0x0,
		ContainerGetSize = 0x0,
		SuppliesGetContainer = 0x0,
		PlayerGetArmorContainer = 0x0,
		PlayerGetSupplies = 0x0,
		NoNametags = 0x0,
	};
}

namespace Fields86_64 {
	enum Fields86_64 {
		GetGamemode = 0x9D0,//Player::getGameMode
		GetLevel = 0x1D0,//Actor::getLevel
		GetPosition = 0x208,//Actor::getPosition
		ActorRotation = 0x218,//Actor::setRotationX
		GetName = 0xB20,//Player::getName
		GetHurtTime = 0x194,//Mob::hurtEffects
		GetCameraPos = 0x62C,//LevelRendererCamera::getCameraPos
		GetLevelRendererPlayer = 0x3A0,//LevelRenderer::getLevelRendererPlayer
		GetLevelRenderer = 0xC0,//ClientInstance::getLevelRenderer
		GetRenderLayer = 0x121,//BlockType::getRenderLayer
		BlockTypeClass = 0x78,//inside Block::getDescriptionId
		// Auto Totem
		SelectedSlot = 0x0,//TODO: find armv7 offset
		ArmorContainerOffset = 0x0,//TODO: find armv7 offset
	};
} 
#endif
