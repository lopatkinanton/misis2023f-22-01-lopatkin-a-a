#include <asterisms/asterisms.hpp>


Asterism::Asterism(cv::Rect rect)
    : _rect(rect)
    , _corners({ cv::Point(0, 0),
                cv::Point(0, rect.width - 1),
                cv::Point(rect.height - 1, 0),
                cv::Point(rect.height - 1, rect.width - 1) })
{
    _updateSubdiv();
}

Asterism::Asterism(int width, int height) : Asterism(cv::Rect(0, 0, width, height)) {};

void Asterism::loadPts(const std::string& path) {
    std::ifstream in(path);
    if (in.is_open()) {
        int x = 0;
        int y = 0;
        while (in >> x >> y) {
            insertPt(cv::Point(x, y));
        }
    }
    else {
        throw std::invalid_argument("File is not found.");
    }
    in.close();
}

void Asterism::savePts(const std::string& path) const {
    std::ofstream out(path);
    if (out.is_open()) {
        std::vector<cv::Point> pts;
        getPtsToDraw(pts);
        for (auto& pt : pts) {
            out << pt.x << " " << pt.y << std::endl;
        }
    }
    out.close();
}

void Asterism::_updateSubdiv() {
    subdiv = cv::Subdiv2D(cv::Rect(0, 0, _rect.width * 10, _rect.height * 10));
    for (auto& pt : _corners)
        subdiv.insert(pt);
    for (auto& pt : _points)
        if (_rect.contains(pt))
            subdiv.insert(pt);
}

int Asterism::insertPt(const cv::Point& pt) {
    if (!_rect.contains(pt)) {
        throw std::invalid_argument("Point is out of bounds.");
    }
    int idx = 0;
    if (_free_indices.empty()) {
        _points.push_back(pt);
        idx = size(_points) - 1;
    }
    else {
        idx = _free_indices.back();
        _points[idx] = pt;
        _free_indices.pop_back();
    }
    _updateSubdiv();
    return idx;
}

void Asterism::movePt(const int& idx, const cv::Point& newCoords) {
    if (!_rect.contains(newCoords)) {
        throw std::invalid_argument("Point is out of bounds.");
    }
    _points[idx] = newCoords;
    _updateSubdiv();
}

void Asterism::deletePt(const int& idx) {
    _points[idx] = _rect.br();
    _free_indices.push_back(idx);
    _updateSubdiv();
}

int Asterism::findNearestPt(const cv::Point& pt) {
    if (!_rect.contains(pt)) {
        throw std::invalid_argument("Point is out of bounds.");
    }
    return subdiv.findNearest(pt) - 8;
}

cv::Point Asterism::getCoords(const int& idx) {
    return subdiv.getVertex(idx + 8);
}

void Asterism::getPtsToDraw(std::vector<cv::Point>& pts) const {
    pts.clear();
    for (auto& pt : _points) {
        if (_rect.contains(pt)) {
            pts.push_back(pt);
        }
    }
}

cv::Point Asterism::predictPairedPt(const cv::Point& pt, Asterism& pairedAst) {
    if (!_rect.contains(pt)) {
        throw std::invalid_argument("Point is out of bounds.");
    }
    std::vector<cv::Point> lhsPts;
    std::vector<cv::Point> rhsPts;
    getPtsToDraw(lhsPts);
    pairedAst.getPtsToDraw(rhsPts);
    if (size(lhsPts) != size(rhsPts)) {
        throw std::invalid_argument("Asterisms must have the same number of points.");
    }

    cv::Point lhs_pt = pt;

    int e, v;
    int l = subdiv.locate(lhs_pt, e, v);
    int ne = subdiv.getEdge(e, cv::Subdiv2D::NEXT_AROUND_LEFT);

    std::vector<cv::Point2f> lhs_triangle = { subdiv.getVertex(subdiv.edgeOrg(e)),
                                              subdiv.getVertex(subdiv.edgeDst(e)),
                                              subdiv.getVertex(subdiv.edgeDst(ne)) };

    std::vector<cv::Point2f> rhs_triangle = { pairedAst.subdiv.getVertex(pairedAst.subdiv.edgeOrg(e)),
                                              pairedAst.subdiv.getVertex(pairedAst.subdiv.edgeDst(e)),
                                              pairedAst.subdiv.getVertex(pairedAst.subdiv.edgeDst(ne)) };

    cv::Mat_<float> M = cv::getAffineTransform(lhs_triangle, rhs_triangle);

    cv::Mat pointMat = (cv::Mat_<float>(3, 1) << lhs_pt.x, lhs_pt.y, 1);

    cv::Mat transformedPointMat = M * pointMat;

    cv::Point rhs_pt = cv::Point(transformedPointMat.at<float>(0, 0), transformedPointMat.at<float>(1, 0));

    return rhs_pt;
}
