#pragma once
#include <jni.h>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdarg>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#include <functional>
#include <chrono>
#include <GLES3/gl3.h>
#include <android/keycodes.h>

#include "stb_image.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "imstb_truetype.h"

// ========================================================================
// Custom OpenGL-based UI - Replaces Dear ImGui entirely
// Provides compatible API that the menu code expects
// ========================================================================

// ─── Types ─────────────────────────────────────────────────────────────
struct ImVec2 {
    float x, y;
    ImVec2() : x(0), y(0) {}
    ImVec2(float _x, float _y) : x(_x), y(_y) {}
    ImVec2 operator+(const ImVec2& o) const { return ImVec2(x+o.x, y+o.y); }
    ImVec2 operator-(const ImVec2& o) const { return ImVec2(x-o.x, y-o.y); }
    ImVec2 operator*(float s) const { return ImVec2(x*s, y*s); }
    ImVec2 operator/(float s) const { return ImVec2(x/s, y/s); }
    ImVec2& operator+=(const ImVec2& o) { x+=o.x; y+=o.y; return *this; }
    ImVec2& operator-=(const ImVec2& o) { x-=o.x; y-=o.y; return *this; }
    bool operator==(const ImVec2& o) const { return x==o.x && y==o.y; }
};

struct ImVec4 {
    float x, y, z, w;
    ImVec4() : x(0),y(0),z(0),w(0) {}
    ImVec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    ImVec4 operator+(const ImVec4& o) const { return ImVec4(x+o.x,y+o.y,z+o.z,w+o.w); }
};

struct ImColor {
    ImVec4 Value;
    ImColor() : Value(0,0,0,1) {}
    ImColor(float r, float g, float b, float a=1) : Value(r,g,b,a) {}
    ImColor(const ImVec4& c) : Value(c) {}
    operator ImVec4() const { return Value; }
    operator uint32_t() const { return ColorConvertFloat4ToU32(Value); }
};

typedef uint32_t ImU32;
typedef int ImGuiID;
typedef GLuint ImTextureID;

// ─── Color utilities ──────────────────────────────────────────────────
inline ImU32 IM_COL32(int r, int g, int b, int a) {
    return ((a&0xFF)<<24) | ((b&0xFF)<<16) | ((g&0xFF)<<8) | (r&0xFF);
}
inline ImU32 ColorConvertFloat4ToU32(const ImVec4& c) {
    return IM_COL32((int)(c.x*255),(int)(c.y*255),(int)(c.z*255),(int)(c.w*255));
}
inline ImVec4 ColorConvertU32ToFloat4(ImU32 c) {
    return ImVec4(((c>>0)&0xFF)/255.0f, ((c>>8)&0xFF)/255.0f, ((c>>16)&0xFF)/255.0f, ((c>>24)&0xFF)/255.0f);
}

// ─── Style Colors ─────────────────────────────────────────────────────
enum ImGuiCol_ {
    ImGuiCol_Text = 0,
    ImGuiCol_TextDisabled,
    ImGuiCol_WindowBg,
    ImGuiCol_ChildBg,
    ImGuiCol_PopupBg,
    ImGuiCol_Border,
    ImGuiCol_BorderShadow,
    ImGuiCol_FrameBg,
    ImGuiCol_FrameBgHovered,
    ImGuiCol_FrameBgActive,
    ImGuiCol_TitleBg,
    ImGuiCol_TitleBgActive,
    ImGuiCol_TitleBgCollapsed,
    ImGuiCol_MenuBarBg,
    ImGuiCol_ScrollbarBg,
    ImGuiCol_ScrollbarGrab,
    ImGuiCol_ScrollbarGrabHovered,
    ImGuiCol_ScrollbarGrabActive,
    ImGuiCol_CheckMark,
    ImGuiCol_SliderGrab,
    ImGuiCol_SliderGrabActive,
    ImGuiCol_Button,
    ImGuiCol_ButtonHovered,
    ImGuiCol_ButtonActive,
    ImGuiCol_Header,
    ImGuiCol_HeaderHovered,
    ImGuiCol_HeaderActive,
    ImGuiCol_Separator,
    ImGuiCol_SeparatorHovered,
    ImGuiCol_SeparatorActive,
    ImGuiCol_ResizeGrip,
    ImGuiCol_ResizeGripHovered,
    ImGuiCol_ResizeGripActive,
    ImGuiCol_Tab,
    ImGuiCol_TabHovered,
    ImGuiCol_TabActive,
    ImGuiCol_TabUnfocused,
    ImGuiCol_TabUnfocusedActive,
    ImGuiCol_PlotLines,
    ImGuiCol_PlotLinesHovered,
    ImGuiCol_PlotHistogram,
    ImGuiCol_PlotHistogramHovered,
    ImGuiCol_TableHeaderBg,
    ImGuiCol_TableBorderStrong,
    ImGuiCol_TableBorderLight,
    ImGuiCol_TableRowBg,
    ImGuiCol_TableRowBgAlt,
    ImGuiCol_TextSelectedBg,
    ImGuiCol_DragDropTarget,
    ImGuiCol_NavHighlight,
    ImGuiCol_NavWindowingHighlight,
    ImGuiCol_NavWindowingDimBg,
    ImGuiCol_ModalWindowDimBg,
    ImGuiCol_COUNT
};

enum ImGuiStyleVar_ {
    ImGuiStyleVar_WindowTitleAlign = 8,
};

// ─── Draw Commands ────────────────────────────────────────────────────
enum DrawPrimType { DRAW_LINE, DRAW_RECT, DRAW_RECT_FILLED, DRAW_CIRCLE, DRAW_CIRCLE_FILLED,
                     DRAW_TRIANGLE, DRAW_TRIANGLE_FILLED, DRAW_TEXT, DRAW_IMAGE, DRAW_PATH };

struct DrawCmd {
    DrawPrimType type;
    float x1, y1, x2, y2, x3, y3, radius;
    ImU32 color;
    float thickness;
    float uv_x, uv_y, uv_w, uv_h;
    ImTextureID tex_id;
    bool filled;
    bool closed;
    std::vector<ImVec2> path_pts;
    std::string text;
};

// ─── Draw List ────────────────────────────────────────────────────────
class ImDrawList {
public:
    std::vector<DrawCmd> commands;
    ImVec2 clip_rect_min, clip_rect_max;
    
    void AddLine(const ImVec2& a, const ImVec2& b, ImU32 col, float thickness=1.0f) {
        DrawCmd cmd;
        cmd.type = DRAW_LINE; cmd.x1 = a.x; cmd.y1 = a.y; cmd.x2 = b.x; cmd.y2 = b.y;
        cmd.color = col; cmd.thickness = thickness;
        commands.push_back(cmd);
    }
    void AddRect(const ImVec2& a, const ImVec2& b, ImU32 col, float rounding=0, int flags=0, float thickness=1.0f) {
        (void)rounding; (void)flags;
        DrawCmd cmd;
        cmd.type = DRAW_RECT; cmd.x1 = a.x; cmd.y1 = a.y; cmd.x2 = b.x; cmd.y2 = b.y;
        cmd.color = col; cmd.thickness = thickness;
        commands.push_back(cmd);
    }
    void AddRectFilled(const ImVec2& a, const ImVec2& b, ImU32 col, float rounding=0, int flags=0) {
        (void)rounding; (void)flags;
        DrawCmd cmd;
        cmd.type = DRAW_RECT_FILLED; cmd.x1 = a.x; cmd.y1 = a.y; cmd.x2 = b.x; cmd.y2 = b.y;
        cmd.color = col;
        commands.push_back(cmd);
    }
    void AddRectFilledMultiColor(const ImVec2& a, const ImVec2& b, ImU32 col_upr, ImU32 col_upl, ImU32 col_dwl, ImU32 col_dwr) {
        AddRectFilled(a, b, col_upr);
    }
    void AddCircleFilled(const ImVec2& center, float radius, ImU32 col, int segments=0) {
        (void)segments;
        DrawCmd cmd;
        cmd.type = DRAW_CIRCLE_FILLED; cmd.x1 = center.x; cmd.y1 = center.y; cmd.radius = radius;
        cmd.color = col;
        commands.push_back(cmd);
    }
    void AddCircle(const ImVec2& center, float radius, ImU32 col, int segments=0, float thickness=1.0f) {
        (void)segments;
        DrawCmd cmd;
        cmd.type = DRAW_CIRCLE; cmd.x1 = center.x; cmd.y1 = center.y; cmd.radius = radius;
        cmd.color = col; cmd.thickness = thickness;
        commands.push_back(cmd);
    }
    void AddTriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 col) {
        DrawCmd cmd;
        cmd.type = DRAW_TRIANGLE_FILLED;
        cmd.x1 = a.x; cmd.y1 = a.y; cmd.x2 = b.x; cmd.y2 = b.y; cmd.x3 = c.x; cmd.y3 = c.y;
        cmd.color = col;
        commands.push_back(cmd);
    }
    void AddImage(ImTextureID tex, const ImVec2& a, const ImVec2& b, const ImVec2& uv0=ImVec2(0,0), const ImVec2& uv1=ImVec2(1,1), ImU32 col=0xFFFFFFFF) {
        DrawCmd cmd;
        cmd.type = DRAW_IMAGE; cmd.x1 = a.x; cmd.y1 = a.y; cmd.x2 = b.x; cmd.y2 = b.y;
        cmd.uv_x = uv0.x; cmd.uv_y = uv0.y; cmd.uv_w = uv1.x - uv0.x; cmd.uv_h = uv1.y - uv0.y;
        cmd.tex_id = tex; cmd.color = col;
        commands.push_back(cmd);
    }
    void AddText(const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end=nullptr) {
        DrawCmd cmd;
        cmd.type = DRAW_TEXT; cmd.x1 = pos.x; cmd.y1 = pos.y; cmd.color = col;
        if (text_end) cmd.text = std::string(text_begin, text_end - text_begin);
        else cmd.text = text_begin ? text_begin : "";
        commands.push_back(cmd);
    }
    void AddText(const ImFont* font, float size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end=nullptr, float wrap_width=0.0f, const ImVec4* cpu_fine_clip=nullptr) {
        (void)font; (void)size; (void)wrap_width; (void)cpu_fine_clip;
        AddText(pos, col, text_begin, text_end);
    }
    void PathLineTo(const ImVec2& p) {
        if (path_pts.empty() || !(path_pts.back() == p)) path_pts.push_back(p);
    }
    void PathStroke(ImU32 col, bool closed=false, float thickness=1.0f) {
        if (path_pts.empty()) return;
        DrawCmd cmd;
        cmd.type = DRAW_PATH; cmd.color = col; cmd.thickness = thickness; cmd.closed = closed;
        cmd.path_pts = path_pts;
        cmd.filled = false;
        commands.push_back(cmd);
        path_pts.clear();
    }
    void PathFillConvex(ImU32 col) {
        if (path_pts.size() < 3) { path_pts.clear(); return; }
        DrawCmd cmd;
        cmd.type = DRAW_PATH; cmd.color = col; cmd.filled = true;
        cmd.path_pts = path_pts;
        commands.push_back(cmd);
        path_pts.clear();
    }
    void Clear() { commands.clear(); clip_rect_min = ImVec2(0,0); clip_rect_max = ImVec2(0,0); }
    void PushClipRect(const ImVec2& min, const ImVec2& max, bool intersect_with_current=false) {
        (void)intersect_with_current;
        clip_rect_min = min; clip_rect_max = max;
    }
    void PopClipRect() {}
