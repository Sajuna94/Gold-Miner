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
        std::cout << "Destructed Log:\n";
        for (const auto &[name, count]: m_NameCounts) {
            std::cout << "  " << name << ": " << count << " times\n";
        }
        m_NameCounts.clear();
    }
}
