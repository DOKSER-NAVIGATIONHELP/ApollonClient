#ifndef ZEFF_CHAMS
#define ZEFF_CHAMS
#include <dlfcn.h>
#include <array>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <GLES2/gl2.h>
using namespace std;
static void *handle;
static void *input;
static bool enableRainbow, enableRainbowWall, osmtBoost, xrayCaves, panic;

int chamsint = 0;

ImVec4 inWallColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);                       
ImVec4 visibleColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);

//GL pointers
void (*p_glGetIntegerv)(unsigned int, int *);
void (*p_glGetBooleanv)(unsigned int, unsigned char *);
void (*p_glDepthRangef)(float, float);
void (*p_glBlendColor)(float, float, float, float);
void (*p_glEnable)(unsigned int);
void (*p_glLineWidth)(float);
void (*p_glBlendFunc)(unsigned int, unsigned int);
void (*p_glDisable)(unsigned int);
void (*p_glCullFace)(unsigned int);

const char *isDumpLocation = (OBFUSCATE("/sdcard/Download/!Apollon_log.txt"));

void int_to_char(int num, char *result) {
    int temp = num;
    int len = 0;
    while (temp > 0) {
        len++;
        temp /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        result[i] = num % 10 + '0';
        num /= 10;
    }
    result[len] = '\0';
}

string isDump(const char *name)
{
    vector<string> isShaders = {name};

    static string isTotalShaders;

    for (const auto &isAddTo: isShaders)
        isTotalShaders += (isAddTo + "\n"); // Adding whatever is added to the string vector to isTotalShaders, with a new line added per shader.

    return isTotalShaders.c_str();
}

int (*old_glGetAttribLocation)(int, const char *);
int new_glGetAttribLocation(int program, const char *name) {
    //ofstream(isDumpLocation) << isDump(name);
    return old_glGetAttribLocation(program, name);
}

void (*old_glDrawElementsInstanced)(unsigned int, int, unsigned int, const void *, int);
void new_glDrawElementsInstanced(unsigned int mode, int count, unsigned int type, const void *indices, int instancecount) {
	if (panic) return old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
	if (mode != GL_TRIANGLES) return old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
	
	unsigned char blend;
    p_glGetBooleanv(GL_BLEND, &blend);
	if (blend) return old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
	int currProgram;
	p_glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
	
	int attribute = old_glGetAttribLocation(currProgram, OBFUSCATE("a_indices"));
	
	if (attribute == -1) {
		if (osmtBoost) {
			p_glEnable(GL_CULL_FACE);
			p_glCullFace(GL_FRONT);
		}
		if (xrayCaves) {
			p_glDepthRangef(1, 0.5);
			old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
			p_glDepthRangef(0.5, 1);
		}
		return old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
	}
	
    {
		if (chamsint == 0) return old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
		
        if (chamsint == 1) {
            p_glDepthRangef(1, 0.5);
            old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
        }

        if (chamsint == 2) {
            old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
            p_glDepthRangef(1, 0.5);
            p_glBlendColor(visibleColor.x, visibleColor.y, visibleColor.z, 1);
            p_glEnable(GL_BLEND);
            p_glBlendFunc(GL_ONE, GL_CONSTANT_COLOR);
            old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
        }

        if (chamsint == 3) {
            old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
            p_glDepthRangef(1, 0.5);
            p_glBlendColor(visibleColor.x, visibleColor.y, visibleColor.z, 1);
            p_glEnable(GL_BLEND);
            p_glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA);
            p_glLineWidth(1);
            old_glDrawElementsInstanced(GL_LINES, count, type, indices, instancecount);
        }

        if (chamsint == 4) {
            old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
            p_glDepthRangef(1, 0);
            p_glLineWidth(10);
            p_glEnable(GL_BLEND);
            p_glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA);
            p_glBlendColor(0, 0, 0, 1);
            old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
            p_glDepthRangef(1, 0.5);
            p_glBlendColor(visibleColor.x, visibleColor.y, visibleColor.z, 1);
            old_glDrawElementsInstanced(GL_LINES, count, type, indices, instancecount);
        }

        if (chamsint == 5) {
            p_glEnable(GL_BLEND);
            p_glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA);
            p_glLineWidth(10);
            p_glBlendColor(visibleColor.x, visibleColor.y, visibleColor.z, 1);
            p_glDepthRangef(0.5, 1);
            old_glDrawElementsInstanced(GL_LINES, count, type, indices, instancecount);
            p_glBlendFunc(GL_ONE_MINUS_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_ALPHA);
            p_glBlendColor(0, 0, 0, 1);
            p_glDepthRangef(1, 0.5);
            old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
        }

        if (chamsint == 6) {
            p_glDisable(GL_DEPTH_TEST);
            p_glEnable(GL_BLEND);
            p_glBlendFunc(GL_ONE, GL_CONSTANT_COLOR);
            p_glBlendColor(inWallColor.x, inWallColor.y, inWallColor.z, 1);
            old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
            p_glEnable(GL_DEPTH_TEST);
            p_glDepthRangef(0.5, 1);
            p_glBlendColor(visibleColor.x, visibleColor.y, visibleColor.z, 1);
            old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
        }

        if (chamsint == 7) {
            p_glDisable(GL_DEPTH_TEST);
            p_glEnable(GL_BLEND);
            p_glBlendFunc(GL_ONE, GL_CONSTANT_COLOR);
            p_glBlendColor(inWallColor.x, inWallColor.y, inWallColor.z, 1);
            old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
            p_glEnable(GL_DEPTH_TEST);
            p_glDepthRangef(0.5, 1);
            p_glBlendColor(visibleColor.x, visibleColor.y, visibleColor.z, 1);
            p_glLineWidth(10);
            old_glDrawElementsInstanced(GL_LINES, count, type, indices, instancecount);
            p_glBlendFunc(GL_ONE_MINUS_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_ALPHA);
            p_glDepthRangef(0.49, 1);
            p_glBlendColor(0, 0, 0, 1);
            old_glDrawElementsInstanced(mode, count, type, indices, instancecount);
        }
    }
		p_glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		p_glLineWidth(1);
		p_glBlendColor(0, 0, 0, 1);
        p_glDepthRangef(0.5, 1);
		return p_glDisable(GL_BLEND);
}

