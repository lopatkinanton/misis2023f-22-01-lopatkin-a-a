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
	//создание двух созвездий на плоскости размером 256x256
	int n = 256;
	cv::Rect rect(0, 0, n, n);
	Asterism leftAst(rect);
	Asterism rightAst(rect);

	//загрузка точек из текстового файла
	leftAst.loadPts("./data/left_points.txt");
	rightAst.loadPts("./data/right_points.txt");

	printPts(leftAst);
	printPts(rightAst);

	int ptRadius = 5; //радиус отрисовки точек в графическом интерфейсе
	std::vector<cv::Point2f> clickedPts = { cv::Point2f(124.0, 190.0),  cv::Point2f(130.0, 190.0), cv::Point2f(140.0, 250.0), cv::Point2f(100.0, 90.0) }; //зафиксированные клики по левому изображению
	
	for (auto& clickedPt : clickedPts) {
		std::cout << "Cursor: " <<  clickedPt << '\n';
		//индекс точки, ближайшей к координатам клика
		int idx = leftAst.findNearestPt(clickedPt);


		if (idx >= 0 && cv::norm(leftAst.getPosition(idx) - clickedPt) < ptRadius) {
			std::cout << "delete\n";
			leftAst.deletePt(idx);
			rightAst.deletePt(idx);
		}
		else {
			//иначе - вычислить координаты парной точки и добавить новую пару в созвездия
			std::cout << "ins\n";
			cv::Point2f pairedPt = rightAst.predictPosition(clickedPt, leftAst);
			leftAst.insertPt(clickedPt);
			rightAst.insertPt(pairedPt);
		}
		
		printPts(leftAst);
		printPts(rightAst);
	}

	//сохранение точек в текстовый файл
	//leftAst.savePts("./data/left_points.txt");
	//rightAst.savePts("./data/right_points.txt");
}