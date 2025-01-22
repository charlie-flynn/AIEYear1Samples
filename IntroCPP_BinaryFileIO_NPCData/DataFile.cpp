#include "DataFile.h"
#include <iostream>
#include <fstream>
using namespace std;

DataFile::DataFile()
{
	recordCount = 0;
}

// adds the record to the list of records given
void DataFile::AddRecord(string imageFilename, string name, int age)
{
	Image i = LoadImage(imageFilename.c_str());

	Record* r = new Record;
	r->image = i;
	r->name = name;
	r->age = age;
	ofstream outfile(currentFile, ios::out | ios::binary);

	if (!outfile.is_open())
		return;

	outfile.seekp(ios::end, ios::beg);

	Color* imgdata = GetImageData(r->image);

	int imageSize = sizeof(Color) * r->image.width * r->image.height;
	int nameSize = r->name.length();
	int ageSize = sizeof(int);

	outfile.write((char*)&r->image.width, sizeof(int));
	outfile.write((char*)&r->image.height, sizeof(int));

	outfile.write((char*)&nameSize, sizeof(int));
	outfile.write((char*)&ageSize, sizeof(int));

	outfile.write((char*)imgdata, imageSize);
	outfile.write((char*)r->name.c_str(), nameSize);
	outfile.write((char*)&r->age, ageSize);
		
	recordCount++;
}

// returns the record at the given index
DataFile::Record* DataFile::GetRecord(int index)
{
	ifstream infile(currentFile, ios::binary | ios::in);

	infile.seekg(sizeof(int), ios::beg);

	if (!infile.is_open())
		return nullptr;

	// skips over every file that isnt the file we're lookin for
	for (int i = 0; i < index; i++)
	{
		int nameSize = 0;
		int ageSize = 0;
		int width = 0, height = 0, format = 0, imageSize = 0;

		infile.read((char*)&width, sizeof(int));
		infile.read((char*)&height, sizeof(int));

		imageSize = sizeof(Color) * width * height;

		infile.read((char*)&nameSize, sizeof(int));
		infile.read((char*)&ageSize, sizeof(int));

		infile.seekg(nameSize + ageSize + imageSize, ios::cur);
	}

	// now that we're on the file we're lookin for, read all of the data from that area
	int nameSize = 0;
	int ageSize = 0;
	int width = 0, height = 0, format = 0, imageSize = 0;

	infile.read((char*)&width, sizeof(int));
	infile.read((char*)&height, sizeof(int));

	imageSize = sizeof(Color) * width * height;

	infile.read((char*)&nameSize, sizeof(int));
	infile.read((char*)&ageSize, sizeof(int));

	char* imgdata = new char[imageSize];
	infile.read(imgdata, imageSize);

	Image img = LoadImageEx((Color*)imgdata, width, height);
	char* name = new char[nameSize];
	int age = 0;

	infile.read((char*)name, nameSize);
	infile.read((char*)&age, ageSize);

	// create a record and slap all the stuff we just read into that thing
	Record* r = new Record();
	r->image = img;
	r->name = string(name);
	r->age = age;

	// resize the name to the proper size so that it doesn't read the unknowable secrets from the depths of the circuitry that permeates this world to the user
	r->name.resize(nameSize);

	delete[] name;
	delete[] imgdata;

	infile.close();

	return r;
}

// writes all of the files in the current file into a different file
void DataFile::Save(string filename)
{
	ifstream infile(currentFile, ios::binary);
	ofstream outfile(filename, ios::binary);

	outfile.write((char*)&recordCount, sizeof(int));
	infile.seekg(sizeof(int), ios::beg);

	if (!outfile.is_open() || !infile.is_open())
		return;

	// gets the records and then writes all of the information into the records file
	for (int i = 0; i < recordCount; i++)
	{		
		// reads the data from a record
		int nameSize = 0;
		int ageSize = 0;
		int width = 0, height = 0, format = 0, imageSize = 0;

		infile.read((char*)&width, sizeof(int));
		infile.read((char*)&height, sizeof(int));

		imageSize = sizeof(Color) * width * height;

		infile.read((char*)&nameSize, sizeof(int));
		infile.read((char*)&ageSize, sizeof(int));

		char* imgdata = new char[imageSize];
		infile.read(imgdata, imageSize);

		Image img = LoadImageEx((Color*)imgdata, width, height);
		char* name = new char[nameSize];
		int age = 0;

		infile.read((char*)name, nameSize);
		infile.read((char*)&age, ageSize);

		// put all the stuff we just read into a record
		Record* r = new Record();
		r->image = img;
		r->name = string(name);
		r->age = age;

		// write everything from that record to the new file
		outfile.write((char*)&r->image.width, sizeof(int));
		outfile.write((char*)&r->image.height, sizeof(int));
		
		outfile.write((char*)&nameSize, sizeof(int));
		outfile.write((char*)&ageSize, sizeof(int));

		outfile.write((char*)imgdata, imageSize);
		outfile.write((char*)r->name.c_str(), nameSize);
		outfile.write((char*)&r->age, ageSize);

		// delete the name and imgdata pointers and continue the cycle
		delete[] name;
		delete[] imgdata;
	}
	
	outfile.close();
	infile.close();
}

// loads the recordCount from the file
void DataFile::Load(string filename)
{
	currentFile = filename;
	ifstream infile(filename, ios::binary);
	if (!infile.is_open())
		throw exception();

	infile.read((char*)&recordCount, sizeof(int));

	infile.close();
}

// removes all the records from memory
// ** this code is deprecated because we no longer store all the records in memory **
void DataFile::Clear()
{
	/*
	for (int i = 0; i < records.size(); i++)
	{
		delete records[i];
	}
	records.clear();
	recordCount = 0;
	*/
}