private:
    std::vector<ImVec2> path_pts;
};

// ─── Font / Texture Atlas ─────────────────────────────────────────────
struct ImFontGlyph {
    uint16_t x, y, w, h;
    float x_off, y_off, x_adv;
};
struct ImFont {
    std::string name;
    float size;
    GLuint tex_id;
    int tex_w, tex_h;
    float line_height;
    std::map<uint32_t, ImFontGlyph> glyphs;
    
    ImVec2 CalcTextSize(float size, const char* text_begin, const char* text_end=nullptr, bool hide_text_after_double_hash=false, float wrap_width=-1.0f) const {
        (void)size; (void)hide_text_after_double_hash; (void)wrap_width;
        if (!text_begin) return ImVec2(0, line_height);
        float x = 0, max_x = 0;
        float y = 0;
        for (const char* p = text_begin; text_end ? p < text_end : *p; ++p) {
            if (*p == '\n') { y += line_height; max_x = std::max(max_x, x); x = 0; continue; }
            auto it = glyphs.find((uint32_t)(unsigned char)*p);
            if (it != glyphs.end()) x += it->second.x_adv;
            else x += 10;
        }
        max_x = std::max(max_x, x);
        return ImVec2(max_x, y + line_height);
    }
};

// ─── Font Atlas ───────────────────────────────────────────────────────
class ImFontAtlas {
public:
    ImFont* Fonts = nullptr;
    ImTextureID TexID = 0;
    unsigned char* m_font_data;
    int m_font_data_size;
    stbtt_fontinfo m_font_info;
    
    ImFont* AddFontFromMemoryTTF(void* data, int size, float size_pixels, const ImFontConfig* cfg=nullptr, const ImWchar* glyph_ranges=nullptr) {
        (void)cfg; (void)glyph_ranges;
        if (!Fonts) Fonts = new ImFont();
        Fonts->size = size_pixels;
        Fonts->name = "Custom";
        m_font_data = (unsigned char*)data;
        m_font_data_size = size;
        return Fonts;
    }
    
    bool Build() {
        if (!Fonts) return false;
        int font_height = (int)(Fonts->size * 1.5f);
        if (font_height < 12) font_height = 12;
        if (font_height > 128) font_height = 128;
        int atlas_w = 512;
        int atlas_h = 512;
        unsigned char* bitmap = new unsigned char[atlas_w * atlas_h];
        memset(bitmap, 0, atlas_w * atlas_h);
        int x = 2, y = 2;
        int max_row_h = 0;
        float scale = stbtt_ScaleForPixelHeight(&m_font_info, (float)font_height);
        
        // Try to use stb_truetype
        bool use_stb = false;
        if (m_font_data_size > 0) {
            int result = stbtt_InitFont(&m_font_info, m_font_data, 0);
            use_stb = (result != 0);
        }
        
        if (use_stb) {
            int ascent, descent, lineGap;
            stbtt_GetFontVMetrics(&m_font_info, &ascent, &descent, &lineGap);
            Fonts->line_height = (float)(ascent - descent + lineGap) * scale;
            for (int c = 32; c < 127; c++) {
                int adv, lsb;
                int x0, y0, x1, y1;
                stbtt_GetCodepointHMetrics(&m_font_info, c, &adv, &lsb);
                stbtt_GetCodepointBitmapBox(&m_font_info, c, scale, scale, &x0, &y0, &x1, &y1);
                int gw = x1 - x0;
                int gh = y1 - y0;
                if (gw <= 0 || gh <= 0) {
                    ImFontGlyph g;
                    g.x = 0; g.y = 0; g.w = 0; g.h = 0;
                    g.x_off = 0; g.y_off = (float)(int)(ascent * scale);
                    g.x_adv = (float)(int)(adv * scale);
                    Fonts->glyphs[(uint32_t)c] = g;
                    continue;
                }
                if (x + gw + 2 >= atlas_w) { x = 2; y += max_row_h + 2; max_row_h = 0; }
                if (y + gh + 2 >= atlas_h) break;
                unsigned char* glyph_bitmap = new unsigned char[gw * gh];
                memset(glyph_bitmap, 0, gw * gh);
                stbtt_MakeCodepointBitmap(&m_font_info, glyph_bitmap, gw, gh, gw, scale, scale, c);
                for (int py = 0; py < gh && y + py < atlas_h; py++) {
                    for (int px = 0; px < gw && x + px < atlas_w; px++) {
                        bitmap[(y + py) * atlas_w + (x + px)] = glyph_bitmap[py * gw + px];
                    }
                }
                ImFontGlyph g;
                g.x = x; g.y = y; g.w = gw; g.h = gh;
                g.x_off = (float)x0;
                g.y_off = (float)(int)(ascent * scale) + y0;
                g.x_adv = (float)(int)(adv * scale);
                Fonts->glyphs[(uint32_t)c] = g;
                x += gw + 2;
                max_row_h = std::max(max_row_h, gh);
                delete[] glyph_bitmap;
            }
        } else {
            // Fallback: simple block font
            float cell_w = Fonts->size * 0.7f;
            float cell_h = Fonts->size;
            Fonts->line_height = cell_h + 2;
            for (int c = 32; c < 127; c++) {
                if (x + (int)cell_w + 1 >= atlas_w) { x = 2; y += (int)cell_h + 1; }
                if (y + (int)cell_h + 1 >= atlas_h) break;
                ImFontGlyph g;
                g.x = x; g.y = y; g.w = (uint16_t)cell_w; g.h = (uint16_t)cell_h;
                g.x_off = 0; g.y_off = 0; g.x_adv = cell_w * 0.7f;
                Fonts->glyphs[(uint32_t)c] = g;
                for (int py = 0; py < (int)cell_h && y + py < atlas_h; py++) {
                    for (int px = 0; px < (int)cell_w && x + px < atlas_w; px++) {
                        bitmap[(y + py) * atlas_w + (x + px)] = 200;
                    }
                }
                x += (int)cell_w + 1;
            }
            Fonts->line_height = cell_h + 2;
        }
        Fonts->tex_w = atlas_w;
        Fonts->tex_h = atlas_h;
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, atlas_w, atlas_h, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap);
        glBindTexture(GL_TEXTURE_2D, 0);
        Fonts->tex_id = tex;
        TexID = (ImTextureID)(intptr_t)tex;
        delete[] bitmap;
        return true;
    }
    
    void Clear() { if (Fonts) delete Fonts; Fonts = nullptr; }
};

