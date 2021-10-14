#ifndef PATHTREE_H
#define PATHTREE_H

#include "Utils/ItemList.h"

class PathTree {
public:
    class Node {
    private:
        Node(const QString &path, Node *parent = nullptr); // Private Constructor
        ~Node();                                           // Private Destructor

        friend class PathTree;

    public:
        bool operator<(const Node &another) const;

        Node *parent() const;
        QList<Node *> childs() const;

        int inc();
        int dec();
        int count() const;
        int &rcount();

        QString path() const;

        long id() const;
        void setId(long id, bool recursive = false);

    private:
        int m_count;
        long m_id;
        QString m_path;

        Node *m_parent;
        ItemList<Node> m_childs;

        void setPath(const QString &path);
        void setParent(Node *newParent);

        QList<Node *> removeOnly();
        void removeRecursively();
        void removeChilds();

        void deleteCore();
    };

    typedef Node *Iterator;

public:
    PathTree();
    ~PathTree();

public:
    Node *root() const;

    // Clear
    void clear();

    // Remove
    bool clearBranch(const QString &path);
    QList<Node *> removeOne(const QString &path);

    void clearBranch(Node *node);
    QList<Node *> removeOne(Node *node);

    // Insert
    Node *insert(const QString &path, bool *success = nullptr);

    // Find
    Node *find(const QString &path) const;
    bool contains(const QString &path) const;

private:
    Node *m_root;

    Node *tryInsert(Node *root, const QString &path) const;
};

#endif // PATHTREE_H
