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
	std::vector<cv::Point2f> clickedPts = { cv::Point2f(124.0, 190.0),  cv::Point2f(130.0, 190.0) }; //зафиксированный клик по левому изображению
	
	for (auto& clickedPt : clickedPts) {
		std::cout << clickedPt << '\n';
		//индекс точки, ближайшей к координатам клика
		int idx = leftAst.findNearestPt(clickedPt);
		//координаты ближайшей точки
		cv::Point2f nearestPt = leftAst.getPosition(idx);

		if (cv::norm(nearestPt - clickedPt) < ptRadius) {
			//если выбрана уже существующая точка, 
			//то ее можно подвинуть или удалить (вместе с ее парой)
			//leftAst.setPosition(idx, cv::Point(115, 112));
			leftAst.deletePt(idx);
			rightAst.deletePt(idx);
		}
		else {
			//иначе - вычислить координаты парной точки и добавить новую пару в созвездия
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