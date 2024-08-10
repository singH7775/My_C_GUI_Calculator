#include "calculator.h"

// Global variables
char current_number[50] = "";
char current_operator = '\0';
GtkWidget *label, *left_label;
char label_text[50];

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.Calculator", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

// Main operation functions
void print_number(GtkWidget *widget, gpointer data) {
  int number = GPOINTER_TO_INT(data);

  switch(number) {
    case 100:
      if (strlen(current_number) > 0) {
        if (current_number[0] == '-') {
          memmove(current_number, current_number + 1, strlen(current_number));
        } else {
          memmove(current_number + 1, current_number, strlen(current_number) + 1);
          current_number[0] = '-';
        }
        update_display();
      } 
      break;
    case 101:
      append_number(".");
      break;
    case 102: case 103: case 104: case 105: case 106: {
      char new_operator = (number == 102) ? '+' :
                          (number == 103) ? '-' :
                          (number == 104) ? 'x' :
                          (number == 105) ? '/' : '%';
      handle_operator(new_operator);
      break;
    }
    case 107:
      if (strlen(current_number) > 0) {
        current_number[strlen(current_number) - 1] = '\0';
        update_display();
      }
      break;
    case 108:
      strcpy(current_number, "");
      set_label_markup(left_label, "");
      current_operator = '\0';
      update_display();
      break;
    case 109:
      if (current_operator != '\0') {
        double num1 = atof(gtk_label_get_text(GTK_LABEL(left_label)));
        double num2 = atof(current_number);

        if (current_operator == '/' && num2 == 0) {
          snprintf(label_text, sizeof(label_text), "ERROR");
          set_label_markup(left_label, label_text);
          current_operator = '\0';
          strcpy(current_number, "");
          update_display();
          return;
        }

        double result = perform_calculation(num1, num2, current_operator);
        snprintf(current_number, sizeof(current_number), "%g", result);
        current_operator = '\0';
        set_label_markup(left_label, current_number);
        strcpy(current_number, "");
        update_display();
      }
      break;
    default:
      char buffer[2];
      snprintf(buffer, sizeof(buffer), "%d", number);
      append_number(buffer);
      break;
  } 
}

void handle_operator(char new_operator) {
    const char *left_text = gtk_label_get_text(GTK_LABEL(left_label)); // Return first operand after operator
    if (current_operator != '\0' && strlen(current_number) > 0) {
        double num1 = atof(left_text);
        double num2 = atof(current_number);

        if(current_operator == '/' && num2 == 0) {
            snprintf(label_text, sizeof(label_text), "ERROR");
            set_label_markup(left_label, label_text);
            current_operator = '\0';
            strcpy(current_number, "");
            update_display();
            return;
        }

        double result = perform_calculation(num1, num2, current_operator);
        snprintf(label_text, sizeof(label_text), "%g", result);
        set_label_markup(left_label, label_text);
        strcpy(current_number, "");
        current_operator = new_operator;
        update_operator_display();
        update_display();
    } else if (strlen(current_number) > 0) {
        snprintf(label_text, sizeof(label_text), "%s %c", current_number, new_operator);
        set_label_markup(left_label, label_text);
        strcpy(current_number, "");
    } else {
        const char *last_operator = strrchr(left_text, ' ');
        if(last_operator != NULL) {
            char *updated_text = g_strdup(left_text);
            updated_text[last_operator - left_text + 1] = new_operator;
            set_label_markup(left_label, updated_text);
            g_free(updated_text);
        } else {
        snprintf(label_text, sizeof(label_text), "%s %c", left_text, new_operator);
        set_label_markup(left_label, label_text);
        }
    }
        current_operator = new_operator;
        set_label_markup(label, current_number);
}

double perform_calculation(double num1, double num2, char op) {
  switch(op) {
    case '+' :
      return num1 + num2;
    case '-' :
      return num1 - num2;
    case 'x' :
      return num1 * num2;
    case '/' :
      if (num2 != 0)
        return num1 / num2;
      return 0;
    case '%' : 
      return fmod(num1, num2);
    default :
      return 0;
  }
}


// Functions to update labels and currentnumber
void set_label_markup(GtkWidget *label, const char *text) {
  char markup[50];
  snprintf(markup, sizeof(markup), "<span font='24'>%s</span>", text);
  gtk_label_set_markup(GTK_LABEL(label), markup);
}

void update_display() {
    set_label_markup(label, current_number);
}

void update_operator_display() {
    char display[50];
    snprintf(display, sizeof(display), "%s %c", gtk_label_get_text(GTK_LABEL(left_label)), current_operator);
    set_label_markup(left_label, display);
}

void append_number(const char *number) {
    if (strlen(current_number) < sizeof(current_number) - 1) {
        strcat(current_number, number);
        update_display();
    }
}


// Creation of window application with its properties
void create_button(GtkWidget *grid, const char *label, int value, int row, int col) {
  GtkWidget *button = gtk_button_new_with_label(label);
  gtk_widget_set_size_request(button, 80, 35);
  gtk_widget_set_hexpand(button, TRUE);
  gtk_widget_set_vexpand(button, TRUE);
  g_signal_connect(button, "clicked", G_CALLBACK(print_number), GINT_TO_POINTER(value));
  gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
}

void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window, *box, *grid, *label_box;

  // Main window
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Calculator");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_valign(box, GTK_ALIGN_END);
  gtk_widget_set_vexpand(box, TRUE);
  gtk_window_set_child(GTK_WINDOW(window), box);
 
  label_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_hexpand(label_box, TRUE);
  gtk_box_append(GTK_BOX(box), label_box);

  // Holding the operand
  left_label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(left_label), "<span font='24'></span>");
  gtk_label_set_xalign(GTK_LABEL(left_label), 0.0);
  gtk_widget_set_hexpand(left_label, TRUE);
  gtk_box_append(GTK_BOX(label_box), left_label);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), "<span font='24'></span>");
  gtk_label_set_xalign(GTK_LABEL(label), 1.0);
  gtk_widget_set_hexpand(label, TRUE);
  gtk_box_append(GTK_BOX(label_box), label);

  grid = gtk_grid_new();
  gtk_widget_set_vexpand(grid, TRUE);
  gtk_widget_set_hexpand(grid, TRUE);
  gtk_box_append(GTK_BOX(box), grid);

  // creating all buttons
  create_button(grid, "1", 1, 0, 0);
  create_button(grid, "2", 2, 0, 1);
  create_button(grid, "3", 3, 0, 2);
  create_button(grid, "4", 4, 1, 0);
  create_button(grid, "5", 5, 1, 1);
  create_button(grid, "6", 6, 1, 2);
  create_button(grid, "7", 7, 2, 0);
  create_button(grid, "8", 8, 2, 1);
  create_button(grid, "9", 9, 2, 2);
  create_button(grid, "0", 0, 3, 1);
  create_button(grid, "+/-", 100, 3, 0);
  create_button(grid, ".", 101, 3, 2);
  create_button(grid, "+", 102, 0, 3);
  create_button(grid, "-", 103, 1, 3);
  create_button(grid, "x", 104, 2, 3);
  create_button(grid, "/", 105, 3, 3);
  create_button(grid, "%", 106, 0, 4);
  create_button(grid, "⌫", 107, 1, 4);
  create_button(grid, "C", 108, 2, 4);
  create_button(grid, "=", 109, 3, 4);

  gtk_window_present(GTK_WINDOW(window));
}