struct ImFontConfig {
    bool FontDataOwnedByAtlas;
    ImFontConfig() : FontDataOwnedByAtlas(false) {}
};

typedef uint16_t ImWchar;

// ─── IO ───────────────────────────────────────────────────────────────
struct ImGuiIO {
    ImVec2 DisplaySize;
    float DeltaTime;
    ImVec2 MousePos;
    bool MouseDown[5];
    float FontGlobalScale;
    const char* IniFilename;
    const char* LogFilename;
    ImFontAtlas* Fonts;
    bool WantCaptureMouse;
    bool WantTextInput;
    
    ImGuiIO() : DeltaTime(1.0f/60.0f), FontGlobalScale(1.0f), IniFilename(nullptr), LogFilename(nullptr),
                Fonts(nullptr), WantCaptureMouse(false), WantTextInput(false) {
        memset(MouseDown, 0, sizeof(MouseDown));
    }
};

// ─── Main Viewport ────────────────────────────────────────────────────
struct ImGuiViewport {
    ImVec2 GetCenter() const { return ImVec2(DisplaySize.x * 0.5f, DisplaySize.y * 0.5f); }
    ImVec2 DisplaySize;
    ImVec2 WorkPos;
    ImVec2 WorkSize;
    ImGuiViewport() : WorkPos(0,0), WorkSize(0,0) {}
};

// ─── Window struct ─────────────────────────────────────────────────
struct ImGuiWindow {
    ImVec2 Pos;
    ImVec2 Size;
    ImDrawList* DrawList;
};

// ─── Clip Rect Stack ──────────────────────────────────────────────────
struct ClipRect { ImVec2 min, max; };

// ─── Draw Flags ────────────────────────────────────────────────
enum ImDrawFlags_ {
    ImDrawFlags_RoundCornersAll = 1,
    ImDrawFlags_RoundCornersLeft = 2,
    ImDrawFlags_RoundCornersNone = 4,
    ImDrawFlags_RoundCornersTop = 8,
    ImDrawFlags_RoundCornersBottom = 16,
};

// ─── Style Colors ─────────────────────────────────────────────────────
struct ImGuiStyle {
    ImVec4 Colors[ImGuiCol_COUNT];
    float WindowBorderSize, ChildBorderSize, PopupBorderSize, FrameBorderSize, TabBorderSize, TabBarBorderSize;
    float WindowRounding, ChildRounding, FrameRounding, PopupRounding, ScrollbarRounding, GrabRounding, TabRounding;
    ImVec2 WindowPadding, FramePadding, CellPadding, ItemSpacing, ItemInnerSpacing, TouchExtraPadding;
    float IndentSpacing, ScrollbarSize, GrabMinSize;
    
    void ScaleAllSizes(float factor) {
        WindowBorderSize *= factor; ChildBorderSize *= factor; PopupBorderSize *= factor;
        FrameBorderSize *= factor; TabBorderSize *= factor;
        WindowRounding *= factor; ChildRounding *= factor; FrameRounding *= factor;
        PopupRounding *= factor; ScrollbarRounding *= factor; GrabRounding *= factor; TabRounding *= factor;
        WindowPadding.x *= factor; WindowPadding.y *= factor;
        FramePadding.x *= factor; FramePadding.y *= factor;
        CellPadding.x *= factor; CellPadding.y *= factor;
        ItemSpacing.x *= factor; ItemSpacing.y *= factor;
        ItemInnerSpacing.x *= factor; ItemInnerSpacing.y *= factor;
        IndentSpacing *= factor; ScrollbarSize *= factor; GrabMinSize *= factor;
    }
    
    ImGuiStyle() {
        WindowBorderSize = ChildBorderSize = PopupBorderSize = FrameBorderSize = TabBorderSize = 2;
        TabBarBorderSize = 0;
        WindowRounding = 7; ChildRounding = 4; FrameRounding = 3; PopupRounding = 7;
        ScrollbarRounding = 9; GrabRounding = 3; TabRounding = 4;
        WindowPadding = ImVec2(8,8); FramePadding = ImVec2(5,2); CellPadding = ImVec2(6,6);
        ItemSpacing = ImVec2(6,6); ItemInnerSpacing = ImVec2(6,6);
        TouchExtraPadding = ImVec2(0,0);
        IndentSpacing = 25; ScrollbarSize = 10; GrabMinSize = 10;
        for (int i = 0; i < ImGuiCol_COUNT; i++)
            Colors[i] = ImVec4(0,0,0,1);
    }
};

// ─── Window Flags & Conditions ────────────────────────────────────────
enum ImGuiCond_ {
    ImGuiCond_None = 0,
    ImGuiCond_Always = 1,
    ImGuiCond_Once = 2,
    ImGuiCond_FirstUseEver = 4,
    ImGuiCond_Appearing = 8,
};

enum ImGuiWindowFlags_ {
    ImGuiWindowFlags_None = 0,
    ImGuiWindowFlags_NoTitleBar = 1,
    ImGuiWindowFlags_NoResize = 2,
    ImGuiWindowFlags_NoMove = 4,
    ImGuiWindowFlags_NoCollapse = 8,
    ImGuiWindowFlags_NoScrollbar = 16,
    ImGuiWindowFlags_NoSavedSettings = 32,
    ImGuiWindowFlags_MenuBar = 64,
    ImGuiWindowFlags_HorizontalScrollbar = 128,
    ImGuiWindowFlags_NoFocusOnAppearing = 256,
    ImGuiWindowFlags_NoBringToFrontOnFocus = 512,
    ImGuiWindowFlags_AlwaysVerticalScrollbar = 1024,
    ImGuiWindowFlags_AlwaysHorizontalScrollbar = 2048,
    ImGuiWindowFlags_AlwaysAutoResize = 4096,
    ImGuiWindowFlags_NoInputs = 8192,
    ImGuiWindowFlags_NavFlattened = 16384,
    ImGuiWindowFlags_ChildWindow = 32768,
    ImGuiWindowFlags_Tooltip = 65536,
    ImGuiWindowFlags_Popup = 131072,
    ImGuiWindowFlags_Modal = 262144,
    ImGuiWindowFlags_ChildMenu = 524288,
};

// ─── Helpers ──────────────────────────────────────────────────────────
template<typename T> inline T ImClamp(T v, T mn, T mx) { return (v < mn) ? mn : (v > mx) ? mx : v; }
template<typename T> inline T ImLerp(T a, T b, float t) { return a + (b - a) * t; }
template<typename T> inline T ImMin(T a, T b) { return (a < b) ? a : b; }
template<typename T> inline T ImMax(T a, T b) { return (a > b) ? a : b; }
#define IM_ARRAYSIZE(_ARR) ((int)(sizeof(_ARR)/sizeof(*_ARR)))

inline bool isInRect(float x, float y, float rx, float ry, float rw, float rh) {
    return x >= rx && x <= rx+rw && y >= ry && y <= ry+rh;
}

inline int getID() {
    static int s_next_id = 1;
    return s_next_id++;
}


// ─── Internal State ───────────────────────────────────────────────────
struct UIState {
    ImGuiIO io;
    ImGuiStyle style;
    ImGuiViewport main_viewport;
    
    struct Window {
        std::string name;
        ImVec2 pos, size;
        ImVec2 cursor_pos;
        ImVec2 content_avail;
        ImVec2 window_pos;
        ImVec2 item_rect_min;
        ImVec2 item_rect_max;
        ImDrawList* draw_list;
        float font_scale;
        bool open;
        std::string tab_bar_name;
        int active_tab;
        bool has_clip;
        ImVec2 clip_min, clip_max;
    };
    
    std::vector<Window> window_stack;
    ImDrawList* current_draw_list;
    ImDrawList bg_draw_list;
    ImDrawList fg_draw_list;
    
    std::vector<int> id_stack;
    float touch_x, touch_y;
    bool touch_down;
    bool touch_just_pressed;
    bool touch_just_released;
    int hot_item;
    int active_item;
    int next_id;
    bool item_just_activated;
    float last_item_x, last_item_y, last_item_width;
    float frame_height;
    ImVec2 last_separator_line_end;
    
    // Combo
    bool combo_open;
    int combo_selected;
    std::string combo_label;
    ImVec2 combo_pos;
    float combo_width;
    
    // Text input
    bool textinput_active;
    std::string textinput_buffer;
    std::string textinput_label;
    ImVec2 textinput_pos;
    float textinput_width;
    char textinput_last_char;
    
    // Next window pos
    bool has_next_window_pos;
    ImVec2 next_window_pos;
    
    std::map<int, float> scroll_y;
    bool needs_sort;
    
    UIState() : current_draw_list(nullptr), touch_down(false), touch_just_pressed(false),
                touch_just_released(false), hot_item(0), active_item(0), next_id(1),
                item_just_activated(false), last_item_x(0), last_item_y(0), last_item_width(0),
                frame_height(0), combo_open(false), combo_selected(0),
                textinput_active(false), textinput_last_char(0), has_next_window_pos(false),
                needs_sort(false) {
        io.DisplaySize = ImVec2(0,0);
        io.Fonts = new ImFontAtlas();
        io.IniFilename = "";
        io.LogFilename = "";
    }
};

