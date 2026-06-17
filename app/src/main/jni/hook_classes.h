class Mob;
class Actor;

class Item {
public:
    void* vTable;
	
};

class ItemStackBase {
public:
    void* vTable;
	
};

// Full ItemStack with item identification
class ItemStack : public ItemStackBase {
public:
    Item *getItem() {
        #if defined(__aarch64__)
        return *(Item **)((uint64_t)this + 0x8);
        #elif defined(__ARM_ARCH_7A__)
        return *(Item **)((uint64_t)this + 0x4);
        #else
        return *(Item **)((uint64_t)this + 0x8);
        #endif
    }
    int getItemId() {
        Item *item = getItem();
        if (!item) return 0;
        #if defined(__aarch64__) || defined(__x86_64__)
        return *(int *)((uint64_t)item + 0x10);
        #else
        return *(int *)((uint64_t)item + 0x8);
        #endif
    }
    int getCount() {
        #if defined(__aarch64__)
        return *(int *)((uint64_t)this + 0x10);
        #elif defined(__ARM_ARCH_7A__)
        return *(int *)((uint64_t)this + 0x8);
        #else
        return *(int *)((uint64_t)this + 0x10);
        #endif
    }
    bool isTotem() {
        int id = getItemId();
        return (id == 601 || id == 1069);
    }
    bool isEmpty() {
        return getItem() == nullptr || getItemId() == 0;
    }
};

// Container for inventory operations
class Container {
public:
    ItemStack* getItem(int slot) {
        #if defined(__aarch64__)
        static auto call = (ItemStack* (*)(Container*, int))(getAbsoluteAddress(MineLib, Offsets64::ContainerGetItem));
        #elif defined(__ARM_ARCH_7A__)
        static auto call = (ItemStack* (*)(Container*, int))(getAbsoluteAddress(MineLib, Offsets::ContainerGetItem + 1));
        #else
        static auto call = (ItemStack* (*)(Container*, int))(getAbsoluteAddress(MineLib, Offsets86_64::ContainerGetItem));
        #endif
        return (*call)(this, slot);
    }
    void setItem(int slot, ItemStack* item) {
        #if defined(__aarch64__)
        static auto call = (void (*)(Container*, int, ItemStack*))(getAbsoluteAddress(MineLib, Offsets64::ContainerSetItem));
        #elif defined(__ARM_ARCH_7A__)
        static auto call = (void (*)(Container*, int, ItemStack*))(getAbsoluteAddress(MineLib, Offsets::ContainerSetItem + 1));
        #else
        static auto call = (void (*)(Container*, int, ItemStack*))(getAbsoluteAddress(MineLib, Offsets86_64::ContainerSetItem));
        #endif
        return (*call)(this, slot, item);
    }
    int getContainerSize() {
        #if defined(__aarch64__)
        static auto call = (int (*)(Container*))(getAbsoluteAddress(MineLib, Offsets64::ContainerGetSize));
        #elif defined(__ARM_ARCH_7A__)
        static auto call = (int (*)(Container*))(getAbsoluteAddress(MineLib, Offsets::ContainerGetSize + 1));
        #else
        static auto call = (int (*)(Container*))(getAbsoluteAddress(MineLib, Offsets86_64::ContainerGetSize));
        #endif
        return (*call)(this);
    }
    // Direct fallback: read item from internal array
    ItemStack* getItemDirect(int slot) {
        #if defined(__aarch64__)
        uint64_t itemsPtr = *(uint64_t *)((uint64_t)this + 0x138);
        if (!itemsPtr) itemsPtr = (uint64_t)this + 0x138;
        return (ItemStack *)(itemsPtr + (slot * sizeof(ItemStack)));
        #else
        uint64_t itemsPtr = *(uint64_t *)((uint64_t)this + 0x98);
        if (!itemsPtr) itemsPtr = (uint64_t)this + 0x98;
        return (ItemStack *)(itemsPtr + (slot * sizeof(ItemStack)));
        #endif
    }
};

