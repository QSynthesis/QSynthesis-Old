#ifndef MORESIZE_H
#define MORESIZE_H

#include <QSizeF>

class MoreSize : public QSizeF {
public:
    MoreSize();
    MoreSize(const QSize &sz);
    MoreSize(const QSizeF &sz);
    MoreSize(double w, double h);
    MoreSize(double w, double h, int l);
    virtual ~MoreSize();

    int length() const;
    void setLength(int length);

private:
    int m_length;
};

#endif // MORESIZE_H
