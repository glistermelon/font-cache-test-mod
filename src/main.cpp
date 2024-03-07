#include <Geode/Geode.hpp>

#ifndef GEODE_IS_WINDOWS
#error This test is for windows only what are you doing
#else

using namespace geode::prelude;

const std::string font1Spr = "Oswald ExtraLight.ttf"_spr;
const std::string font2Spr = "Satisfy.ttf"_spr;
ghc::filesystem::path font1 = Mod::get()->getResourcesDir() / "Oswald ExtraLight.ttf";
ghc::filesystem::path font2 = Mod::get()->getResourcesDir() / "Satisfy.ttf";

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
    CCLabelTTF* label;
    void modFont(float) {
        std::string font2Str = font2.string();
        m_fields->label->setFontName(font2Spr.c_str());
        m_fields->label->setString("Close the game.");
    }
	bool init() {
        std::string font1Str = font1.string(), font2Str = font2.string();
        {
            ghc::filesystem::copy_file(font1, font1Str + ".backup");
            ghc::filesystem::copy_file(font2, font2Str + ".backup");
            std::error_code ec;
            bool fail1 = false, fail2 = false;
            ghc::filesystem::remove(font1, ec);
            if (ec) {
                fail1 = true;
                ghc::filesystem::remove(font1Str + ".backup");
            }
            else ghc::filesystem::rename(font1Str + ".backup", font1);
            ghc::filesystem::remove(font2, ec);
            if (ec) {
                fail2 = true;
                ghc::filesystem::remove(font2Str + ".backup");
            }
            else ghc::filesystem::rename(font2Str + ".backup", font2);
            std::string result;
            if (fail1 || fail2) {
                if (fail1 && fail2) result = "Both fonts are locked.";
                else if (fail1) result = "Font 1 is locked.";
                else result = "Font 2 is locked.";
                result.insert(0, "Failed. ");
            }
            else result = "Success. Both fonts were released. (Ignore this if this is the first time you opened the test.)";
            MessageBoxA(NULL, result.c_str(), "Font Cache Fix Test Results", 0);
        }
		if (!MenuLayer::init()) return false;
        m_fields->label = CCLabelTTF::create("Wait...", font1Spr.c_str(), 70.0f);
        m_fields->label->setPosition(this->getContentSize() / 2);
        m_fields->label->setZOrder(1000); // sure
        this->addChild(m_fields->label);
        this->scheduleOnce(schedule_selector(MyMenuLayer::modFont), 1);
        return true;
	}
};

#endif