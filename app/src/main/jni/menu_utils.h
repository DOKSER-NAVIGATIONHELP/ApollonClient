#include "Images/death_icon.h"
#include "Images/heart_icon.h"
#include "Images/heart_blink_icon.h"

#include "Images/Platforms/android_icon.h"
#include "Images/Platforms/ios_icon.h"
#include "Images/Platforms/linux_icon.h"
#include "Images/Platforms/macos_icon.h"
#include "Images/Platforms/nx_icon.h"
#include "Images/Platforms/ps_icon.h"
#include "Images/Platforms/windows_icon.h"
#include "Images/Platforms/xbox_icon.h"

float calculateResolutionX(int screenWidth, int baseWidth) {
    float scale = static_cast<float>(screenWidth) / baseWidth;
    return scale;
}

float calculateResolutionScale(int screenWidth, int screenHeight, int baseWidth, int baseHeight) {
   if (screenWidth == baseWidth && screenHeight == baseHeight) {
     return 1.0f;
   }

   float scaleWidth = static_cast<float>(screenWidth) / baseWidth;
   float scaleHeight = static_cast<float>(screenHeight) / baseHeight;
   float newScale = std::min(scaleWidth, scaleHeight);
   return newScale;
}
     

void DrawSeparatorToWindowEdge(const ImVec2& verticalLineEnd, float verticalPadding) {
  ImGuiWindow *window = ImGui::GetCurrentWindow();
  if (window == nullptr)
    return;
	float separatorThickness = 2.0f * scaleGlobal;

  ImGui::Dummy(ImVec2(0.0f, verticalPadding));

  ImVec2 separatorStart = ImVec2(verticalLineEnd.x, ImGui::GetItemRectMin().y + verticalPadding / 2.0f);

  float availableWidth = window->Size.x - (separatorStart.x - window->Pos.x);
  ImVec2 separatorEnd = ImVec2(separatorStart.x + availableWidth, separatorStart.y);

  window->DrawList->AddLine(separatorStart, separatorEnd, ImGui::GetColorU32(ImGuiCol_Separator), separatorThickness);
}

GLuint CreateTextureFromMemoryPNG(const unsigned char* png_data, int png_size) {
    int width, height, channels;

    unsigned char* img_data = stbi_load_from_memory(png_data, png_size, &width, &height, &channels, STBI_rgb_alpha);

    if (!img_data) {
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLenum format = GL_RGBA;
    if (channels == 1) {
        format = GL_LUMINANCE;
    } else if (channels == 3) {
        format = GL_RGB;
    } else if (channels == 4) {
        format = GL_RGBA;
    } else {
        stbi_image_free(img_data);
        glDeleteTextures(1, &textureID);
        return 0;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, img_data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(img_data);

    return textureID;
}

struct Point {
    ImVec2 position;
    ImVec2 velocity;
    float radius;
};

float randomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(gen);
}

static std::vector<Point> points;

void BackGroundDots(int numberOfDots, float minimumSize, float maximumSize, float connectionDistance) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    static float pointAlpha = 0.5f;
    
    ImVec4 whiteColor = ImVec4(1.0f, 1.0f, 1.0f, pointAlpha);

    static auto lastTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    points.erase(std::remove_if(points.begin(), points.end(), [&](const Point& p) {
        return (p.position.x < 0 - p.radius || p.position.x > windowSize.x + p.radius ||
                p.position.y < 0 - p.radius || p.position.y > windowSize.y + p.radius);
    }), points.end());

    while (points.size() < numberOfDots) {
        Point newPoint;
        newPoint.position.x = randomFloat(0, windowSize.x);
        newPoint.position.y = randomFloat(0, windowSize.y);
        newPoint.velocity.x = randomFloat(-0.5f, 0.5f);
        newPoint.velocity.y = randomFloat(-0.5f, 0.5f);
        newPoint.radius = randomFloat(minimumSize, maximumSize);
        points.push_back(newPoint);
    }

    for (int i = 0; i < points.size(); ++i) {
        points[i].position.x += points[i].velocity.x * deltaTime.count() * 100;
        points[i].position.y += points[i].velocity.y * deltaTime.count() * 100;

        if (points[i].position.x < 0 || points[i].position.x > windowSize.x) {
            points[i].velocity.x *= -1;
        }
        if (points[i].position.y < 0 || points[i].position.y > windowSize.y) {
            points[i].velocity.y *= -1;
        }

        draw_list->AddCircleFilled(points[i].position, points[i].radius, ImGui::ColorConvertFloat4ToU32(whiteColor));

        for (int j = i + 1; j < points.size(); ++j) {
            float distance = std::sqrt(
                std::pow(points[i].position.x - points[j].position.x, 2) +
                std::pow(points[i].position.y - points[j].position.y, 2)
            );

            if (distance < connectionDistance) {
                float alpha = 1.0f - (distance / connectionDistance);
                ImVec4 lineColor = ImVec4(1.0f, 1.0f, 1.0f, alpha);

                draw_list->AddLine(points[i].position, points[j].position, ImGui::ColorConvertFloat4ToU32(lineColor), 1.0f);
            }
        }
    }
}

struct ColoredText {
    std::string text;
    ImVec4 color;
    bool bold;
};

