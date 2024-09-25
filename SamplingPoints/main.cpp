#include <iostream>
#include "KDTree.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned>(time(0)));

    std::vector<Point> points;
    const int numPoints = 1000; 
    int start = 1;
    int end = 100;

    // ��������� ��������� ����� (��������� ������ ��� ��������)
    for (int i = 0; i < numPoints; i++) {
        Point tmp;
        tmp.x = rand() % (end - start + 1) + start;
        tmp.y = rand() % (end - start + 1) + start;
        points.push_back(tmp);
    }

    KDTree kdTree(points);

    // ��������� ��� �������
    double xMin = 10, xMax = 20, yMin = 1, yMax = 15;
    std::cout << "Enter the range for selection (xMin xMax yMin yMax) " << start << " - " << end << ": ";
    std::cin >> xMin >> xMax >> yMin >> yMax;
    auto result = kdTree.rangeSearch(xMin, xMax, yMin, yMax);

    std::cout << "Points in range (" << xMin << ", " << yMin << ") to (" << xMax << ", " << yMax << "):\n";
    
    // ��� �������� �� ����� ���-�� �����
    for (const Point& p : result) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}
 