static UIState s_ui;

// ─── OpenGL State ─────────────────────────────────────────────────────
static GLuint s_ui_vao = 0, s_ui_vbo = 0, s_ui_ebo = 0;
static GLuint s_ui_program = 0;
static bool s_ui_initialized = false;

struct UIVertex { float x, y, u, v; uint8_t r, g, b, a; };

static const char* ui_vertex_shader = 
    "attribute vec2 aPos;\nattribute vec2 aUV;\nattribute vec4 aColor;\n"
    "varying vec2 vUV;\nvarying vec4 vColor;\nuniform vec2 uScreenSize;\n"
    "void main() {\n"
    "   vec2 p = aPos / uScreenSize * 2.0 - 1.0;\n"
    "   gl_Position = vec4(p.x, -p.y, 0.0, 1.0);\n"
    "   vUV = aUV;\n   vColor = aColor;\n}";

static const char* ui_fragment_shader = 
    "precision mediump float;\nvarying vec2 vUV;\nvarying vec4 vColor;\n"
    "uniform sampler2D uTex;\nuniform bool uUseTex;\n"
    "void main() {\n"
    "   if (uUseTex) { vec4 texel = texture2D(uTex, vUV); gl_FragColor = vColor * texel.a; }\n"
    "   else { gl_FragColor = vColor; }\n}";

static GLuint createShader(GLenum type, const char* src) {
    GLuint sh = glCreateShader(type);
    glShaderSource(sh, 1, &src, nullptr);
    glCompileShader(sh);
    return sh;
}

static void initGLShaders() {
    GLuint vs = createShader(GL_VERTEX_SHADER, ui_vertex_shader);
    GLuint fs = createShader(GL_FRAGMENT_SHADER, ui_fragment_shader);
    s_ui_program = glCreateProgram();
    glAttachShader(s_ui_program, vs);
    glAttachShader(s_ui_program, fs);
    glLinkProgram(s_ui_program);
    glDeleteShader(vs); glDeleteShader(fs);
    glGenVertexArrays(1, &s_ui_vao);
    glGenBuffers(1, &s_ui_vbo);
    glGenBuffers(1, &s_ui_ebo);
    s_ui_initialized = true;
}

static void renderDrawList(ImDrawList* dl) {
    if (dl->commands.empty() || !s_ui_initialized) {
        if (!s_ui_initialized) initGLShaders();
        if (dl->commands.empty()) return;
    }
    
    glUseProgram(s_ui_program);
    glUniform2f(glGetUniformLocation(s_ui_program, "uScreenSize"), 
                s_ui.io.DisplaySize.x, s_ui.io.DisplaySize.y);
    GLint uTexLoc = glGetUniformLocation(s_ui_program, "uTex");
    GLint uUseTexLoc = glGetUniformLocation(s_ui_program, "uUseTex");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    std::vector<UIVertex> vertices;
    
    for (auto& cmd : dl->commands) {
        vertices.clear();
        auto c = ColorConvertU32ToFloat4(cmd.color);
        uint8_t r=c.x*255,g=c.y*255,b=c.z*255,a=c.w*255;
        
        switch (cmd.type) {
            case DRAW_LINE: {
                UIVertex v[2] = {{cmd.x1,cmd.y1,0,0,r,g,b,a},{cmd.x2,cmd.y2,0,0,r,g,b,a}};
                glUniform1i(uUseTexLoc, 0);
                glLineWidth(cmd.thickness > 0 ? cmd.thickness : 1);
                glBindVertexArray(s_ui_vao);
                glBindBuffer(GL_ARRAY_BUFFER, s_ui_vbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_DYNAMIC_DRAW);
                glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)0);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)(sizeof(float)*2));
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(2,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(UIVertex),(void*)(sizeof(float)*4));
                glEnableVertexAttribArray(2);
                glDrawArrays(GL_LINES,0,2);
                break;
            }
            case DRAW_RECT:
            case DRAW_RECT_FILLED: {
                float x1=cmd.x1,y1=cmd.y1,x2=cmd.x2,y2=cmd.y2;
                UIVertex verts[4] = {{x1,y1,0,0,r,g,b,a},{x2,y1,0,0,r,g,b,a},{x2,y2,0,0,r,g,b,a},{x1,y2,0,0,r,g,b,a}};
                GLubyte idx[6] = {0,1,2,0,2,3};
                glUniform1i(uUseTexLoc, 0);
                glBindVertexArray(s_ui_vao);
                glBindBuffer(GL_ARRAY_BUFFER, s_ui_vbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ui_ebo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_DYNAMIC_DRAW);
                glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)0);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)(sizeof(float)*2));
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(2,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(UIVertex),(void*)(sizeof(float)*4));
                glEnableVertexAttribArray(2);
                if (cmd.type == DRAW_RECT_FILLED) glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,0);
                else glDrawArrays(GL_LINE_LOOP,0,4);
                break;
            }
            case DRAW_CIRCLE:
            case DRAW_CIRCLE_FILLED: {
                int segs = 32;
                for (int i = 0; i <= segs; i++) {
                    float ang = (float)i / segs * 6.283185f;
                    vertices.push_back({cmd.x1+cosf(ang)*cmd.radius,cmd.y1+sinf(ang)*cmd.radius,0,0,r,g,b,a});
                }
                glUniform1i(uUseTexLoc, 0);
                glBindVertexArray(s_ui_vao);
                glBindBuffer(GL_ARRAY_BUFFER, s_ui_vbo);
                glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(UIVertex), vertices.data(), GL_DYNAMIC_DRAW);
                glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)0);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)(sizeof(float)*2));
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(2,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(UIVertex),(void*)(sizeof(float)*4));
                glEnableVertexAttribArray(2);
                if (cmd.type == DRAW_CIRCLE_FILLED) {
                    std::vector<GLubyte> idxv(segs*3);
                    for (int i=0;i<segs;i++){idxv[i*3]=0;idxv[i*3+1]=i+1;idxv[i*3+2]=i+2;}
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,s_ui_ebo);
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER,idxv.size(),idxv.data(),GL_DYNAMIC_DRAW);
                    glDrawElements(GL_TRIANGLES,segs*3,GL_UNSIGNED_BYTE,0);
                } else glDrawArrays(GL_LINE_STRIP,0,vertices.size());
                vertices.clear();
                break;
            }
            case DRAW_TRIANGLE_FILLED: {
                UIVertex v[3]={{cmd.x1,cmd.y1,0,0,r,g,b,a},{cmd.x2,cmd.y2,0,0,r,g,b,a},{cmd.x3,cmd.y3,0,0,r,g,b,a}};
                glUniform1i(uUseTexLoc, 0);
                glBindVertexArray(s_ui_vao);
                glBindBuffer(GL_ARRAY_BUFFER,s_ui_vbo);
                glBufferData(GL_ARRAY_BUFFER,sizeof(v),v,GL_DYNAMIC_DRAW);
                glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)0);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)(sizeof(float)*2));
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(2,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(UIVertex),(void*)(sizeof(float)*4));
                glEnableVertexAttribArray(2);
                glDrawArrays(GL_TRIANGLES,0,3);
                break;
            }
            case DRAW_IMAGE: {
                float x1=cmd.x1,y1=cmd.y1,x2=cmd.x2,y2=cmd.y2;
                float u1=cmd.uv_x,v1=cmd.uv_y,u2=cmd.uv_x+cmd.uv_w,v2=cmd.uv_y+cmd.uv_h;
                UIVertex verts[4]={{x1,y1,u1,v1,r,g,b,a},{x2,y1,u2,v1,r,g,b,a},{x2,y2,u2,v2,r,g,b,a},{x1,y2,u1,v2,r,g,b,a}};
                GLubyte idx[6]={0,1,2,0,2,3};
                glUniform1i(uUseTexLoc,1);
                glUniform1i(uTexLoc,0);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D,(GLuint)(intptr_t)cmd.tex_id);
                glBindVertexArray(s_ui_vao);
                glBindBuffer(GL_ARRAY_BUFFER,s_ui_vbo);
                glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,s_ui_ebo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(idx),idx,GL_DYNAMIC_DRAW);
                glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)0);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)(sizeof(float)*2));
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(2,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(UIVertex),(void*)(sizeof(float)*4));
                glEnableVertexAttribArray(2);
                glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,0);
                break;
            }
            case DRAW_TEXT: {
                if (cmd.text.empty() || !s_ui.io.Fonts->Fonts) break;
                GLuint font_tex = s_ui.io.Fonts->Fonts->tex_id;
                float char_w = s_ui.io.Fonts->Fonts->size * 0.6f;
                float char_h = s_ui.io.Fonts->Fonts->size;
                float x = cmd.x1, y = cmd.y1;
                
                glUniform1i(uUseTexLoc,1);
                glUniform1i(uTexLoc,0);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, font_tex);
                
                for (size_t si = 0; si < cmd.text.size(); si++) {
                    unsigned char ch = (unsigned char)cmd.text[si];
                    if (ch == '\n') { x = cmd.x1; y += char_h + 2; continue; }
                    if (ch < 32) continue;
                    
                    auto it = s_ui.io.Fonts->Fonts->glyphs.find(ch);
                    if (it == s_ui.io.Fonts->Fonts->glyphs.end()) continue;
                    auto& g = it->second;
                    if (g.w == 0 || g.h == 0) { x += g.x_adv; continue; }
                    
                    float tx1 = x + g.x_off;
                    float ty1 = y + g.y_off;
                    float tx2 = tx1 + g.w;
                    float ty2 = ty1 + g.h;
                    
                    float tu1 = (float)g.x / s_ui.io.Fonts->Fonts->tex_w;
                    float tv1 = (float)g.y / s_ui.io.Fonts->Fonts->tex_h;
                    float tu2 = (float)(g.x + g.w) / s_ui.io.Fonts->Fonts->tex_w;
                    float tv2 = (float)(g.y + g.h) / s_ui.io.Fonts->Fonts->tex_h;
                    
                    UIVertex verts[4] = {
                        {tx1,ty1,tu1,tv1,r,g,b,a},{tx2,ty1,tu2,tv1,r,g,b,a},
                        {tx2,ty2,tu2,tv2,r,g,b,a},{tx1,ty2,tu1,tv2,r,g,b,a}
                    };
                    GLubyte idx[6] = {0,1,2,0,2,3};
                    
                    glBindVertexArray(s_ui_vao);
                    glBindBuffer(GL_ARRAY_BUFFER,s_ui_vbo);
                    glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_DYNAMIC_DRAW);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,s_ui_ebo);
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(idx),idx,GL_DYNAMIC_DRAW);
                    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)0);
                    glEnableVertexAttribArray(0);
                    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)(sizeof(float)*2));
                    glEnableVertexAttribArray(1);
                    glVertexAttribPointer(2,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(UIVertex),(void*)(sizeof(float)*4));
                    glEnableVertexAttribArray(2);
                    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,0);
                    
                    x += g.x_adv + 1;
                }
                break;
            }
            case DRAW_PATH: {
                if (cmd.path_pts.size() < 2) break;
                vertices.clear();
                for (auto& pt : cmd.path_pts)
                    vertices.push_back({pt.x,pt.y,0,0,r,g,b,a});
                glUniform1i(uUseTexLoc,0);
                glBindVertexArray(s_ui_vao);
                glBindBuffer(GL_ARRAY_BUFFER,s_ui_vbo);
                glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(UIVertex),vertices.data(),GL_DYNAMIC_DRAW);
                glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)0);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(UIVertex),(void*)(sizeof(float)*2));
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(2,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(UIVertex),(void*)(sizeof(float)*4));
                glEnableVertexAttribArray(2);
                if (cmd.filled) glDrawArrays(GL_TRIANGLE_FAN,0,vertices.size());
                else if (cmd.closed) glDrawArrays(GL_LINE_LOOP,0,vertices.size());
                else glDrawArrays(GL_LINE_STRIP,0,vertices.size());
                vertices.clear();
                break;
            }
        }
    }
    glDisable(GL_BLEND);
    dl->commands.clear();
}

