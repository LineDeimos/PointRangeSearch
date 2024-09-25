#include "KDTree.hpp"
#include <algorithm>

Node::Node(Point p, int a) : point(p), left(nullptr), right(nullptr), axis(a) {}

Node* KDTree::buildTree(std::vector<Point>& points, int depth, int start, int end) {
    if (start >= end) return nullptr;

    int axis = depth % 2;

    // Сортиртировка текущего участка массива по оси (0 по x, 1 по y)
    if (axis == 0) {
        std::sort(points.begin() + start, points.begin() + end, [](Point a, Point b) { return a.x < b.x; });
    } else {
        std::sort(points.begin() + start, points.begin() + end, [](Point a, Point b) { return a.y < b.y; });
    }

    int medianIndex = start + (end - start) / 2;
    Node* node = new Node(points[medianIndex], axis);

    node->left = buildTree(points, depth + 1, start, medianIndex);
    node->right = buildTree(points, depth + 1, medianIndex + 1, end);

    return node;
}

void KDTree::rangeSearch(Node* node, double xMin, double xMax, double yMin, double yMax, std::vector<Point>& result) {
    if (!node) return;

    if (node->point.x >= xMin && node->point.x <= xMax && node->point.y >= yMin && node->point.y <= yMax) {
        result.push_back(node->point);
    }

    if (!node->axis) {
        if (node->left && xMin <= node->point.x) {
            rangeSearch(node->left, xMin, xMax, yMin, yMax, result);
        }
        if (node->right && xMax >= node->point.x) {
            rangeSearch(node->right, xMin, xMax, yMin, yMax, result);
        }
    }
    else {
        if (node->left && yMin <= node->point.y) {
            rangeSearch(node->left, xMin, xMax, yMin, yMax, result);
        }
        if (node->right && yMax >= node->point.y) {
            rangeSearch(node->right, xMin, xMax, yMin, yMax, result);
        }
    }
}

KDTree::KDTree(std::vector<Point>& points) {
    root = buildTree(points, 0, 0, points.size());
}

std::vector<Point> KDTree::rangeSearch(double xMin, double xMax, double yMin, double yMax) {
    std::vector<Point> result;
    rangeSearch(root, xMin, xMax, yMin, yMax, result);
    return result;
}

KDTree::~KDTree() {
    deleteTree(root);
}

void KDTree::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}
