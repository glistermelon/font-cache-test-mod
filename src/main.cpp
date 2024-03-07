#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
        auto label = CCLabelTTF::create("Hello World", "Satisfy.ttf"_spr, 100.0f);
        label->setPosition(this->getContentSize() / 2);
        label->setZOrder(1000); // sure
        this->addChild(label);
        return true;
	}
};