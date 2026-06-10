#pragma once

struct AppState {
    // These switches control which windows are currently open.
    // They all start as 'false' so the desktop is clean when the OS boots up.
    
    bool showTaskManager = false;
    bool showApp1 = false;       // Replace 'App1' with whatever custom app Member 2 decides to make
    bool showApp2 = false;       // Replace 'App2' with whatever custom app Member 2 decides to make
};