// PlayerInventory (Supplies)
class PlayerInventory {
public:
    Container* getContainer() {
        #if defined(__aarch64__)
        static auto call = (Container* (*)(PlayerInventory*))(getAbsoluteAddress(MineLib, Offsets64::SuppliesGetContainer));
        #elif defined(__ARM_ARCH_7A__)
        static auto call = (Container* (*)(PlayerInventory*))(getAbsoluteAddress(MineLib, Offsets::SuppliesGetContainer + 1));
        #else
        static auto call = (Container* (*)(PlayerInventory*))(getAbsoluteAddress(MineLib, Offsets86_64::SuppliesGetContainer));
        #endif
        return (*call)(this);
    }
    int getSelectedSlot() {
        #if defined(__aarch64__)
        return *(int *)((uint64_t)this + Fields64::SelectedSlot);
        #elif defined(__ARM_ARCH_7A__)
        return *(int *)((uint64_t)this + Fields::SelectedSlot);
        #else
        return *(int *)((uint64_t)this + Fields86_64::SelectedSlot);
        #endif
    }
};

class ClientInstanceScreenModel {
public:
    void* vTable;
	
};

class BlockType {
public:
	
};

class Block {
public:
	BlockType *getBlockTypeClassCustom() {
		#if defined(__aarch64__)
		return *(BlockType **)((uint64_t)this + Fields64::BlockTypeClass);
		#elif defined(__ARM_ARCH_7A__)
		return *(BlockType **)((uint64_t)this + Fields::BlockTypeClass);
		#else
		return *(BlockType **)((uint64_t)this + Fields86_64::BlockTypeClass);
		#endif
    }
	bool isAir() {
		#if defined(__aarch64__)
		static auto call = (bool (*)(Block *))(getAbsoluteAddress(MineLib, Offsets64::IsAir));
		#else
		static auto call = (bool (*)(Block *))(getAbsoluteAddress(MineLib, Offsets::IsAir + 1));
		#endif
		return (*call)(this);
	 }
};

class BlockSource {
public:
    Block *getBlock(const vec3_ti &pos) {
		#if defined(__aarch64__)
		static auto call = (Block *(*)(BlockSource *, const vec3_ti &))(getAbsoluteAddress(MineLib, Offsets64::GetBlock));
		#else
		static auto call = (Block *(*)(BlockSource *, const vec3_ti &))(getAbsoluteAddress(MineLib, Offsets::GetBlock + 1));
		#endif
		return (*call)(this, pos);
	 }
};

class LevelRendererCamera {
public:
	vec3_t &getCameraPos() {
		#if defined(__aarch64__)
		return *(vec3_t *)((uint64_t)this + Fields64::GetCameraPos);
		#elif defined(__ARM_ARCH_7A__)
		return *(vec3_t *)((uint64_t)this + Fields::GetCameraPos);
		#else
		return *(vec3_t *)((uint64_t)this + Fields86_64::GetCameraPos);
		#endif
    }
	glm::vec2 getFov() {
		glm::vec2 AxisFov;
		#if defined(__aarch64__)
	    AxisFov.x = *(float *)((uint64_t)this + Fields64::FovX);
	    AxisFov.y = *(float *)((uint64_t)this + Fields64::FovY);
		#else
		AxisFov.x = *(float *)((uint64_t)this + Fields::FovX);
	    AxisFov.y = *(float *)((uint64_t)this + Fields::FovY);
		#endif
		return AxisFov;
	}
};

class LevelRenderer {
public:
	LevelRendererCamera* getLevelRendererPlayer() {
		#if defined(__aarch64__)
        return *(LevelRendererCamera **)((uint64_t)this + Fields64::GetLevelRendererPlayer);
		#elif defined(__ARM_ARCH_7A__)
		return *(LevelRendererCamera **)((uint64_t)this + Fields::GetLevelRendererPlayer);
		#else
		return *(LevelRendererCamera **)((uint64_t)this + Fields86_64::GetLevelRendererPlayer);
		#endif
    }
	void rebuildAllRenderChunkGeometry() {
		#if defined(__aarch64__)
		static auto call = (void (*)(LevelRenderer *))(getAbsoluteAddress(MineLib, Offsets64::RebuildAllChunkGeometry));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void (*)(LevelRenderer *))(getAbsoluteAddress(MineLib, Offsets::RebuildAllChunkGeometry + 1));
		#else
		static auto call = (void (*)(LevelRenderer *))(getAbsoluteAddress(MineLib, Offsets86_64::RebuildAllChunkGeometry));
		#endif
		return (*call)(this);
	}
};

