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
	std::vector<cv::Point2f> clickedPts = { cv::Point2f(124.0, 190.0),  cv::Point2f(130.0, 190.0), cv::Point2f(140.0, 250.0), cv::Point2f(100.0, 90.0) }; //��������������� ����� �� ������ �����������
	
	for (auto& clickedPt : clickedPts) {
		std::cout << "Cursor: " <<  clickedPt << '\n';
		//������ �����, ��������� � ����������� �����
		int idx = leftAst.findNearestPt(clickedPt);


		if (idx >= 0 && cv::norm(leftAst.getPosition(idx) - clickedPt) < ptRadius) {
			std::cout << "delete\n";
			leftAst.deletePt(idx);
			rightAst.deletePt(idx);
		}
		else {
			//����� - ��������� ���������� ������ ����� � �������� ����� ���� � ���������
			std::cout << "ins\n";
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