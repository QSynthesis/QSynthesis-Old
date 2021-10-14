#include "VibratoLineHandle.h"
#include "../../Editor/Areas/NotesArea.h"
#include "../../Controllers/Mode2Handler.h"
#include "../../TuningGroup.h"
#include "QUtils.h"

VibratoLineHandle::VibratoLineHandle(Qt::Orientation orient, NotesArea *editor, Mode2Handler *scope,
                                     QGraphicsItem *parent)
    : VibratoObject(editor, scope), GraphicsLineHandle(orient, parent) {
    init();
}

VibratoLineHandle::~VibratoLineHandle() {
}

void VibratoLineHandle::init() {
    m_region = NO_RECT;
    m_show = false;
    m_lineColor = Qt::darkGray;
}

void VibratoLineHandle::updateRect() {
    if (m_orient == Qt::Horizontal) {
        setTopLeft(-m_lineWidth / 2, 0);
        setSize(m_lineWidth, m_region.height());
    } else {
        setTopLeft(0, -m_lineWidth / 2);
        setSize(m_region.width(), m_lineWidth);
    }
}

MorePoint VibratoLineHandle::limitArea(MorePoint origin) {
    if (m_region == NO_RECTF) {
        return origin;
    }

    int h = m_editor->ptrs()->currentHeight;
    double h1 = h / 2;
    double unit_y = int(origin.y() / h1 - 0.5) * h1 + double(h) / 2;

    QPointF p = origin;

    if (m_orient == Qt::Horizontal) {
        if (origin.x() < m_region.left()) {
            origin.setX(m_region.left());
        } else if (origin.x() > m_region.right()) {
            origin.setX(m_region.right());
        }
        origin.setY(m_region.top());
    } else {
        Qt::KeyboardModifiers c = QApplication::keyboardModifiers();
        bool c1 = c == Qt::ControlModifier;

        if (c1 && m_move) {
            origin.setY(unit_y);
        }

        if (origin.y() < m_region.top()) {
            origin.setY(m_region.top());
        } else if (origin.y() > m_region.bottom()) {
            origin.setY(m_region.bottom());
        }
        origin.setX(m_region.left());
    }

    return origin;
}

void VibratoLineHandle::setRegion(const QRectF &region) {
    m_region = region;

    if (m_region == NO_RECT) {
        hide();
        return;
    } else {
        show();
    }

    if (m_orient == Qt::Horizontal) {
        setLocation(limitArea(MorePoint(x(), region.top())));
    } else {
        setLocation(limitArea(MorePoint(region.left(), y())));
    }
    updateRect();
}

double VibratoLineHandle::lineWidth() const {
    return m_lineWidth;
}

void VibratoLineHandle::setLineWidth(double lineWidth) {
    m_lineWidth = lineWidth;
    updateRect();
}

QColor VibratoLineHandle::lineColor() const {
    return m_lineColor;
}

void VibratoLineHandle::setLineColor(const QColor &lineColor) {
    m_lineColor = lineColor;
    update();
}

bool VibratoLineHandle::showLine() const {
    return m_show;
}

void VibratoLineHandle::setShowLine(bool show) {
    m_show = show;
}

void VibratoLineHandle::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDragIn.removeAll();
    if (event->button() == Qt::LeftButton) {
        afterPress();
    }
}

void VibratoLineHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        afterMove(event->scenePos());
    }
}

void VibratoLineHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    afterRelease();
}

void VibratoLineHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    GraphicsLineHandle::hoverLeaveEvent(event);
    if (m_move) {
        afterRelease();
    }
}

void VibratoLineHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                             QWidget *widget) {
    if (!m_show) {
        return;
    }
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_lineColor);
    painter->drawRect(0, 0, rect().width(), rect().height());
}

void VibratoLineHandle::afterPress() {
    emit pressed();
}

void VibratoLineHandle::afterMove(QPointF pos) {
    if (!m_move) {
        linkPress(pos);
    }
    if (m_move) {
        linkMove(pos);
        emit moved();
    }
}

void VibratoLineHandle::afterRelease() {
    if (m_move) {
        linkRelease();
        emit clicked();
    }
}