class GameplayUserManager {
public:
	void forEachActivePlayer(std::function<bool(struct Player&)> func, bool a3) {
		#if defined(__aarch64__)
        static auto call = (void (*)(GameplayUserManager*, std::function<bool(Player&)>, bool))(getAbsoluteAddress(MineLib, Offsets64::ForEachActivePlayer));
		#else
		static auto call = (void (*)(GameplayUserManager*, std::function<bool(Player&)>, bool))(getAbsoluteAddress(MineLib, Offsets::ForEachActivePlayer + 1));
		#endif
        return (*call)(this, func, a3);
    }
};

class Level {
public:
    GameplayUserManager* getGameplayUserManager() {
		#if defined(__aarch64__)
		return *(GameplayUserManager **)((uint64_t)this + Fields64::GetGameplayUserManager);
		#else
		return *(GameplayUserManager **)((uint64_t)this + Fields::GetGameplayUserManager);
        #endif
	}
	std::vector<Mob*> getRuntimeActorList() {
	    #if defined(__aarch64__)
        static auto call = (std::vector<Mob*> (*)(Level*))(getAbsoluteAddress(MineLib, Offsets64::GetRuntimeActor));
	    #elif defined(__ARM_ARCH_7A__)
	    static auto call = (std::vector<Mob*> (*)(Level*))(getAbsoluteAddress(MineLib, Offsets::GetRuntimeActor + 1));
		#else
		static auto call = (std::vector<Mob*> (*)(Level*))(getAbsoluteAddress(MineLib, Offsets86_64::GetRuntimeActor));
	    #endif
        return (*call)(this);
    }
};

class GameMode {
public:
	void attack(Actor* obj, bool a2) {
		#if defined(__aarch64__)
		static auto call = (void (*)(GameMode*, Actor*, bool))(getAbsoluteAddress(MineLib, Offsets64::Attack));
		#elif defined(__ARM_ARCH_7A__)
        static auto call = (void (*)(GameMode*, Actor*, bool))(getAbsoluteAddress(MineLib, Offsets::Attack + 1));
		#else
		static auto call = (void (*)(GameMode*, Actor*, bool))(getAbsoluteAddress(MineLib, Offsets86_64::Attack));
        #endif
		return (*call)(this, obj, a2);
    }
};

