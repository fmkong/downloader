//
//#include "sir.h"
//
//bool report_error(void)
//{
//    sirchar_t message[SIR_MAXERROR] = {0};
//    uint16_t code = sir_geterror(message);
//    fprintf(stderr, "libsir error: (%hu, %s)\n", code, message);
//    return false;
//}
//
//bool loggerInit()
//{
//    sirinit si;
//
//    memset(&si, 0, sizeof(si));
///*
// * Configure levels for stdout.
// * Send debug, information, warning, and notice messages there.
// */
//    si.d_stdout.levels = SIRL_DEBUG | SIRL_INFO | SIRL_WARN | SIRL_NOTICE;
///*
// * Configure options for stdout.
// * Don't show the time stamp or process ID.
// */
//    si.d_stdout.opts = SIRO_NOTIME | SIRO_NOPID;
///*
// * Configure levels for stderr.
// * Send error and above there.
// */
//    si.d_stderr.levels = SIRL_ERROR | SIRL_CRIT | SIRL_ALERT | SIRL_EMERG;
///*
// * Configure options for stderr.
// * Don't show the time stamp or process ID.
// */
//    si.d_stderr.opts = SIRO_NOTIME | SIRO_NOPID;
///*
// * Configure options for syslog.
// * Don't send any output there.
// */
//    si.d_syslog.levels = 0;
///* Configure a name to associate with our output. */
//    strcpy(si.processName, "example");
///* Initialize SIR. */
//    if (!sir_init(&si)) {
//        return report_error();
//    }
///*
// * Configure and add a log file.
// * Don't show the process name.
// * Send all severity levels there.
// */
//    sirfileid_t fileid1 = sir_addfile("sir-example.log", SIRL_ALL, SIRO_NONAME);
//    if (NULL == fileid1) {
//        return report_error();
//    }
//
//    return true;
//}
//
//bool loggerCleanup()
//{
//    return sir_cleanup();
//}