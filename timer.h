#pragma once
#include <iostream>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include <stdio.h>
#include "ServerListener.h"

volatile static long counter = 0;

static void notify(int signum);

typedef void (ServerListener::*ProcessHandler)(int n);

class Timer {
protected:

    struct sigaction  _act;

    struct sigaction  _oldact;

    struct itimerval  _tim_ticks;

    void wait(long timeout_ms);

public:

    Timer(int sec, int usec);

    void setHandler(ProcessHandler handler);

    bool reset();
};
