#ifndef LOGGER_H
#define LOGGER_H
#include <mutex>
#include <string>
#include <unordered_map>


class Logger {
public:
    static void Add(const std::string &name) {
        Instance().AddInternal(name);
    }

    static void Flush() {
        Instance().FlushInternal();
    }

private:
    Logger() = default;

    static Logger &Instance();

    void AddInternal(const std::string &name);

    void FlushInternal();

    std::unordered_map<std::string, int> m_NameCounts;
    std::mutex m_Mutex;
};


#endif //LOGGER_H
