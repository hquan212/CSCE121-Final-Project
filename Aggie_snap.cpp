#include "Aggie_snap.h"

using namespace Graph_lib;

	//eDIT THIS YOu need to.
//------------------------------------------------------------------------------


//Constructors!
Simple_window::Simple_window(Point xy, int w, int h, const string& t):Window(xy,w,h,t)
{
		//---Attach Initial!!! Buttons and Text ONLY WHAT STARTS UP
	next_button = new Button(Point(x_max()-70, y_max()-20), 70, 20, "Next", [](Address, Address pw){reference_to<Simple_window>(pw).next();}),
	quit_button = new Button(Point(x_max()-70,0), 70, 20, "Quit", [](Address, Address pw){reference_to<Simple_window>(pw).quit();}),
	title = new Text{Point{310,150},"AggieSnap"},
	instr  = new Text{Point{300,250},"Please choose a button below to: "},
	instr2 = new Text{Point{280,275},"Upload by URL, upload by image name, "},
	instr3 = new Text{Point{340,300},"view library, or exit."},
	current = 0;
	search = false;
	current_search = 0;
	
    attach(*next_button);		//Main Buttons
	attach(*quit_button);
	title->set_font_size(40),
	
	attach(*title);				//Main Text
	attach(*instr);
	attach(*instr2);
	attach(*instr3);
	load_pictures_from_file();
}


void Simple_window::load_pictures_from_file()
{
	ifstream file("savedPictures.txt");
	if(file.is_open())
	{
		while(!file.eof())
		{
			string fname,tag1,tag2,tag3,tag4,tag5;
			file >> fname;
			file >> tag1;
			file >> tag2;
			file >> tag3;
			file >> tag4;
			file >> tag5;
			tag1 = tag1 == "null" ? "" : tag1;
			tag2 = tag2 == "null" ? "" : tag2;
			tag3 = tag3 == "null" ? "" : tag3;
			tag4 = tag4 == "null" ? "" : tag4;
			tag5 = tag5 == "null" ? "" : tag5;
			if(file.fail()) break;
			Picture_data *pic = new Picture_data(fname,tag1,tag2,tag3,tag4,tag5);
			pictures.push_back(pic);
		}
	}
	file.close();
}

void Simple_window::save_pictures_into_file()
{
	ofstream file("savedPictures.txt");
	if(file.is_open())
	{
		for(Picture_data *pic : pictures)
		{
			file << pic->get_pic_location() << " ";
			for(string tag : pic->get_tags())
			{
				file << (tag == "" ? "null" : tag);
				file << " ";
			}
			file << endl;
		}
	}
	file.close();
}

//-------------------------BUTTON-----------------------------------------------------

bool Simple_window::wait_for_button()

{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    Fl::run();
#endif
    return button_pushed;
}

//-------------------------FUCNTIONS-----------------------------------------------------
void Simple_window::get()
{
	string pic1 = fname->get_string();	
	Picture_data *pic_data = new Picture_data(pic1);
	add_picture(pic_data);
}
void Simple_window::get_url()
{
	system((string("curl ") + url_name->get_string() + string(" > ") + file_name->get_string()).c_str());
	string pic2 = file_name->get_string();				//Download from Net, and save name. cHEKC
	Picture_data *pic_data = new Picture_data(pic2);
	add_picture(pic_data);
}


void Simple_window::add_picture(Picture_data* pic)
{
	pictures.push_back(pic);
}

void Simple_window::quit()
{
    button_pushed=true;     						    // curious FLTK idiom for delete window
	hide();
	save_pictures_into_file();
}
void Simple_window::next_picture()
{
	
	if(search == false)
	{
		++current;
		if(current == pictures.size())
		{
			current =0;
		}
		detach(*image);
		image = new Image(Point(x_max()/3,y_max()/6), pictures[current]->get_pic_location());
		attach(*image);
		tag_name->put(pictures[current]->get_pic_location());
		out_tag1->put(pictures[current]->get_tag(1));
		out_tag2->put(pictures[current]->get_tag(2));
		out_tag3->put(pictures[current]->get_tag(3));
		out_tag4->put(pictures[current]->get_tag(4));
		out_tag5->put(pictures[current]->get_tag(5));
		Fl::redraw();
	}
	
	
	if(search == true)
	{
		++current_search;
		if(current_search >= searchis.size())
		{
			current_search =0;
		}
		detach(*image);
		if(searchis.empty()!=true)
		{	
			image = new Image(Point(x_max()/3,y_max()/6), searchis[current_search]->get_pic_location());
			attach(*image);
			tag_name->put(searchis[current_search]->get_pic_location());
			out_tag1->put(searchis[current_search]->get_tag(1));
			out_tag2->put(searchis[current_search]->get_tag(2));
			out_tag3->put(searchis[current_search]->get_tag(3));
			out_tag4->put(searchis[current_search]->get_tag(4));
			out_tag5->put(searchis[current_search]->get_tag(5));
			Fl::redraw();
		}	
	}
	
	
}

