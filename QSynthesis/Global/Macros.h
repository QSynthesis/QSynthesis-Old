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
private:                                                                                           \
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
#define Q_CHARSET_INSTANCE                                                                         \
protected:                                                                                         \
    QTextCodec *m_codec;                                                                           \
                                                                                                   \
public:                                                                                            \
    QTextCodec *codec() const;                                                                     \
    void setCodec(QTextCodec *codec);

#define Q_CHARSET_STATIC                                                                           \
private:                                                                                           \
    static QTextCodec *defaultCodec;                                                               \
                                                                                                   \
public:                                                                                            \
    static QTextCodec *codeForDefault();                                                           \
    static void setCodeForDefault(QTextCodec *codec);

#define Q_CHARSET_INSTANCE_DECLARE(T)                                                              \
    QTextCodec *T::codec() const {                                                                 \
        return m_codec;                                                                            \
    }                                                                                              \
                                                                                                   \
    void T::setCodec(QTextCodec *codec) {                                                          \
        m_codec = codec;                                                                           \
    }

#define Q_CHARSET_STATIC_DECLARE(T)                                                                \
    QTextCodec *T::defaultCodec = nullptr;                                                         \
                                                                                                   \
    QTextCodec *T::codeForDefault() {                                                              \
        return defaultCodec;                                                                       \
    }                                                                                              \
                                                                                                   \
    void T::setCodeForDefault(QTextCodec *codec) {                                                 \
        defaultCodec = codec;                                                                      \
    }

#define Q_CHARSET                                                                                  \
    Q_CHARSET_INSTANCE                                                                             \
    Q_CHARSET_STATIC

#define Q_CHARSET_DECLARE(T)                                                                       \
    Q_CHARSET_INSTANCE_DECLARE(T)                                                                  \
    Q_CHARSET_STATIC_DECLARE(T)

#define Q_W(T) qobject_cast<QWidget *>(T)

#endif // MACROS_H
