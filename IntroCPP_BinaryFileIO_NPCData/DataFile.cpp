#include "DataFile.h"
#include <iostream>
#include <fstream>
using namespace std;

DataFile::DataFile()
{
	recordCount = 0;
}

DataFile::~DataFile()
{
	Clear();
}

// adds the record to the list of records given
void DataFile::AddRecord(string imageFilename, string name, int age)
{
	Image i = LoadImage(imageFilename.c_str());

	Record* r = new Record;
	r->image = i;
	r->name = name;
	r->age = age;

	records.push_back(r);
	recordCount++;
}

// returns the record at the given index
DataFile::Record* DataFile::GetRecord(int index)
{
	return records[index];
}

// writes all of the files into the database
void DataFile::Save(string filename)
{
	ofstream outfile(filename, ios::binary);

	outfile.write((char*)&recordCount, sizeof(int));

	// gets the records and then writes all of the information into the records file
	for (int i = 0; i < recordCount; i++)
	{		

		Color* imgdata = GetImageData(records[i]->image);
				
		int imageSize = sizeof(Color) * records[i]->image.width * records[i]->image.height;
		int nameSize = records[i]->name.length();
		int ageSize = sizeof(int);

		outfile.write((char*)&records[i]->image.width, sizeof(int));
		outfile.write((char*)&records[i]->image.height, sizeof(int));
		
		outfile.write((char*)&nameSize, sizeof(int));
		outfile.write((char*)&ageSize, sizeof(int));

		outfile.write((char*)imgdata, imageSize);
		outfile.write((char*)records[i]->name.c_str(), nameSize);
		outfile.write((char*)&records[i]->age, ageSize);
	}

	outfile.close();
}

// loads all of the files from the database
void DataFile::Load(string filename)
{
	Clear();

	ifstream infile(filename, ios::binary);

	recordCount = 0;
	infile.read((char*)&recordCount, sizeof(int));

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
		records.push_back(r);

		delete [] imgdata;
		delete [] name;
	}
	recordCount = records.size();
	infile.close();
}

// removes all the records from memory
void DataFile::Clear()
{
	for (int i = 0; i < records.size(); i++)
	{
		delete records[i];
	}
	records.clear();
	recordCount = 0;
}