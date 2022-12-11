// Include statements
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "phi_interfaces.h"
#include "phi_prompt.h"
#include "phi_big_font.h"
#include "defs.h"

//End of include statements

//define statements
#define lcd_rows 4
#define lcd_columns 20


//
// Menu texts
PROGMEM prog_char top_menu_item00[]="Collect data";
PROGMEM prog_char top_menu_item01[]="Upload to PC";
PROGMEM prog_char top_menu_item02[]="Set Menu Style";
PROGMEM prog_char top_menu_item03[]="File management";
PROGMEM prog_char top_menu_item04[]="Show credit See who spent so much time making it happen!";
PROGMEM const char *top_menu_items[] = {top_menu_item00, top_menu_item01, top_menu_item02, top_menu_item03, top_menu_item04};

PROGMEM prog_char sub_menu_1_item00[]="Load file";
PROGMEM prog_char sub_menu_1_item01[]="Save file";
PROGMEM prog_char sub_menu_1_item02[]="Delete file";
PROGMEM prog_char sub_menu_1_item03[]="Back to main menu";
PROGMEM const char *sub_menu_1_items[] = {sub_menu_1_item00, sub_menu_1_item01, sub_menu_1_item02, sub_menu_1_item03};

PROGMEM prog_char menu_style00[]="Arrow/dot indicator on";
PROGMEM prog_char menu_style01[]="Index1 on-excludes index2";
PROGMEM prog_char menu_style02[]="Index2 on-excludes index1";
PROGMEM prog_char menu_style03[]="Autoscroll long items on";
PROGMEM prog_char menu_style04[]="Flashing cursor on";
PROGMEM prog_char menu_style05[]="Center on item on";
PROGMEM prog_char menu_style06[]="Scroll bar to the right on";
PROGMEM const char *menu_styles[] = {menu_style00, menu_style01, menu_style02, menu_style03, menu_style04, menu_style05, menu_style06};
//End of definitions


//create global objects
LiquidCrystal_I2C lcd(0x27, 20, 4);


//end of global objects