// ─── Widget Drawing Primitives ───────────────────────────────────────
static void drawCheckbox(float x, float y, float size, bool checked, ImU32 border, ImU32 bg, ImU32 check) {
    auto& dl = s_ui.fg_draw_list;
    dl.AddRectFilled(ImVec2(x,y),ImVec2(x+size,y+size),bg,3);
    dl.AddRect(ImVec2(x,y),ImVec2(x+size,y+size),border,3,0,2);
    if (checked) { float s=size*0.25f; dl.AddRectFilled(ImVec2(x+s,y+s),ImVec2(x+size-s,y+size-s),check,2); }
}
static void drawButton(float x, float y, float w, float h, ImU32 bg, ImU32 border) {
    auto& dl = s_ui.fg_draw_list;
    dl.AddRectFilled(ImVec2(x,y),ImVec2(x+w,y+h),bg,3);
    dl.AddRect(ImVec2(x,y),ImVec2(x+w,y+h),border,3,0,2);
}
static void drawSlider(float x, float y, float w, float h, float frac, ImU32 bg, ImU32 fill, ImU32 border) {
    auto& dl = s_ui.fg_draw_list;
    dl.AddRectFilled(ImVec2(x,y),ImVec2(x+w,y+h),bg,3);
    if (frac > 0) dl.AddRectFilled(ImVec2(x,y),ImVec2(x+frac*w,y+h),fill,3);
    dl.AddRect(ImVec2(x,y),ImVec2(x+w,y+h),border,3,0,2);
}
static void drawComboBox(float x, float y, float w, float h, const std::string& preview, bool open, ImU32 bg, ImU32 border, ImU32 text_col) {
    (void)open;
    auto& dl = s_ui.fg_draw_list;
    dl.AddRectFilled(ImVec2(x,y),ImVec2(x+w,y+h),bg,3);
    dl.AddRect(ImVec2(x,y),ImVec2(x+w,y+h),border,3,0,2);
    float ax = x+w-h, ay = y+h/2;
    dl.AddTriangleFilled(ImVec2(ax-4,ay-2),ImVec2(ax+4,ay-2),ImVec2(ax,ay+3),text_col);
    if (!preview.empty()) dl.AddText(ImVec2(x+5,y+2),text_col,preview.c_str());
}


// ─── ImGui Namespace ──────────────────────────────────────────────────
namespace ImGui {

ImGuiIO& GetIO() { return s_ui.io; }
ImGuiStyle& GetStyle() { return s_ui.style; }
ImGuiViewport* GetMainViewport() { 
    s_ui.main_viewport.DisplaySize = s_ui.io.DisplaySize;
    return &s_ui.main_viewport; 
}
ImDrawList* GetWindowDrawList() { return &s_ui.fg_draw_list; }
ImDrawList* GetBackgroundDrawList() { return &s_ui.bg_draw_list; }
ImDrawList* GetForegroundDrawList(ImGuiViewport* viewport=nullptr) { (void)viewport; return &s_ui.fg_draw_list; }
float GetFontSize() { return 14.0f * s_ui.io.FontGlobalScale; }
float GetWindowHeight() {
    if (s_ui.window_stack.empty()) return 0;
    return s_ui.window_stack.back().size.y;
}

static ImGuiWindow s_dummy_window;
ImGuiWindow* GetCurrentWindow() {
    if (!s_ui.window_stack.empty()) {
        auto& w = s_ui.window_stack.back();
        s_dummy_window.Pos = w.pos;
        s_dummy_window.Size = w.size;
        s_dummy_window.DrawList = &s_ui.fg_draw_list;
    } else {
        s_dummy_window.Pos = ImVec2(0,0);
        s_dummy_window.Size = ImVec2(400,300);
        s_dummy_window.DrawList = &s_ui.fg_draw_list;
    }
    return &s_dummy_window;
}

ImVec2 CalcTextSize(const char* text, const char* text_end=nullptr, bool hide_text_after_double_hash=false, float wrap_width=-1.0f) {
    if (s_ui.io.Fonts && s_ui.io.Fonts->Fonts)
        return s_ui.io.Fonts->Fonts->CalcTextSize(s_ui.io.Fonts->Fonts->size, text, text_end, hide_text_after_double_hash, wrap_width);
    if (!text) return ImVec2(0,14);
    float len = text_end ? (text_end - text) : strlen(text);
    return ImVec2(len * 9, 14);
}
ImU32 GetColorU32(ImU32 col) { return col; }
ImU32 GetColorU32(const ImVec4& col) { return ColorConvertFloat4ToU32(col); }
ImVec2 GetItemRectMin() {
    if (s_ui.window_stack.empty()) return ImVec2(0,0);
    return s_ui.window_stack.back().item_rect_min;
}
ImVec2 GetCursorScreenPos() {
    if (s_ui.window_stack.empty()) return ImVec2(0,0);
    auto& w = s_ui.window_stack.back();
    return ImVec2(w.pos.x + w.cursor_pos.x, w.pos.y + w.cursor_pos.y);
}
ImVec2 GetWindowPos() {
    if (s_ui.window_stack.empty()) return ImVec2(0,0);
    return s_ui.window_stack.back().pos;
}
ImVec2 GetContentRegionAvail() {
    if (s_ui.window_stack.empty()) return ImVec2(200,200);
    auto& w = s_ui.window_stack.back();
    return ImVec2(w.size.x - w.cursor_pos.x - 20, w.size.y - w.cursor_pos.y - 20);
}

float ImSaturate(float v) { return (v < 0.0f) ? 0.0f : (v > 1.0f) ? 1.0f : v; }
double GetTime() {
    static auto start = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(now - start).count();
}

// ─── Input ────────────────────────────────────────────────────────────
void AddInputCharacter(unsigned int c) {
    if (s_ui.textinput_active && c >= 32 && c < 127) s_ui.textinput_buffer += (char)c;
}
void AddInputCharactersUTF8(const char* utf8_chars) {
    if (s_ui.textinput_active && utf8_chars) s_ui.textinput_buffer += utf8_chars;
}

// ─── ID Stack ─────────────────────────────────────────────────────────
void PushID(const char* str_id) {
    int h = 0;
    for (const char* p = str_id; *p; p++) h = h * 31 + *p;
    s_ui.id_stack.push_back(h);
}
void PushID(int int_id) { s_ui.id_stack.push_back(int_id); }
void PopID() { if (!s_ui.id_stack.empty()) s_ui.id_stack.pop_back(); }

// ─── Style ────────────────────────────────────────────────────────────
void PushStyleColor(int idx, const ImVec4& col) { (void)idx; (void)col; }
void PopStyleColor(int count=1) { (void)count; }
void PushStyleVar(int idx, float val) { (void)idx; (void)val; }
void PushStyleVar(int idx, const ImVec2& val) { (void)idx; (void)val; }
void PopStyleVar(int count=1) { (void)count; }
void SetWindowFontScale(float scale) { 
    if (!s_ui.window_stack.empty()) s_ui.window_stack.back().font_scale = scale;
}
void PushItemWidth(float width) { (void)width; }
void PopItemWidth() {}

// ─── Layout ───────────────────────────────────────────────────────────
void SetCursorPos(const ImVec2& pos) {
    if (!s_ui.window_stack.empty()) s_ui.window_stack.back().cursor_pos = pos;
}
void SameLine(float offset_from_start=0, float spacing=-1) {
    (void)offset_from_start;
    if (s_ui.window_stack.empty()) return;
    auto& w = s_ui.window_stack.back();
    w.cursor_pos.x = s_ui.last_item_x + s_ui.last_item_width + (spacing > 0 ? spacing : 8);
}
void Separator() {
    if (s_ui.window_stack.empty()) return;
    auto& w = s_ui.window_stack.back();
    float y = w.cursor_pos.y + 8;
    w.cursor_pos.y = y + 4;
    s_ui.fg_draw_list.AddLine(ImVec2(w.pos.x+10, y), ImVec2(w.pos.x+w.size.x-10, y), 
        ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Separator]), 2);
}
void Dummy(const ImVec2& size) {
    if (s_ui.window_stack.empty()) return;
    auto& w = s_ui.window_stack.back();
    w.cursor_pos.x += size.x;
    w.cursor_pos.y += size.y;
    s_ui.last_item_x = w.cursor_pos.x - size.x;
    s_ui.last_item_y = w.cursor_pos.y - size.y;
    s_ui.last_item_width = size.x;
}
void NewLine() {
    if (!s_ui.window_stack.empty()) s_ui.window_stack.back().cursor_pos.y += 18;
}
void BeginGroup() {}
void EndGroup() {}

