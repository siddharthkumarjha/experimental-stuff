#include <fcntl.h>
#include <libudev.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <execinfo.h>
#include <signal.h>
#include <stdbool.h>

#define STRINGIFY(TOK) #TOK

static const char* g_ErrToStr[] = {
    [SIGHUP]     =  STRINGIFY(SIGHUP),
    [SIGINT]     =  STRINGIFY(SIGINT),
    [SIGQUIT]    =  STRINGIFY(SIGQUIT),
    [SIGILL]     =  STRINGIFY(SIGILL),
    [SIGTRAP]    =  STRINGIFY(SIGTRAP),
    [SIGABRT]    =  STRINGIFY(SIGABRT),
    [SIGBUS]     =  STRINGIFY(SIGBUS),
    [SIGFPE]     =  STRINGIFY(SIGFPE),
    [SIGKILL]    =  STRINGIFY(SIGKILL),
    [SIGUSR1]    =  STRINGIFY(SIGUSR1),
    [SIGSEGV]    =  STRINGIFY(SIGSEGV),
    [SIGUSR2]    =  STRINGIFY(SIGUSR2),
    [SIGPIPE]    =  STRINGIFY(SIGPIPE),
    [SIGALRM]    =  STRINGIFY(SIGALRM),
    [SIGTERM]    =  STRINGIFY(SIGTERM),
    [SIGSTKFLT]  =  STRINGIFY(SIGSTKFLT),
    [SIGCHLD]    =  STRINGIFY(SIGCHLD),
    [SIGCONT]    =  STRINGIFY(SIGCONT),
    [SIGSTOP]    =  STRINGIFY(SIGSTOP),
    [SIGTSTP]    =  STRINGIFY(SIGTSTP),
    [SIGTTIN]    =  STRINGIFY(SIGTTIN),
    [SIGTTOU]    =  STRINGIFY(SIGTTOU),
    [SIGURG]     =  STRINGIFY(SIGURG),
    [SIGXCPU]    =  STRINGIFY(SIGXCPU),
    [SIGXFSZ]    =  STRINGIFY(SIGXFSZ),
    [SIGVTALRM]  =  STRINGIFY(SIGVTALRM),
    [SIGPROF]    =  STRINGIFY(SIGPROF),
    [SIGWINCH]   =  STRINGIFY(SIGWINCH),
    [SIGPOLL]    =  STRINGIFY(SIGPOLL),
    [SIGPWR]     =  STRINGIFY(SIGPWR),
    [SIGSYS]     =  STRINGIFY(SIGSYS),
};

static const char *my_strrchr(const char *lStart, size_t const lStrSize,
                              char const lCharToMatch)
{
    const char *lStrEnd = lStart + lStrSize;
    const char *lRetVal = lStart;
    while ((--lStrEnd >= lStart) && (*lStrEnd != lCharToMatch))
        ;
    if (lStrEnd >= lStart)
        lRetVal = lStrEnd + 1;
    return lRetVal;
}

static const char* g_ProgName = nullptr;

static void dumpStacktrace(void)
{
    const int32_t kBacktraceSize = 20; // NETS_CS_SUPRESS_DEBUG
    void *lTraceArray[kBacktraceSize];
    size_t lTraceSize = 0;
    char **lTraceStrings = nullptr;

    lTraceSize = backtrace(lTraceArray, kBacktraceSize); 
    lTraceStrings = backtrace_symbols(lTraceArray, lTraceSize); 

    printf("--- STACK TRACE --- %s\n", g_ProgName);

    for (size_t i = 0; i < lTraceSize; i++)
    {
       printf("[%s][%s]\n", g_ProgName, lTraceStrings[i]);
    }

    printf("--- STACK TRACE --- %s\n", g_ProgName);
    free(lTraceStrings);
}

static void sigTermHandler(int signum) // NETS_CS_SUPRESS_DEBUG
{
    printf(":Signal [%s] %s\n", g_ErrToStr[signum], g_ProgName);

    if (signum == SIGTERM || signum == SIGINT)
    {
        printf("WTF!! why?\n");
    }
    else
    {
        dumpStacktrace();
    }
}

void registerSignalHandler()
{
    static bool lRegisterSignal = false;

    if(!lRegisterSignal)
    {
        printf(":Signals registered %s\n", g_ProgName);
        signal(SIGTERM, sigTermHandler);        
        signal(SIGABRT, sigTermHandler);
        signal(SIGINT, sigTermHandler);
        signal(SIGSEGV, sigTermHandler);
        lRegisterSignal = true;
    }
}

int main(void)
{
    g_ProgName = my_strrchr(__FILE__, sizeof(__FILE__), '/');
    registerSignalHandler();

    struct udev *lUdev;
    struct udev_monitor *lMonUdev;
    struct pollfd lFdsToPoll[1];
    int lThisFd;

    lUdev = udev_new();
    if (lUdev == nullptr)
    {
        return 1;
    }

    lMonUdev = udev_monitor_new_from_netlink(lUdev, "kernel");
    udev_monitor_filter_add_match_subsystem_devtype(lMonUdev, "power_supply", nullptr);
    udev_monitor_enable_receiving(lMonUdev);

    lThisFd               = udev_monitor_get_fd(lMonUdev);
    lFdsToPoll[0].fd      = lThisFd;
    lFdsToPoll[0].events  = POLLIN;
    lFdsToPoll[0].revents = 0;

    if (poll(lFdsToPoll, 1, -1) > 0)
    {
        /* Never gets here! */
        struct udev_device *const dev = udev_monitor_receive_device(lMonUdev);
        if (dev != nullptr)
        {
            puts(udev_device_get_sysname(dev));
            udev_device_unref(dev);
        }
        else
            fputs("udev_monitor_receive_device() failed\n", stderr);
    }
    udev_unref(lUdev);
    return 0;
}