class Actor {
public:
    Level* getLevel() {
		#if defined(__aarch64__)
		return *(Level **)((uint64_t)this + Fields64::GetLevel);
		#elif defined(__ARM_ARCH_7A__)
        return *(Level **)((uint64_t)this + Fields::GetLevel);
		#else
		return *(Level **)((uint64_t)this + Fields86_64::GetLevel);
        #endif
    }
    vec3_t *getPosition() {
		#if defined(__aarch64__)
		return *(vec3_t **)((uint64_t)this + Fields64::GetPosition);
		#elif defined(__ARM_ARCH_7A__)
        return *(vec3_t **)((uint64_t)this + Fields::GetPosition);
		#else
		return *(vec3_t **)((uint64_t)this + Fields86_64::GetPosition);
        #endif
    }
	int getEntityTypeId() {
		#if defined(__aarch64__)
		static auto call = (int (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets64::GetEntityTypeId));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (int (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets::GetEntityTypeId + 1));
		#else
		static auto call = (int (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets86_64::GetEntityTypeId));
		#endif
		return (*call)(this);
    }
	int getHealth() {
		#if defined(__aarch64__)
		static auto call = (int (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets64::GetHealth));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (int (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets::GetHealth + 1));
		#else
		static auto call = (int (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets86_64::GetHealth));
		#endif
		return (*call)(this);
    }
	vec2_t *getAABBDim() {
		#if defined(__aarch64__)
		static auto call = (vec2_t *(*)(Actor*))(getAbsoluteAddress(MineLib, Offsets64::GetAABBDim));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (vec2_t *(*)(Actor*))(getAbsoluteAddress(MineLib, Offsets::GetAABBDim + 1));
		#else
		static auto call = (vec2_t *(*)(Actor*))(getAbsoluteAddress(MineLib, Offsets86_64::GetAABBDim));
		#endif
		return (*call)(this);
    }
	void setYHeadRot(float that) {
		#if defined(__aarch64__)
		static auto call = (void (*)(Actor*, float))(getAbsoluteAddress(MineLib, Offsets64::SetYHeadRot));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void (*)(Actor*, float))(getAbsoluteAddress(MineLib, Offsets::SetYHeadRot + 1));
		#else
		static auto call = (void (*)(Actor*, float))(getAbsoluteAddress(MineLib, Offsets86_64::SetYHeadRot));
		#endif
		return (*call)(this, that);
    }
	void setRotationX(float that) {
		#if defined(__aarch64__)
		float *Rotation = *(float **)((uint64_t)this + Fields64::ActorRotation);
		#elif defined(__ARM_ARCH_7A__)
        float *Rotation = *(float **)((uint64_t)this + Fields::ActorRotation);
		#else
		float *Rotation = *(float **)((uint64_t)this + Fields86_64::ActorRotation);
        #endif
		*Rotation = that;
    }
	void setClimbing(bool that) {
		#if defined(__aarch64__)
		static auto call = (void (*)(Actor*, bool))(getAbsoluteAddress(MineLib, Offsets64::SetClimbing));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void (*)(Actor*, bool))(getAbsoluteAddress(MineLib, Offsets::SetClimbing + 1));
		#else
		static auto call = (void (*)(Actor*, bool))(getAbsoluteAddress(MineLib, Offsets86_64::SetClimbing));
		#endif
		return (*call)(this, that);
    }
	void setRotationY(float that) {
		#if defined(__aarch64__)
		float *Rotation = *(float **)((uint64_t)this + Fields64::ActorRotation);
		#elif defined(__ARM_ARCH_7A__)
        float *Rotation = *(float **)((uint64_t)this + Fields::ActorRotation);
		#else
		float *Rotation = *(float **)((uint64_t)this + Fields86_64::ActorRotation);
        #endif
		*(float *)((uint64_t)Rotation + 0x4) = that;
    }
	vec2_t *getRotation() {
		#if defined(__aarch64__)
		return *(vec2_t **)((uint64_t)this + Fields64::ActorRotation);
		#elif defined(__ARM_ARCH_7A__)
        return *(vec2_t **)((uint64_t)this + Fields::ActorRotation);
		#else
		return *(vec2_t **)((uint64_t)this + Fields86_64::ActorRotation);
        #endif
    }
	float getYHeadRot() {
		#if defined(__aarch64__)
		static auto call = (float (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets64::GetYHeadRot));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (float (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets::GetYHeadRot + 1));
		#else
		static auto call = (float (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets86_64::GetYHeadRot));
		#endif
		return (*call)(this);
    }
	void setInvisible(bool that) {
		#if defined(__aarch64__)
		static auto call = (void (*)(Actor*, bool))(getAbsoluteAddress(MineLib, Offsets64::SetInvisible));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void (*)(Actor*, bool))(getAbsoluteAddress(MineLib, Offsets::SetInvisible + 1));
		#else
		static auto call = (void (*)(Actor*, bool))(getAbsoluteAddress(MineLib, Offsets86_64::SetInvisible));
		#endif
		return (*call)(this, that);
    }
	bool isAttackableGamemode() {
		#if defined(__aarch64__)
		static auto call = (bool (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets64::IsAttackable));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (bool (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets::IsAttackable + 1));
		#else
		static auto call = (bool (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets86_64::IsAttackable));
		#endif
		return (*call)(this);
    }
	void initializeMaxAutoStep(float that) {
		#if defined(__aarch64__)
		static auto call = (void (*)(Actor*, float))(getAbsoluteAddress(MineLib, Offsets64::InitMaxAutoStep));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void (*)(Actor*, float))(getAbsoluteAddress(MineLib, Offsets::InitMaxAutoStep + 1));
		#else
		static auto call = (void (*)(Actor*, float))(getAbsoluteAddress(MineLib, Offsets86_64::InitMaxAutoStep));
		#endif
		return (*call)(this, that);
    }
	const std::string &getNameTag() {
		#if defined(__aarch64__)
		static auto call = (const std::string & (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets64::GetNameTag));
		#else
		static auto call = (const std::string & (*)(Actor*))(getAbsoluteAddress(MineLib, Offsets::GetNameTag + 1));
		#endif
		return (*call)(this);
    }
	BlockSource *getDimensionBlockSource() {
		#if defined(__aarch64__)
		static auto call = (BlockSource *(*)(Actor *))(getAbsoluteAddress(MineLib, Offsets64::GetDimensionBlockSource));
		#else
		static auto call = (BlockSource *(*)(Actor *))(getAbsoluteAddress(MineLib, Offsets::GetDimensionBlockSource + 1));
		#endif
		return (*call)(this);
	 }
};