//Create global varibles
char mapping[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
byte pins[]={PB9, PC13, PC14, PC15, PA0, PA2, PA3, PA4};
phi_matrix_keypads my_btns(mapping, pins, 4, 4);
phi_serial_keypads debug_keypad(&Serial,115200);
char up_keys[]={'2'}; ///< All keys that act as the up key are listed here.
char down_keys[]={'8'}; ///< All keys that act as the down key are listed here.
char left_keys[]={'4'}; ///< All keys that act as the left key are listed here.
char right_keys[]={'6'}; ///< All keys that act as the right key are listed here.
char enter_keys[]={'5','D'}; ///< All keys that act as the enter key are listed here.
char escape_keys[]={'0','C'}; ///< All keys that act as the escape key are listed here.
char * function_keys[]={up_keys,down_keys,left_keys,right_keys,enter_keys,escape_keys}; ///< All function key names are gathered here fhr phi_prompt.
multiple_button_input * keypads[]={&my_btns,&debug_keypad,0};
int global_style=109;
//end of global variables
PROGMEM prog_char msg_00[]="Developed by:\nDr.Liu 05/23/11\nhttp://liudr.wordpress.com\nThis is just a mock-up of an actual data acquisition system with a 2-level menu.\nIt serves as a template for your actual project. It also shows off various features of the phi_prompt library.\nGo in \"Set Menu Style\" to find out some menu features you could be using in your project.\nPress Confirm to continue";

//menu functions
void show_credit()
{
  // Display credits
  phi_prompt_struct myLongMsg;

  lcd.clear();
  lcd.noBlink();
  myLongMsg.ptr.msg_P=msg_00; // Assign the address of the text string to the pointer.
  myLongMsg.low.i=0; // Default text starting position. 0 is highly recommended.
  myLongMsg.high.i=strlen_P(msg_00); // Position of the last character in the text string, which is size of the string - 1.
  myLongMsg.step.c_arr[0]=lcd_rows; // rows to auto fit entire screen
  myLongMsg.step.c_arr[1]=lcd_columns; // one col list
  myLongMsg.col=0; // Display the text area starting at column 0
  myLongMsg.row=0; // Display the text area starting at row 0
  myLongMsg.option=0; // Option 0, display classic message, option 1, display message with scroll bar on right.

  text_area_P(&myLongMsg);
}
void top_menu_function_5() //Replace this with the actual function of menu item #2
{
  show_credit();
}

void sub_menu_1_function_1()
{
  lcd.clear();
  lcd.print("Loading file...");
  lcd.setCursor(0,1);
  lcd.print("-Your code here-");
  wait_on_escape(4000);
}

void sub_menu_1_function_2()
{
  lcd.clear();
  lcd.print("Saving file....");
  lcd.setCursor(0,1);
  lcd.print("-Your code here-");
  wait_on_escape(4000);
}

void sub_menu_1_function_3()
{
  lcd.clear();
  lcd.print("Deleting file..");
  lcd.setCursor(0,1);
  lcd.print("-Your code here-");
  wait_on_escape(4000);
}

void top_menu_function_1() //Replace this with the actual function of menu item #1
{
  lcd.clear();
  lcd.print("Collecting data.");
  lcd.setCursor(0,1);
  lcd.print("-Your code here-");
  wait_on_escape(4000);
}

void top_menu_function_2() //Replace this with the actual function of menu item #2
{
  lcd.clear();
  lcd.print("Sending data....");
  lcd.setCursor(0,1);
  lcd.print("-Your code here-");
  wait_on_escape(4000);
}

void top_menu_function_3(phi_prompt_struct * para) //Settings
{
  char buffer[32];
  byte opt=global_style, yn;
  
  lcd.clear();
  sprintf(buffer, "%s%d","Current style:", global_style);
  lcd.print(buffer);
  wait_on_escape(2000);
  for (byte i=0;i<7;i++)
  {
    lcd.clear();
    strcpy_P(buffer,(char*)pgm_read_word(menu_styles+i));
    yn=yn_dialog(buffer);
    bitWrite(opt,i,yn);
  }

  lcd.clear();
  sprintf(buffer, "%s%d","New style:", global_style=opt);
  lcd.print(buffer);
  wait_on_escape(2000);
  lcd.clear();
}


void sub_menu_1() // This is the sub_menu_1
{
  int menu_pointer_1=0;
  phi_prompt_struct myMenu; // This structure stores the sub menu.

// Initialize the top menu
  myMenu.ptr.list=(char**)&sub_menu_1_items; // Assign the list to the pointer
  myMenu.low.i=0; // Default item highlighted on the list
  myMenu.high.i=3; // Last item of the list is size of the list - 1.
  myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.
  myMenu.step.c_arr[0]=lcd_rows-1; // rows to auto fit entire screen
  myMenu.step.c_arr[1]=1; // one col list
  myMenu.step.c_arr[2]=0; // y for additional feature such as an index
  myMenu.step.c_arr[3]=lcd_columns-4; // x for additional feature such as an index
  myMenu.col=0; // Display prompt at column 0
  myMenu.row=1; // Display prompt at row 1
  myMenu.option=global_style;

  while(1)
  {
    lcd.clear();  // Refresh menu if a button has been pushed
    center_text("File Menu");

    myMenu.option=global_style; // This makes sure the change of menu style is updated if there is a menu style option in this level of menu.
    myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.


    select_list(&myMenu);
    menu_pointer_1=myMenu.low.i;
    switch (menu_pointer_1)
    {
      case 0:
      sub_menu_1_function_1();
      break;
      case 1:
      sub_menu_1_function_2();
      break;
      
      case 2:
      sub_menu_1_function_3();
      break;
      
      case 3: // This option returns to previous level.
      return; // This returns to previous menu level. Only sub menus should have this unless the top level menu also returns.
      break;
  
      default:
      break;
    }
  }
}

void top_menu()
{
  int menu_pointer_1=0; // This stores the menu choice the user made.
  phi_prompt_struct myMenu; // This structure stores the main menu.

// Initialize the top menu
  myMenu.ptr.list=(char**)&top_menu_items; // Assign the list to the pointer
  myMenu.low.i=0; // Default item highlighted on the list
  myMenu.high.i=4; // Last item of the list is size of the list - 1.
  myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.
  myMenu.step.c_arr[0]=lcd_rows-1; // rows to auto fit entire screen
  myMenu.step.c_arr[1]=1; // one col list
  myMenu.step.c_arr[2]=0; // y for additional feature such as an index
  myMenu.step.c_arr[3]=lcd_columns-4-((global_style&phi_prompt_index_list)!=0); // x for additional feature such as an index
  myMenu.col=0; // Display menu at column 0
  myMenu.row=1; // Display menu at row 1
  myMenu.option=global_style; // Option 0, display classic list, option 1, display 2X2 list, option 2, display list with index, option 3, display list with index2.
  
  while(1) // This loops every time a menu item is selected.
  {
    lcd.clear();  // Refresh menu if a button has been pushed
    center_text("Top Menu");

    myMenu.option=global_style; // This makes sure the change of menu style is updated if there is a menu style option in this level of menu.
    myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // This makes sure the change of menu style is updated if there is a menu style option in this level of menu. Auto fit the size of the list to the screen. Length in characters of the longest list item.
    myMenu.step.c_arr[3]=lcd_columns-4-((global_style&phi_prompt_index_list)!=0); // This makes sure the change of menu style is updated if there is a menu style option in this level of menu. x for additional feature such as an index
    select_list(&myMenu); // Use the select_list to ask the user to select an item of the list, that is a menu item from your menu.
    menu_pointer_1=myMenu.low.i; // Get the selected item number and store it in the menu pointer.
    switch (menu_pointer_1) // See which menu item is selected and execute that correspond function
    {
      case 0:
      top_menu_function_1();
      break;
      case 1:
      top_menu_function_2();
      break;
      
      case 2:
      top_menu_function_3(&myMenu); // This is the setting function that changes how menu is rendered
      break;
      
      case 3:
      sub_menu_1(); // This is actually the sub menu.
      break;
  
      case 4:
      top_menu_function_5(); // If this were a sub level menu, this last one should return to previous level by using "return".
      break;
  
      default:
      break;
    }

  }
}

// Menu functions go here. The functions are called when their menu items are selected. They are called only once so if you want to do something repeatedly, make sure you have a while loop.







//end of function protoypes
void setup(){
    Wire.begin();
    lcd.init();
    pinMode(LED_BUILTIN,OUTPUT);
    init_phi_prompt(&lcd,keypads,function_keys, lcd_columns, lcd_rows, '~');

}

void loop(){
     top_menu();
}

