#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>

struct Point {
    double x, y;
};

struct Node {
    Point point;
    Node* left;
    Node* right;
    int axis; // 0 для оси x, 1 для оси y

    Node(Point p, int a);
};

class KDTree {
private:
    Node* root;

    Node* buildTree(std::vector<Point>& points, int depth, int start, int end);
    void rangeSearch(Node* node, double xMin, double xMax, double yMin, double yMax, std::vector<Point>& result);
    void deleteTree(Node* node);

public:
    KDTree(std::vector<Point>& points);
    std::vector<Point> rangeSearch(double xMin, double xMax, double yMin, double yMax);
    ~KDTree();
};

#endif // KDTREE_HPP