// ─── Window ───────────────────────────────────────────────────────────
void SetNextWindowPos(const ImVec2& pos, int cond=0, const ImVec2& pivot=ImVec2(0,0)) {
    (void)cond; (void)pivot;
    s_ui.has_next_window_pos = true;
    s_ui.next_window_pos = pos;
}
void SetWindowSize(const ImVec2& size, int cond=0) {
    (void)cond;
    if (!s_ui.window_stack.empty()) s_ui.window_stack.back().size = size;
}

bool Begin(const char* name, bool* p_open=nullptr, int flags=0) {
    (void)flags;
    UIState::Window w;
    w.name = name;
    if (s_ui.has_next_window_pos) {
        w.pos = s_ui.next_window_pos;
        s_ui.has_next_window_pos = false;
    } else {
        w.pos = ImVec2(50, 50);
    }
    w.size = ImVec2(400, 300);
    w.cursor_pos = ImVec2(10, 30);
    w.font_scale = 1.0f;
    w.open = true;
    w.draw_list = &s_ui.fg_draw_list;
    
    ImVec4 bg = s_ui.style.Colors[ImGuiCol_WindowBg];
    ImVec4 border = s_ui.style.Colors[ImGuiCol_Border];
    ImVec4 title = s_ui.style.Colors[ImGuiCol_TitleBgActive];
    
    s_ui.fg_draw_list.AddRectFilled(w.pos, ImVec2(w.pos.x+w.size.x, w.pos.y+w.size.y), 
        ColorConvertFloat4ToU32(bg), s_ui.style.WindowRounding);
    s_ui.fg_draw_list.AddRect(w.pos, ImVec2(w.pos.x+w.size.x, w.pos.y+w.size.y), 
        ColorConvertFloat4ToU32(border), s_ui.style.WindowRounding, 0, s_ui.style.WindowBorderSize);
    s_ui.fg_draw_list.AddRectFilled(w.pos, ImVec2(w.pos.x+w.size.x, w.pos.y+25), 
        ColorConvertFloat4ToU32(title), s_ui.style.WindowRounding, 0);
    s_ui.fg_draw_list.AddText(ImVec2(w.pos.x+w.size.x/2 - strlen(name)*4, w.pos.y+5),
        ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]), name);
    
    s_ui.window_stack.push_back(w);
    return true;
}

void End() {
    if (s_ui.window_stack.empty()) return;
    auto& w = s_ui.window_stack.back();
    s_ui.fg_draw_list.AddLine(ImVec2(w.pos.x, w.pos.y+25), ImVec2(w.pos.x+w.size.x, w.pos.y+25),
        ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Separator]), 2);
    s_ui.window_stack.pop_back();
}

// ─── Tab Bar ──────────────────────────────────────────────────────────
static int g_tab_item_index = 0;
struct TabState {
    std::string bar_id;
    float x_offset;
    int selected_tab;
};
static std::vector<TabState> g_tab_states;

bool BeginTabBar(const char* str_id, int flags=0) {
    (void)flags;
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    w.tab_bar_name = str_id ? str_id : "";
    
    float tab_bar_height = 35;
    s_ui.fg_draw_list.AddRectFilled(
        ImVec2(w.pos.x+2, w.pos.y+27),
        ImVec2(w.pos.x+w.size.x-2, w.pos.y+27+tab_bar_height),
        ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Tab]), 0);
    
    s_ui.window_stack.back().cursor_pos = ImVec2(10, 27 + tab_bar_height + 5);
    g_tab_item_index = 0;
    return true;
}

void EndTabBar() {
    if (s_ui.window_stack.empty()) return;
    auto& w = s_ui.window_stack.back();
    float y = w.pos.y + 27 + 35;
    s_ui.fg_draw_list.AddLine(ImVec2(w.pos.x+5, y), ImVec2(w.pos.x+w.size.x-5, y),
        ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Separator]), 2);
}

bool BeginTabItem(const char* label, bool* p_open=nullptr, int flags=0) {
    (void)p_open; (void)flags;
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    
    std::string bar_id = w.tab_bar_name;
    TabState* ts = nullptr;
    for (auto& t : g_tab_states) { if (t.bar_id == bar_id && !bar_id.empty()) { ts = &t; break; } }
    if (!ts) {
        TabState new_ts;
        new_ts.bar_id = bar_id;
        new_ts.x_offset = 5;
        new_ts.selected_tab = 0;
        g_tab_states.push_back(new_ts);
        ts = &g_tab_states.back();
    }
    
    int my_idx = g_tab_item_index++;
    float tab_w = strlen(label) * 9 + 20;
    float tab_h = 30;
    float tab_y = w.pos.y + 29;
    float this_x = w.pos.x + ts->x_offset;
    
    bool is_hot = isInRect(s_ui.touch_x, s_ui.touch_y, this_x, tab_y, tab_w, tab_h);
    bool is_selected = (my_idx == ts->selected_tab);
    
    if (is_hot && s_ui.touch_just_pressed) { ts->selected_tab = my_idx; is_selected = true; }
    
    ImVec4 tab_col = is_selected ? s_ui.style.Colors[ImGuiCol_TabActive] : 
                     (is_hot ? s_ui.style.Colors[ImGuiCol_TabHovered] : s_ui.style.Colors[ImGuiCol_Tab]);
    ImVec4 text_col = s_ui.style.Colors[ImGuiCol_Text];
    
    s_ui.fg_draw_list.AddRectFilled(ImVec2(this_x, tab_y), ImVec2(this_x+tab_w, tab_y+tab_h), 
        ColorConvertFloat4ToU32(tab_col), 4);
    s_ui.fg_draw_list.AddText(ImVec2(this_x+10, tab_y+7), ColorConvertFloat4ToU32(text_col), label);
    
    s_ui.last_item_x = this_x;
    s_ui.last_item_y = tab_y;
    s_ui.last_item_width = tab_w;
    ts->x_offset += tab_w + 2;
    
    return is_selected;
}

void EndTabItem() {}