class Mob: public Actor {
public:
	bool canBeHurted() {
		#if defined(__aarch64__)
		return *(int *)((uint64_t)this + Fields64::GetHurtTime) < 2;
		#elif defined(__ARM_ARCH_7A__)
		return *(int *)((uint64_t)this + Fields::GetHurtTime) < 2;
		#else
		return *(int *)((uint64_t)this + Fields86_64::GetHurtTime) < 2;
		#endif
    }
	int getHurtTime() {
		#if defined(__aarch64__)
		return *(int *)((uint64_t)this + Fields64::GetHurtTime);
		#elif defined(__ARM_ARCH_7A__)
		return *(int *)((uint64_t)this + Fields::GetHurtTime);
		#else
		return *(int *)((uint64_t)this + Fields86_64::GetHurtTime);
		#endif
    }
	void setYBodyRotation(float that) {
		#if defined(__aarch64__)
		static auto call = (void (*)(Mob*, float))(getAbsoluteAddress(MineLib, Offsets64::SetYBodyRot));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void (*)(Mob*, float))(getAbsoluteAddress(MineLib, Offsets::SetYBodyRot + 1));
		#else
		static auto call = (void (*)(Mob*, float))(getAbsoluteAddress(MineLib, Offsets86_64::SetYBodyRot));
		#endif
		return (*call)(this, that);
    }
	 void *setNoJumpDelay(int EntityContext, int a3) {
		 #if defined(__aarch64__)
		static auto call = (void *(*)(Mob *, int, int))(getAbsoluteAddress(MineLib, Offsets64::SetNoJumpDelay));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void *(*)(Mob *, int, int))(getAbsoluteAddress(MineLib, Offsets::SetNoJumpDelay + 1));
		#else
		static auto call = (void *(*)(Mob *, int, int))(getAbsoluteAddress(MineLib, Offsets86_64::SetNoJumpDelay));
		#endif
		return (*call)(this, EntityContext, a3);
	 }
};

class LayeredAbilities {
public:
	void setAbility(int index, bool enable) {
		#if defined(__aarch64__)
		static auto call = (void (*)(LayeredAbilities *, int, bool))(getAbsoluteAddress(MineLib, Offsets64::SetAbility));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void (*)(LayeredAbilities *, int, bool))(getAbsoluteAddress(MineLib, Offsets::SetAbility + 1));
		#else
		static auto call = (void (*)(LayeredAbilities *, int, bool))(getAbsoluteAddress(MineLib, Offsets86_64::SetAbility));
		#endif
		return (*call)(this, index, enable);
    }
};

class Abilities : public LayeredAbilities {
public:
	LayeredAbilities *getLayer(int numberOfLayer) {
		#if defined(__aarch64__)
		static auto call = (LayeredAbilities *(*)(Abilities *, int))(getAbsoluteAddress(MineLib, Offsets64::GetLayer));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (LayeredAbilities *(*)(Abilities *, int))(getAbsoluteAddress(MineLib, Offsets::GetLayer + 1));
		#else
		static auto call = (LayeredAbilities *(*)(Abilities *, int))(getAbsoluteAddress(MineLib, Offsets86_64::GetLayer));
		#endif
		return (*call)(this, numberOfLayer);
    }
};

