#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define GTK_ENABLE_BROKEN

// Global Variables
extern char current_number[50];
extern char current_operator;
extern GtkWidget *label, *left_label;
extern char label_text[50];

// Functions
void create_button(GtkWidget *grid, const char *label, int value, int row, int col);
void print_number(GtkWidget *widget, gpointer data);
void activate(GtkApplication *app, gpointer user_data);

double perform_calculation(double num1, double num2, char op);
void set_label_markup(GtkWidget *label, const char *text);
void update_display();
void update_operator_display();
void append_number(const char *number);
void handle_operator(char new_operator);

#endif