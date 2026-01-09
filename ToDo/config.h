#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

class Config {
public:
    static Config& instance() {
        static Config instance;
        return instance;
    }
    QString serverUrl() const { return "http://localhost:8000"; }
    bool useLocalStorage() const { return false; }
    QString localDataPath() const { return "tasks.txt"; }

private:
    Config() {}
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
};

#endif // CONFIG_H