void Simple_window::previous_picture()
{
	
	if(search == false)
	{
		--current;
		if(current == -1)
		{
			current = pictures.size() -1;
		}
		detach(*image);
		image = new Image(Point(x_max()/3,y_max()/6), pictures[current]->get_pic_location());
		attach(*image);
		tag_name->put(pictures[current]->get_pic_location());
		out_tag1->put(pictures[current]->get_tag(1));
		out_tag2->put(pictures[current]->get_tag(2));
		out_tag3->put(pictures[current]->get_tag(3));
		out_tag4->put(pictures[current]->get_tag(4));
		out_tag5->put(pictures[current]->get_tag(5));
		Fl::redraw();
	}
	
	//if search == true
	
	if(search == true)
	{
		--current_search;
		if(current_search <= -1)
		{
			current_search = searchis.size() -1;
		}
		detach(*image);
		if(searchis.empty()!=true)
		{	
			image = new Image(Point(x_max()/3,y_max()/6), searchis[current_search]->get_pic_location());
			attach(*image);
			tag_name->put(searchis[current_search]->get_pic_location());
			out_tag1->put(searchis[current_search]->get_tag(1));
			out_tag2->put(searchis[current_search]->get_tag(2));
			out_tag3->put(searchis[current_search]->get_tag(3));
			out_tag4->put(searchis[current_search]->get_tag(4));
			out_tag5->put(searchis[current_search]->get_tag(5));
			Fl::redraw();
		}	
	}
	
}
void Simple_window::save_tags()
{
	string tag1b = tag1->get_string();
	string tag2b = tag2->get_string();
	string tag3b = tag3->get_string();
	string tag4b = tag4->get_string();
	string tag5b = tag5->get_string();
	
	pictures[current]->retag(tag1b, tag2b, tag3b, tag4b, tag5b);
	
	Fl::redraw();
}
void Simple_window::search_tags()
{
	search = true;
	
	detach(*save_tags_button);
	detach(*tag_name);
	detach(*image);
	
	attach(*text_search);
	
	string tag1b = tag1->get_string();
	string tag2b = tag2->get_string();
	string tag3b = tag3->get_string();
	string tag4b = tag4->get_string();
	string tag5b = tag5->get_string();
	
	for(int i= 0; i<pictures.size(); ++i)
	{
		for(int j = 1; j<6; j++)
		{	
			if(tag1b == pictures[i]->get_tag(j))
				searchis.push_back(pictures[i]);
		}
	}
	for(int i = 0; i<searchis.size(); i++)
	{	
		bool found = false;
		for(int j = 1; j<6; j++)
		{	
			if(tag2b == searchis[i]->get_tag(j))
				found = true;
		}
		
		if(found == false)
		{
			if(tag2b == "")
				found = true;
		}
		
		if(found == false){
			searchis.erase(searchis.begin()+i);
			i--;
		}
	}	
	for(int i = 0; i<searchis.size(); i++)
	{	
		bool found = false;
		for(int j = 1; j<6; j++)
		{	
			if(tag3b == searchis[i]->get_tag(j))
				found = true;
		}
		
		if(found == false)
		{
			if(tag3b == "")
				found = true;
		}
		
		if(found == false){
			searchis.erase(searchis.begin()+i);
			i--;
		}
	}	
	for(int i = 0; i<searchis.size(); i++)
	{	
		bool found = false;
		for(int j = 1; j<6; j++)
		{	
			if(tag4b == searchis[i]->get_tag(j))
				found = true;
		}
		
		if(found == false)
		{
			if(tag4b == "")
				found = true;
		}
		
		if(found == false){
			searchis.erase(searchis.begin()+i);
			i--;
		}
	}	
	for(int i = 0; i<searchis.size(); i++)
	{	
		bool found = false;
		for(int j = 1; j<6; j++)
		{	
			if(tag5b == searchis[i]->get_tag(j))
				found = true;
		}
		
		if(found == false)
		{
			if(tag5b == "")
				found = true;
		}
		
		if(found == false){
			searchis.erase(searchis.begin()+i);
			i--;
		}
	}	
	if(searchis.size() != 0)
	{
		image = new Image(Point(x_max()/3,y_max()/6), searchis[0]->get_pic_location());
		attach(*image);
	}
		
	Fl::redraw();
	
}


