#include "SystemMonitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <ncurses.h>
#include <string>
#include <locale.h>

using namespace std;

void drawBar (double rate, int row, int col, int max){
    mvprintw(row, col,  "[");
    int fill=max*rate/100;

    for (int i=0; i<max; i++){
        if (i<fill){
            printw("#");
        } else{
            printw("-");
        }
    }
    printw("]   ");
    printw(" %.1f%%",rate);
}

void dashboard(SystemMonitor& monitor){
    clear();

    double cpuRate=monitor.getCpuUsage();
    double memoryRate=100*monitor.getUsedGB()/monitor.getTotalGB();
    double temp=monitor.getTempC();

    mvprintw(0, 0,  "===========================================");
    mvprintw(1, 0,  "    Pi System Monitor                      ");
    mvprintw(2, 0,  "===========================================");

    mvprintw(3, 0,  "  CPU   ");
    drawBar(cpuRate, 3, 10, 20);

    mvprintw(4, 0,  "  Memory   ");
    drawBar(memoryRate, 4, 10, 20);

    mvprintw(5, 0,  "  Temp   ");
    mvprintw(5, 10,  "%.1f C", temp);
    mvprintw(6, 0,  "===========================================");
    
    mvprintw(8, 0, "Press 'q' to quit");

    refresh();  
}

int main() {
    SystemMonitor monitor;

    setlocale(LC_ALL, "");  
    initscr();   
    noecho();    
    cbreak();  
    nodelay(stdscr, TRUE); 
    curs_set(0); 

    while (true) {
        monitor.updateAll();
        dashboard(monitor);

        this_thread::sleep_for(chrono::seconds(1));

        if (getch() == 'q') break;
    }

    endwin();  
    return 0;
}
