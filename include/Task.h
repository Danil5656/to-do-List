#include <string>
#include <ctime>
#include <cstdint>

class Task
{
public: 
    Task(const std::string &description, uint8_t priority, bool isCompleted = false):
    m_description(description), m_isCompleted(isCompleted) {
        m_priority = priority;
        m_dateAdded = getCurrentTime();
        m_dateAdded.pop_back();
    }

    void markCompleted()
    {
        m_isCompleted = true;
        m_dateCompleted = getCurrentTime();
    }

    std::string getCurrentTime()
    {
        time_t now = time(nullptr);
        std::string currentTime = std::ctime(&now);
        return currentTime;
    }

private:
    std::string m_description;
    std::string m_dateAdded;
    std::string m_dateCompleted;
    bool m_isCompleted;
    uint8_t m_priority;
    enum Priority {
        low    = 1,
        medium = 2,
        heigh  = 3
    };
};
