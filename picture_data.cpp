//CSCE-121-502
//AggieSnap Project
//picture_data.cpp
//Handles data associated with pictures.

#include "std_lib_facilities_4.h"
#include "picture_data.h"


Picture_data::Picture_data(String pic_loc_in)
{
	pic_location= pic_loc_in;
	tag1= "";
	tag2= "";
	tag3= "";
	tag4= "";
	tag5= "";
}

Picture_data::Picture_data(String pic_loc_in, String tag1i, String tag2i, String tag3i, String tag4i, String tag5i)
{
	pic_location= pic_loc_in;
	tag1= tag1i;
	tag2= tag2i;
	tag3= tag3i;
	tag4= tag4i;
	tag5= tag5i;
}

void Picture_data::retag(String tag1i, String tag2i, String tag3i, String tag4i, String tag5i)
{
	tag1= tag1i;
	tag2= tag2i;
	tag3= tag3i;
	tag4= tag4i;
	tag5= tag5i;
}

String Picture_data::get_pic_location()
{
	return pic_location;
}

String Picture_data::get_tag(int num)
{
	switch (num)
	{
		case 1:
			return tag1;
		case 2:
			return tag2;
		case 3:
			return tag3;
		case 4:
			return tag4;
		case 5:
			return tag5;
	}
}

Vector<String> Picture_data::get_tags()
{
	Vector<String> tags;
	
	tags={tag1, tag2, tag3, tag4, tag5};
	
	return tags;
}