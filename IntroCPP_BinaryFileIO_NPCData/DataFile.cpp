#include "DataFile.h"
#include <iostream>
#include <fstream>

using namespace std;

DataFile::DataFile()
{
	recordCount = 0;
	currentRecord = nullptr;
}

DataFile::~DataFile()
{
	Clear();
	delete currentRecord;
	currentRecord = nullptr;
}

// adds the record to the list of records given
void DataFile::AddRecord(string imageFilename, string name, int age)
{
	// opens the file named fileName
	std::fstream writer;
	writer.open(fileName, std::ios::binary | std::ios::app);

	if (writer.is_open())
	{
		// loads all the record stuff and appends the record to the file
		Image i = LoadImage(imageFilename.c_str());

		Record* r = new Record;
		r->image = i;
		r->name = name;
		r->age = age;

		recordCount++;

		writer.write((char*)r, sizeof(Record));
	}
}

// returns the record at the given index
DataFile::Record* DataFile::GetRecord(int index)
{
	// read the indicated file
	std::fstream findRecord;
	Record* record = new Record();

	findRecord.open(fileName, ios::out | ios::binary | ios::app);

	if (findRecord.is_open())
	{
		findRecord.seekg(sizeof(Record) * (index), ios::beg);
		findRecord.read((char*)record, sizeof(Record));
	}
	else 
	{
		findRecord.close();
		return nullptr;
	}

	findRecord.close();

	return record;
}

// writes all of the files into the database
void DataFile::Save(string filename)
{
	ofstream outfile(filename, std::ios::binary);

	// dont worry about this for now :thumbsup:
	outfile.write((char*)&recordCount, sizeof(int));

	// gets the records and then writes all of the information into the records file
	for (int i = 0; i < recordCount; i++)
	{		

		Color* imgdata = GetImageData(currentRecord->image);
				
		int imageSize = sizeof(Color) * currentRecord->image.width * currentRecord->image.height;
		int nameSize = currentRecord->name.length();
		int ageSize = sizeof(int);

		outfile.write((char*)&currentRecord->image.width, sizeof(int));
		outfile.write((char*)&currentRecord->image.height, sizeof(int));
		
		outfile.write((char*)&nameSize, sizeof(int));
		outfile.write((char*)&ageSize, sizeof(int));

		outfile.write((char*)imgdata, imageSize);
		outfile.write((char*)currentRecord->name.c_str(), nameSize);
		outfile.write((char*)&currentRecord->age, ageSize);
	}

	outfile.close();
}

// loads all of the files from the database
void DataFile::Load(string filename)
{
	Clear();
	fileName = filename;
	recordCount = 5;

	/*
	for (int i = 0; i < recordCount; i++)
	{		
		int nameSize = 0;
		int ageSize = 0;
		int width = 0, height = 0, format = 0, imageSize = 0;

		// reads the stuff from the file
		infile.read((char*)&width, sizeof(int));
		infile.read((char*)&height, sizeof(int));

		imageSize = sizeof(Color) * width * height;

		infile.read((char*)&nameSize, sizeof(int));
		infile.read((char*)&ageSize, sizeof(int));

		char* imgdata = new char[imageSize];
		infile.read(imgdata, imageSize);

		Image img = LoadImageEx((Color*)imgdata, width, height);
		char* name = new char[nameSize + 1];
		int age = 0;
				
		infile.read((char*)name, nameSize);
		infile.read((char*)&age, ageSize);

		// appends the null terminator to the end of the name so that it doesn't read the unknowable secrets from the depths of the circuitry that permeates this world
		name[nameSize] = *"\0";

		// adds a record which is the one from the file that we're lookin at
		Record* r = new Record();
		r->image = img;
		r->name = string(name);
		r->age = age;

		delete [] imgdata;
		delete [] name;
	}
	*/

}

// removes all the records from memory
void DataFile::Clear()
{
	currentRecord = nullptr;
	recordCount = 0;
}