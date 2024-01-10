#include <opencv2/core/core.hpp>
#include <iostream>

#include <asterisms/asterisms.hpp>


void printPts(Asterism& ast) {
	for (int i = 0; i < ast.countPts(); i += 1) {
		std::cout << ast.getPosition(i) << ' ';
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

	printPts(leftAst);
	printPts(rightAst);

	int ptRadius = 5; //������ ��������� ����� � ����������� ����������
	std::vector<cv::Point2f> clickedPts = { cv::Point2f(124.0, 190.0),  cv::Point2f(130.0, 190.0) }; //��������������� ���� �� ������ �����������
	
	for (auto& clickedPt : clickedPts) {
		std::cout << clickedPt << '\n';
		//������ �����, ��������� � ����������� �����
		int idx = leftAst.findNearestPt(clickedPt);
		//���������� ��������� �����
		cv::Point2f nearestPt = leftAst.getPosition(idx);

		if (cv::norm(nearestPt - clickedPt) < ptRadius) {
			//���� ������� ��� ������������ �����, 
			//�� �� ����� ��������� ��� ������� (������ � �� �����)
			//leftAst.setPosition(idx, cv::Point(115, 112));
			leftAst.deletePt(idx);
			rightAst.deletePt(idx);
		}
		else {
			//����� - ��������� ���������� ������ ����� � �������� ����� ���� � ���������
			cv::Point2f pairedPt = rightAst.predictPosition(clickedPt, leftAst);
			leftAst.insertPt(clickedPt);
			rightAst.insertPt(pairedPt);
		}

		printPts(leftAst);
		printPts(rightAst);
	}

	//���������� ����� � ��������� ����
	//leftAst.savePts("./data/left_points.txt");
	//rightAst.savePts("./data/right_points.txt");
}