std::vector<ColoredText> convertMinecraftColorsToImGui(const std::string& text) {
    std::vector<ColoredText> result;
    std::string currentText;
    ImVec4 currentColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    bool currentBold = false;
    
    std::map<char, ImVec4> colorMap = {
        {'0', ImVec4(0.0f, 0.0f, 0.0f, 1.0f)},
        {'1', ImVec4(0.0f, 0.0f, 0.66f, 1.0f)},
        {'2', ImVec4(0.0f, 0.66f, 0.0f, 1.0f)},
        {'3', ImVec4(0.0f, 0.66f, 0.66f, 1.0f)},
        {'4', ImVec4(0.66f, 0.0f, 0.0f, 1.0f)},
        {'5', ImVec4(0.66f, 0.0f, 0.66f, 1.0f)},
        {'6', ImVec4(1.0f, 0.66f, 0.0f, 1.0f)},
        {'7', ImVec4(0.66f, 0.66f, 0.66f, 1.0f)},
        {'8', ImVec4(0.33f, 0.33f, 0.33f, 1.0f)},
        {'9', ImVec4(0.33f, 0.33f, 1.0f, 1.0f)},
        {'a', ImVec4(0.33f, 1.0f, 0.33f, 1.0f)},
        {'b', ImVec4(0.33f, 1.0f, 1.0f, 1.0f)},
        {'c', ImVec4(1.0f, 0.33f, 0.33f, 1.0f)},
        {'d', ImVec4(1.0f, 0.33f, 1.0f, 1.0f)},
        {'e', ImVec4(1.0f, 1.0f, 0.33f, 1.0f)},
        {'f', ImVec4(1.0f, 1.0f, 1.0f, 1.0f)},
        {'r', ImVec4(1.0f, 1.0f, 1.0f, 1.0f)},
        {'g', ImVec4(0.86666667f, 0.83921569f, 0.01960784f, 1.0f)},
        {'h', ImVec4(0.89019608f, 0.83137255f, 0.81960784f, 1.0f)},
        {'i', ImVec4(0.80784314f, 0.79215686f, 0.79215686f, 1.0f)},
        {'j', ImVec4(0.26666667f, 0.22745098f, 0.23137255f, 1.0f)},
        {'m', ImVec4(0.59215686f, 0.08627451f, 0.02745098f, 1.0f)},
        {'n', ImVec4(0.70588235f, 0.40784314f, 0.30196078f, 1.0f)},
        {'p', ImVec4(0.87058824f, 0.69411765f, 0.17647059f, 1.0f)},
        {'q', ImVec4(0.27843137f, 0.62745098f, 0.21176471f, 1.0f)},
        {'s', ImVec4(0.17254902f, 0.72941176f, 0.65882353f, 1.0f)},
        {'t', ImVec4(0.12941176f, 0.28627451f, 0.48235294f, 1.0f)},
        {'u', ImVec4(0.60392157f, 0.36078431f, 0.77647059f, 1.0f)}
    };

    for (size_t i = 0; i < text.length(); ++i) {
        if (text[i] == '\n') {
            if (!currentText.empty()) {
                result.push_back({currentText, currentColor, currentBold});
                currentText.clear();
            }
            result.push_back({"\n", currentColor, currentBold});
        }
        else if (text[i] == '\xC2' && i + 1 < text.length() && text[i + 1] == '\xA7') {
            if (!currentText.empty()) {
                result.push_back({currentText, currentColor, currentBold});
                currentText.clear();
            }

            if (i + 2 < text.length()) {
                char formatCode = tolower(text[i + 2]);
             
                switch (formatCode) {
                    case 'l':
                        currentBold = true;
                        break;
                    case 'r':
                        currentColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                        currentBold = false;
                        break;
                    default:
                        auto it = colorMap.find(formatCode);
                        if (it != colorMap.end()) {
                            currentColor = it->second;
                        } else {
                            currentText += "§";
                            currentText += text[i + 2];
                        }
                        break;
                }
                i += 2;
            } else {
                currentText += "§";
                i += 1;
            }
        } else {
            currentText += text[i];
        }
    }

    if (!currentText.empty()) {
        result.push_back({currentText, currentColor, currentBold});
    }

    return result;
}

void ImGuiColoredText(const std::string& minecraftText) {
    std::vector<ColoredText> coloredText = convertMinecraftColorsToImGui(minecraftText);

    for (const auto& ct : coloredText) {
        if (ct.text == "\n") {
            ImGui::NewLine();
        } else {
            ImGui::TextColored(ct.color, "%s", ct.text.c_str());
            ImGui::SameLine(0,0);
        }
    }
}

struct Notification {
    std::string text;
    double start_time;
    double duration;
    bool is_fading_out;
    int id;
    float width;
    ImVec4 line_color;
};

static std::vector<Notification> g_notifications;

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> distrib(1000, 9999);

void AddNotification(const std::string& text, float duration, ImVec4 line_color) {
    Notification notification;
    notification.text = text;
    notification.start_time = ImGui::GetTime();
    notification.duration = duration;
    notification.is_fading_out = false;
    notification.id = distrib(gen);
    notification.width = 300.0f * calcResX;
    notification.line_color = line_color;

    g_notifications.push_back(notification);
}

