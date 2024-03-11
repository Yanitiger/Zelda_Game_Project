#pragma once

#include "ofMain.h"
#include "Map.h"
#include "Fire.h"
#include "PixelConstants.h"
#include <map>
#include <memory>

class MapBuilder {

private:
    shared_ptr<Handler> handler;
    ofFbo createFbo(ofImage pixelMap);
    EntityPixelColors entityPixelColors;
    TilePixelColors tilePixelColors;
    shared_ptr<Section> createSection(int, int, shared_ptr<Link>&, ofImage);

public:
    MapBuilder(shared_ptr<Handler> handler);
    unique_ptr<Map> createMap(ofImage);

};
