#pragma once
class FilePath
{
public:
	static FilePath* GetInstance();
	// mainmenu
	char* mainmenu_bg;
	char* mainmenu_foregroundTrees;
	char* mainmenu_backgroundTrees;
	char* mainmenu_mountainFar;
	char* mainmenu_mountains;
	// test
	char* chacracter01;
	// test
	char* tileMap;
	// test
	char* tmxFile_0;
	char* tmxFile_1;
	~FilePath();

	void Test();
private:
	static FilePath* instance;
	FilePath();
}; 