void RenderNotifications() {
    float margin = 10.0f * scaleGlobal;
    float notification_height = 50.0f * scaleGlobal;
    float notification_spacing = 5.0f * scaleGlobal;
    float text_offset = 5.0f * scaleGlobal;
    float rounding = 5.0f;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImDrawList* draw_list = ImGui::GetForegroundDrawList(viewport);

    ImVec2 work_pos = viewport->WorkPos;

    for (int i = g_notifications.size() - 1; i >= 0; --i) {
        Notification& notification = g_notifications[i];
        double elapsed_time = ImGui::GetTime() - notification.start_time;

        float animation_duration = 0.2f;
        float animation_progress = ImSaturate(elapsed_time / animation_duration);

        float alpha_progress = ImSaturate(elapsed_time / animation_duration);

        float offset1 = 0.0f;
        float offset2 = -notification.width * 0.5f;
        float offset3 = -notification.width - 30;
        float offset4 = -notification.width;

        float current_offset;
        if (animation_progress < 0.33f) {
            float t = animation_progress / 0.33f;
            current_offset = ImLerp(offset1, offset2, t);
        } else if (animation_progress < 0.66f) {
            float t = (animation_progress - 0.33f) / 0.33f;
            current_offset = ImLerp(offset2, offset3, t);
        } else {
            float t = (animation_progress - 0.66f) / 0.34f;
            current_offset = ImLerp(offset3, offset4, t);
        }

        float fade_out_progress = 1.0f;
        if (notification.is_fading_out) {
            fade_out_progress = static_cast<float>(1.0 - ImClamp((ImGui::GetTime() - notification.start_time - notification.duration) / 0.5, 0.0, 1.0));
        } else if (elapsed_time > notification.duration) {
            notification.is_fading_out = true;
        }
          float alpha = fade_out_progress * alpha_progress;

        ImVec4 base_color = ImVec4(0.1f, 0.1f, 0.1f, 0.75f);
        base_color.w *= alpha;
        ImColor bg_color = ImColor(base_color);
        ImColor text_color = ImColor(ImVec4(1.0f, 1.0f, 1.0f, alpha));
         ImVec4 line_base_color = notification.line_color;
        line_base_color.w *= alpha;
        ImColor line_color = ImColor(line_base_color);

        float y_offset = (notification_height + notification_spacing) * (g_notifications.size() - 1 - i);

        ImVec2 notification_pos = ImVec2(work_pos.x + screenWidth - margin + current_offset,
                                         work_pos.y + screenHeight - margin - notification_height - y_offset);

        ImVec2 rect_size = ImVec2(notification.width, notification_height);
        ImVec2 rect_pos = notification_pos;

        float line_width = text_offset;
        ImVec2 line_rect_pos = rect_pos;

        draw_list->AddRectFilled(rect_pos, ImVec2(rect_pos.x + rect_size.x, rect_pos.y + rect_size.y), bg_color, rounding, ImDrawFlags_RoundCornersAll);
		draw_list->AddRectFilled(line_rect_pos, ImVec2(rect_pos.x + line_width, rect_pos.y + rect_size.y), line_color, rounding, ImDrawFlags_RoundCornersLeft);

        ImVec2 text_pos = ImVec2(line_rect_pos.x + line_width + text_offset, rect_pos.y + text_offset);

        draw_list->AddText(text_pos, text_color, notification.text.c_str());
    }

    g_notifications.erase(std::remove_if(g_notifications.begin(), g_notifications.end(), [](const Notification& n) {
        return n.is_fading_out && (ImGui::GetTime() - n.start_time - n.duration) > 0.5;
    }), g_notifications.end());
}

void DrawBackgroundText(const char* text, float xOffset, float yOffset, ImVec4 textColor, ImVec4 bgColor, float padding = 5.0f) {
	ImVec2 centerPos = ImGui::GetMainViewport()->GetCenter();
	
	ImVec2 position;
	position.x = centerPos.x + xOffset;
	position.y = centerPos.y + yOffset;

	ImVec2 textSize = ImGui::CalcTextSize(text);
	
	ImVec2 rectMin = position;
	ImVec2 rectMax = ImVec2(position.x + textSize.x + padding * 2, position.y + textSize.y + padding * 2);
	
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	
	drawList->AddRectFilled(rectMin, rectMax, ImGui::ColorConvertFloat4ToU32(bgColor));

	drawList->AddText(ImVec2(position.x + padding, position.y + padding), ImGui::ColorConvertFloat4ToU32(textColor), text);
}

