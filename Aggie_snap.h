#ifndef SIMPLE_WINDOW_GUARD
#define SIMPLE_WINDOW_GUARD 1

#include "GUI.h"    
#include "Graph.h"
#include "picture_data.h"


using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Simple_window : Graph_lib::Window {
    Simple_window(Point xy, int w, int h, const string& t);
	
	vector<Picture_data*> pictures;
	vector<Picture_data*> searchis;
    bool wait_for_button(); // simple event loop
	int current;
	bool search;
	int current_search;
	
	//MainPage
    Button *next_button;     // the "next" button
	Button *quit_button;		//Original Buttons
	Text *title;				//Initial Screen Text
	Text *instr;
	Text *instr2;
	Text *instr3;

	
	//Page2
	In_box *fname;			//Tag Boxes!
	Button *url_button;		// the "url" button	
	Button *get_button;
	Text *in1;
	Text *next_page;
	
	//Page3
	Button *tags_button;
	Button *get_url_button;
	In_box *url_name;			//URL Page
	In_box *file_name;
	Text *title2;
	Text *title3;

	//Page4
	Out_box *tag_name;
	In_box *tag1;
	In_box *tag2;
	In_box *tag3;
	In_box *tag4;
	In_box *tag5;
	Out_box *out_tag1;
	Out_box *out_tag2;
	Out_box *out_tag3;
	Out_box *out_tag4;
	Out_box *out_tag5;
	Button *next_pic_button;
	Button *previous_pic_button;
	Button *next_pic_button_s;
	Button *previous_pic_button_s;
	Button *save_tags_button;
	Button *search_tags_button;
	Text *text_search;
	Image  *image;			//Next function
	
	
	//extra
    bool button_pushed;     // implementation detail

	 // actions invoked by callbacks:
private:
    void next();            
	void next_url(); 
	void next_tags();
	void quit(); 
	void get();
	void get_url();
	void add_picture(Picture_data *pic);
	void next_picture();
	void previous_picture();
	void save_pictures_into_file();
	void load_pictures_from_file();
	void save_tags();
	void search_tags();
};

//------------------------------------------------------------------------------

#endif // SIMPLE_WINDOW_GUARD