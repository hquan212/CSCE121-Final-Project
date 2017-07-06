//CSCE-121-502
//AggieSnap Project
//picture_data.h
//Handles data associated with pictures.


class Picture_data{

private:
	String pic_location;
	String tag1;
	String tag2;
	String tag3;
	String tag4;
	String tag5;
	
public:	
	
	Picture_data(String);
	Picture_data(String, String, String, String, String, String);
	
	void retag(String, String, String, String, String); //Part of the first extra credit.
	String get_pic_location();
	String get_tag(int);
	Vector<String> get_tags(); // ! Beware of vector range,  tags[1] != tag1, tags[0] == tag1
	
};