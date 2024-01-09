#include <opencv2/core/core.hpp>
#include <iostream>

#include <asterisms/asterisms.hpp>


void printPts(std::vector<cv::Point> pts) {
    for (auto& pt : pts) {
        std::cout << pt << " ";
    }
    std::cout << '\n';
}

int main(int argc, char** argv) {
	//�������� ���� ��������� �� ��������� �������� 256x256
	int n = 256;
	cv::Rect rect(0, 0, n, n);
	Asterism leftAst(rect);
	Asterism rightAst(rect);

	//�������� ����� �� ���������� �����
	leftAst.loadPts("./data/left_points.txt");
	rightAst.loadPts("./data/right_points.txt");

	std::vector<cv::Point> lpts = leftAst.getPts();
	printPts(lpts);
	std::vector<cv::Point> rpts = rightAst.getPts();
	printPts(rpts);

	int ptRadius = 5; //������ ��������� ����� � ����������� ����������
	std::vector<cv::Point> clickedPts = { cv::Point(124, 190),  cv::Point(130, 190) }; //��������������� ���� �� ������ �����������
	
	for (auto& clickedPt : clickedPts) {
		std::cout << clickedPt << '\n';
		//������ �����, ��������� � ����������� �����
		int idx = leftAst.findNearestPt(clickedPt);
		//���������� ��������� �����
		cv::Point nearestPt = leftAst.getPosition(idx);

		if (cv::norm(nearestPt - clickedPt) < ptRadius) {
			//���� ������� ��� ������������ �����, 
			//�� �� ����� ��������� ��� ������� (������ � �� �����)
			//leftAst.setPosition(idx, cv::Point(115, 112));
			leftAst.deletePt(idx);
			rightAst.deletePt(idx);
		}
		else {
			//����� - ��������� ���������� ������ ����� � �������� ����� ���� � ���������
			cv::Point pairedPt = rightAst.predictPosition(clickedPt, leftAst);
			leftAst.insertPt(clickedPt);
			rightAst.insertPt(pairedPt);
		}

		//��������� ������� ���������� �����
		std::vector<cv::Point> lpts = leftAst.getPts();
		printPts(lpts);
		std::vector<cv::Point> rpts = rightAst.getPts();
		printPts(rpts);
	}

	//���������� ����� � ��������� ����
	//leftAst.savePts("./data/left_points.txt");
	//rightAst.savePts("./data/right_points.txt");
}