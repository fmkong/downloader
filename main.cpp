#include <iostream>

#include "logger.h"
#include "sir.hh"
#include "sir.h"

int report_error(void)
{
    sirchar_t message[SIR_MAXERROR] = {0};
    uint16_t code = sir_geterror(message);
    fprintf(stderr, "libsir error: (%hu, %s)\n", code, message);
    return 1;
}

int main()
{
//    std::cout << "hello\n";
    sirinit si = {0};
    /*
     * Configure levels for stdout.
     * Send debug, information, warning, and notice messages there.
     */
    si.d_stdout.levels = SIRL_DEBUG | SIRL_INFO | SIRL_WARN | SIRL_NOTICE;
    /*
     * Configure options for stdout.
     * Don't show the time stamp or process ID.
     */
    si.d_stdout.opts = SIRO_NOTIME | SIRO_NOPID;
    /*
     * Configure levels for stderr.
     * Send error and above there.
     */
    si.d_stderr.levels = SIRL_ERROR | SIRL_CRIT | SIRL_ALERT | SIRL_EMERG;
    /*
     * Configure options for stderr.
     * Don't show the time stamp or process ID.
     */
    si.d_stderr.opts = SIRO_NOTIME | SIRO_NOPID;
    /*
     * Configure options for syslog.
     * Don't send any output there.
     */
    si.d_syslog.levels = 0;
    /* Configure a name to associate with our output. */
    strcpy(si.processName, "example");
    /* Initialize SIR. */
    if (!sir_init(&si)) {
        return report_error();
    }
    /*
     * Configure and add a log file.
     * Don't show the process name.
     * Send all severity levels there.
     */
    sirfileid_t fileid1 = sir_addfile("sir-example.log", SIRL_ALL, SIRO_NONAME);
    if (NULL == fileid1) {
        return report_error();
    }
    /* Now we're ready to start generating output. */
    int n = 12345;
    const char* somestr = "my string contents";
    float f = 0.0009f;
    /*
     * This will be sent to all destinations registered for ::SIRL_DEBUG.
     * Notice that it is not necessary to add a newline at the end. libsir does
     * this automatically.
     */
    sir_debug("debug-level message: {n=%d, somestr='%s', f=%.04f}",
              n, somestr, f);
    /* Do the same for the rest of available severity levels. */
    sir_info("info-level message: {n=%d, somestr='%s', f=%.04f}", n, somestr, f);
    sir_notice("notice-level message: {n=%d, somestr='%s', f=%.04f}", n, somestr, f);
    sir_warn("warning-level message: {n=%d, somestr='%s', f=%.04f}", n, somestr, f);
    sir_error("error-level message: {n=%d, somestr='%s', f=%.04f}", n, somestr, f);
    sir_crit("critical error-level message: {n=%d, somestr='%s', f=%.04f}", n, somestr, f);
    sir_alert("alert-level message: {n=%d, somestr='%s', f=%.04f}", n, somestr, f);
    sir_emerg("emergency-level message: {n=%d, somestr='%s', f=%.04f}", n, somestr, f);

//    sir::logger logger;
//    logger.info("info c++ test");

    XLOGE("main") << "TEST " << f;
    XLOGD("main") << "TEST ";
    LOGD("main", "test");
    /* Clean up. */
    sir_cleanup();
}