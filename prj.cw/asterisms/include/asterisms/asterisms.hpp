#pragma once
#ifndef ASTERISMS_HPP
#define ASTERISMS_HPP


#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>


class Asterism {
public:
    Asterism() = default;
    Asterism(cv::Rect rect);

    void loadPts(const std::string& path);
    void savePts(const std::string& path) const;
    std::vector<cv::Point> getPts() const;

    int insertPt(const cv::Point& pt);
    void movePt(const int& idx, const cv::Point& offset);
    void deletePt(const int& idx);

    void setPosition(const int& idx, const cv::Point& position);
    cv::Point getPosition(const int& idx);
    cv::Point predictPosition(const cv::Point& srcPt, Asterism& srcAst);

    int findNearestPt(const cv::Point& pt);
    std::vector<int> getTriangleIndices(const cv::Point& pt);

private:
    cv::Rect _rect;
    std::vector<cv::Point> _corners;
    cv::Subdiv2D _subdiv;
    std::vector<cv::Point> _points;
    std::vector<int> _free_indices;
    std::vector<int> _bias;

    void _updateSubdiv();
};

#endif