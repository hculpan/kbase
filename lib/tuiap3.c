#include <conio.h>
#include <stdlib.h>
#include <apple2enh.h>
#include <tuilibap.h>
#include <stdio.h>

void x1numbox(void *ptr) {
tgui_Window *win;

   win=ptr;
   process_numbox(win, get_obj(win,1));

}

void y1numbox(void *ptr) {
tgui_Window *win;

   win=ptr;
   process_numbox(win, get_obj(win,3));

}

void quit_btn(void *ptr){

tgui_Window *win;


    win =ptr;

   win->quitflag=1;

 }

void render_btn(void *ptr){

tgui_Window *win;
tgui_Window *tgw;
int x1,y1,x2,y2;


    win = ptr;

        x1 = atoi(get_objdata(win,1));
		y1 = atoi(get_objdata(win,3));
	    x2 = atoi(get_objdata(win,5));
		y2 = atoi(get_objdata(win,7));

        tgw=newwindow( (unsigned char) x1, (unsigned char)y1,
                       (unsigned char)x2,(unsigned char)y2,
		               COLOR_BLACK, 0, get_objdata(win, 9) );


        //tgw=newwindow(10,4,69,13,0," TUI APPLE TEST \0");

	    newobject(0,1,0,1,1,0,"press enter\0","\0", label, tgw,NULL);
	    showallobjects(tgw);



	    cgetc();
	    closewindow(tgw);
    }




void main() {

tgui_Window *tgw3;
int menu;


    videomode(1);
    clrscr();


	tgw3=newwindow(0,0,79,23,COLOR_BLACK, 1," TUI APPLE TEST \0");

	newobject(1,1,0, 1,0,0,"X1:\0","\0", label, tgw3, NULL); //0
	newobject(5,1,2,75,0,0,"\0","10\0", numbox, tgw3,NULL); //1
    newobject(1,2,0, 1,0,0,"Y1:\0","\0", label, tgw3,NULL);  //2
	newobject(5,2,2,20,0,0,"\0", "5\0",numbox, tgw3,NULL);  //3
	newobject(1,3,0, 1,0,0,"X2:\0","\0", label, tgw3,NULL);             //4
	newobject(5,3,2,79,0,0,"\0", "30\0",numbox, tgw3,NULL);             //5
	newobject(1,4,0, 1,0,0,"Y2:\0","\0", label, tgw3,NULL);             //6
	newobject(5,4,2,23,0,4,"\0", "15\0",numbox, tgw3,NULL);             //7
	newobject(1,6,0, 1,0,0,"title:\0","\0", label, tgw3,NULL);          //8
	newobject(7,6,25,1,0,0,"\0", " TEST \0",simpletext, tgw3,NULL); //9



	newobject( 6,12,6,1,0,0,"render\0", "\0",button, tgw3, render_btn);
	newobject(16,12,6,1,0,0,"quit\0",   "\0",button, tgw3, quit_btn);


	showallobjects(tgw3);
	addmenu(tgw3, "File\0", NULL);
	addmenu(tgw3, "Settings\0", NULL);


	addmenuitem(tgw3, 1, "X1\0", x1numbox);
	addmenuitem(tgw3, 1, "Y1\0", y1numbox);
	addmenu(tgw3, "Render\0", render_btn);

	addmenu(tgw3, "Quit\0", NULL);

    showmenu(tgw3);




do {
      tgw3->quitflag = 0;

      menu = processmenu(tgw3);

	  if (menu==10) processobj(tgw3, tgw3->firstobj->next);

	} while (menu != 40);


	closewindow(tgw3);


}
