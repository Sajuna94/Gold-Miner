#include "Core/Logger.h"

#include <iostream>

Logger &Logger::Instance() {
    static Logger instance;
    return instance;
}

void Logger::AddInternal(const std::string &name) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_NameCounts[name]++;
}

void Logger::FlushInternal() {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (!m_NameCounts.empty()) {
        std::cout << "[Destruct]\n";
        for (const auto &[name, count]: m_NameCounts) {
            printf("> %-8s x %-2d\n", name.c_str(), count);
        }
        m_NameCounts.clear();
    }
}
