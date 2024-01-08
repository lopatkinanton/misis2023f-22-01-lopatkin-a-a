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
	//создание двух созвездий на плоскости размером 256x256
	int n = 256;
	Asterism leftAst(n, n);
	Asterism rightAst(n, n);

	//загрузка точек из текстового файла
	leftAst.loadPts("./data/left_points.txt");
	rightAst.loadPts("./data/right_points.txt");

	int ptRadius = 5; //радиус отрисовки точек в графическом интерфейсе
	cv::Point clickedPt(34, 112); //зафиксированный клик по левому изображению

	//индекс точки, ближайшей к координатам клика
	int idx = leftAst.findNearestPt(clickedPt);
	//координаты ближайшей точки
	cv::Point nearestPt = leftAst.getCoords(idx);

	if (cv::norm(nearestPt - clickedPt) < ptRadius) {
		//если выбрана уже существующая точка, 
		//то ее можно подвинуть или удалить (вместе с ее парой)
		leftAst.movePt(idx, cv::Point(115, 112));
		leftAst.deletePt(idx);
		rightAst.deletePt(idx);
	}
	else {
		//иначе - вычислить координаты парной точки и добавить новую пару в созвездия
		cv::Point pairedPt = leftAst.predictPairedPt(clickedPt, rightAst);
		leftAst.insertPt(clickedPt);
		rightAst.insertPt(pairedPt);
	}

	//получение массива отмеченных точек
	std::vector<cv::Point> pts;
	leftAst.getPtsToDraw(pts);

	//сохранение точек в текстовый файл
	leftAst.savePts("./data/left_points.txt");
	rightAst.savePts("./data/right_points.txt");
}