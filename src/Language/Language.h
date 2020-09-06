#pragma once
#include "../Singleton/Singleton.h"
#include <string>
#include <vector>

class Language : public Singleton<Language> {
    Language();
    ~Language();
    friend Singleton<Language>;
public:
    bool Initialize();
    bool Finalize();
    bool ChangeLanguage(std::string lang);

    std::string GetString(std::string key, ...);
private:
    bool LoadFile();

    std::string m_language;
};