void RenderESP(ImDrawList* draw_list, vec3_t cameraPos, glm::vec2 axisFov, glm::mat4 viewMatrix) {
    glm::vec2 displaySize = glm::vec2(screenWidth, screenHeight);
    ImVec2 screenCenter = ImVec2(displaySize.x / 2.0f, displaySize.y / 2.0f);
    glm::vec3 camPos = glm::vec3(cameraPos.x, cameraPos.y, cameraPos.z);
    float currentFontSize = ImGui::GetFontSize();
    
    static GLint heart_icon = 0;
    if (!heart_icon) heart_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(HeartIcon), sizeof(HeartIcon));
    static GLint heart_blink_icon = 0;
    if (!heart_blink_icon) heart_blink_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(HeartBlinkIcon), sizeof(HeartBlinkIcon));
    
    static GLint android_icon = 0;
    if (!android_icon) android_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(AndroidIcon), sizeof(AndroidIcon));
    static GLint ios_icon = 0;
    if (!ios_icon) ios_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(IOSIcon), sizeof(IOSIcon));
    static GLint linux_icon = 0;
    if (!linux_icon) linux_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(LinuxIcon), sizeof(LinuxIcon));
    static GLint macos_icon = 0;
    if (!macos_icon) macos_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(MacOSIcon), sizeof(MacOSIcon));
    static GLint nx_icon = 0;
    if (!nx_icon) nx_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(NXIcon), sizeof(NXIcon));
    static GLint ps_icon = 0;
    if (!ps_icon) ps_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(PSIcon), sizeof(PSIcon));
    static GLint windows_icon = 0;
    if (!windows_icon) windows_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(WindowsIcon), sizeof(WindowsIcon));
    static GLint xbox_icon = 0;
    if (!xbox_icon) xbox_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(XboxIcon), sizeof(XboxIcon));
    
    ImU32 outlineColor = IM_COL32(0, 0, 0, 255);
    float outlineThickness = 5 * scaleGlobal;

    for (PlayerStruct& player : nearPlayerList) {
        if (!player.isBot) {
            ImU32 currentColor = IM_COL32(255, 255, 255, 255);
            if (player.isFriend) {
                currentColor = IM_COL32(0, 255, 255, 255);
            }
            else if (player.isProtected) {
                currentColor = IM_COL32(255, 0, 0, 255);
            }

            float correctedPosY = player.position->y - 1.62f;
            float halfYHitBox = player.hitBox.y / 2.0f;
            float halfXHitBox = player.hitBox.x / 2.0f;
            
            glm::vec3 points[8] = {
                glm::vec3(player.position->x - halfXHitBox, correctedPosY, player.position->z - halfXHitBox),
                glm::vec3(player.position->x + halfXHitBox, correctedPosY, player.position->z - halfXHitBox),
                glm::vec3(player.position->x + halfXHitBox, correctedPosY, player.position->z + halfXHitBox),
                glm::vec3(player.position->x - halfXHitBox, correctedPosY, player.position->z + halfXHitBox),
                glm::vec3(player.position->x - halfXHitBox, correctedPosY + player.hitBox.y, player.position->z - halfXHitBox),
                glm::vec3(player.position->x + halfXHitBox, correctedPosY + player.hitBox.y, player.position->z - halfXHitBox),
                glm::vec3(player.position->x + halfXHitBox, correctedPosY + player.hitBox.y, player.position->z + halfXHitBox),
                glm::vec3(player.position->x - halfXHitBox, correctedPosY + player.hitBox.y, player.position->z + halfXHitBox)
            };

            glm::vec2 screenPoints[8];
            bool visiblePoints[8];
            
            bool allVisible = true;
            for (int i = 0; i < 8; i++) {
                visiblePoints[i] = OWorldToScreen(camPos, points[i], screenPoints[i], axisFov, displaySize, viewMatrix);
                if (!visiblePoints[i]) {
                    allVisible = false;
                    break;
                }
            }

            glm::vec2 screenBottom, screenTop;
            bool bottomVisible = OWorldToScreen(camPos, glm::vec3(player.position->x, correctedPosY, player.position->z), screenBottom, axisFov, displaySize, viewMatrix);
            bool topVisible = OWorldToScreen(camPos, glm::vec3(player.position->x, correctedPosY + player.hitBox.y, player.position->z), screenTop, axisFov, displaySize, viewMatrix);
			
            if (allVisible && espBox) {
                draw_list->AddLine(ImVec2(screenPoints[0].x, screenPoints[0].y), ImVec2(screenPoints[1].x, screenPoints[1].y), outlineColor, outlineThickness);
                draw_list->AddLine(ImVec2(screenPoints[1].x, screenPoints[1].y), ImVec2(screenPoints[2].x, screenPoints[2].y), outlineColor, outlineThickness);
                draw_list->AddLine(ImVec2(screenPoints[2].x, screenPoints[2].y), ImVec2(screenPoints[3].x, screenPoints[3].y), outlineColor, outlineThickness);
                draw_list->AddLine(ImVec2(screenPoints[3].x, screenPoints[3].y), ImVec2(screenPoints[0].x, screenPoints[0].y), outlineColor, outlineThickness);
                
                draw_list->AddLine(ImVec2(screenPoints[4].x, screenPoints[4].y), ImVec2(screenPoints[5].x, screenPoints[5].y), outlineColor, outlineThickness);
                draw_list->AddLine(ImVec2(screenPoints[5].x, screenPoints[5].y), ImVec2(screenPoints[6].x, screenPoints[6].y), outlineColor, outlineThickness);
                draw_list->AddLine(ImVec2(screenPoints[6].x, screenPoints[6].y), ImVec2(screenPoints[7].x, screenPoints[7].y), outlineColor, outlineThickness);
                draw_list->AddLine(ImVec2(screenPoints[7].x, screenPoints[7].y), ImVec2(screenPoints[4].x, screenPoints[4].y), outlineColor, outlineThickness);
                
                draw_list->AddLine(ImVec2(screenPoints[0].x, screenPoints[0].y), ImVec2(screenPoints[4].x, screenPoints[4].y), outlineColor, outlineThickness);
                draw_list->AddLine(ImVec2(screenPoints[1].x, screenPoints[1].y), ImVec2(screenPoints[5].x, screenPoints[5].y), outlineColor, outlineThickness);
                draw_list->AddLine(ImVec2(screenPoints[2].x, screenPoints[2].y), ImVec2(screenPoints[6].x, screenPoints[6].y), outlineColor, outlineThickness);
                draw_list->AddLine(ImVec2(screenPoints[3].x, screenPoints[3].y), ImVec2(screenPoints[7].x, screenPoints[7].y), outlineColor, outlineThickness);
                
                float boxThickness = 2.0f * scaleGlobal;
                draw_list->AddLine(ImVec2(screenPoints[0].x, screenPoints[0].y), ImVec2(screenPoints[1].x, screenPoints[1].y), currentColor, boxThickness);
                draw_list->AddLine(ImVec2(screenPoints[1].x, screenPoints[1].y), ImVec2(screenPoints[2].x, screenPoints[2].y), currentColor, boxThickness);
                draw_list->AddLine(ImVec2(screenPoints[2].x, screenPoints[2].y), ImVec2(screenPoints[3].x, screenPoints[3].y), currentColor, boxThickness);
                draw_list->AddLine(ImVec2(screenPoints[3].x, screenPoints[3].y), ImVec2(screenPoints[0].x, screenPoints[0].y), currentColor, boxThickness);
                
                draw_list->AddLine(ImVec2(screenPoints[4].x, screenPoints[4].y), ImVec2(screenPoints[5].x, screenPoints[5].y), currentColor, boxThickness);
                draw_list->AddLine(ImVec2(screenPoints[5].x, screenPoints[5].y), ImVec2(screenPoints[6].x, screenPoints[6].y), currentColor, boxThickness);
                draw_list->AddLine(ImVec2(screenPoints[6].x, screenPoints[6].y), ImVec2(screenPoints[7].x, screenPoints[7].y), currentColor, boxThickness);
                draw_list->AddLine(ImVec2(screenPoints[7].x, screenPoints[7].y), ImVec2(screenPoints[4].x, screenPoints[4].y), currentColor, boxThickness);
                
                draw_list->AddLine(ImVec2(screenPoints[0].x, screenPoints[0].y), ImVec2(screenPoints[4].x, screenPoints[4].y), currentColor, boxThickness);
                draw_list->AddLine(ImVec2(screenPoints[1].x, screenPoints[1].y), ImVec2(screenPoints[5].x, screenPoints[5].y), currentColor, boxThickness);
                draw_list->AddLine(ImVec2(screenPoints[2].x, screenPoints[2].y), ImVec2(screenPoints[6].x, screenPoints[6].y), currentColor, boxThickness);
                draw_list->AddLine(ImVec2(screenPoints[3].x, screenPoints[3].y), ImVec2(screenPoints[7].x, screenPoints[7].y), currentColor, boxThickness);
            }
			
            float verticalSpacing = 45 * scaleGlobal;
            float platformY = screenTop.y - verticalSpacing * 2.1;
            float healthY = screenTop.y - verticalSpacing * 1.5;
            float nametagY = screenTop.y - verticalSpacing;

            if (topVisible) {
                if (espHealth) {
                    std::string healthText = std::to_string(player.health);
                    
                    ImU32 healthColor = IM_COL32(255, 255, 255, 255);
                    if (player.health <= 10) healthColor = IM_COL32(255, 255, 0, 255);
                    if (player.health <= 5) healthColor = IM_COL32(255, 0, 0, 255);
                    
                    ImVec2 healthTextSize = ImGui::CalcTextSize(healthText.c_str());
                    float iconSize = healthTextSize.y - 10 * scaleGlobal;
                    float totalWidth = healthTextSize.x + ImGui::CalcTextSize(" ").x + iconSize;
                    
                    float centerX = screenTop.x;
                    float startX = centerX - (totalWidth / 2.0f);
                    
                    float textX = startX;
                    float iconX = textX + healthTextSize.x + ImGui::CalcTextSize(" ").x;
                    float iconY = healthY + 5 * scaleGlobal;
                    
                    draw_list->AddText(nullptr, currentFontSize, ImVec2(textX - 1, healthY - 1), outlineColor, healthText.c_str());
                    draw_list->AddText(nullptr, currentFontSize, ImVec2(textX + 1, healthY + 1), outlineColor, healthText.c_str());
                    draw_list->AddText(nullptr, currentFontSize, ImVec2(textX - 1, healthY + 1), outlineColor, healthText.c_str());
                    draw_list->AddText(nullptr, currentFontSize, ImVec2(textX + 1, healthY - 1), outlineColor, healthText.c_str());
                    
                    draw_list->AddText(ImVec2(textX, healthY), healthColor, healthText.c_str());
                    
                    ImVec2 iconPos = ImVec2(iconX, iconY);
                    if (player.hurtTime >= 8) {
                        draw_list->AddImage((void*)(intptr_t)heart_blink_icon, iconPos, ImVec2(iconPos.x + iconSize, iconPos.y + iconSize));
                    } else {
                        draw_list->AddImage((void*)(intptr_t)heart_icon, iconPos, ImVec2(iconPos.x + iconSize, iconPos.y + iconSize));
                    }
                }
                
                if (espPlatform) {
                    GLint platformIcon = 0;
                    
                    if (player.platform == 1) platformIcon = android_icon;
                    else if (player.platform == 2) platformIcon = ios_icon;
                    else if (player.platform == 3) platformIcon = macos_icon;
                    else if (player.platform == 7 || player.platform == 8) platformIcon = windows_icon;
                    else if (player.platform == 11) platformIcon = ps_icon;
                    else if (player.platform == 12) platformIcon = nx_icon;
                    else if (player.platform == 13) platformIcon = xbox_icon;
                    else if (player.platform == 15) platformIcon = linux_icon;
                    
                    if (platformIcon != 0) {
                        float iconSize = currentFontSize;
                        float iconX = screenTop.x - (iconSize / 2.0f);
                        
                        ImVec2 iconPos = ImVec2(iconX, platformY);
                        draw_list->AddImage((void*)(intptr_t)platformIcon, iconPos, ImVec2(iconPos.x + iconSize, iconPos.y + iconSize));
                    }
                }
				
				if (espNametag) {
                    std::vector<ColoredText> coloredText = convertMinecraftColorsToImGui(player.nameTag);

                    float totalTextWidth = 0.0f;
                    for (const auto& ct : coloredText) {
                        float width = ImGui::CalcTextSize(ct.text.c_str()).x;
                        totalTextWidth += width;
                     }

                     float centerX = screenTop.x;
                     float startX = centerX - (totalTextWidth / 2.0f);
                     float nameCurrentX = startX;

                     for (const auto& ct : coloredText) {
                         ImVec2 textSize = ImGui::CalcTextSize(ct.text.c_str());
                         ImVec2 nameOutlinePos = ImVec2(nameCurrentX, nametagY);

                         draw_list->AddText(nullptr, currentFontSize, ImVec2(nameOutlinePos.x -1, nameOutlinePos.y -1), outlineColor, ct.text.c_str());
                         draw_list->AddText(nullptr, currentFontSize, ImVec2(nameOutlinePos.x +1, nameOutlinePos.y +1), outlineColor, ct.text.c_str());
                         draw_list->AddText(nullptr, currentFontSize, ImVec2(nameOutlinePos.x -1, nameOutlinePos.y +1), outlineColor, ct.text.c_str());
                         draw_list->AddText(nullptr, currentFontSize, ImVec2(nameOutlinePos.x +1, nameOutlinePos.y -1), outlineColor, ct.text.c_str());

                         if (ct.bold) {
                             draw_list->AddText(ImVec2(nameCurrentX + 0.5f, nametagY), ImGui::ColorConvertFloat4ToU32(ct.color), ct.text.c_str());
                             draw_list->AddText(ImVec2(nameCurrentX - 0.5f, nametagY), ImGui::ColorConvertFloat4ToU32(ct.color), ct.text.c_str());
                         } else {
                             draw_list->AddText(ImVec2(nameCurrentX, nametagY), ImGui::ColorConvertFloat4ToU32(ct.color), ct.text.c_str());
                         }
                         nameCurrentX += textSize.x;
                     }
                }
            }

            if (bottomVisible) {
                if (espLine) {
                    ImVec2 tracerEnd = ImVec2(displaySize.x / 2, displaySize.y / 2);
                    draw_list->AddLine(ImVec2(screenBottom.x, screenBottom.y), tracerEnd, outlineColor, outlineThickness);
                    draw_list->AddLine(ImVec2(screenBottom.x, screenBottom.y), tracerEnd, currentColor, 2.0f * scaleGlobal);
                }
                
                if (espDistance) {
                    float distance = distanceTo(&cameraPos, player.position);
                    std::string distanceText = std::to_string(static_cast<int>(distance)) + "m";

                    ImVec2 textSize = ImGui::CalcTextSize(distanceText.c_str());
                    float textX = screenBottom.x - (textSize.x / 2.0f);
                    float textY = screenBottom.y + 10 * scaleGlobal;

                    draw_list->AddText(nullptr, currentFontSize, ImVec2(textX - 1, textY - 1), outlineColor, distanceText.c_str());
                    draw_list->AddText(nullptr, currentFontSize, ImVec2(textX + 1, textY + 1), outlineColor, distanceText.c_str());
                    draw_list->AddText(nullptr, currentFontSize, ImVec2(textX - 1, textY + 1), outlineColor, distanceText.c_str());
                    draw_list->AddText(nullptr, currentFontSize, ImVec2(textX + 1, textY - 1), outlineColor, distanceText.c_str());

                    draw_list->AddText(ImVec2(textX, textY), currentColor, distanceText.c_str());
                }
            }
        }
    }
}