class Player : public Mob {
public:
    GameMode* getGameMode() {
		#if defined(__aarch64__)
		return *(GameMode **)((uint64_t)this + Fields64::GetGamemode);
		#elif defined(__ARM_ARCH_7A__)
        return *(GameMode **)((uint64_t)this + Fields::GetGamemode);
		#else
		return *(GameMode **)((uint64_t)this + Fields86_64::GetGamemode);
        #endif
    }
	const std::string& getName() {
        #if defined(__aarch64__)
        return *(reinterpret_cast<std::string*>((uint64_t)this + Fields64::GetName));
        #elif defined(__ARM_ARCH_7A__)
        return *(reinterpret_cast<std::string*>((uint64_t)this + Fields::GetName));
		#else
		return *(reinterpret_cast<std::string*>((uint64_t)this + Fields86_64::GetName));
        #endif
    }
	Abilities *getAbilities() {
		#if defined(__aarch64__)
		static auto call = (Abilities *(*)(Player *))(getAbsoluteAddress(MineLib, Offsets64::GetAbilities));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (Abilities *(*)(Player *))(getAbsoluteAddress(MineLib, Offsets::GetAbilities + 1));
		#else
		static auto call = (Abilities *(*)(Player *))(getAbsoluteAddress(MineLib, Offsets86_64::GetAbilities));
		#endif
		return (*call)(this);
    }
	int getPlatform() {
		#if defined(__aarch64__)
		return *(int *)((uint64_t)this + Fields64::GetPlatform);
		#else
		return *(int *)((uint64_t)this + Fields::GetPlatform);
		#endif
    }
	// Access armor container (offhand is slot 4)
	Container* getArmorContainer() {
		#if defined(__aarch64__)
		static auto call = (Container* (*)(Player*))(getAbsoluteAddress(MineLib, Offsets64::PlayerGetArmorContainer));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (Container* (*)(Player*))(getAbsoluteAddress(MineLib, Offsets::PlayerGetArmorContainer + 1));
		#else
		static auto call = (Container* (*)(Player*))(getAbsoluteAddress(MineLib, Offsets86_64::PlayerGetArmorContainer));
		#endif
		return (*call)(this);
	}
	// Access supplies (inventory manager)
	PlayerInventory* getSupplies() {
		#if defined(__aarch64__)
		static auto call = (PlayerInventory* (*)(Player*))(getAbsoluteAddress(MineLib, Offsets64::PlayerGetSupplies));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (PlayerInventory* (*)(Player*))(getAbsoluteAddress(MineLib, Offsets::PlayerGetSupplies + 1));
		#else
		static auto call = (PlayerInventory* (*)(Player*))(getAbsoluteAddress(MineLib, Offsets86_64::PlayerGetSupplies));
		#endif
		return (*call)(this);
	}
	// Direct offhand access (fallback using memory offset)
	ItemStack* getOffhandSlotDirect() {
		#if defined(__aarch64__)
		Container* armor = (Container*)((uint64_t)this + Fields64::ArmorContainerOffset);
		return armor->getItemDirect(4);
		#elif defined(__ARM_ARCH_7A__)
		Container* armor = (Container*)((uint64_t)this + Fields::ArmorContainerOffset);
		return armor->getItemDirect(4);
		#else
		Container* armor = (Container*)((uint64_t)this + Fields86_64::ArmorContainerOffset);
		return armor->getItemDirect(4);
		#endif
	}
};

