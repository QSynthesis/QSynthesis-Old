#ifndef MACROS_H
#define MACROS_H

#include <QObject>
#include <cstdarg>

#define Slash '/'

// Singleton
#define Q_SINGLETON(T)                                                                             \
private:                                                                                           \
    static T *self;                                                                                \
                                                                                                   \
public:                                                                                            \
    static T *createCase() {                                                                       \
        Q_ASSERT(!self);                                                                           \
        self = new T();                                                                            \
        return self;                                                                               \
    }                                                                                              \
                                                                                                   \
    static void destroyCase() {                                                                    \
        Q_ASSERT(self);                                                                            \
        delete self;                                                                               \
        self = nullptr;                                                                            \
    }                                                                                              \
                                                                                                   \
    T *createCasePrivate() {                                                                       \
        Q_ASSERT(!self);                                                                           \
        self = this;                                                                               \
        return self;                                                                               \
    }                                                                                              \
                                                                                                   \
    T *createCasePrior() {                                                                         \
        if (!self) {                                                                               \
            self = this;                                                                           \
        }                                                                                          \
        return this;                                                                               \
    }                                                                                              \
                                                                                                   \
public:                                                                                            \
    static T *instance() {                                                                         \
        return self;                                                                               \
    }

#define Q_SINGLETON_DECLARE(T) T *T::self = nullptr;

// Default Codec
#ifndef Q_CHARSET_PRIVATE
#define Q_CHARSET                                                                                  \
protected:                                                                                         \
    QTextCodec *m_codec;                                                                           \
                                                                                                   \
public:                                                                                            \
    QTextCodec *codec() const;                                                                     \
    void setCodec(QTextCodec *codec);                                                              \
                                                                                                   \
private:                                                                                           \
    static QTextCodec *defaultCodec;                                                               \
                                                                                                   \
public:                                                                                            \
    static QTextCodec *codeForDefault();                                                           \
    static void setCodeForDefault(QTextCodec *codec);

#define Q_CHARSET_DECLARE(T)                                                                       \
    QTextCodec *T::defaultCodec = nullptr;                                                         \
                                                                                                   \
    QTextCodec *T::codec() const {                                                                 \
        return m_codec;                                                                            \
    }                                                                                              \
                                                                                                   \
    void T::setCodec(QTextCodec *codec) {                                                          \
        m_codec = codec;                                                                           \
    }                                                                                              \
                                                                                                   \
    QTextCodec *T::codeForDefault() {                                                              \
        return defaultCodec;                                                                       \
    }                                                                                              \
                                                                                                   \
    void T::setCodeForDefault(QTextCodec *codec) {                                                 \
        defaultCodec = codec;                                                                      \
    }
#else
#define Q_CHARSET                                                                                  \
private:                                                                                           \
    static QTextCodec *defaultCodec;                                                               \
                                                                                                   \
public:                                                                                            \
    static QTextCodec *codeForDefault();                                                           \
    static void setCodeForDefault(QTextCodec *codec);

#define Q_CHARSET_DECLARE(T)                                                                       \
    QTextCodec *T::defaultCodec = nullptr;                                                         \
                                                                                                   \
    QTextCodec *T::codeForDefault() {                                                              \
        return defaultCodec;                                                                       \
    }                                                                                              \
                                                                                                   \
    void T::setCodeForDefault(QTextCodec *codec) {                                                 \
        defaultCodec = codec;                                                                      \
    }
#endif

#endif // MACROS_H