// ---------------------------------------------------------------
void Simple_window::next()
{
	//First Page, or NON startup Page!
	fname = new In_box(Point{100,200},500,25,"Image Name "),
	url_button = new Button(Point(x_max()-70, y_max()-20), 70, 20, "URL", [](Address, Address pw){reference_to<Simple_window>(pw).next_url();}),
	get_button = new Button(Point(610,200), 70, 20, "Get", [](Address, Address pw){reference_to<Simple_window>(pw).get();}),
	in1 = new Text{Point{100,190},"Enter your file name to enter in the library. "},
	next_page = new Text{Point{10,10},"AggieSnap v 1.0"},
	
	attach(*fname);
	attach(*next_page);
	attach(*url_button);
	attach(*get_button);
	attach(*in1);

	detach(*title);
	detach(*instr);
	detach(*instr2);
	detach(*instr3);
	detach(*next_button);
	
	delete title;
	delete instr;
	delete instr2;
	delete instr3;
	delete next_button;
	
	Fl::redraw();
	
}

void Simple_window::next_url()
{
	//Second Page
	tags_button = new Button(Point(x_max()-70, y_max()-20), 70, 20, "Tags", [](Address, Address pw){reference_to<Simple_window>(pw).next_tags();}),
	url_name = new In_box(Point{100,150},500,25,"URL: "),
	file_name = new In_box(Point{100,200},500,25,"File Name: "),
	get_url_button = new Button(Point(610,200), 70, 20, "Get URL", [](Address, Address pw){reference_to<Simple_window>(pw).get_url();}),
	title2 = new Text{Point{100,100},"Enter the URL of the image and then "},
	title3 = new Text{Point{100,125},"rename the file using the File Name box."},	

	attach(*tags_button);
	attach(*url_name);
	attach(*file_name);
	attach(*get_url_button);
	attach(*title2);
	attach(*title3);
	
	detach(*fname);
	detach(*in1);
	detach(*url_button);
	detach(*get_button);
	
	delete fname;
	delete in1;
	delete url_button;
	delete get_button;
	
	Fl::redraw();
}
void Simple_window::next_tags()
{
	/*Third and Library Page. 
	This page also includes the Tagging functions, 
	The search function and everything.
	*/
	tag_name = new Out_box(Point{100,y_max()-100},400,25,"Image Name "),
	tag1 = new In_box(Point(100,y_max()-50),75,25,"Tag 1: "),
	tag2 = new In_box(Point(225,y_max()-50),75,25,"Tag 2: "),
	tag3 = new In_box(Point(350,y_max()-50),75,25,"Tag 3: "),
	tag4 = new In_box(Point(475,y_max()-50),75,25,"Tag 4: "),
	tag5 = new In_box(Point(600,y_max()-50),75,25,"Tag 5: "),
	out_tag1 = new Out_box(Point(100,30),75,25,"Tag 1: "),
	out_tag2 = new Out_box(Point(225,30),75,25,"Tag 2: "),
	out_tag3 = new Out_box(Point(350,30),75,25,"Tag 3: "),
	out_tag4 = new Out_box(Point(475,30),75,25,"Tag 4: "),
	out_tag5 = new Out_box(Point(600,30),75,25,"Tag 5: "),
	image = new Image(Point(x_max()/3,y_max()/6), pictures[current]->get_pic_location()),
	next_pic_button = new Button(Point(610,100), 120, 40, "Next Picture", [](Address, Address pw){reference_to<Simple_window>(pw).next_picture();}),
	previous_pic_button = new Button(Point(60,100), 120, 40, "Previous Picture", [](Address, Address pw){reference_to<Simple_window>(pw).previous_picture();}),
	save_tags_button = new Button(Point(550,y_max()-110), 120, 40, "Save Tags", [](Address, Address pw){reference_to<Simple_window>(pw).save_tags();}),
	search_tags_button = new Button(Point(670,y_max()-110), 100, 40, "Search Tags", [](Address, Address pw){reference_to<Simple_window>(pw).search_tags();}),
	text_search = new Text{Point{100,y_max()-750},"Enter your tags to search for your file"},	
	
	attach(*tag_name);
	attach(*tag1);
	attach(*tag2);
	attach(*tag3);
	attach(*tag4);
	attach(*tag5);
	attach(*out_tag1);
	attach(*out_tag2);
	attach(*out_tag3);
	attach(*out_tag4);
	attach(*out_tag5);
	attach(*image);
	attach(*next_pic_button);
	attach(*previous_pic_button);
	attach(*save_tags_button);
	attach(*search_tags_button);
	       
	detach(*title2);
	detach(*title3);
	detach(*tags_button);
	detach(*url_name);
	detach(*file_name);
	detach(*get_url_button);
	
	
	delete title2;
	delete title3;
	delete tags_button;
	delete url_name;
	delete file_name;
	delete get_url_button;
	
	tag_name->put(pictures[current]->get_pic_location());
	out_tag1->put(pictures[current]->get_tag(1));
	out_tag2->put(pictures[current]->get_tag(2));
	out_tag3->put(pictures[current]->get_tag(3));
	out_tag4->put(pictures[current]->get_tag(4));
	out_tag5->put(pictures[current]->get_tag(5));
	
	Fl::redraw();
}
