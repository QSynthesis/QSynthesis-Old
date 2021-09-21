#include "GraphicsDragger.h"

GraphicsDragger::GraphicsDragger(QGraphicsItem *parent) : QGraphicsRectItem(parent) {
    init();
}

GraphicsDragger::GraphicsDragger(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent) {
    init();
}

GraphicsDragger::GraphicsDragger(double x, double y, double w, double h, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, w, h, parent) {
    init();
}

void GraphicsDragger::init() {
    m_element = Unknown;

    m_move = false;
    m_moving = false;
    m_involved = false;

    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
}

GraphicsDragger::~GraphicsDragger() {
}

GraphicsDragger::Element GraphicsDragger::element() const {
    return m_element;
}

bool GraphicsDragger::isToMove() const {
    return m_move;
}

bool GraphicsDragger::isMoving() const {
    return m_moving;
}

QSizeF GraphicsDragger::size() const {
    return rect().size();
}

double GraphicsDragger::width() const {
    return rect().width();
}

double GraphicsDragger::height() const {
    return rect().height();
}

QPointF GraphicsDragger::topLeft() const {
    return rect().topLeft();
}

double GraphicsDragger::top() const {
    return rect().top();
}

double GraphicsDragger::left() const {
    return rect().left();
}

void GraphicsDragger::setSize(QSizeF size) {
    setRect(rect().x(), rect().y(), size.width(), size.height());
}

void GraphicsDragger::setSize(double x, double y) {
    setSize(QSizeF(x, y));
}

void GraphicsDragger::setWidth(double w) {
    setSize(QSizeF(w, height()));
}

void GraphicsDragger::setHeight(double h) {
    setSize(QSizeF(width(), h));
}

void GraphicsDragger::setLocation(QPointF pos) {
    prepareGeometryChange();
    setPos(pos);
}

void GraphicsDragger::setLocation(double x, double y) {
    setLocation(QPointF(x, y));
}

void GraphicsDragger::setXLocation(double x) {
    setLocation(QPointF(x, y()));
}

void GraphicsDragger::setYLocation(double y) {
    setLocation(QPointF(x(), y));
}

void GraphicsDragger::setTopLeft(QPointF topLeft) {
    QPointF bottomRight = rect().bottomRight();
    prepareGeometryChange();
    setRect(topLeft.x(), topLeft.y(), bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y());
}

void GraphicsDragger::setTopLeft(double left, double top) {
    setTopLeft(QPointF(left, top));
}

void GraphicsDragger::setLeft(double left) {
    setTopLeft(left, top());
}

void GraphicsDragger::setTop(double top) {
    setTopLeft(left(), top);
}

QPointF GraphicsDragger::staticPos() const {
    if (m_moving || m_involved) {
        return m_windowPoint;
    } else {
        return pos();
    }
}

QSizeF GraphicsDragger::staticSize() const {
    return m_windowSize;
}

void GraphicsDragger::setInvolved(bool value) {
    m_involved = value;
}

bool GraphicsDragger::isInvolved() const {
    return m_involved;
}

void GraphicsDragger::setSelected(bool selected) {
    QGraphicsRectItem::setSelected(selected);
}

void GraphicsDragger::externLimitArea() {
    setLocation(limitAreaT(pos()));
}

bool GraphicsDragger::operator<(const GraphicsDragger &another) const {
    return this->x() < another.x();
}

void GraphicsDragger::linkPress(QPointF pos) {
    QPointF global_pos = pos;

    m_move = true;
    m_startPoint = global_pos;
    m_prevPoint = this->pos();

    m_windowSize = size();
    m_prevSize = size();
    m_windowPoint = this->pos();
}

void GraphicsDragger::linkMove(QPointF pos) {
    QPointF global_pos = pos;
    QPointF relative_pos = global_pos - m_startPoint;

    m_moving = true;
    setLocation(limitArea(MorePoint(m_windowPoint + relative_pos)));

    m_posChanged = false;
    if (this->pos() != m_prevPoint) {
        handlePosChange();
        m_prevPoint = this->pos();
        m_posChanged = true;
    }
}

void GraphicsDragger::linkRelease() {
    m_move = false;
    m_moving = false;
}

void GraphicsDragger::linkAbandon() {
    m_move = false;
    m_moving = false;

    setSize(m_windowSize);
    setLocation(m_windowPoint);
}

void GraphicsDragger::involvePress(QPointF pos) {
    m_involved = true;
    m_windowSize = size();
    m_windowPoint = this->pos();
}

void GraphicsDragger::involveMove(QPointF pos) {
    setLocation(limitAreaT(m_windowPoint));

    m_posChanged = false;
    if (this->pos() != m_prevPoint) {
        handlePosChange();
        m_prevPoint = this->pos();
        m_posChanged = true;
    }
}

void GraphicsDragger::involveRelease() {
    m_involved = false;
}

void GraphicsDragger::involveAbandon() {
    m_involved = false;
    setLocation(m_windowPoint);
    setSize(m_windowSize);
}

MorePoint GraphicsDragger::limitArea(MorePoint p) {
    return p;
}

MorePoint GraphicsDragger::limitAreaT(MorePoint p) {
    return p;
}

MoreSize GraphicsDragger::limitSize(MoreSize s) {
    return s;
}

void GraphicsDragger::handlePosChange() {
}

void GraphicsDragger::handleSizeChange() {
}