void RenderDeathPosition(ImDrawList* draw_list, vec3_t cameraPos, glm::vec2 axisFov, glm::mat4 viewMatrix) {
    glm::vec2 displaySize = glm::vec2(screenWidth, screenHeight);
    glm::vec3 camPos = glm::vec3(cameraPos.x, cameraPos.y, cameraPos.z);

    static GLint death_icon = 0;
    if (!death_icon) death_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(DeathIcon), sizeof(DeathIcon));

    if (playerDeathPosX != 0 && playerDeathPosY != 0 && playerDeathPosZ != 0) {
        glm::vec3 deathPosition = glm::vec3(playerDeathPosX, playerDeathPosY, playerDeathPosZ);
        glm::vec2 screenPos;

        if (OWorldToScreen(camPos, deathPosition, screenPos, axisFov, displaySize, viewMatrix)) {
            vec3_t deathPos_t;
            deathPos_t.x = playerDeathPosX;
            deathPos_t.y = playerDeathPosY;
            deathPos_t.z = playerDeathPosZ;

            float distance = distanceTo(&cameraPos, &deathPos_t);
            std::string distanceText = std::to_string(static_cast<int>(distance)) + "m";

            ImVec2 iconSize = ImVec2(32 * scaleGlobal, 32 * scaleGlobal);

            ImVec2 iconPos = ImVec2(screenPos.x - iconSize.x / 2, screenPos.y - iconSize.y / 2);

            ImVec2 textSize = ImGui::CalcTextSize(distanceText.c_str());
            ImVec2 textPos = ImVec2(screenPos.x - textSize.x / 2, screenPos.y - iconSize.y / 2 - textSize.y - 2);

            float outline_thickness = 1.5 * scaleGlobal;
            ImU32 outline_color = IM_COL32(0, 0, 0, 255);

            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue;
                    ImVec2 offset_text_pos = ImVec2(textPos.x + x * outline_thickness, textPos.y + y * outline_thickness);
                    draw_list->AddText(offset_text_pos, outline_color, distanceText.c_str());
                }
            }

            draw_list->AddText(textPos, IM_COL32(255, 255, 255, 255), distanceText.c_str());

            draw_list->AddImage((ImTextureID)death_icon, iconPos, ImVec2(iconPos.x + iconSize.x, iconPos.y + iconSize.y));
        }
    }
}