class LocalPlayer : public Player {
public:
     void swing() {
		#if defined(__aarch64__)
		static auto call = (void (*)(LocalPlayer *))(getAbsoluteAddress(MineLib, Offsets64::Swing));
		#elif defined(__ARM_ARCH_7A__)
        static auto call = (void (*)(LocalPlayer *))(getAbsoluteAddress(MineLib, Offsets::Swing + 1));
		#else
		static auto call = (void (*)(LocalPlayer *))(getAbsoluteAddress(MineLib, Offsets86_64::Swing));
        #endif
		return (*call)(this);
	 }
	 void setSprinting(bool that) {
		#if defined(__aarch64__)
		static auto call = (void (*)(LocalPlayer *, bool))(getAbsoluteAddress(MineLib, Offsets64::SetSprinting));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void (*)(LocalPlayer *, bool))(getAbsoluteAddress(MineLib, Offsets::SetSprinting + 1));
		#else
		static auto call = (void (*)(LocalPlayer *, bool))(getAbsoluteAddress(MineLib, Offsets86_64::SetSprinting));
		#endif
		return (*call)(this, that);
	 }
	 void *setOnGround(int EntityContext, bool a3) {
		#if defined(__aarch64__)
		static auto call = (void *(*)(LocalPlayer *, int, bool))(getAbsoluteAddress(MineLib, Offsets64::SetOnGround));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void *(*)(LocalPlayer *, int, bool))(getAbsoluteAddress(MineLib, Offsets::SetOnGround + 1));
		#else
		static auto call = (void *(*)(LocalPlayer *, int, bool))(getAbsoluteAddress(MineLib, Offsets86_64::SetOnGround));
		#endif
		return (*call)(this, EntityContext, a3);
	 }
	 void *setIsJumping(int EntityContext, bool a3) {
		#if defined(__aarch64__)
		static auto call = (void *(*)(LocalPlayer *, int, bool))(getAbsoluteAddress(MineLib, Offsets64::MobIsJumping));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void *(*)(LocalPlayer *, int, bool))(getAbsoluteAddress(MineLib, Offsets::MobIsJumping + 1));
		#else
		static auto call = (void *(*)(LocalPlayer *, int, bool))(getAbsoluteAddress(MineLib, Offsets86_64::MobIsJumping));
		#endif
		return (*call)(this, EntityContext, a3);
	 }
	 void displayClientMessage(const std::string &message, const std::string &filteredMessage) {
		#if defined(__aarch64__)
		static auto call = (void (*)(LocalPlayer *, const std::string &, const std::string &))(getAbsoluteAddress(MineLib, Offsets64::DisplayMessage));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void (*)(LocalPlayer *, const std::string &, const std::string &))(getAbsoluteAddress(MineLib, Offsets::DisplayMessage + 1));
		#else
		static auto call = (void (*)(LocalPlayer *, const std::string &, const std::string &))(getAbsoluteAddress(MineLib, Offsets86_64::DisplayMessage));
		#endif
		return (*call)(this, message, filteredMessage);
	}
};

class ClientInstance {
public:
	std::string getScreenName() {
		std::string currentScreen = oxorany("no_screen");
		#if defined(__aarch64__)
		static auto call = (std::string (*)(ClientInstance*, std::string))(getAbsoluteAddress(MineLib, Offsets64::ScreenName));
		#else
		static auto call = (std::string (*)(ClientInstance*, std::string))(getAbsoluteAddress(MineLib, Offsets::ScreenName + 1));
		#endif
		return (*call)(this, currentScreen);
	}
	void handleDestoryOrAttackButtonPress() {
		#if defined(__aarch64__)
		static auto call = (void (*)(ClientInstance*))(getAbsoluteAddress(MineLib, Offsets64::HandleDestroyOrAttack));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void (*)(ClientInstance*))(getAbsoluteAddress(MineLib, Offsets::HandleDestroyOrAttack + 1));
		#else
		static auto call = (void (*)(ClientInstance*))(getAbsoluteAddress(MineLib, Offsets86_64::HandleDestroyOrAttack));
		#endif
		return (*call)(this);
	}
	LevelRenderer* getLevelRenderer() {
		#if defined(__aarch64__)
        return *(LevelRenderer **)((uint64_t)this + Fields64::GetLevelRenderer);
		#elif defined(__ARM_ARCH_7A__)
		return *(LevelRenderer **)((uint64_t)this + Fields::GetLevelRenderer);
		#else
		return *(LevelRenderer **)((uint64_t)this + Fields86_64::GetLevelRenderer);
		#endif
    }
	void playUI(const std::string &sound, float volume, float pitch) {
		#if defined(__aarch64__)
		static auto call = (void (*)(ClientInstance*, const std::string &, float, float))(getAbsoluteAddress(MineLib, Offsets64::PlayUI));
		#elif defined(__ARM_ARCH_7A__)
		static auto call = (void (*)(ClientInstance*, const std::string &, float, float))(getAbsoluteAddress(MineLib, Offsets::PlayUI + 1));
		#else
		static auto call = (void (*)(ClientInstance*, const std::string &, float, float))(getAbsoluteAddress(MineLib, Offsets86_64::PlayUI));
		#endif
		return (*call)(this, sound, volume, pitch);
	}
	glm::mat4 getViewMatrix() {
		#if defined(__aarch64__)
		return *(glm::mat4 *)((uint64_t)this + Fields64::ViewMatrix);
		#else
		return *(glm::mat4 *)((uint64_t)this + Fields::ViewMatrix);
		#endif
	}
};
