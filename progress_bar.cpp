#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <unistd.h>


using namespace std;

const int BAR_LENGTH = 50;
const int MAX_TASK = 5;

struct Task {
    int id;
    int progress;
    int step;
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait(int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}

void printBar(const Task& t) {
    cout << "Task " << t.id << ": [";

    int filled = (t.progress * BAR_LENGTH) / 100;
    for (int i = 0; i < BAR_LENGTH; ++i) {
        if (i < filled)
            cout << "=";
        else
            cout << " ";
    }

    cout << "] " << t.progress << "%\n";
}

int main() {
    Task tasks[MAX_TASK];
    srand((time(nullptr)));

    for (int i = 0; i < MAX_TASK; ++i) {
        tasks[i].id = i + 1;
        tasks[i].progress = 0;
        tasks[i].step = rand() % 5 + 1;
    }

    bool taskIncomplete = true;

    while (taskIncomplete) {
        taskIncomplete = false;
        clearScreen();

        for (int i = 0; i < MAX_TASK; ++i) {
            if (tasks[i].progress < 100) {
                tasks[i].progress += tasks[i].step;
                if (tasks[i].progress > 100)
                    tasks[i].progress = 100;
                taskIncomplete = true;
            }
            printBar(tasks[i]);
        }

        wait(1);
    }

    cout << "ALL TASKS COMPLETED!!" << endl;
    printf("Developed By: Anuj Shukla");
    return 0;
}