void RenderOreESP(ImDrawList* draw_list, vec3_t cameraPos, glm::vec2 axisFov, glm::mat4 viewMatrix) {
    glm::vec2 displaySize = glm::vec2(screenWidth, screenHeight);
    glm::vec3 camPos = glm::vec3(cameraPos.x, cameraPos.y, cameraPos.z);

    for (XrayOres &ore : renderOresESP) {
        glm::vec3 basePos = glm::vec3(ore.orePosFloat.x, ore.orePosFloat.y, ore.orePosFloat.z);
        
        glm::vec3 corners[8] = {
            glm::vec3(basePos.x,         basePos.y,         basePos.z),
            glm::vec3(basePos.x + 1.0f, basePos.y,         basePos.z),
            glm::vec3(basePos.x + 1.0f, basePos.y,         basePos.z + 1.0f),
            glm::vec3(basePos.x,         basePos.y,         basePos.z + 1.0f),
            glm::vec3(basePos.x,         basePos.y + 1.0f, basePos.z),
            glm::vec3(basePos.x + 1.0f, basePos.y + 1.0f, basePos.z),
            glm::vec3(basePos.x + 1.0f, basePos.y + 1.0f, basePos.z + 1.0f),
            glm::vec3(basePos.x,         basePos.y + 1.0f, basePos.z + 1.0f)
        };

        glm::vec2 screen[8];
        bool allVisible = true;
        
        for (int i = 0; i < 8; i++) {
            if (!OWorldToScreen(camPos, corners[i], screen[i], axisFov, displaySize, viewMatrix)) {
                allVisible = false;
                break;
            }
        }
        
        if (!allVisible) continue;

        vec3_ti pos = ore.orePos;

        auto hasBlockAt = [&](int x, int y, int z) -> bool {
            for (XrayOres &otherOre : renderOresESP) {
                if (otherOre.orePos.x == x && otherOre.orePos.y == y && otherOre.orePos.z == z) {
                    return true;
                }
            }
            return false;
        };

        bool hasLeft = hasBlockAt(pos.x-1, pos.y, pos.z);
        bool hasRight = hasBlockAt(pos.x+1, pos.y, pos.z);
        bool hasBottom = hasBlockAt(pos.x, pos.y-1, pos.z);
        bool hasTop = hasBlockAt(pos.x, pos.y+1, pos.z);
        bool hasFront = hasBlockAt(pos.x, pos.y, pos.z-1);
        bool hasBack = hasBlockAt(pos.x, pos.y, pos.z+1);

        bool hasBottomLeft = hasBlockAt(pos.x-1, pos.y-1, pos.z);
        bool hasBottomRight = hasBlockAt(pos.x+1, pos.y-1, pos.z);
        bool hasBottomFront = hasBlockAt(pos.x, pos.y-1, pos.z-1);
        bool hasBottomBack = hasBlockAt(pos.x, pos.y-1, pos.z+1);
        
        bool hasTopLeft = hasBlockAt(pos.x-1, pos.y+1, pos.z);
        bool hasTopRight = hasBlockAt(pos.x+1, pos.y+1, pos.z);
        bool hasTopFront = hasBlockAt(pos.x, pos.y+1, pos.z-1);
        bool hasTopBack = hasBlockAt(pos.x, pos.y+1, pos.z+1);
        
        bool hasLeftFront = hasBlockAt(pos.x-1, pos.y, pos.z-1);
        bool hasLeftBack = hasBlockAt(pos.x-1, pos.y, pos.z+1);
        bool hasRightFront = hasBlockAt(pos.x+1, pos.y, pos.z-1);
        bool hasRightBack = hasBlockAt(pos.x+1, pos.y, pos.z+1);

        if (!hasLeft) {
            if (!hasBottom && !hasBottomLeft) 
                draw_list->AddLine(ImVec2(screen[0].x, screen[0].y), ImVec2(screen[3].x, screen[3].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasTop && !hasTopLeft)
                draw_list->AddLine(ImVec2(screen[4].x, screen[4].y), ImVec2(screen[7].x, screen[7].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasFront && !hasLeftFront)
                draw_list->AddLine(ImVec2(screen[0].x, screen[0].y), ImVec2(screen[4].x, screen[4].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasBack && !hasLeftBack)
                draw_list->AddLine(ImVec2(screen[3].x, screen[3].y), ImVec2(screen[7].x, screen[7].y), ore.oreColor, 1.5f * scaleGlobal);
        }

        if (!hasRight) {
            if (!hasBottom && !hasBottomRight)
                draw_list->AddLine(ImVec2(screen[1].x, screen[1].y), ImVec2(screen[2].x, screen[2].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasTop && !hasTopRight)
                draw_list->AddLine(ImVec2(screen[5].x, screen[5].y), ImVec2(screen[6].x, screen[6].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasFront && !hasRightFront)
                draw_list->AddLine(ImVec2(screen[1].x, screen[1].y), ImVec2(screen[5].x, screen[5].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasBack && !hasRightBack)
                draw_list->AddLine(ImVec2(screen[2].x, screen[2].y), ImVec2(screen[6].x, screen[6].y), ore.oreColor, 1.5f * scaleGlobal);
        }

        if (!hasBottom) {
            if (!hasFront && !hasBottomFront)
                draw_list->AddLine(ImVec2(screen[0].x, screen[0].y), ImVec2(screen[1].x, screen[1].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasRight && !hasBottomRight)
                draw_list->AddLine(ImVec2(screen[1].x, screen[1].y), ImVec2(screen[2].x, screen[2].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasBack && !hasBottomBack)
                draw_list->AddLine(ImVec2(screen[2].x, screen[2].y), ImVec2(screen[3].x, screen[3].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasLeft && !hasBottomLeft)
                draw_list->AddLine(ImVec2(screen[3].x, screen[3].y), ImVec2(screen[0].x, screen[0].y), ore.oreColor, 1.5f * scaleGlobal);
        }

        if (!hasTop) {
            if (!hasFront && !hasTopFront)
                draw_list->AddLine(ImVec2(screen[4].x, screen[4].y), ImVec2(screen[5].x, screen[5].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasRight && !hasTopRight)
                draw_list->AddLine(ImVec2(screen[5].x, screen[5].y), ImVec2(screen[6].x, screen[6].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasBack && !hasTopBack)
                draw_list->AddLine(ImVec2(screen[6].x, screen[6].y), ImVec2(screen[7].x, screen[7].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasLeft && !hasTopLeft)
                draw_list->AddLine(ImVec2(screen[7].x, screen[7].y), ImVec2(screen[4].x, screen[4].y), ore.oreColor, 1.5f * scaleGlobal);
        }

        if (!hasFront) {
            if (!hasBottom && !hasBottomFront)
                draw_list->AddLine(ImVec2(screen[0].x, screen[0].y), ImVec2(screen[1].x, screen[1].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasTop && !hasTopFront)
                draw_list->AddLine(ImVec2(screen[4].x, screen[4].y), ImVec2(screen[5].x, screen[5].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasLeft && !hasLeftFront)
                draw_list->AddLine(ImVec2(screen[0].x, screen[0].y), ImVec2(screen[4].x, screen[4].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasRight && !hasRightFront)
                draw_list->AddLine(ImVec2(screen[1].x, screen[1].y), ImVec2(screen[5].x, screen[5].y), ore.oreColor, 1.5f * scaleGlobal);
        }

        if (!hasBack) {
            if (!hasBottom && !hasBottomBack)
                draw_list->AddLine(ImVec2(screen[2].x, screen[2].y), ImVec2(screen[3].x, screen[3].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasTop && !hasTopBack)
                draw_list->AddLine(ImVec2(screen[6].x, screen[6].y), ImVec2(screen[7].x, screen[7].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasRight && !hasRightBack)
                draw_list->AddLine(ImVec2(screen[2].x, screen[2].y), ImVec2(screen[6].x, screen[6].y), ore.oreColor, 1.5f * scaleGlobal);
            if (!hasLeft && !hasLeftBack)
                draw_list->AddLine(ImVec2(screen[3].x, screen[3].y), ImVec2(screen[7].x, screen[7].y), ore.oreColor, 1.5f * scaleGlobal);
        }
    }
}