#ifndef MACROS_H
#define MACROS_H

#include <QObject>
#include <cstdarg>

#define Slash '/'

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

#endif // MACROS_H