// ─── Widgets ──────────────────────────────────────────────────────────
bool Checkbox(const char* label, bool* v) {
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    float box_size = 16;
    float text_offset = box_size + 8;
    
    bool hot = isInRect(s_ui.touch_x, s_ui.touch_y, x, y, box_size + CalcTextSize(label).x + 5, box_size + 4);
    if (hot && s_ui.touch_just_pressed) *v = !(*v);
    
    ImU32 border = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Border]);
    ImU32 bg = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_FrameBg]);
    ImU32 check = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_CheckMark]);
    ImU32 text_col = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]);
    
    drawCheckbox(x, y+2, box_size, *v, border, bg, check);
    s_ui.fg_draw_list.AddText(ImVec2(x+text_offset, y+2), text_col, label);
    
    w.cursor_pos.y += box_size + 6;
    s_ui.last_item_x = x;
    s_ui.last_item_y = y;
    s_ui.last_item_width = text_offset + CalcTextSize(label).x;
    w.item_rect_min = ImVec2(x, y);
    return hot && s_ui.touch_just_pressed;
}

bool Button(const char* label) {
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    float text_w = CalcTextSize(label).x;
    float btn_w = std::max(text_w + 20, 80.0f);
    float btn_h = 28;
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    
    bool hot = isInRect(s_ui.touch_x, s_ui.touch_y, x, y, btn_w, btn_h);
    bool pressed = hot && s_ui.touch_just_pressed;
    
    ImU32 bg = hot ? ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_ButtonHovered]) : 
                     ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Button]);
    ImU32 border = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Border]);
    ImU32 text_col = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]);
    
    drawButton(x, y, btn_w, btn_h, bg, border);
    s_ui.fg_draw_list.AddText(ImVec2(x + btn_w/2 - text_w/2, y + 6), text_col, label);
    
    w.cursor_pos.y += btn_h + 6;
    s_ui.last_item_x = x;
    s_ui.last_item_y = y;
    s_ui.last_item_width = btn_w;
    w.item_rect_min = ImVec2(x, y);
    return pressed;
}

bool Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items=-1) {
    (void)popup_max_height_in_items;
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    float cmb_w = 200;
    float cmb_h = 26;
    float line_h = 22;
    std::string preview = (*current_item >= 0 && *current_item < items_count) ? items[*current_item] : "";
    
    bool hot = isInRect(s_ui.touch_x, s_ui.touch_y, x, y, cmb_w, cmb_h);
    if (hot && s_ui.touch_just_pressed) {
        s_ui.combo_open = !s_ui.combo_open;
        s_ui.combo_selected = *current_item;
        s_ui.combo_label = label;
        s_ui.combo_pos = ImVec2(x, y + cmb_h + 2);
        s_ui.combo_width = cmb_w;
    }
    
    ImU32 bg = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_FrameBg]);
    ImU32 border = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Border]);
    ImU32 text_col = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]);
    
    s_ui.fg_draw_list.AddText(ImVec2(x, y-16), text_col, label);
    drawComboBox(x, y, cmb_w, cmb_h, preview, s_ui.combo_open, bg, border, text_col);
    
    w.cursor_pos.y += cmb_h + 18;
    s_ui.last_item_x = x;
    s_ui.last_item_y = y;
    s_ui.last_item_width = cmb_w;
    
    if (s_ui.combo_open && s_ui.combo_label == label) {
        float list_h = items_count * line_h + 4;
        ImU32 popup_bg = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_PopupBg]);
        ImU32 header_col = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Header]);
        s_ui.fg_draw_list.AddRectFilled(s_ui.combo_pos, ImVec2(s_ui.combo_pos.x+cmb_w, s_ui.combo_pos.y+list_h), popup_bg, 4);
        s_ui.fg_draw_list.AddRect(s_ui.combo_pos, ImVec2(s_ui.combo_pos.x+cmb_w, s_ui.combo_pos.y+list_h), border, 4, 0, 2);
        for (int i = 0; i < items_count; i++) {
            float iy = s_ui.combo_pos.y + i * line_h + 2;
            bool item_hot = isInRect(s_ui.touch_x, s_ui.touch_y, s_ui.combo_pos.x, iy, cmb_w, line_h);
            if (i == s_ui.combo_selected) 
                s_ui.fg_draw_list.AddRectFilled(ImVec2(s_ui.combo_pos.x+2, iy+1), ImVec2(s_ui.combo_pos.x+cmb_w-2, iy+line_h-1), header_col, 2);
            s_ui.fg_draw_list.AddText(ImVec2(s_ui.combo_pos.x+8, iy+3), text_col, items[i]);
            if (item_hot && s_ui.touch_just_pressed) { *current_item = i; s_ui.combo_open = false; }
        }
        if (s_ui.touch_just_pressed) {
            bool in_combo = isInRect(s_ui.touch_x, s_ui.touch_y, x, y, cmb_w, cmb_h);
            bool in_dropdown = isInRect(s_ui.touch_x, s_ui.touch_y, s_ui.combo_pos.x, s_ui.combo_pos.y, cmb_w, items_count * line_h + 4);
            if (!in_combo && !in_dropdown) s_ui.combo_open = false;
        }
    }
    return false;
}

bool DragInt(const char* label, int* v, float v_speed=1.0f, int v_min=0, int v_max=100, const char* display_format="%d", int flags=0) {
    (void)v_speed; (void)flags;
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    float sl_w = 150;
    float sl_h = 20;
    
    s_ui.fg_draw_list.AddText(ImVec2(x, y-14), ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]), label);
    int clamped = std::max(v_min, std::min(v_max, *v));
    float frac = (v_max != v_min) ? (float)(clamped - v_min) / (v_max - v_min) : 0;
    char buf[64]; snprintf(buf, sizeof(buf), display_format, *v);
    
    ImU32 bg = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_FrameBg]);
    ImU32 fill = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_SliderGrab]);
    ImU32 border = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Border]);
    ImU32 text_col = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]);
    drawSlider(x, y, sl_w, sl_h, frac, bg, fill, border);
    s_ui.fg_draw_list.AddText(ImVec2(x+sl_w/2 - strlen(buf)*4, y+2), text_col, buf);
    
    int id = getID();
    if (s_ui.active_item == id) {
        float rel = (s_ui.touch_x - x) / sl_w;
        rel = std::max(0.0f, std::min(1.0f, rel));
        *v = v_min + (int)(rel * (v_max - v_min));
        if (!s_ui.touch_down) s_ui.active_item = 0;
    }
    bool hot = isInRect(s_ui.touch_x, s_ui.touch_y, x, y, sl_w, sl_h);
    if (hot && s_ui.touch_just_pressed) s_ui.active_item = id;
    
    w.cursor_pos.y += sl_h + 18;
    s_ui.last_item_x = x;
    s_ui.last_item_y = y;
    s_ui.last_item_width = sl_w;
    return false;
}

bool DragFloat(const char* label, float* v, float v_speed=0.1f, float v_min=0.0f, float v_max=100.0f, const char* display_format="%.3f", int flags=0) {
    (void)v_speed; (void)flags;
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    float sl_w = 150;
    float sl_h = 20;
    
    s_ui.fg_draw_list.AddText(ImVec2(x, y-14), ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]), label);
    float clamped = std::max(v_min, std::min(v_max, *v));
    float frac = (v_max != v_min) ? (clamped - v_min) / (v_max - v_min) : 0;
    char buf[64]; snprintf(buf, sizeof(buf), display_format, *v);
    
    ImU32 bg = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_FrameBg]);
    ImU32 fill = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_SliderGrab]);
    ImU32 border = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Border]);
    ImU32 text_col = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]);
    drawSlider(x, y, sl_w, sl_h, frac, bg, fill, border);
    s_ui.fg_draw_list.AddText(ImVec2(x+sl_w/2 - strlen(buf)*4, y+2), text_col, buf);
    
    int id = getID();
    if (s_ui.active_item == id) {
        float rel = (s_ui.touch_x - x) / sl_w;
        rel = std::max(0.0f, std::min(1.0f, rel));
        *v = v_min + rel * (v_max - v_min);
        if (!s_ui.touch_down) s_ui.active_item = 0;
    }
    bool hot = isInRect(s_ui.touch_x, s_ui.touch_y, x, y, sl_w, sl_h);
    if (hot && s_ui.touch_just_pressed) s_ui.active_item = id;
    
    w.cursor_pos.y += sl_h + 18;
    s_ui.last_item_x = x;
    s_ui.last_item_y = y;
    s_ui.last_item_width = sl_w;
    return false;
}

bool SliderInt(const char* label, int* v, int v_min, int v_max, const char* format="%d", int flags=0) {
    return DragInt(label, v, 1.0f, v_min, v_max, format, flags);
}
bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format="%.3f", int flags=0) {
    return DragFloat(label, v, 0.1f, v_min, v_max, format, flags);
}

void Text(const char* fmt, ...) {
    if (s_ui.window_stack.empty()) return;
    auto& w = s_ui.window_stack.back();
    char buf[1024]; va_list args; va_start(args, fmt); vsnprintf(buf, sizeof(buf), fmt, args); va_end(args);
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    s_ui.fg_draw_list.AddText(ImVec2(x, y), ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]), buf);
    w.cursor_pos.y += 18;
    s_ui.last_item_x = x;
    s_ui.last_item_y = y;
    s_ui.last_item_width = CalcTextSize(buf).x;
}

