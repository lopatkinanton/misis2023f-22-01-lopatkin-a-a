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
	Asterism leftAst(n, n);
	Asterism rightAst(n, n);

	//�������� ����� �� ���������� �����
	leftAst.loadPts("./data/left_points.txt");
	rightAst.loadPts("./data/right_points.txt");

	int ptRadius = 5; //������ ��������� ����� � ����������� ����������
	cv::Point clickedPt(34, 112); //��������������� ���� �� ������ �����������

	//������ �����, ��������� � ����������� �����
	int idx = leftAst.findNearestPt(clickedPt);
	//���������� ��������� �����
	cv::Point nearestPt = leftAst.getCoords(idx);

	if (cv::norm(nearestPt - clickedPt) < ptRadius) {
		//���� ������� ��� ������������ �����, 
		//�� �� ����� ��������� ��� ������� (������ � �� �����)
		leftAst.movePt(idx, cv::Point(115, 112));
		leftAst.deletePt(idx);
		rightAst.deletePt(idx);
	}
	else {
		//����� - ��������� ���������� ������ ����� � �������� ����� ���� � ���������
		cv::Point pairedPt = leftAst.predictPairedPt(clickedPt, rightAst);
		leftAst.insertPt(clickedPt);
		rightAst.insertPt(pairedPt);
	}

	//��������� ������� ���������� �����
	std::vector<cv::Point> pts;
	leftAst.getPtsToDraw(pts);

	//���������� ����� � ��������� ����
	leftAst.savePts("./data/left_points.txt");
	rightAst.savePts("./data/right_points.txt");
}