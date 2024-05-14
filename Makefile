build:
	g++ -std=c++11 -o ./project2.out ./src/main.cpp ./src/File.cpp

tasks:
	./project2.out ./output/task11.tga ./input/circles.tga multiply ./input/layer1.tga
	./project2.out ./output/task12.tga ./input/layer1.tga flip
	./project2.out ./output/task11.tga ./input/layer1.tga subtract ./input/layer2.tga