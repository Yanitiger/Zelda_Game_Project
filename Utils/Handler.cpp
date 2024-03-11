#include "Handler.h"

// Initialize the static variables
ofRectangle Handler::HUD_SCREEN = ofRectangle(0, 0, Handler::SECTION_WIDTH, Handler::HUD_HEIGHT);
ofRectangle Handler::GAME_SCREEN = ofRectangle(0, Handler::HUD_HEIGHT, Handler::SECTION_WIDTH, Handler::SECTION_HEIGHT);
bool Handler::DEBUG = false;