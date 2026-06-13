#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "AWindow.h"

class TaskManagerWindow : public AWindow {
public:
    TaskManagerWindow() : AWindow("Task Manager") {}
    ~TaskManagerWindow() override = default;

    void draw() override;
};

#endif