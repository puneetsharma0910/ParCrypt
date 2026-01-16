#include "Cryption.hpp"
#include "../fileHandling/ReadEnv.cpp"
#include "../processes/Task.hpp"
using namespace std;

int executeCryption(const string &taskData)
{
    Task task = Task::fromString(taskData);
    ReadEnv env;

    string envKey = env.getenv();
    int key = stoi(envKey);

    if (task.action == Action::ENCRYPT)
    {
        char ch;
        while (task.f_stream.get(ch))
        {
            ch = (ch + key) % 256;
            task.f_stream.seekp(-1, std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }
    else
    {
        char ch;
        while (task.f_stream.get(ch))
        {
            ch = (ch - key + 256) % 256;
            task.f_stream.seekp(-1, std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }
    return 0;
}