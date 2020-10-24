
#ifndef LOGGER_H
#define LOGGER_H
#include <stdarg.h>
#include "../libsir/sir.h"

#ifdef __cplusplus
#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <functional>
extern "C" {
#endif /*__cplusplus */

typedef enum {
    TLOGGER_DEBUG = 0,
    TLOGGER_INFO,
    TLOGGER_NOTICE,
    TLOGGER_WARN,
    TLOGGER_ERROR,
    TLOGGER_CRITICAL,
    TLOGGER_ALERT,
    TLOGGER_EMERG,
    TLOGGER_END,
} TLoggerLevel;

#define LOGD(TAG, fmt, ...)     sir_debug("[%s]" fmt "\n", TAG, ##__VA_ARGS__)
#define LOGI(TAG, fmt, ...)     sir_info("[%s]" fmt "\n", TAG, ##__VA_ARGS__)
#define LOGN(TAG, fmt, ...)     sir_notice("[%s]" fmt "\n", TAG, ##__VA_ARGS__)
#define LOGW(TAG, fmt, ...)     sir_warn("[%s]" fmt "\n", TAG, ##__VA_ARGS__)
#define LOGE(TAG, fmt, ...)     sir_error("[%s]" fmt "\n", TAG, ##__VA_ARGS__)
#define LOGCRIT(TAG, fmt, ...)  sir_crit("[%s]" fmt "\n", TAG, ##__VA_ARGS__)
#define LOGALERT(TAG, fmt, ...) sir_alert("[%s]" fmt "\n", TAG, ##__VA_ARGS__)
#define LOGEMERG(TAG, fmt, ...) sir_emerg("[%s]" fmt "\n", TAG, ##__VA_ARGS__)

bool loggerInit();
bool loggerCleanup();


#ifdef __cplusplus
class TLogger {
    using Stream = std::ostringstream;
    using Buffer = std::unique_ptr<Stream, std::function<void(Stream*)>>;
public:
    TLogger(){}
    ~TLogger(){}

    static TLogger &Instance() {
        static TLogger logger;
        return logger;
    }

    Buffer LogStream(const char *tag, TLoggerLevel level, const char *file, int line, const char *func, void *userptr) {
            return Buffer(new Stream, [=](Stream *st) {
                switch(level) {
                    case TLOGGER_DEBUG:
                        sir_debug("[%s] %s\n", tag, st->str().c_str());
                        break;
                    case TLOGGER_INFO:
                        sir_info("[%s] %s\n", tag, st->str().c_str());
                        break;
                    case TLOGGER_NOTICE:
                        sir_notice("[%s] %s\n", tag, st->str().c_str());
                        break;
                    case TLOGGER_WARN:
                        sir_warn("[%s] %s\n", tag, st->str().c_str());
                        break;
                    case TLOGGER_ERROR:
                        sir_error("[%s] %s\n", tag, st->str().c_str());
                        break;
                    case TLOGGER_CRITICAL:
                        sir_crit("[%s] %s\n", tag, st->str().c_str());
                        break;
                    case TLOGGER_ALERT:
                        sir_alert("[%s] %s\n", tag, st->str().c_str());
                        break;
                    case TLOGGER_EMERG:
                        sir_emerg("[%s] %s\n", tag, st->str().c_str());
                        break;
                    default:
                        break;
                }
                delete st;
        });
    }
};

#define TLoggerIns (TLogger::Instance())
#define TLoggerStream(tag, level)  (*TLoggerIns.LogStream(tag, level, __FILE__, __LINE__, __func__, NULL))
#define XLOGD(TAG)        TLoggerStream(TAG, TLOGGER_DEBUG)
#define XLOGI(TAG)        TLoggerStream(TAG, TLOGGER_INFO)
#define XLOGN(TAG)        TLoggerStream(TAG, TLOGGER_NOTICE)
#define XLOGW(TAG)        TLoggerStream(TAG, TLOGGER_WARN)
#define XLOGE(TAG)        TLoggerStream(TAG, TLOGGER_ERROR)
#define XLOGCRIT(TAG)     TLoggerStream(TAG, TLOGGER_CRITICAL)
#define XLOGALERT(TAG)    TLoggerStream(TAG, TLOGGER_ALERT)
#define XLOGEMERG(TAG)    TLoggerStream(TAG, TLOGGER_EMERG)

} /*__cplusplus */
#else

#endif
#endif // !LOGGER_H