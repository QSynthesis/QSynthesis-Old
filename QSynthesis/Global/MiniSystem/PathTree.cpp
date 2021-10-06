#include "PathTree.h"

// PathTree::Node
PathTree::Node::Node(const QString &path, Node *parent)
    : m_count(0), m_id(0), m_path(path), m_parent(nullptr) {
    if (parent) {
        setParent(parent);
    }
}

PathTree::Node::~Node() {
}

bool PathTree::Node::operator<(const PathTree::Node &another) const {
    return m_path < another.m_path;
}

PathTree::Node *PathTree::Node::parent() const {
    return m_parent;
}

QList<PathTree::Node *> PathTree::Node::childs() const {
    return m_childs;
}

int PathTree::Node::inc() {
    m_count++;
    return m_count;
}

int PathTree::Node::dec() {
    if (m_count > 0) {
        m_count--;
    }
    return m_count;
}

int PathTree::Node::count() const {
    return m_count;
}

QString PathTree::Node::path() const {
    return m_path;
}

long PathTree::Node::id() const {
    return m_id;
}

void PathTree::Node::setId(long id, bool recursive) {
    m_id = id;
    if (recursive) {
        for (auto it = m_childs.begin(); it != m_childs.end(); ++it) {
            (*it)->setId(id, true);
        }
    }
}

void PathTree::Node::setPath(const QString &path) {
    m_path = path;
}

void PathTree::Node::setParent(PathTree::Node *newParent) {
    if (m_parent) {
        m_parent->m_childs.removeAuto(this);
    }
    if (newParent) {
        newParent->m_childs.insertAuto(this);
    }
    m_parent = newParent;
}

QList<PathTree::Node *> PathTree::Node::removeOnly() {
    auto res = m_childs;

    // Change Parent
    for (auto it = res.begin(); it != res.end(); ++it) {
        (*it)->setParent(m_parent);
    }
    // Remove
    deleteCore();

    return std::move(res);
}

void PathTree::Node::removeRecursively() {
    removeChilds();
    deleteCore();
}

void PathTree::Node::removeChilds() {
    for (auto it = m_childs.begin(); it != m_childs.end(); ++it) {
        (*it)->removeRecursively();
    }
}

void PathTree::Node::deleteCore() {
    setParent(nullptr);
    delete this;
}

// PathTree
PathTree::PathTree() {
    m_root = new Node("");
}

PathTree::~PathTree() {
    m_root->removeRecursively();
}

PathTree::Node *PathTree::root() const {
    return m_root;
}

void PathTree::clear() {
    m_root->removeChilds();
}

bool PathTree::clearBranch(const QString &path) {
    // Check
    if (path.isEmpty()) {
        return {};
    }
    // Remove
    Node *target = find(path);
    if (target) {
        target->removeRecursively();
        return true;
    }
    return false;
}

QList<PathTree::Node *> PathTree::removeOne(const QString &path) {
    // Check
    if (path.isEmpty()) {
        return {};
    }
    // Remove
    Node *target = find(path);
    if (target) {
        return target->removeOnly();
    }
    return {};
}

void PathTree::clearBranch(PathTree::Node *node) {
    // Check
    if (node == m_root) {
        return;
    }
    // Remove
    node->removeRecursively();
}

QList<PathTree::Node *> PathTree::removeOne(PathTree::Node *node) {
    // Check
    if (node == m_root) {
        return {};
    }
    // Remove
    return node->removeOnly();
}

PathTree::Node *PathTree::insert(const QString &path, bool *success) {
    // Check
    if (path.isEmpty()) {
        if (success) {
            *success = false;
        }
        return nullptr;
    }
    // Insert
    Node *target = tryInsert(m_root, path);
    if (target->path() == path) {
        if (success) {
            *success = false;
        }
        return target;
    }
    if (success) {
        *success = true;
    }

    // Find Possible Childs
    auto childs = target->childs();
    ItemList<Node> list;
    for (auto it = childs.begin(); it != childs.end(); ++it) {
        if ((*it)->m_path.startsWith(path)) {
            list.append(*it);
        }
    }

    Node *node = new Node(path, target);

    // Set Childs
    for (auto it = list.begin(); it != list.end(); ++it) {
        (*it)->setParent(node);
    }

    return node;
}

PathTree::Node *PathTree::find(const QString &path) const {
    if (path.isEmpty()) {
        return nullptr;
    }
    Node *target = tryInsert(m_root, path);
    if (target->path() == path) {
        return target;
    }
    return nullptr;
}

bool PathTree::contains(const QString &path) const {
    return find(path);
}

PathTree::Node *PathTree::tryInsert(PathTree::Node *root, const QString &path) const {
    auto &childs = root->m_childs;
    Node tmp(path);
    int pos;

    childs.findAuto(&tmp, &pos);

    Node *node;
    if (pos < childs.size() && (node = childs.at(pos))->m_path == path) {
        return node;
    } else if (pos > 0 && path.startsWith((node = childs.at(pos - 1))->m_path)) {
        return tryInsert(node, path);
    }

    return root;
}