void RenderHook(){
	
	#if defined(__aarch64__) || defined (__ARM_ARCH_7A__)
	DobbyHook(reinterpret_cast<void*>((const void*(*)(...))dlsym(handle, OBFUSCATE("glGetAttribLocation"))), reinterpret_cast<void*>(new_glGetAttribLocation), reinterpret_cast<void**>(&old_glGetAttribLocation));
	
    DobbyHook(reinterpret_cast<void*>((const void*(*)(...))dlsym(handle, OBFUSCATE("glDrawElementsInstanced"))), reinterpret_cast<void*>(new_glDrawElementsInstanced), reinterpret_cast<void**>(&old_glDrawElementsInstanced));
	
	#else
	
	MSHookX86_64(reinterpret_cast<void*>((const void*(*)(...))dlsym(handle, OBFUSCATE("glGetAttribLocation"))), reinterpret_cast<void*>(new_glGetAttribLocation), reinterpret_cast<void**>(&old_glGetAttribLocation));
	
    MSHookX86_64(reinterpret_cast<void*>((const void*(*)(...))dlsym(handle, OBFUSCATE("glDrawElementsInstanced"))), reinterpret_cast<void*>(new_glDrawElementsInstanced), reinterpret_cast<void**>(&old_glDrawElementsInstanced));
	
	#endif
	
	p_glGetIntegerv = (void (*)(unsigned int, int *))((const void*(*)(...))dlsym(handle, OBFUSCATE("glGetIntegerv")));
	
	p_glGetBooleanv = (void (*)(unsigned int, unsigned char *))((const void*(*)(...))dlsym(handle, OBFUSCATE("glGetBooleanv")));
	
	p_glDepthRangef = (void (*)(float, float))((const void*(*)(...))dlsym(handle, OBFUSCATE("glDepthRangef")));
	
	p_glBlendColor = (void (*)(float, float, float, float))((const void*(*)(...))dlsym(handle, OBFUSCATE("glBlendColor")));
	
	p_glEnable = (void (*)(unsigned int))((const void*(*)(...))dlsym(handle, OBFUSCATE("glEnable")));
	
	p_glLineWidth = (void (*)(float))((const void*(*)(...))dlsym(handle, OBFUSCATE("glLineWidth")));
	
	p_glBlendFunc = (void (*)(unsigned int, unsigned int))((const void*(*)(...))dlsym(handle, OBFUSCATE("glBlendFunc")));
	
	p_glDisable = (void (*)(unsigned int))((const void*(*)(...))dlsym(handle, OBFUSCATE("glDisable")));
	
	p_glCullFace = (void (*)(unsigned int))((const void*(*)(...))dlsym(handle, OBFUSCATE("glCullFace")));
}


#endif

