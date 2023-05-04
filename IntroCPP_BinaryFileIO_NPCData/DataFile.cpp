#include "DataFile.h"
#include <fstream>
#include <string>
using namespace std;

DataFile::DataFile()
{
	recordCount = 0; //used to store the number of records
}

DataFile::~DataFile() //deconstruct data file
{
	Clear();
}

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

//////////////////////////////////
////Not Going To Be Needed
//////////////////////////////////
DataFile::Record* DataFile::GetRecord(int index)
{
	return records[index]; //return the current record from array
}

////////////////////////////////////
///Save Record To File
////////////////////////////////////
void DataFile::Save(string filename)
{
	ofstream outfile(filename, ios::binary);

	int recordCount = records.size();
	outfile.write((char*)&recordCount, sizeof(int));

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

///////////////////////////////////////////////////
/////LOAD DATA INTO ARRAY
/////MODIFY THIS OR REMOVE IT TO LOAD RANDOM READS
///////////////////////////////////////////////////
void DataFile::Load(string filename)
{
	Clear();

	ifstream infile(filename, ios::binary);//initiate ifstream

	recordCount = 0; //set record count to 0
	infile.read((char*)&recordCount, sizeof(int)); //read the record count from file

	for (int i = 0; i < recordCount; i++)
	{	
		//initialise variables to store name length age lenght, image width heifght and size
		int nameSize = 0;
		int ageSize = 0;
		int width = 0, height = 0, format = 0, imageSize = 0;

		infile.read((char*)&width, sizeof(int)); //read image width
		infile.read((char*)&height, sizeof(int)); //read image height

		imageSize = sizeof(Color) * width * height; //set image size to be height * width

		infile.read((char*)&nameSize, sizeof(int)); //read in the length of name
		infile.read((char*)&ageSize, sizeof(int)); //read in the length of age

		char* imgdata = new char[imageSize]; //create a variable to store the image data
		infile.read(imgdata, imageSize); //read in the image data

		Image img = LoadImageEx((Color*)imgdata, width, height); //load the imagedate as an image and save it as img
		char* name = new char[nameSize + 1]; //create variable to store name
		int age = 0; //create variable to store age
			
		/////////////////////////////////////////////////
		/////EDITS TO FIX NAME BUG
		////////////////////////////////////////////////
		
		infile.read((char*)name, nameSize); //read the name from file
		infile.read((char*)&age, ageSize); //read the age

		name[nameSize] = '\0'; //add null reminator to end of name based on name size variable		

		Record* r = new Record(); //create new record
		r->image = img; //load img to record
		r->name = string(name); //load name into record		
		r->age = age; //load name into record
		records.push_back(r);

		//clean up data
		delete [] imgdata;
		delete [] name;
	}

	//close file
	infile.close();
}

//////////////////////
////delete array
//////////////////////
void DataFile::Clear()
{
	for (int i = 0; i < records.size(); i++)
	{
		delete records[i];
	}
	records.clear();
	recordCount = 0;
}