void TextColored(const ImVec4& col, const char* fmt, ...) {
    if (s_ui.window_stack.empty()) return;
    auto& w = s_ui.window_stack.back();
    char buf[1024]; va_list args; va_start(args, fmt); vsnprintf(buf, sizeof(buf), fmt, args); va_end(args);
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    s_ui.fg_draw_list.AddText(ImVec2(x, y), ColorConvertFloat4ToU32(col), buf);
    w.cursor_pos.y += 18;
}

void Image(ImTextureID tex, const ImVec2& size, const ImVec2& uv0=ImVec2(0,0), const ImVec2& uv1=ImVec2(1,1), 
           const ImVec4& tint_col=ImVec4(1,1,1,1), const ImVec4& border_col=ImVec4(0,0,0,0)) {
    if (s_ui.window_stack.empty()) return;
    auto& w = s_ui.window_stack.back();
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    s_ui.fg_draw_list.AddImage(tex, ImVec2(x,y), ImVec2(x+size.x,y+size.y), uv0, uv1, ColorConvertFloat4ToU32(tint_col));
    if (border_col.w > 0) s_ui.fg_draw_list.AddRect(ImVec2(x,y), ImVec2(x+size.x,y+size.y), ColorConvertFloat4ToU32(border_col),0,0,1);
    w.cursor_pos.y += size.y + 4;
    s_ui.last_item_x = x;
    s_ui.last_item_y = y;
    s_ui.last_item_width = size.x;
}

bool InputText(const char* label, char* buf, size_t buf_size, int flags=0) {
    (void)flags;
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    float inp_w = 200;
    float inp_h = 24;
    
    s_ui.fg_draw_list.AddText(ImVec2(x, y-14), ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]), label);
    ImU32 bg = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_FrameBg]);
    ImU32 border = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Border]);
    ImU32 text_col = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]);
    
    s_ui.fg_draw_list.AddRectFilled(ImVec2(x, y), ImVec2(x+inp_w, y+inp_h), bg, 3);
    s_ui.fg_draw_list.AddRect(ImVec2(x, y), ImVec2(x+inp_w, y+inp_h), border, 3, 0, 2);
    s_ui.fg_draw_list.AddText(ImVec2(x+5, y+4), text_col, buf);
    
    bool hot = isInRect(s_ui.touch_x, s_ui.touch_y, x, y, inp_w, inp_h);
    if (hot && s_ui.touch_just_pressed) {
        s_ui.textinput_active = true;
        s_ui.textinput_buffer = buf;
        s_ui.textinput_label = label;
        s_ui.io.WantTextInput = true;
    }
    if (s_ui.textinput_active && s_ui.textinput_label == label) {
        if (s_ui.touch_just_pressed && !hot) {
            s_ui.textinput_active = false;
            s_ui.io.WantTextInput = false;
            strncpy(buf, s_ui.textinput_buffer.c_str(), buf_size);
        }
        float cx = x + 5 + s_ui.textinput_buffer.size() * 8;
        s_ui.fg_draw_list.AddLine(ImVec2(cx, y+3), ImVec2(cx, y+inp_h-3), text_col, 2);
    }
    
    w.cursor_pos.y += inp_h + 18;
    s_ui.last_item_x = x;
    s_ui.last_item_y = y;
    s_ui.last_item_width = inp_w;
    return false;
}

bool ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items=-1) {
    (void)height_in_items;
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    float lb_w = 200;
    float item_h = 22;
    float list_h = std::min(items_count, 6) * item_h + 4;
    
    s_ui.fg_draw_list.AddText(ImVec2(x, y-14), ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]), label);
    ImU32 bg = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_FrameBg]);
    ImU32 border = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Border]);
    ImU32 header = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Header]);
    ImU32 text_col = ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]);
    
    s_ui.fg_draw_list.AddRectFilled(ImVec2(x, y), ImVec2(x+lb_w, y+list_h), bg, 3);
    s_ui.fg_draw_list.AddRect(ImVec2(x, y), ImVec2(x+lb_w, y+list_h), border, 3, 0, 2);
    
    for (int i = 0; i < items_count; i++) {
        float iy = y + i * item_h + 2;
        if (iy + item_h > y + list_h) break;
        bool is_selected = (i == *current_item);
        bool item_hot = isInRect(s_ui.touch_x, s_ui.touch_y, x+2, iy, lb_w-4, item_h);
        if (is_selected) s_ui.fg_draw_list.AddRectFilled(ImVec2(x+2, iy), ImVec2(x+lb_w-2, iy+item_h), header, 2);
        s_ui.fg_draw_list.AddText(ImVec2(x+8, iy+3), text_col, items[i]);
        if (item_hot && s_ui.touch_just_pressed) *current_item = i;
    }
    w.cursor_pos.y += list_h + 18;
    s_ui.last_item_x = x;
    s_ui.last_item_y = y;
    s_ui.last_item_width = lb_w;
    return false;
}

bool Selectable(const char* label, bool selected=0, int flags=0, const ImVec2& size_arg=ImVec2(0,0)) {
    (void)flags;
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    float sel_w = size_arg.x > 0 ? size_arg.x : w.size.x - 20;
    float sel_h = size_arg.y > 0 ? size_arg.y : 22;
    bool hot = isInRect(s_ui.touch_x, s_ui.touch_y, x, y, sel_w, sel_h);
    bool clicked = hot && s_ui.touch_just_pressed;
    if (selected) s_ui.fg_draw_list.AddRectFilled(ImVec2(x,y), ImVec2(x+sel_w,y+sel_h), ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_HeaderActive]), 2);
    else if (hot) s_ui.fg_draw_list.AddRectFilled(ImVec2(x,y), ImVec2(x+sel_w,y+sel_h), ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_HeaderHovered]), 2);
    s_ui.fg_draw_list.AddText(ImVec2(x+5, y+3), ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]), label);
    w.cursor_pos.y += sel_h + 2;
    s_ui.last_item_x = x;
    s_ui.last_item_y = y;
    s_ui.last_item_width = sel_w;
    return clicked;
}

bool BeginChild(const char* str_id, const ImVec2& size=ImVec2(0,0), bool border=false, int flags=0) {
    (void)str_id; (void)border; (void)flags;
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    float cw = size.x > 0 ? size.x : w.size.x - 20;
    float ch = size.y > 0 ? size.y : w.size.y - 40;
    w.content_avail = ImVec2(cw, ch);
    return true;
}
void EndChild() {
    if (s_ui.window_stack.empty()) return;
    s_ui.window_stack.back().cursor_pos.y += s_ui.window_stack.back().content_avail.y + 10;
}

bool ColorEdit3(const char* label, float col[3]) {
    (void)label; (void)col;
    if (s_ui.window_stack.empty()) return false;
    auto& w = s_ui.window_stack.back();
    float x = w.pos.x + w.cursor_pos.x;
    float y = w.pos.y + w.cursor_pos.y;
    ImU32 color = IM_COL32((int)(col[0]*255),(int)(col[1]*255),(int)(col[2]*255),255);
    s_ui.fg_draw_list.AddRectFilled(ImVec2(x,y), ImVec2(x+20,y+16), color, 2);
    s_ui.fg_draw_list.AddRect(ImVec2(x,y), ImVec2(x+20,y+16), ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Border]), 2, 0, 2);
    char buf[64]; snprintf(buf,sizeof(buf),"%s (%.2f,%.2f,%.2f)",label,col[0],col[1],col[2]);
    s_ui.fg_draw_list.AddText(ImVec2(x+26,y), ColorConvertFloat4ToU32(s_ui.style.Colors[ImGuiCol_Text]), buf);
    w.cursor_pos.y += 22;
    return false;
}

// ─── Frame Management ────────────────────────────────────────────────
void NewFrame() {
    static bool prev_mouse = false;
    bool curr_mouse = s_ui.io.MouseDown[0];
    s_ui.touch_just_pressed = curr_mouse && !prev_mouse;
    s_ui.touch_just_released = !curr_mouse && prev_mouse;
    s_ui.touch_down = curr_mouse;
    s_ui.touch_x = s_ui.io.MousePos.x;
    s_ui.touch_y = s_ui.io.MousePos.y;
    prev_mouse = curr_mouse;
    
    s_ui.next_id = 1;
    s_ui.fg_draw_list.Clear();
    s_ui.bg_draw_list.Clear();
    
    if (s_ui.io.Fonts && !s_ui.io.Fonts->TexID) s_ui.io.Fonts->Build();
}

void EndFrame() {}
void Render() {
    renderDrawList(&s_ui.bg_draw_list);
    renderDrawList(&s_ui.fg_draw_list);
}
void RenderNotifications() {}

void DestroyContext() {
    if (s_ui.io.Fonts) { s_ui.io.Fonts->Clear(); delete s_ui.io.Fonts; s_ui.io.Fonts = nullptr; }
}
void StyleColorsClassic() {}

} // namespace ImGui
